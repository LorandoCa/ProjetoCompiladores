#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ast1.h"
#include "codegen.h"

struct string_const {
    char *token;
    char *label;
    char *llvm_data;
    int len;
    struct string_const *next;
};

struct var_binding {
    char *name;
    char *ptr;
    sem_type type;
    int is_global;
    struct var_binding *next;
};

struct method_ctx {
    sem_type return_type;
    struct var_binding *locals;
    int temp_counter;
    int label_counter;
    int dead_counter;
    const char *current_label;
    int terminated;
};

struct string_const *string_pool = NULL;
struct var_binding *global_bindings = NULL;
struct node *entry_method = NULL;
int string_counter = 0;

static struct node *nth_child(struct node *node, int idx) {
    struct node_list *cur = node ? node->children : NULL;
    int i;
    for (i = 0; cur != NULL && i < idx; i++) {
        cur = cur->next;
    }
    return cur ? cur->node : NULL;
}

static char *xstrdup(const char *s) {
    size_t len;
    char *copy;
    if (s == NULL) {
        return NULL;
    }
    len = strlen(s);
    copy = (char *)malloc(len + 1);
    memcpy(copy, s, len + 1);
    return copy;
}

static char *str_printf(const char *fmt, ...) {
    va_list args;
    va_list copy;
    int needed;
    char *buffer;

    va_start(args, fmt);
    va_copy(copy, args);
    needed = vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);

    buffer = (char *)malloc((size_t)needed + 1);
    vsnprintf(buffer, (size_t)needed + 1, fmt, args);
    va_end(args);
    return buffer;
}

static const char *llvm_type(sem_type type) {
    switch (type) {
        case TYPE_BOOL: return "i1";
        case TYPE_INT: return "i32";
        case TYPE_DOUBLE: return "double";
        case TYPE_VOID: return "void";
        case TYPE_STRING: return "i8*";
        case TYPE_STRING_ARRAY: return "%struct.StringArray";
        default: return "i32";
    }
}

static char *sanitize_number(const char *token) {
    size_t i, j, len;
    char *out;
    len = strlen(token);
    out = (char *)malloc(len + 1);
    j = 0;
    for (i = 0; i < len; i++) {
        if (token[i] != '_') {
            out[j++] = token[i];
        }
    }
    out[j] = '\0';
    return out;
}

static int append_llvm_byte(char *dst, int pos, unsigned char byte) {
    if (byte >= 32 && byte <= 126 && byte != '\\' && byte != '"') {
        dst[pos++] = (char)byte;
    } else {
        sprintf(dst + pos, "\\%02X", byte);
        pos += 3;
    }
    return pos;
}

static void decode_string_token(const char *token, char **llvm_data, int *len) {
    size_t i, src_len;
    int pos = 0;
    int count = 0;
    char *buf;

    src_len = strlen(token);
    buf = (char *)malloc(src_len * 4 + 8);

    for (i = 1; i + 1 < src_len; i++) {
        unsigned char ch = (unsigned char)token[i];
        if (ch == '\\' && i + 1 < src_len - 1) {
            i++;
            switch (token[i]) {
                case 'n': ch = '\n'; break;
                case 't': ch = '\t'; break;
                case 'r': ch = '\r'; break;
                case 'f': ch = '\f'; break;
                case '\\': ch = '\\'; break;
                case '"': ch = '"'; break;
                default: ch = (unsigned char)token[i]; break;
            }
        }
        pos = append_llvm_byte(buf, pos, ch);
        count++;
    }

    pos = append_llvm_byte(buf, pos, 0);
    count++;
    buf[pos] = '\0';
    *llvm_data = buf;
    *len = count;
}

static struct string_const *find_string_const(const char *token) {
    struct string_const *cur = string_pool;
    while (cur != NULL) {
        if (strcmp(cur->token, token) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

static struct string_const *intern_string_const(const char *token) {
    struct string_const *found;
    struct string_const *item;
    int len = 0;
    char *llvm_data = NULL;
    struct string_const *tail;

    found = find_string_const(token);
    if (found != NULL) {
        return found;
    }

    decode_string_token(token, &llvm_data, &len);
    item = (struct string_const *)calloc(1, sizeof(struct string_const));
    item->token = xstrdup(token);
    item->label = str_printf("@.str.%d", string_counter++);
    item->llvm_data = llvm_data;
    item->len = len;

    if (string_pool == NULL) {
        string_pool = item;
    } else {
        tail = string_pool;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = item;
    }

    return item;
}

static void collect_strings(struct node *node) {
    struct node_list *child;
    if (node == NULL) {
        return;
    }
    if (node->category == StrLit && node->token != NULL) {
        intern_string_const(node->token);
    }
    child = node->children;
    while (child != NULL) {
        collect_strings(child->node);
        child = child->next;
    }
}

static void append_binding(struct var_binding **head, const char *name, const char *ptr, sem_type type, int is_global) {
    struct var_binding *item = (struct var_binding *)calloc(1, sizeof(struct var_binding));
    item->name = xstrdup(name);
    item->ptr = xstrdup(ptr);
    item->type = type;
    item->is_global = is_global;
    item->next = *head;
    *head = item;
}

static struct var_binding *lookup_binding(struct method_ctx *ctx, const char *name) {
    struct var_binding *cur;
    if (ctx != NULL) {
        for (cur = ctx->locals; cur != NULL; cur = cur->next) {
            if (strcmp(cur->name, name) == 0) {
                return cur;
            }
        }
    }
    for (cur = global_bindings; cur != NULL; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) {
            return cur;
        }
    }
    return NULL;
}

static char *new_temp(struct method_ctx *ctx) {
    return str_printf("%%t%d", ctx->temp_counter++);
}

static char *new_label(struct method_ctx *ctx, const char *prefix) {
    return str_printf("%s%d", prefix, ctx->label_counter++);
}

static void start_block(struct method_ctx *ctx, const char *label) {
    printf("%s:\n", label);
    ctx->current_label = label;
    ctx->terminated = 0;
}

static void ensure_live_block(struct method_ctx *ctx) {
    char *label;
    if (!ctx->terminated) {
        return;
    }
    label = str_printf("dead%d", ctx->dead_counter++);
    start_block(ctx, label);
}

static char *cast_value(struct method_ctx *ctx, char *value, sem_type from, sem_type to) {
    char *tmp;
    if (from == to) {
        return value;
    }
    if (from == TYPE_INT && to == TYPE_DOUBLE) {
        tmp = new_temp(ctx);
        printf("  %s = sitofp i32 %s to double\n", tmp, value);
        return tmp;
    }
    return value;
}

static char *default_value(sem_type type) {
    switch (type) {
        case TYPE_BOOL: return xstrdup("0");
        case TYPE_INT: return xstrdup("0");
        case TYPE_DOUBLE: return xstrdup("0.0000000000000000e+00");
        case TYPE_STRING_ARRAY: return xstrdup("zeroinitializer");
        default: return xstrdup("0");
    }
}

struct cg_value {
    sem_type type;
    char *repr;
};

static struct cg_value emit_expr(struct method_ctx *ctx, struct node *node);

static char *emit_load(struct method_ctx *ctx, struct var_binding *binding) {
    char *tmp = new_temp(ctx);
    printf("  %s = load %s, %s* %s\n", tmp, llvm_type(binding->type), llvm_type(binding->type), binding->ptr);
    return tmp;
}

static char *mangle_type_name(sem_type type) {
    switch (type) {
        case TYPE_INT: return xstrdup("i");
        case TYPE_DOUBLE: return xstrdup("d");
        case TYPE_BOOL: return xstrdup("b");
        case TYPE_STRING_ARRAY: return xstrdup("sa");
        case TYPE_VOID: return xstrdup("v");
        default: return xstrdup("u");
    }
}

static char *mangle_from_header(struct node *header) {
    struct node *id = nth_child(header, 1);
    struct node *params = nth_child(header, 2);
    char *name = xstrdup(id->token);
    struct node_list *cur;
    char *piece;
    char *next;

    if (params == NULL || params->children == NULL || params->children->node == NULL) {
        next = str_printf("%s$v", name);
        free(name);
        return next;
    }

    cur = params->children;
    while (cur != NULL && cur->node != NULL) {
        piece = mangle_type_name(category_to_type(nth_child(cur->node, 0)->category));
        next = str_printf("%s$%s", name, piece);
        free(piece);
        free(name);
        name = next;
        cur = cur->next;
    }
    return name;
}

static char *mangle_from_signature(const char *base, const char *signature) {
    const char *p = signature;
    char token[32];
    int idx = 0;
    char *name = xstrdup(base);
    char *next;

    if (signature == NULL || strcmp(signature, "()") == 0) {
        next = str_printf("%s$v", name);
        free(name);
        return next;
    }

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            idx = 0;
            while (*p != '\0' && *p != ',' && *p != ')') {
                if (!isspace((unsigned char)*p)) {
                    token[idx++] = *p;
                }
                p++;
            }
            token[idx] = '\0';
            if (strcmp(token, "int") == 0) {
                next = str_printf("%s$i", name);
            } else if (strcmp(token, "double") == 0) {
                next = str_printf("%s$d", name);
            } else if (strcmp(token, "boolean") == 0) {
                next = str_printf("%s$b", name);
            } else if (strcmp(token, "String[]") == 0) {
                next = str_printf("%s$sa", name);
            } else {
                next = str_printf("%s$u", name);
            }
            free(name);
            name = next;
        } else {
            p++;
        }
    }
    return name;
}

static sem_type signature_type_at(const char *signature, int index) {
    const char *p = signature;
    char token[32];
    int idx = 0;
    int current = 0;

    if (signature == NULL || strcmp(signature, "()") == 0) {
        return TYPE_UNDEF;
    }

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            idx = 0;
            while (*p != '\0' && *p != ',' && *p != ')') {
                if (!isspace((unsigned char)*p)) {
                    token[idx++] = *p;
                }
                p++;
            }
            token[idx] = '\0';
            if (current == index) {
                if (strcmp(token, "int") == 0) return TYPE_INT;
                if (strcmp(token, "double") == 0) return TYPE_DOUBLE;
                if (strcmp(token, "boolean") == 0) return TYPE_BOOL;
                if (strcmp(token, "String[]") == 0) return TYPE_STRING_ARRAY;
                return TYPE_UNDEF;
            }
            current++;
        } else {
            p++;
        }
    }

    return TYPE_UNDEF;
}

static void emit_global_preamble(void) {
    struct string_const *cur;
    printf("%%struct.StringArray = type { i32, i8** }\n");
    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*)\n\n");
    printf("@.fmt.int = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
    printf("@.fmt.double = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("@.fmt.str = private unnamed_addr constant [3 x i8] c\"%%s\\00\"\n");
    printf("@.str.true = private unnamed_addr constant [5 x i8] c\"true\\00\"\n");
    printf("@.str.false = private unnamed_addr constant [6 x i8] c\"false\\00\"\n");

    cur = string_pool;
    while (cur != NULL) {
        printf("%s = private unnamed_addr constant [%d x i8] c\"%s\"\n",
               cur->label, cur->len, cur->llvm_data);
        cur = cur->next;
    }
    printf("\n");
}

static void collect_globals_and_entry(struct node *program) {
    struct node_list *cur = program ? program->children : NULL;
    cur = cur ? cur->next : NULL;
    while (cur != NULL) {
        struct node *decl = cur->node;
        if (decl != NULL && decl->category == FieldDecl) {
            struct node *type_node = nth_child(decl, 0);
            struct node *id_node = nth_child(decl, 1);
            sem_type type = category_to_type(type_node->category);
            printf("@%s = global %s %s\n", id_node->token, llvm_type(type), default_value(type));
            append_binding(&global_bindings, id_node->token, str_printf("@%s", id_node->token), type, 1);
        } else if (decl != NULL && decl->category == MethodDecl) {
            struct node *header = nth_child(decl, 0);
            struct node *id_node = nth_child(header, 1);
            struct node *params = nth_child(header, 2);
            if (id_node != NULL && strcmp(id_node->token, "main") == 0 &&
                params != NULL && params->children != NULL && params->children->next == NULL) {
                struct node *param = params->children->node;
                struct node *ptype = nth_child(param, 0);
                if (ptype != NULL && ptype->category == StringArray) {
                    entry_method = decl;
                }
            }
        }
        cur = cur->next;
    }
    if (global_bindings != NULL) {
        printf("\n");
    }
}

static struct cg_value emit_call(struct method_ctx *ctx, struct node *node) {
    struct node *id_node = nth_child(node, 0);
    struct node *args_node = nth_child(node, 1);
    struct node_list *cur;
    char *mangled = mangle_from_signature(id_node->token, id_node->args);
    char *arg_text = xstrdup("");
    char *new_text;
    int first = 1;
    int arg_index = 0;
    struct cg_value arg_val;
    sem_type result_type = node->type;
    sem_type expected_type;
    char *tmp;

    if (args_node != NULL) {
        cur = args_node->children;
        while (cur != NULL) {
            arg_val = emit_expr(ctx, cur->node);
            expected_type = signature_type_at(id_node->args, arg_index++);
            if (expected_type == TYPE_UNDEF) {
                expected_type = arg_val.type;
            }
            arg_val.repr = cast_value(ctx, arg_val.repr, arg_val.type, expected_type);
            new_text = str_printf("%s%s%s %s",
                                  arg_text,
                                  first ? "" : ", ",
                                  llvm_type(expected_type),
                                  arg_val.repr);
            free(arg_text);
            arg_text = new_text;
            first = 0;
            cur = cur->next;
        }
    }

    if (result_type == TYPE_VOID) {
        printf("  call void @%s(%s)\n", mangled, arg_text);
        tmp = NULL;
    } else {
        tmp = new_temp(ctx);
        printf("  %s = call %s @%s(%s)\n", tmp, llvm_type(result_type), mangled, arg_text);
    }

    free(arg_text);
    free(mangled);
    return (struct cg_value){ result_type, tmp };
}

static struct cg_value emit_expr(struct method_ctx *ctx, struct node *node) {
    struct cg_value left, right;
    struct node *child0, *child1;
    struct var_binding *binding;
    char *tmp, *tmp2;
    struct string_const *strc;
    char *clean;
    char *end_label;
    char *rhs_label;
    const char *lhs_label;
    sem_type left_type;
    sem_type right_type;

    switch (node->category) {
        case Natural:
            clean = sanitize_number(node->token);
            return (struct cg_value){ TYPE_INT, clean };

        case Decimal:
            clean = sanitize_number(node->token);
            return (struct cg_value){ TYPE_DOUBLE, str_printf("%.16e", strtod(clean, NULL)) };

        case BoolLit:
            return (struct cg_value){ TYPE_BOOL, xstrdup(strcmp(node->token, "true") == 0 ? "1" : "0") };

        case StrLit:
            strc = intern_string_const(node->token);
            return (struct cg_value){ TYPE_STRING, str_printf("getelementptr inbounds ([%d x i8], [%d x i8]* %s, i32 0, i32 0)",
                    strc->len, strc->len, strc->label) };

        case Identifier:
            binding = lookup_binding(ctx, node->token);
            return (struct cg_value){ binding->type, emit_load(ctx, binding) };

        case Assign:
            child0 = nth_child(node, 0);
            child1 = nth_child(node, 1);
            binding = lookup_binding(ctx, child0->token);
            right = emit_expr(ctx, child1);
            right.repr = cast_value(ctx, right.repr, right.type, binding->type);
            printf("  store %s %s, %s* %s\n", llvm_type(binding->type), right.repr, llvm_type(binding->type), binding->ptr);
            return (struct cg_value){ binding->type, right.repr };

        case Call:
            return emit_call(ctx, node);

        case ParseArgs: {
            struct cg_value array_val = emit_expr(ctx, nth_child(node, 0));
            struct cg_value idx_val = emit_expr(ctx, nth_child(node, 1));
            char *arr_ptr = new_temp(ctx);
            char *elem_ptr = new_temp(ctx);
            char *str_ptr = new_temp(ctx);
            char *result = new_temp(ctx);
            printf("  %s = extractvalue %%struct.StringArray %s, 1\n", arr_ptr, array_val.repr);
            printf("  %s = getelementptr inbounds i8*, i8** %s, i32 %s\n", elem_ptr, arr_ptr, idx_val.repr);
            printf("  %s = load i8*, i8** %s\n", str_ptr, elem_ptr);
            printf("  %s = call i32 @atoi(i8* %s)\n", result, str_ptr);
            return (struct cg_value){ TYPE_INT, result };
        }

        case Length: {
            struct cg_value array_val = emit_expr(ctx, nth_child(node, 0));
            char *result = new_temp(ctx);
            printf("  %s = extractvalue %%struct.StringArray %s, 0\n", result, array_val.repr);
            return (struct cg_value){ TYPE_INT, result };
        }

        case Plus:
            return emit_expr(ctx, nth_child(node, 0));

        case Minus:
            left = emit_expr(ctx, nth_child(node, 0));
            tmp = new_temp(ctx);
            if (left.type == TYPE_DOUBLE) {
                printf("  %s = fsub double -0.0000000000000000e+00, %s\n", tmp, left.repr);
            } else {
                printf("  %s = sub i32 0, %s\n", tmp, left.repr);
            }
            return (struct cg_value){ left.type, tmp };

        case Not:
            left = emit_expr(ctx, nth_child(node, 0));
            tmp = new_temp(ctx);
            printf("  %s = xor i1 %s, true\n", tmp, left.repr);
            return (struct cg_value){ TYPE_BOOL, tmp };

        case And:
        case Or:
            lhs_label = ctx->current_label;
            left = emit_expr(ctx, nth_child(node, 0));
            rhs_label = new_label(ctx, node->category == And ? "and.rhs" : "or.rhs");
            end_label = new_label(ctx, node->category == And ? "and.end" : "or.end");
            if (node->category == And) {
                printf("  br i1 %s, label %%%s, label %%%s\n", left.repr, rhs_label, end_label);
            } else {
                printf("  br i1 %s, label %%%s, label %%%s\n", left.repr, end_label, rhs_label);
            }
            ctx->terminated = 1;
            start_block(ctx, rhs_label);
            right = emit_expr(ctx, nth_child(node, 1));
            printf("  br label %%%s\n", end_label);
            ctx->terminated = 1;
            start_block(ctx, end_label);
            tmp = new_temp(ctx);
            if (node->category == And) {
                printf("  %s = phi i1 [ 0, %%%s ], [ %s, %%%s ]\n", tmp, lhs_label, right.repr, rhs_label);
            } else {
                printf("  %s = phi i1 [ 1, %%%s ], [ %s, %%%s ]\n", tmp, lhs_label, right.repr, rhs_label);
            }
            return (struct cg_value){ TYPE_BOOL, tmp };

        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
        case Eq:
        case Ne:
        case Lt:
        case Le:
        case Gt:
        case Ge:
        case Xor:
        case Lshift:
        case Rshift:
            child0 = nth_child(node, 0);
            child1 = nth_child(node, 1);
            left = emit_expr(ctx, child0);
            right = emit_expr(ctx, child1);
            left_type = left.type;
            right_type = right.type;

            if (node->category == Add || node->category == Sub || node->category == Mul ||
                node->category == Div || node->category == Mod ||
                node->category == Eq || node->category == Ne || node->category == Lt ||
                node->category == Le || node->category == Gt || node->category == Ge) {
                if ((left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) &&
                    left_type != TYPE_BOOL && right_type != TYPE_BOOL) {
                    left.repr = cast_value(ctx, left.repr, left_type, TYPE_DOUBLE);
                    right.repr = cast_value(ctx, right.repr, right_type, TYPE_DOUBLE);
                    left_type = right_type = TYPE_DOUBLE;
                }
            }

            tmp = new_temp(ctx);

            if (node->category == Add) {
                if (left_type == TYPE_DOUBLE) printf("  %s = fadd double %s, %s\n", tmp, left.repr, right.repr);
                else printf("  %s = add i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ node->type, tmp };
            }
            if (node->category == Sub) {
                if (left_type == TYPE_DOUBLE) printf("  %s = fsub double %s, %s\n", tmp, left.repr, right.repr);
                else printf("  %s = sub i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ node->type, tmp };
            }
            if (node->category == Mul) {
                if (left_type == TYPE_DOUBLE) printf("  %s = fmul double %s, %s\n", tmp, left.repr, right.repr);
                else printf("  %s = mul i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ node->type, tmp };
            }
            if (node->category == Div) {
                if (left_type == TYPE_DOUBLE) printf("  %s = fdiv double %s, %s\n", tmp, left.repr, right.repr);
                else printf("  %s = sdiv i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ node->type, tmp };
            }
            if (node->category == Mod) {
                if (left_type == TYPE_DOUBLE) printf("  %s = frem double %s, %s\n", tmp, left.repr, right.repr);
                else printf("  %s = srem i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ node->type, tmp };
            }
            if (node->category == Xor) {
                printf("  %s = xor i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ TYPE_INT, tmp };
            }
            if (node->category == Lshift) {
                printf("  %s = shl i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ TYPE_INT, tmp };
            }
            if (node->category == Rshift) {
                printf("  %s = ashr i32 %s, %s\n", tmp, left.repr, right.repr);
                return (struct cg_value){ TYPE_INT, tmp };
            }

            if (left_type == TYPE_DOUBLE) {
                const char *op = "oeq";
                if (node->category == Ne) op = "one";
                else if (node->category == Lt) op = "olt";
                else if (node->category == Le) op = "ole";
                else if (node->category == Gt) op = "ogt";
                else if (node->category == Ge) op = "oge";
                printf("  %s = fcmp %s double %s, %s\n", tmp, op, left.repr, right.repr);
            } else {
                const char *op = "eq";
                if (node->category == Ne) op = "ne";
                else if (node->category == Lt) op = "slt";
                else if (node->category == Le) op = "sle";
                else if (node->category == Gt) op = "sgt";
                else if (node->category == Ge) op = "sge";
                printf("  %s = icmp %s %s %s, %s\n", tmp, op, llvm_type(left_type), left.repr, right.repr);
            }
            return (struct cg_value){ TYPE_BOOL, tmp };

        default:
            tmp2 = xstrdup("0");
            return (struct cg_value){ TYPE_INT, tmp2 };
    }
}

static void emit_stmt(struct method_ctx *ctx, struct node *node) {
    struct node_list *cur;
    struct cg_value cond;
    char *then_label;
    char *else_label;
    char *end_label;

    if (node == NULL) {
        return;
    }

    switch (node->category) {
        case Block:
            cur = node->children;
            while (cur != NULL) {
                ensure_live_block(ctx);
                emit_stmt(ctx, cur->node);
                cur = cur->next;
            }
            break;

        case If:
            cond = emit_expr(ctx, nth_child(node, 0));
            then_label = new_label(ctx, "if.then");
            else_label = new_label(ctx, "if.else");
            end_label = new_label(ctx, "if.end");
            printf("  br i1 %s, label %%%s, label %%%s\n", cond.repr, then_label, else_label);
            ctx->terminated = 1;
            start_block(ctx, then_label);
            emit_stmt(ctx, nth_child(node, 1));
            if (!ctx->terminated) {
                printf("  br label %%%s\n", end_label);
                ctx->terminated = 1;
            }
            start_block(ctx, else_label);
            emit_stmt(ctx, nth_child(node, 2));
            if (!ctx->terminated) {
                printf("  br label %%%s\n", end_label);
                ctx->terminated = 1;
            }
            start_block(ctx, end_label);
            break;

        case While: {
            char *cond_label = new_label(ctx, "while.cond");
            char *body_label = new_label(ctx, "while.body");
            char *endw_label = new_label(ctx, "while.end");
            printf("  br label %%%s\n", cond_label);
            ctx->terminated = 1;
            start_block(ctx, cond_label);
            cond = emit_expr(ctx, nth_child(node, 0));
            printf("  br i1 %s, label %%%s, label %%%s\n", cond.repr, body_label, endw_label);
            ctx->terminated = 1;
            start_block(ctx, body_label);
            emit_stmt(ctx, nth_child(node, 1));
            if (!ctx->terminated) {
                printf("  br label %%%s\n", cond_label);
                ctx->terminated = 1;
            }
            start_block(ctx, endw_label);
            break;
        }

        case Return:
            if (nth_child(node, 0) == NULL) {
                printf("  ret void\n");
            } else {
                struct cg_value value = emit_expr(ctx, nth_child(node, 0));
                value.repr = cast_value(ctx, value.repr, value.type, ctx->return_type);
                printf("  ret %s %s\n", llvm_type(ctx->return_type), value.repr);
            }
            ctx->terminated = 1;
            break;

        case Assign:
        case Call:
        case ParseArgs:
            (void)emit_expr(ctx, node);
            break;

        case Print: {
            struct node *expr = nth_child(node, 0);
            struct cg_value value = emit_expr(ctx, expr);
            if (value.type == TYPE_INT) {
                printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %s)\n", value.repr);
            } else if (value.type == TYPE_DOUBLE) {
                printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %s)\n", value.repr);
            } else if (value.type == TYPE_BOOL) {
                char *bool_ptr = new_temp(ctx);
                printf("  %s = select i1 %s, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.true, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.false, i32 0, i32 0)\n", bool_ptr, value.repr);
                printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* %s)\n", bool_ptr);
            } else if (expr->category == StrLit) {
                printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* %s)\n", value.repr);
            }
            break;
        }

        default:
            break;
    }
}

static void emit_allocas_for_method(struct method_ctx *ctx, struct node *header, struct node *body) {
    struct node *params = nth_child(header, 2);
    struct node_list *cur;
    int param_index = 0;

    if (params != NULL) {
        cur = params->children;
        while (cur != NULL && cur->node != NULL) {
            struct node *param = cur->node;
            struct node *type_node = nth_child(param, 0);
            struct node *id_node = nth_child(param, 1);
            sem_type type = category_to_type(type_node->category);
            char *ptr = str_printf("%%%s.addr", id_node->token);
            char *incoming = str_printf("%%p%d", param_index++);
            printf("  %s = alloca %s\n", ptr, llvm_type(type));
            printf("  store %s %s, %s* %s\n", llvm_type(type), incoming, llvm_type(type), ptr);
            append_binding(&ctx->locals, id_node->token, ptr, type, 0);
            cur = cur->next;
        }
    }

    cur = body ? body->children : NULL;
    while (cur != NULL) {
        if (cur->node != NULL && cur->node->category == VarDecl) {
            struct node *type_node = nth_child(cur->node, 0);
            struct node *id_node = nth_child(cur->node, 1);
            sem_type type = category_to_type(type_node->category);
            char *ptr = str_printf("%%%s", id_node->token);
            char *init = default_value(type);
            printf("  %s = alloca %s\n", ptr, llvm_type(type));
            printf("  store %s %s, %s* %s\n", llvm_type(type), init, llvm_type(type), ptr);
            append_binding(&ctx->locals, id_node->token, ptr, type, 0);
        }
        cur = cur->next;
    }
}

static void emit_method(struct node *decl) {
    struct node *header = nth_child(decl, 0);
    struct node *body = nth_child(decl, 1);
    struct node *ret_node = nth_child(header, 0);
    struct node *params = nth_child(header, 2);
    sem_type ret_type = category_to_type(ret_node->category);
    char *mangled = mangle_from_header(header);
    char *param_text = xstrdup("");
    char *next_text;
    struct node_list *cur;
    int param_index = 0;
    int first = 1;
    struct method_ctx ctx;

    if (params != NULL) {
        cur = params->children;
        while (cur != NULL && cur->node != NULL) {
            struct node *param = cur->node;
            sem_type type = category_to_type(nth_child(param, 0)->category);
            next_text = str_printf("%s%s%s %%p%d",
                                   param_text,
                                   first ? "" : ", ",
                                   llvm_type(type),
                                   param_index++);
            free(param_text);
            param_text = next_text;
            first = 0;
            cur = cur->next;
        }
    }

    printf("define %s @%s(%s) {\n", llvm_type(ret_type), mangled, param_text);
    memset(&ctx, 0, sizeof(ctx));
    ctx.return_type = ret_type;
    ctx.current_label = "entry";
    printf("entry:\n");
    emit_allocas_for_method(&ctx, header, body);

    cur = body ? body->children : NULL;
    while (cur != NULL) {
        if (cur->node != NULL && cur->node->category != VarDecl) {
            ensure_live_block(&ctx);
            emit_stmt(&ctx, cur->node);
        }
        cur = cur->next;
    }

    if (!ctx.terminated) {
        if (ret_type == TYPE_VOID) {
            printf("  ret void\n");
        } else if (ret_type == TYPE_DOUBLE) {
            printf("  ret double 0.0000000000000000e+00\n");
        } else if (ret_type == TYPE_BOOL) {
            printf("  ret i1 0\n");
        } else {
            printf("  ret i32 0\n");
        }
    }
    printf("}\n\n");

    free(param_text);
    free(mangled);
}

static void emit_main_wrapper(void) {
    struct node *header;
    char *callee;
    sem_type ret_type;

    if (entry_method == NULL) { // emite o main quando ele nao existe
        printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
        printf("entry:\n");
        printf("  ret i32 0\n");
        printf("}\n");
        return;
    }

    header = nth_child(entry_method, 0);
    callee = mangle_from_header(header);
    ret_type = category_to_type(nth_child(header, 0)->category);

    printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
    printf("entry:\n");
    printf("  %%arg.count = sub i32 %%argc, 1\n");
    printf("  %%arg.ptr = getelementptr inbounds i8*, i8** %%argv, i32 1\n");
    printf("  %%args.0 = insertvalue %%struct.StringArray zeroinitializer, i32 %%arg.count, 0\n");
    printf("  %%args.1 = insertvalue %%struct.StringArray %%args.0, i8** %%arg.ptr, 1\n");
    if (ret_type == TYPE_VOID) {
        printf("  call void @%s(%%struct.StringArray %%args.1)\n", callee);
        printf("  ret i32 0\n");
    } else if (ret_type == TYPE_INT) {
        printf("  %%entry.ret = call i32 @%s(%%struct.StringArray %%args.1)\n", callee);
        printf("  ret i32 %%entry.ret\n");
    } else if (ret_type == TYPE_BOOL) {
        printf("  %%entry.ret = call i1 @%s(%%struct.StringArray %%args.1)\n", callee);
        printf("  %%entry.ret.i32 = zext i1 %%entry.ret to i32\n");
        printf("  ret i32 %%entry.ret.i32\n");
    } else {
        printf("  call double @%s(%%struct.StringArray %%args.1)\n", callee);
        printf("  ret i32 0\n");
    }
    printf("}\n");

    free(callee);
}

void generate_llvm_ir(struct node *program) {
    struct node_list *cur;
    string_pool = NULL;
    global_bindings = NULL;
    entry_method = NULL;
    string_counter = 0;

    collect_strings(program);
    emit_global_preamble();
    collect_globals_and_entry(program);

    cur = program ? program->children : NULL;
    cur = cur ? cur->next : NULL;
    while (cur != NULL) {
        if (cur->node != NULL && cur->node->category == MethodDecl) {
            emit_method(cur->node);
        }
        cur = cur->next;
    }

    emit_main_wrapper();
}
