#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ast1.h"
#include "semantics.h"

int semantic_errors = 0;
extern int print_semantics;

struct symbol_list *listaGlobal;
struct symbol_list_stack *stack;
struct symbol_list_stack *functionsList;





const char *op_name(enum category c) {
    switch(c) {
        case Add: return "+";
        case Sub: return "-";
        case Mul: return "*";
        case Div: return "/";
        case Mod: return "%";
        case Assign: return "=";
        case Xor: return "^";
        case Eq: return "==";
        case Ne: return "!=";
        case Lshift: return "<<";
        case Rshift: return ">>";
        case Gt: return ">";
        case Lt: return "<";
        case Le: return "<=";
        case Ge: return ">=";
        case And: return "&&";
        case Or: return "||";
        default:  return "?";
    }
}


void fill_args_from_header(struct node *header, char *args) {
    struct node *params_node = nth_child(header, 2);
    args[0] = '\0';
    strcat(args, "(");
    int i = 0;
    if (params_node == NULL) { strcat(args, ")"); return; } 
    struct node_list *p = params_node->children;
    while (p != NULL && p->node != NULL) {
        struct node *ptype = nth_child(p->node, 0);
        if (i > 0) strcat(args, ",");
        strcat(args, type_name(category_to_type(ptype->category)));
        p = p->next;
        i++;
    }
    strcat(args, ")");
}


sem_type check_calls(struct node *call) {
    struct node *id_node   = call->children->node;
    struct node *args_node = nth_child(call, 1); // Args ou NULL
    char *call_id = id_node->token;

    sem_type result_type = TYPE_UNDEF;

    char *args= (char*)malloc(1024*sizeof(char));

    // 1. Recolhe tipos dos argumentos reais
    int n_args = 0;
    sem_type arg_types[128];
    char call_args[1024];
    call_args[0] = '\0';
    strcat(call_args, "(");
    if (args_node != NULL) {
        struct node_list *a = args_node->children;
        while (a != NULL) {
            arg_types[n_args++] = check_expression(a->node);
            //if(arg_types[n_args - 1] == TYPE_DOUBLE ) printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
            if (n_args > 1) strcat(call_args, ",");
            strcat(call_args, type_name(arg_types[n_args - 1]));
            a = a->next;
        }
    }
    strcat(call_args, ")");

    //printf("%s\n", call_args);
    
    
    // 2. Percorre TODA a tabela global à procura de métodos com este nome
    struct symbol_list *sym        = listaGlobal->next;
    struct symbol_list *exact      = NULL;
    struct symbol_list *compat     = NULL;
    int n_compat = 0;

    //if(sym->identifier == NULL) printf("aqui\n");
    //return 1;
    while (sym != NULL) {
        if (strcmp(sym->identifier, call_id) != 0) { sym = sym->next; continue; }


        // Acede aos parâmetros formais via MethodHeader → filho 2 = MethodParams
        struct node *header      = sym->node; // sym->node aponta para MethodHeader
        struct node *params_node = nth_child(header, 2);

        result_type = nth_child(header, 0) == NULL ? TYPE_UNDEF : nth_child(header, 0)->type;

        // Conta e recolhe tipos dos parâmetros formais
        int n_params = 0;
        sem_type param_types[128];
        if (params_node == NULL) { sym = sym->next; continue; }
        struct node_list *p = params_node->children;
        while (p != NULL && p->node != NULL) {
            struct node *ptype = nth_child(p->node, 0); // filho 0 de ParamDecl = tipo
            param_types[n_params++] = category_to_type(ptype->category);
            p = p->next;
        }


        // Número de parâmetros tem de coincidir
        if (n_params != n_args) { sym = sym->next; continue; }

        //printf("Printing id nos simbolos %s\n", sym->identifier);

        // Verifica match exacto (mesmo tipo em todas as posições)
        int is_exact = 1;
        for (int i = 0; i < n_params; i++) {
            if (param_types[i] != arg_types[i]) { is_exact = 0;  /*printf(" %d %d\n", param_types[i], arg_types[i] )*/; break;  }
        }
        if (is_exact) { exact = sym; break ;}

        //printf("%d %d \n", n_params, n_args);
        //if(exact != NULL) break;

        // Verifica compatibilidade (int↔double nas posições numéricas). OU seja, mesmo nao sendo exact, se for compativel é aceite
        int is_compat = 1;
        for (int i = 0; i < n_params; i++) {
            if (param_types[i] == arg_types[i]) continue; // exact nesta posição
            // só permite promoção int → double
            if (param_types[i] == TYPE_DOUBLE && arg_types[i] == TYPE_INT) continue;
            // tudo o resto é incompatível
            //printf("Aquii %d     %d   \n", arg_types[i], param_types[i]);
            is_compat = 0; break;
        }
        if (is_compat) { compat = sym; n_compat++;  }
        sym = sym->next;
    }



    // 3. Aplica regras do enunciado
    if (exact != NULL) {
        call->type    = exact->type;
        id_node->type = exact->type;
        fill_args_from_header(exact->node, args);
        id_node->args = args;
        result_type = exact->type;
        return result_type;
    }
    if (n_compat == 1 ) {
        call->type    = compat->type;
        id_node->type = compat->type;
        fill_args_from_header(compat->node, args);
        id_node->args = args;
        result_type = compat->type;
        return result_type;
    }
    if (n_compat >= 1) {
        printf("Line %d, col %d: Reference to method %s%s is ambiguous\n",
               id_node->line, id_node->column, call_id, call_args);
              
    } else {
        //printf("Nao encontro no check_calls\n");
        printf("Line %d, col %d: Cannot find symbol %s%s\n",
               id_node->line, id_node->column, call_id, call_args);
    }
    call->type = TYPE_UNDEF;
    id_node->type = TYPE_UNDEF;
    //id_node->args = strdup(call_args); // Use strdup pois call_args é local
    semantic_errors++;
    return TYPE_UNDEF;
}



struct symbol_list *check_parameters(struct node *MethodParams, struct symbol_list *symbol_table_prov){
    
    struct node_list *children_atual = MethodParams->children; // Cada filho é um nó "ParamDecl" com filhos type e Identifier

    while (children_atual != NULL && children_atual->node != NULL){ // é um nó "ParamDecl". Agora é preciso iterar sobre os seus filhos
        struct node *ParamDecl = children_atual->node;
        struct node_list *ParamDecl_children = ParamDecl->children; // a lista de nós dos 2 filhos de ParamDecl

        struct node *type_node = ParamDecl_children->node;
        struct node *ID_node = ParamDecl_children->next->node;

        ParamDecl->type = TYPE_UNDEF;
        ID_node->type = TYPE_UNDEF;
        ID_node->varDecl = 1; //Para nao ser printado o undef

        if (ID_node->token != NULL && (strcmp(ID_node->token, "_") == 0) ) { // Caso especial ja resolvido no pre_check
                /*printf("Line %d, col %d: Symbol %s is reserved\n",
                       ID_node->line, ID_node->column, ID_node->token);*/
                 //semantic_errors++;
                children_atual = children_atual->next;
                continue;
        }
        
        struct symbol_list *result = insert_symbol(symbol_table_prov, ID_node->token, category_to_type(type_node->category), ID_node, 1);

        if(result == NULL) {
            // Ja feito no pre-check
          /* printf("Line %d, col %d: Symbol %s already defined\n",
                       ID_node->line, ID_node->column, ID_node->token);*/
                //semantic_errors++;
        }

        children_atual = children_atual->next;
    }

    return symbol_table_prov;
}


/*
 * check_expression
 *
 * Recebe um nó de expressão da AST e devolve o seu tipo semântico.
 * Anota o nó com o tipo calculado (n->annot_type).
 *
 * Parâmetros:
 *   n            - nó da expressão a verificar
 *   local        - tabela de símbolos do método actual (params + vars locais)
 *   class_table  - tabela de símbolos da classe (fields + métodos)
 *
 * A navegação nos filhos segue a estrutura do teu yacc:
 *   filho 0 → n->children->node
 *   filho 1 → n->children->next->node
 *   filho 2 → n->children->next->next->node
 */

int natural_out_of_bounds(const char *lit)
{
    char *clean;
    size_t i, j, len;
    int is_out_of_bounds = 0;

    if (!lit)
        return 0;

    len = strlen(lit);
    clean = (char *)malloc(len + 1);
    if (!clean)
        return 0;

    j = 0;
    for (i = 0; i < len; i++)
    {
        if (lit[i] != '_')
            clean[j++] = lit[i];
    }
    clean[j] = '\0';

    size_t clean_len = strlen(clean);

    if (clean_len > 10)
    {
        is_out_of_bounds = 1;
    }
    else if (clean_len < 10)
    {
        is_out_of_bounds = 0;
    }
    else
    {
        is_out_of_bounds = (strcmp(clean, "2147483647") > 0);
    }

    free(clean);
    return is_out_of_bounds;
}

int decimal_out_of_bounds(const char *lit)
{
    char *clean;
    size_t i, j, len;
    double v;
    char *end;
    int has_nonzero_mantissa = 0;
    int in_exponent = 0;

    if (!lit)
        return 0;

    len = strlen(lit);
    clean = (char *)malloc(len + 1);
    if (!clean)
        return 0;

    j = 0;
    for (i = 0; i < len; i++)
    {
        if (lit[i] == 'e' || lit[i] == 'E')
            in_exponent = 1;

        if (lit[i] != '_')
        {
            clean[j++] = lit[i];
            if (!in_exponent && lit[i] >= '1' && lit[i] <= '9')
                has_nonzero_mantissa = 1;
        }
    }
    clean[j] = '\0';

    errno = 0;
    v = strtod(clean, &end);
    free(clean);

    if (v == 0.0 && has_nonzero_mantissa)
        return 1;

    if (v > 1.7976931348623157e+308 || v < -1.7976931348623157e+308)
        return 1;

    return 0;
}

// Helper interno para aceder ao n-ésimo filho (0-based)
static struct node *nth_child(struct node *n, int idx) {
    struct node_list *c = n->children;
    for (int i = 0; i < idx && c != NULL; i++)
        c = c->next;
    return (c != NULL) ? c->node : NULL;
}

// Helper: conta filhos de um nó
static int count_children(struct node *n) {
    int count = 0;
    struct node_list *c = n->children;
    while (c != NULL) { count++; c = c->next; }
    return count;
}

sem_type check_expression(struct node *n) {

    // o primeiro elemento na pilha pertence ao metodo

    if (n == NULL) return TYPE_UNDEF;
    struct symbol_list *local = (stack != NULL) ? stack->list : NULL;
    struct symbol_list *class_sym = listaGlobal;

    sem_type result = TYPE_UNDEF;

    switch (n->category) {

        // ── Literais ──────────────────────────────────────────────────────────
        case Natural: {
            
            //printf("token='%s' len=%zu\n", n->token, strlen(n->token));
            //printf("clean='%s' len=%zu\n", clean, strlen(clean));
            if (natural_out_of_bounds(n->token)){
                printf("Line %d, col %d: Number %s out of bounds\n",
                    n->line, n->column, n->token);
                semantic_errors++;
            }
            result = TYPE_INT;
            n->type = result;
            break;
        }

        case Decimal: {
            
            if (decimal_out_of_bounds(n->token)) { // Infinito 
                printf("Line %d, col %d: Number %s out of bounds\n",
                    n->line, n->column, n->token);
                semantic_errors++;
            } 
            result = TYPE_DOUBLE;
            n->type = result;
            break;
        }

        case BoolLit:
            result = TYPE_BOOL;
            n->type = TYPE_BOOL;
            break;

        case StrLit:
            // Só aparece em Print, mas por segurança
            result = TYPE_STRING;
            n->type = TYPE_STRING;
            break;

        // ── Identificador ─────────────────────────────────────────────────────
        case Identifier: {

            if (n->token != NULL && (strcmp(n->token, "_") == 0 ) ) {
                printf("Line %d, col %d: Symbol %s is reserved\n",
                       n->line, n->column, n->token);
                result =  TYPE_UNDEF;
                n->type = result;
                semantic_errors++;
                break;
            }

            // Procura na tabela local, ignorando MethodHeaders
            struct symbol_list *sym = search_var(local, n->token);
            if (sym == NULL)
                sym = search_var(class_sym, n->token);
            
            if (sym == NULL) {
                printf("Line %d, col %d: Cannot find symbol %s\n",
                       n->line, n->column, n->token);
                result = TYPE_UNDEF;
                semantic_errors++;
            } else {
                //printf("%s\n", sym->identifier);
                result = sym->type;
            }
            n->type = result;
            break;
        }

        // ── Assign: IDENTIFIER ASSIGN Expr ───────────────────────────────────
        // AST: Assign → [Identifier, Expr]
        case Assign: {
            struct node *id_node  = nth_child(n, 0);
            struct node *rhs_node = nth_child(n, 1);

            sem_type lt = check_expression(id_node);
            sem_type rt = check_expression(rhs_node);

            // ambos têm de ser tipos válidos (bool, int, double)
            int valid_lt = (lt == TYPE_BOOL || lt == TYPE_INT || lt == TYPE_DOUBLE);
            int valid_rt = (rt == TYPE_BOOL || rt == TYPE_INT || rt == TYPE_DOUBLE);

            if (!valid_lt || !valid_rt) {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                    n->line, n->column, op_name(n->category),
                    type_name(lt), type_name(rt));
                semantic_errors++;
                result = lt;
                break;
            }

            int numeric = (lt == TYPE_DOUBLE && rt == TYPE_INT);
            if (lt == rt || numeric) {
                result = lt;
            } else {
                printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n",
                    n->line, n->column, type_name(lt), type_name(rt));
                result = lt;
                semantic_errors++;
            }
            n->type = result;
            break;
        }
        // ── Operadores aritméticos binários: +, -, *, /, % ───────────────────
        // Aceitam int e double, resultado é double se algum for double
       case Add: case Sub: case Mul: case Div: case Mod: {
            sem_type lt = check_expression(nth_child(n, 0));
            sem_type rt = check_expression(nth_child(n, 1));

            if ((lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                (rt == TYPE_INT || rt == TYPE_DOUBLE)) {
                result = (lt == TYPE_DOUBLE || rt == TYPE_DOUBLE)
                         ? TYPE_DOUBLE : TYPE_INT;
                //printf("%d heree\n", result);
            } else {
                    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                           n->line, n->column, op_name(n->category),type_name(lt),
                           type_name(rt));
                result = TYPE_UNDEF;
                semantic_errors++;
            }
            n->type = result;
            break;
        }

        // ── Operadores de bit: <<, >>, ^ ──────────────────────────────────────
        // Apenas aceitam int
        case Xor:
        case Lshift:
        case Rshift: {
            sem_type lt = check_expression(nth_child(n, 0));
            sem_type rt = check_expression(nth_child(n, 1));

            if (lt == TYPE_INT && rt == TYPE_INT) {
                result = TYPE_INT;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                        n->line, n->column, op_name(n->category),
                        type_name(lt), type_name(rt));
                
                // Se houver UNDEF, propaga UNDEF. Caso contrário, assume-se INT por omissão
                if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) {
                    result = TYPE_INT;
                }
                semantic_errors++;
            }
            n->type = result;
            break;
        }

        // ── Operadores lógicos binários: &&, || ───────────────────────────────
        // Apenas aceitam boolean
        case And: case Or: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );


            if (lt == TYPE_BOOL && rt == TYPE_BOOL) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_BOOL;
                semantic_errors++;
                //if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) { result = TYPE_UNDEF; } // Pode ser uma solucao para os outros
            }
            n->type = result;

            break;
        }

        // ── Operadores relacionais: ==, != ────────────────────────────────────
        // int/double entre si, ou mesmo tipo(bool)
       case Eq: case Ne: {
            sem_type lt = check_expression(nth_child(n, 0));
            sem_type rt = check_expression(nth_child(n, 1));

            int numeric =( (lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                            (rt == TYPE_INT || rt == TYPE_DOUBLE) );
            numeric = numeric || (lt == TYPE_BOOL && rt == TYPE_BOOL);


            if (numeric) {
               result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                    n->line, n->column, n->token,
                    type_name(lt), type_name(rt));
                semantic_errors++;
            }
            result = TYPE_BOOL;
            n->type = result;
            break;
        }
        // ── Operadores relacionais: <, <=, >, >= ──────────────────────────────
        // Apenas int e double
        case Lt: case Le: case Gt: case Ge: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );

            //if (lt == TYPE_UNDEF && rt == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if ((lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                (rt == TYPE_INT || rt == TYPE_DOUBLE)) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_BOOL; //Forçado
                semantic_errors++;
                //if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) { result = TYPE_UNDEF; } // Pode ser uma solucao para os outros

            }
            n->type = result;
            break;
        }

        // ── Operadores unários: -, + ──────────────────────────────────────────
        // Apenas int e double
        case Minus: case Plus: {
            sem_type t = check_expression(nth_child(n, 0) );

            //if (t == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (t == TYPE_INT || t == TYPE_DOUBLE) {
                result = t;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",
                       n->line, n->column, n->token, type_name(t));
                result = TYPE_UNDEF;
                semantic_errors++;
            }
            n->type = result;
            break;
        }

        // ── Operador unário: ! ────────────────────────────────────────────────
        case Not: {
            sem_type t = check_expression(nth_child(n, 0) );
            //printf("Aqui a negacao %d\n", t );
            //if (t == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (t == TYPE_BOOL) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator ! cannot be applied to type %s\n",
                       n->line, n->column, type_name(t));
                result = TYPE_BOOL; // Forçado
                semantic_errors++;
            }
            n->type = result;
            break;
        }

        // ── Length: IDENTIFIER.length → int ──────────────────────────────────
        // AST (do yacc): Length → [Identifier]
        case Length: {
            // O filho tem de ser String[] para ter sentido, mas o enunciado
            // diz que .length devolve sempre int
            struct node *id_node  = nth_child(n, 0); // Identifier(args)

            id_node->type = check_expression(id_node);
            if(id_node->type != TYPE_STRING_ARRAY){
                printf("Line %d, col %d: Operator .length cannot be applied to type %s\n", 
                n->line , n->column, type_name(id_node->type));
                semantic_errors++;
            }
            result = TYPE_INT; // Forçado 
            n->type = result;
            break;
        }

        // ── ParseArgs: Integer.parseInt(id[expr]) → int ───────────────────────
        // AST: ParseArgs → [Identifier, Expr]
        case ParseArgs: {
            struct node *id_node  = nth_child(n, 0); // Identifier(args)
            struct node *idx_node = nth_child(n, 1); // Natural(0)
            
            id_node->type = check_expression(id_node);
            idx_node->type = check_expression(idx_node); 
            
            if(idx_node->type != TYPE_INT || id_node->type != TYPE_STRING_ARRAY ) {
                printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", 
                n->line, n->column, type_name(id_node->type), type_name(idx_node->type));
                semantic_errors++;
            }
            result = TYPE_INT;
            n->type = result;
            break;
        }

        // ── Call: IDENTIFIER(args) ────────────────────────────────────────────
        // AST: Call → [Identifier, Args?]
        // Args → [Expr, Expr, ...]
        case Call:
            result = check_calls(n);
            break;

        // ── Dummy: nó de erro sintático, ignora ──────────────────────────────
        case Dummy:
            result = TYPE_UNDEF;
            n->type = result;
            break;

        default:
            result = TYPE_UNDEF;
            n->type = result;
            break;
    }

    // Anota o nó com o tipo calculado (requer campo annot_type na struct node)
    n->type = result;
    return result;
}

struct symbol_list *newlist(){
    struct symbol_list *symbol_table = (struct symbol_list *) malloc(sizeof(struct symbol_list)); // Tabela tem de ser global
    symbol_table->next = NULL;
    symbol_table->identifier = NULL;
    return symbol_table;

}

struct symbol_list_stack *newStack(){
    struct symbol_list_stack *stack = (struct symbol_list_stack *) malloc(sizeof(struct symbol_list_stack)); // Tabela tem de ser global
    stack->list = NULL;
    stack->next = NULL;
    stack->identifier = NULL;
    return stack;
}

int pre_check_MethodHead(struct node *head) {
    if (head == NULL) return 0;
    if (head->children == NULL || head->children->node == NULL) return 0;
    if (head->children->next == NULL || head->children->next->node == NULL) return 0;

    struct node *typeNode = head->children->node;
    struct node *idNode   = head->children->next->node;

    if (idNode->token == NULL) return 0;

    sem_type ret_type = category_to_type(typeNode->category);
    char *args_str = malloc(4096 * sizeof(char));
    if (args_str == NULL) return 0;

    struct node *params_node = nth_child(head, 2);
    if (params_node != NULL) pre_check_parameters(params_node);

    fill_args_from_header(head, args_str);
    head->args = args_str;

    idNode->type = ret_type;
    idNode->varDecl = 1;

    if (strcmp(idNode->token, "_") == 0 ) {
        printf("Line %d, col %d: Symbol %s is reserved\n",
               idNode->line, idNode->column, idNode->token);
        semantic_errors++;
        return 0;
    }

    struct symbol_list *res = insert_method_symbol(listaGlobal, idNode->token, ret_type, head);
    if (res == NULL) {
        printf("Line %d, col %d: Symbol %s%s already defined\n",
               idNode->line, idNode->column, idNode->token, args_str);
        head->visit = 0;
        semantic_errors++;
        return 0;
    }

    return 1;
}

void pre_check_parameters(struct node *MethodParams) {
    if (MethodParams == NULL) return;

    struct symbol_list *temp = calloc(1, sizeof(struct symbol_list));
    if (temp == NULL) return;

    struct node_list *children_atual = MethodParams->children;

    while (children_atual != NULL && children_atual->node != NULL) {
        struct node *ParamDecl = children_atual->node;

        if (ParamDecl->children == NULL || ParamDecl->children->node == NULL) {
            children_atual = children_atual->next;
            continue;
        }
        if (ParamDecl->children->next == NULL || ParamDecl->children->next->node == NULL) {
            children_atual = children_atual->next;
            continue;
        }

        struct node *type_node = ParamDecl->children->node;
        struct node *ID_node   = ParamDecl->children->next->node;

        if (ID_node->token == NULL) {
            children_atual = children_atual->next;
            continue;
        }

        if (strcmp(ID_node->token, "_") == 0 ) {
            printf("Line %d, col %d: Symbol %s is reserved\n",
                   ID_node->line, ID_node->column, ID_node->token);
            semantic_errors++;
            children_atual = children_atual->next;
            continue;
        }

        if (search_symbol(temp, ID_node->token) != NULL) {
            printf("Line %d, col %d: Symbol %s already defined\n",
                   ID_node->line, ID_node->column, ID_node->token);
            semantic_errors++;
        } else {
            insert_symbol(temp, ID_node->token, category_to_type(type_node->category), ID_node, 1);
        }

        children_atual = children_atual->next;
    }

    // liberta a lista temporária
    struct symbol_list *s = temp->next;
    while (s != NULL) {
        struct symbol_list *next = s->next;
        free(s->identifier);
        free(s);
        s = next;
    }
    free(temp);
}

void check_MethodHead(struct node *head) {
    if (head == NULL) return;
    if (head->children == NULL || head->children->node == NULL) return;
    if (head->children->next == NULL || head->children->next->node == NULL) return;
    if (head->children->next->next == NULL || head->children->next->next->node == NULL) return;

    struct node *typeNode   = head->children->node;
    struct node *idNode     = head->children->next->node;
    struct node *paramsNode = head->children->next->next->node;

    if (idNode->token == NULL) return;

    sem_type ret_type = category_to_type(typeNode->category);

    struct symbol_list_stack *stc = newStack();
    if (stc == NULL) return;
    stc->identifier = idNode->token;

    struct symbol_list *symbol_table_prov = calloc(1, sizeof(struct symbol_list));
    if (symbol_table_prov == NULL) return;
    symbol_table_prov->identifier = NULL;
    symbol_table_prov->next = NULL;
    symbol_table_prov->node = NULL;

    insert_symbol(symbol_table_prov, "return", ret_type, head, 0);
    stc->list = check_parameters(paramsNode, symbol_table_prov);

    stc->next = stack;
    stack = stc;

    struct symbol_list_stack *copy = newStack();
    if (copy == NULL) return;
    copy->identifier = stc->identifier;
    copy->list = stc->list;
    copy->header = head;

    if (functionsList == NULL) {
        functionsList = copy;
        functionsList->next = NULL;
    } else {
        struct symbol_list_stack *itr = functionsList;
        while (itr->next != NULL)
            itr = itr->next;
        itr->next = copy;
    }
}



void check_statement(struct node *n) {
    if(n == NULL) return;

    switch(n->category) {

        case If:

        case While: {
            // filho 0 = condição (expressão booleana)
            // filhos seguintes são statements
            sem_type ct = check_expression(nth_child(n, 0));
            check_statement(nth_child(n, 1));
            if(n->category == If)
                check_statement(nth_child(n, 2)); // else
            if(ct != TYPE_BOOL) {
                printf("Line %d, col %d: Incompatible type %s in %s statement\n",
                       nth_child(n,0)->line, nth_child(n,0)->column,
                       type_name(ct),
                       n->category == If ? "if" : "while");
                semantic_errors++;
            }
            
            break;
        }

        case Return: { // ponto fraco
            struct node *expr = nth_child(n, 0); // pode ser NULL
            // tipo de retorno esperado está no topo da stack como "return"
            struct symbol_list *ret = search_symbol(stack->list, "return");
            sem_type expected = ret ? ret->type : TYPE_VOID;
            if(expected == TYPE_VOID) {
                if(expr != NULL) {
                    sem_type rt = check_expression(expr);
                    printf("Line %d, col %d: Incompatible type %s in return statement\n",
                            expr->line, expr->column, type_name(rt));
                    semantic_errors++;
                }
            } else {
                if(expr == NULL) {
                    printf("Line %d, col %d: Incompatible type void in return statement\n",
                           n->line, n->column);
                    semantic_errors++;
                } else {

                    sem_type rt = check_expression(expr);
                    int numeric = (expected == TYPE_DOUBLE && rt == TYPE_INT);
                    int assignable = (rt == expected) || numeric;

                    if (!assignable) {
                        printf("Line %d, col %d: Incompatible type %s in return statement\n",
                            expr->line, expr->column, type_name(rt));
                        semantic_errors++;
                    }

                }
            }
            break;
        }

        case Print:
            // filho 0 pode ser qualquer expr ou StrLit
            struct node *expr = nth_child(n, 0); // pode ser NULL
            if (expr == NULL) break;
            sem_type res = check_expression(expr);


            if(res != TYPE_INT && res != TYPE_BOOL && res != TYPE_DOUBLE && res != TYPE_STRING){
                //if(expr->category  != Call){
                    
                    printf("Line %d, col %d: Incompatible type %s in System.out.print statement\n",
                                expr->line, expr->column, type_name(res) ) ;
                                semantic_errors++;
                
                /*}else{
                    struct node *expr_child = nth_child(expr, 0); // identifier
                    printf("Line %d, col %d: Incompatible type %s in System.out.print statement\n",
                                expr_child->line, expr_child->column, type_name(res) ) ;
                                semantic_errors++;
                }*/
            }
            break;

        case Block:
            struct node_list *c = n->children;
            while(c != NULL) {
                check_statement(c->node);
                c = c->next;
            }
            break;

        case Assign:
        case Call:
        case ParseArgs:
            check_expression(n);
            break;

        case Dummy:
            break; // erro sintático, ignora

        default:
            break;
    }
}


void check_MethodBody(struct node *body) {
    if (body == NULL) return;
    if (stack == NULL || stack->list == NULL) return;

    struct node_list *child = body->children;

    while (child != NULL && child->node != NULL) {

        if (child->node->category == VarDecl) {
            if (child->node->children == NULL || child->node->children->node == NULL) {
                child = child->next;
                continue;
            }
            if (child->node->children->next == NULL || child->node->children->next->node == NULL) {
                child = child->next;
                continue;
            }

            struct symbol_list *local = stack->list;
            struct node *type_node = child->node->children->node;
            struct node *id_node   = child->node->children->next->node;

            if (id_node->token == NULL) {
                child = child->next;
                continue;
            }

            if (strcmp(id_node->token, "_") == 0 ) {
                printf("Line %d, col %d: Symbol %s is reserved\n",
                       id_node->line, id_node->column, id_node->token);
                semantic_errors++;
                id_node->varDecl  = 1;
                child = child->next;
                continue;
            }

            sem_type t = category_to_type(type_node->category);
            id_node->type = t;
            id_node->varDecl = 1;

            if (insert_symbol(local, id_node->token, t, id_node, 0) == NULL) {
                printf("Line %d, col %d: Symbol %s already defined\n",
                       id_node->line, id_node->column, id_node->token);
                semantic_errors++;
            }

        } else {
            check_statement(child->node);
        }

        child = child->next;
    }
}


void check_MethodDecl(struct node *Decl){
    struct node *header = nth_child(Decl, 0);
    struct node *body   = nth_child(Decl, 1);

    if(Decl != NULL && Decl->visit){ // if its not a duuplicated method

        check_MethodHead(header); // constrói tabela local e empurra para a stack

        check_MethodBody(body);   // usa stack->list como tabela local

    }

}


// semantic analysis begins here, with the AST root node
int check_program(struct node *program) {
    listaGlobal = newlist();
    stack = NULL;
    
    // 1. Proteção: Verificar se program ou program->children são nulos
    if(program == NULL || program->children == NULL) return semantic_errors;
    
    // 2. Proteção: Verificar se o node principal existe antes de alterar o type
    if(program->children->node != NULL) {
        program->children->node->type = TYPE_CLASS;
    }

    // Primeira fase: adicionar cabeçalhos e fields à lista de símbolos
    struct node_list *child = program->children->next;
    while(child != NULL) {
        struct node *decl = child->node;
        
        if(decl != NULL && decl->category == FieldDecl) {
            struct node *type_node = nth_child(decl, 0);
            struct node *id_node   = nth_child(decl, 1);

            sem_type t = (type_node != NULL) ? category_to_type(type_node->category) : TYPE_UNDEF;

            // 3. Proteção: Garantir que id_node não é NULL antes de acessar propriedades
            if (id_node != NULL) {
                id_node->type = t;
                id_node->varDecl = 1;

                if (id_node->token != NULL && (strcmp(id_node->token, "_") == 0  ) ) { // Caso especial 
                    printf("Line %d, col %d: Symbol %s is reserved\n",
                           id_node->line, id_node->column, id_node->token);
                    child = child->next;
                    semantic_errors++;
                    continue;
                }

                // 4. Proteção: Garantir que o token existe antes de procurar ou duplicar
                if (id_node->token != NULL) {
                    struct symbol_list *search_res = search_field_decl(listaGlobal, id_node->token);
                    if(search_res != NULL) {
                        printf("Line %d, col %d: Symbol %s already defined\n",
                               id_node->line, id_node->column, id_node->token);
                        semantic_errors++;
                    } else {
                        struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
                        
                        // 5. Proteção: Verificar se o malloc foi bem sucedido
                        if (new != NULL) {
                            new->identifier = strdup(id_node->token);
                            new->type = t;
                            new->node = decl;
                            new->next = NULL;
                            new->param = 1;
                            
                            // 6. Proteção: Garantir que listaGlobal não falhou ao ser inicializada
                            if (listaGlobal != NULL) {
                                struct symbol_list *symbol = listaGlobal;
                                while(symbol->next != NULL) {
                                    symbol = symbol->next;
                                }
                                symbol->next = new;
                            }
                        }
                    } 
                }
            }
        }
        
        if(decl != NULL && decl->category == MethodDecl) {
            // 7. Proteção: Verificar a cadeia de ponteiros antes de pre_check_MethodHead
            if (decl->children != NULL && decl->children->node != NULL) {
                int res = pre_check_MethodHead(decl->children->node);
                if(!res){
                    decl->visit = 0;
                }
            }
        }

        child = child->next;
    }

    // Após registar todos os métodos e field declarations, iniciar a análise
    child = program->children->next;
    while(child != NULL) {
        struct node *decl = child->node;

        // 8. Proteção: Verificar se decl é não-nulo antes de acessar category
        if(decl != NULL && decl->category == MethodDecl) {
            check_MethodDecl(decl);
        }

        child = child->next;
    }
    
    // 9. Proteção: Verificar ponteiros antes de imprimir a tabela
    if (print_semantics && program->children->node != NULL && program->children->node->token != NULL) {
        print_symbol_tables(program->children->node->token);
    }
    
    return semantic_errors;
}


// insert a new symbol in the list, unless it is already there
struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, sem_type type, struct node *node, int param) {
    if(search_symbol(table, identifier) != NULL)
        return NULL;       /* return NULL if symbol is already inserted */
    struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    new->node = node;
    new->next = NULL;
    new->param = param;
    struct symbol_list *symbol = table;
    while(symbol->next != NULL)
        symbol = symbol->next;
    symbol->next = new;    /* insert new symbol at the tail of the list */
    //printf("%s\n", identifier);
    return new;
}


// para métodos - permite overloading (mesmo nome, args diferentes)
struct symbol_list *insert_method_symbol(struct symbol_list *table, char *identifier, sem_type type, struct node *node) {
    // Verifica se já existe método com MESMO nome E mesma assinatura
    char *args = malloc(4096 * sizeof(char));
    fill_args_from_header(node, args);
    
    struct symbol_list *sym = table->next;
    while (sym != NULL) {
        if (strcmp(sym->identifier, identifier) == 0 &&
            sym->node->args != NULL &&
            strcmp(sym->node->args, args) == 0) {
            free(args);
            return NULL; // mesmo nome E mesma assinatura → duplicado
        }
        sym = sym->next;
    }

    // Insere normalmente
    struct symbol_list *new = calloc(1, sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    new->node = node;
    new->next = NULL;
    new->param = 0;
    struct symbol_list *s = table;
    while (s->next != NULL) s = s->next;
    s->next = new;
    free(args);
    return new;
}

// look up a symbol by its identifier
struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    if (table == NULL || identifier == NULL) return NULL;
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0 )
            return symbol;
    return NULL;
}

struct symbol_list *search_var(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0 
           && symbol->node->category != MethodHeader)
            return symbol;
    return NULL;
}

struct symbol_list *search_field_decl(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0 
           && symbol->node->category == FieldDecl)
            return symbol;
    return NULL;
}



void print_symbol_tables(char *class_name) {
    // Tabela global da classe
    printf("===== Class %s Symbol Table =====\n", class_name);
    struct symbol_list *sym = listaGlobal->next;
    while (sym != NULL) {
        if(sym->param == 0){ // Uma declaracao de metodo
            struct node *header = sym->node;
            struct node *params_node = nth_child(header, 2);

            // Constrói string dos parâmetros
            char *params = malloc(4096 * sizeof(char));
            params[0] = '\0';
            strcat(params, "(");
            int i = 0;
            struct node_list *p = params_node->children;
            while (p != NULL && p->node != NULL) {
                struct node *ptype = nth_child(p->node, 0);
                if (i > 0) strcat(params, ",");
                strcat(params, type_name(category_to_type(ptype->category)));
                p = p->next;
                i++;
            }
            strcat(params, ")");

            printf("%s\t%s\t%s\n", sym->identifier, params, type_name(sym->type));
            free(params);
        }else{
            printf("%s\t\t%s\n", sym->identifier, type_name(sym->type));
        }
        sym = sym->next;
    }
    printf("\n");

    // Tabelas dos métodos
    struct symbol_list_stack *scope = functionsList;
    while (scope != NULL) {
        char *args = (scope->header != NULL && scope->header->args != NULL) 
                    ? scope->header->args : "()";
        printf("===== Method %s%s Symbol Table =====\n", scope->identifier, args);
        struct symbol_list *s = scope->list->next;
        while (s != NULL) {
            if (s->param)
                printf("%s\t\t%s\t%s\n", s->identifier, type_name(s->type), "param");
            else
                printf("%s\t\t%s\n", s->identifier, type_name(s->type));
            s = s->next;
        }
        printf("\n");

        scope = scope->next;
    }
}
