#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ast1.h"
#include "semantics.h"

int semantic_errors = 0;

struct symbol_list *listaGlobal;
struct symbol_list_stack *stack;
struct symbol_list_stack *functionsList;


void printError(struct node *no){
    // Put the printf here
}



const char *op_name(enum category c) {
    switch(c) {
        case Add: return "+";
        case Sub: return "-";
        case Mul: return "*";
        case Div: return "/";
        case Mod: return "%";
        case Assign: return "=";
        case Lshift: return "<<";
        case Rshift: return ">>";
        case Xor: return "^";
        case Not: return "!";
        case Plus: return "+";
        case Minus: return "-";
        case And: return "&&";
        case Or: return "||";
        case Eq: return "==";
        case Ne: return "!=";
        case Lt: return "<";
        case Le: return "<=";
        case Gt: return ">";
        case Ge: return ">=";
        default:  return "?";
    }
}


void fill_args_from_header(struct node *header, char *args) {
    struct node *params_node = nth_child(header, 2);
    args[0] = '\0';
    strcat(args, "(");
    int i = 0;
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

    char *args= (char*)malloc(64*sizeof(char));

    // 1. Recolhe tipos dos argumentos reais
    int n_args = 0;
    sem_type arg_types[64];
    char call_args[256];
    call_args[0] = '\0';
    strcat(call_args, "(");
    if (args_node != NULL) {
        struct node_list *a = args_node->children;
        while (a != NULL) {
            arg_types[n_args++] = check_expression(a->node);
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

        result_type = nth_child(header, 0)->type;

        // Conta e recolhe tipos dos parâmetros formais
        int n_params = 0;
        sem_type param_types[64];
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
        if (is_exact) { exact = sym; break; }

        //printf("%d %d \n", n_params, n_args);
        if(exact != NULL) break;

        // Verifica compatibilidade (int↔double nas posições numéricas). OU seja, mesmo nao sendo exact, se for compativel é aceite
        int is_compat = 1;
        for (int i = 0; i < n_params; i++) {
            if (param_types[i] == arg_types[i]) continue; // exact nesta posição
            // só permite promoção int → double
            if (param_types[i] == TYPE_DOUBLE && arg_types[i] == TYPE_INT) continue;
            // tudo o resto é incompatível
            is_compat = 0; break;
        }
        if (is_compat) { compat = sym; n_compat++; }
            sym = sym->next;
        }

    // 3. Aplica regras do enunciado
    if (exact != NULL) {
        call->type    = exact->type;
        id_node->type = exact->type;
        fill_args_from_header(exact->node, args);
        id_node->args = args;
        return exact->type;
    }
    if (n_compat == 1) {
        call->type    = compat->type;
        id_node->type = compat->type;
        fill_args_from_header(compat->node, args);
        id_node->args = args;
        return compat->type;
    }
    if (n_compat > 1) {
        printf("Line %d, col %d: Reference to method %s is ambiguous\n",
               id_node->line, id_node->column, call_id);
    } else {
        //printf("Nao encontro no check_calls\n");
        printf("Line %d, col %d: Cannot find symbol %s%s\n",
               id_node->line, id_node->column, call_id, call_args);
    }
    semantic_errors++;
   
    //id_node->type  // Este tem de ter todos os tipos de argumentos entre parenteses
    return result_type;
}



struct symbol_list *check_parameters(struct node *MethodParams, struct symbol_list *symbol_table_prov){
    
    struct node_list *children_atual = MethodParams->children; // Cada filho é um nó "ParamDecl" com filhos type e Identifier

    while (children_atual != NULL && children_atual->node != NULL){ // é um nó "ParamDecl". Agora é preciso iterar sobre os seus filhos
        struct node *ParamDecl = children_atual->node;
        struct node_list *ParamDecl_children = ParamDecl->children; // a lista de nós dos 2 filhos de ParamDecl

        struct node *type_node = ParamDecl_children->node;
        struct node *ID_node = ParamDecl_children->next->node;

        ParamDecl->type = TYPE_UNDEF;
        ID_node->type = TYPE_DECL;
        
        struct symbol_list *result = insert_symbol(symbol_table_prov, ID_node->token, category_to_type(type_node->category), ID_node, 1);

        if(result == NULL) {
            // TODO 
           printf("Line %d, col %d: Symbol %s already defined\n",
                       ID_node->line, ID_node->column, ID_node->token);
                semantic_errors++;
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

    
    struct symbol_list *local = stack->list; // o primeiro elemento na pilha pertence ao metodo
    struct symbol_list *class_sym = listaGlobal;
    if (n == NULL) return TYPE_UNDEF;

    sem_type result = TYPE_INT;

    switch (n->category) {

        // ── Literais ──────────────────────────────────────────────────────────
        case Natural:
            // Verifica overflow: NATURAL > 2147483647 → erro
            // (o token está em n->token como string)
            if (strlen(n->token) > 10 ||
                (strlen(n->token) == 10 && strcmp(n->token, "2147483647") > 0)) {
                char msg[256];
                snprintf(msg, sizeof msg, "Number %s out of bounds", n->token);
                printf("Line %d, col %d: %s\n", n->line, n->column, msg);
                result = TYPE_INT;
            } else {
                result = TYPE_INT;
            }
            break;

        case Decimal: {
            errno = 0;
            char clean[256];
            int j = 0;
            for (int i = 0; n->token[i] != '\0'; i++)
                if (n->token[i] != '_') clean[j++] = n->token[i];
            clean[j] = '\0';
            
            double val = strtod(clean, NULL);
            // só é out of bounds se for mesmo 0 (underflow total) ou infinito
            if (errno == ERANGE && val == 0.0) {
                printf("Line %d, col %d: Number %s out of bounds\n",
                    n->line, n->column, n->token);
                semantic_errors++;
                result = TYPE_DOUBLE;
            } else {
                result = TYPE_DOUBLE;
            }
            n->type = result;
            break;
        }

        case BoolLit:
            result = TYPE_BOOL;
            break;

        case StrLit:
            // Só aparece em Print, mas por segurança
            result = TYPE_INT;
            break;

        // ── Identificador ─────────────────────────────────────────────────────
        case Identifier: {

            // Procura primeiro na tabela local, depois na da classe
            struct symbol_list *sym = search_symbol(local, n->token);
            if (sym == NULL)
                sym = search_symbol(class_sym, n->token);

            if (sym == NULL) {
                printf("Line %d, col %d: Cannot find symbol %s\n",
                       n->line, n->column, n->token);
                result = TYPE_INT;
            } else {
                //printf("%s\n", sym->identifier);
                result = sym->type;
            }
            break;
        }

        // ── Assign: IDENTIFIER ASSIGN Expr ───────────────────────────────────
        // AST: Assign → [Identifier, Expr]
        case Assign: {
            struct node *id_node  = nth_child(n, 0);
            struct node *rhs_node = nth_child(n, 1);

            sem_type lt = check_expression(id_node);
            sem_type rt = check_expression(rhs_node );

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = lt; break;
            }

            // Compatibilidade: int←int, double←double, double←int, int←double
            int numeric = (lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                          (rt == TYPE_INT || rt == TYPE_DOUBLE);
            if (lt == rt || numeric) {
                result = lt;
            } else {
                printf("Line %d, col %d: Incompatible type %s in = statement\n",
                       n->line, n->column, type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores aritméticos binários: +, -, *, /, % ───────────────────
        // Aceitam int e double, resultado é double se algum for double
       case Add: case Sub: case Mul: case Div: case Mod: {
            sem_type lt = check_expression(nth_child(n, 0));
            sem_type rt = check_expression(nth_child(n, 1));

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_UNDEF; break;
            }
           /* if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) {
                printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",
                       n->line, n->column, op_name(n->category),
                       lt == TYPE_UNDEF ? type_name(lt) : type_name(rt));
                result = TYPE_UNDEF; break;
            }*/

            if ((lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                (rt == TYPE_INT || rt == TYPE_DOUBLE)) {
                result = (lt == TYPE_DOUBLE || rt == TYPE_DOUBLE)
                         ? TYPE_DOUBLE : TYPE_INT;
            } else {
                if (lt != TYPE_INT && lt != TYPE_DOUBLE && rt != TYPE_INT && rt != TYPE_DOUBLE)
                    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                           n->line, n->column, op_name(n->category),
                           type_name(lt), type_name(rt));
                else
                    printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",
                           n->line, n->column, op_name(n->category),
                           (lt != TYPE_INT && lt != TYPE_DOUBLE)
                           ? type_name(lt) : type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores de bit: <<, >>, ^ ──────────────────────────────────────
        // Apenas aceitam int
        case Lshift: case Rshift: case Xor: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (lt == TYPE_INT && rt == TYPE_INT) {
                result = TYPE_INT;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores lógicos binários: &&, || ───────────────────────────────
        // Apenas aceitam boolean
        case And: case Or: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (lt == TYPE_BOOL && rt == TYPE_BOOL) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores relacionais: ==, != ────────────────────────────────────
        // int/double entre si, ou mesmo tipo
        case Eq: case Ne: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_UNDEF; break;
            }

            int numeric = (lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                          (rt == TYPE_INT || rt == TYPE_DOUBLE);
            if (lt == rt || numeric) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores relacionais: <, <=, >, >= ──────────────────────────────
        // Apenas int e double
        case Lt: case Le: case Gt: case Ge: {
            sem_type lt = check_expression(nth_child(n, 0) );
            sem_type rt = check_expression(nth_child(n, 1) );

            if (lt == TYPE_UNDEF || rt == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if ((lt == TYPE_INT || lt == TYPE_DOUBLE) &&
                (rt == TYPE_INT || rt == TYPE_DOUBLE)) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
                       n->line, n->column, op_name(n->category),
                       type_name(lt), type_name(rt));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operadores unários: -, + ──────────────────────────────────────────
        // Apenas int e double
        case Minus: case Plus: {
            sem_type t = check_expression(nth_child(n, 0) );

            if (t == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (t == TYPE_INT || t == TYPE_DOUBLE) {
                result = t;
            } else {
                printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",
                       n->line, n->column, op_name(n->category), type_name(t));
                result = TYPE_INT;
            }
            break;
        }

        // ── Operador unário: ! ────────────────────────────────────────────────
        case Not: {
            sem_type t = check_expression(nth_child(n, 0) );

            if (t == TYPE_UNDEF) { result = TYPE_UNDEF; break; }

            if (t == TYPE_BOOL) {
                result = TYPE_BOOL;
            } else {
                printf("Line %d, col %d: Operator ! cannot be applied to type %s\n",
                       n->line, n->column, type_name(t));
                result = TYPE_INT;
            }
            break;
        }

        // ── Length: IDENTIFIER.length → int ──────────────────────────────────
        // AST (do yacc): Length → [Identifier]
        case Length: {
            // O filho tem de ser String[] para ter sentido, mas o enunciado
            // diz que .length devolve sempre int
            struct node *id_node  = nth_child(n, 0); // Identifier(args)
            id_node->type = TYPE_STRING_ARRAY;
            result = TYPE_INT;
            break;
        }

        // ── ParseArgs: Integer.parseInt(id[expr]) → int ───────────────────────
        // AST: ParseArgs → [Identifier, Expr]
        case ParseArgs: {
            struct node *id_node  = nth_child(n, 0); // Identifier(args)
            struct node *idx_node = nth_child(n, 1); // Natural(0)
            
            check_expression(id_node);
            idx_node->type = TYPE_INT; // força int, não precisa de check_expression
            
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
            result = TYPE_INT;
            break;

        default:
            result = TYPE_INT;
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

void pre_check_MethodHead(struct node *head){
    // filho 1: Type ou Void
    // filho 2: Identifier
    struct node *typeNode   = head->children->node;
    struct node *idNode     = head->children->next->node;

    //printf("aqui %s", idNode->token);

    sem_type ret_type = category_to_type(typeNode->category);
    char *args_str= (char*)malloc(64*sizeof(char));

    fill_args_from_header(head, args_str); // preenche args primeiro

    idNode->type = TYPE_DECL;
    // Try to insert method symbol - if it returns NULL, there's a duplicate
    struct symbol_list *result = insert_method_symbol(listaGlobal, idNode->token, ret_type, head);
    if (result == NULL) {
        printf("Line %d, col %d: Symbol %s%s already defined\n",
               idNode->line, idNode->column, idNode->token, args_str);
        semantic_errors++;
        head->args = NULL; // Mark as duplicate so check_MethodDecl skips it
    } else {
        head->args = args_str;
    }
}


void check_MethodHead(struct node *head){
    
    // filho 1: Type ou Void
    // filho 2: Identifier
    // filho 3: MethodParams
    struct node *typeNode   = head->children->node;
    struct node *idNode     = head->children->next->node;
    struct node *paramsNode = head->children->next->next->node;


    char *methodName = (char*) malloc(1024 * sizeof(char));
    sprintf(methodName, "===== Method %s(", idNode->token);

    // iterar pelos ParamDecl dentro de MethodParams
    struct node_list *param = paramsNode->children;
    while(param != NULL && param->node != NULL){
        // primeiro filho de ParamDecl é o Type (ou StringArray)
        sem_type tp = param->node->children->node->type;
        char *type = type_name(tp);
        strcat(methodName, type);

        if(param->next != NULL)
            strcat(methodName, ", ");

        param = param->next;
    }

    strcat(methodName, ") Symbol Table =====");

    //printf("Printing id %s\n", idNode->token);
    sem_type ret_type = category_to_type(typeNode->category);

    char *args_str= (char*)malloc(64*sizeof(char));

    fill_args_from_header(head, args_str); // preenche args primeiro
    head->args = args_str;

    idNode->type = TYPE_DECL;
    
    //Nao é preciso porque ja foi adicionado no pre_check
    //insert_symbol(listaGlobal, idNode->token, ret_type, head, 0); // Simbolo inserido na tabela de simbolos
    
    struct symbol_list_stack *stc = newStack();
    stc->identifier = idNode->token;
    struct symbol_list *symbol_table_prov = (struct symbol_list *) malloc(sizeof(struct symbol_list)); // Tabela provisoria
    symbol_table_prov->identifier = NULL;
    symbol_table_prov->next = NULL;
    symbol_table_prov->node = NULL;


    insert_symbol(symbol_table_prov, "return", ret_type, head, 0);
    stc->list = check_parameters(paramsNode, symbol_table_prov); // Estao na lista os parametros do método


    stc->next = stack;
    stack = stc;

    struct symbol_list_stack *copy = newStack();
    copy->identifier = stc->identifier;
    copy->list = stc->list;
    copy->header = head;
    if(functionsList == NULL){
       
        functionsList = copy;
        functionsList->next = NULL;
    }else{

        struct symbol_list_stack *itr = functionsList;
        while (itr->next != NULL){
            itr = itr->next;
        }
        itr->next = copy ;
        
    }

}

void check_statement(struct node *n) {
    if(n == NULL) return;

    switch(n->category) {

        case If:

        case While: {
            // filho 0 = condição (expressão booleana)
            sem_type ct = check_expression(nth_child(n, 0));
            if(ct != TYPE_BOOL && ct != TYPE_UNDEF) {
                printf("Line %d, col %d: Incompatible type %s in %s statement\n",
                       nth_child(n,0)->line, nth_child(n,0)->column,
                       type_name(ct),
                       n->category == If ? "if" : "while");
                semantic_errors++;
            }
            // filhos seguintes são statements
            check_statement(nth_child(n, 1));
            if(n->category == If)
                check_statement(nth_child(n, 2)); // else
            break;
        }

        case Return: {
            struct node *expr = nth_child(n, 0); // pode ser NULL
            // tipo de retorno esperado está no topo da stack como "return"
            struct symbol_list *ret = search_symbol(stack->list, "return");
            sem_type expected = ret ? ret->type : TYPE_VOID;
            if(expected == TYPE_VOID) {
                if(expr != NULL) {
                    sem_type rt = check_expression(expr);
                    if(rt != TYPE_UNDEF) {
                        printf("Line %d, col %d: Incompatible type %s in return statement\n",
                               expr->line, expr->column, type_name(rt));
                        semantic_errors++;
                    }
                }
            } else {
                if(expr == NULL) {
                    printf("Line %d, col %d: Incompatible type void in return statement\n",
                           n->line, n->column);
                    semantic_errors++;
                } else {
                    sem_type rt = check_expression(expr);
                    //printf("%d aqui\n", rt);
                    
                    if(rt == TYPE_UNDEF){
                        printf("Line %d, col %d: Incompatible type %s in return statement\n",
                               expr->line, expr->column, type_name(rt));
                        semantic_errors++;
                    }

                    int numeric = (expected == TYPE_INT || expected == TYPE_DOUBLE)
                               && (rt == TYPE_INT || rt == TYPE_DOUBLE);
                    if(rt != TYPE_UNDEF && rt != expected && !numeric) {
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
            sem_type res = check_expression(expr);


            if(res == TYPE_UNDEF){
                if(expr->category  != Call){
                    
                    printf("Line %d, col %d: Incompatible type undef in System.out.print statement\n",
                                expr->line, expr->column);
                
                }else{
                    struct node *expr_child = nth_child(expr, 0); // identifier
                    printf("Line %d, col %d: Incompatible type undef in System.out.print statement\n",
                                    expr_child->line, expr_child->column);
                }
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


void check_MethodBody(struct node *body){
    // Pode ser statement or varDecl

    struct node_list *child = body->children;

    while(child != NULL && child->node != NULL) {
        if(child->node->category == VarDecl){
            // Tratar declaracao de variaveis
            struct symbol_list *local = stack->list;
            struct node *id_node = child->node->children->next->node;

            sem_type t = category_to_type(child->node->children->node->category);
            id_node->type = TYPE_DECL;
;            if(insert_symbol(local, id_node->token, t, id_node, 0) == NULL) {
                printf("Line %d, col %d: Symbol %s already defined\n",
                       id_node->line, id_node->column, id_node->token);
                semantic_errors++;
            } 

        }else{
            // é uma statement
            check_statement(child->node);
            // se for um block, adicionar mais um slot na stack q será inicializada com info do nó anterior
        }

        child = child->next;

    }

}

void check_MethodDecl(struct node *Decl){
    struct node *header = nth_child(Decl, 0);
    struct node *body   = nth_child(Decl, 1);

    // Skip processing if method was already defined as duplicate (header->args will be NULL if duplicate)
    if (header->args == NULL) {
        return;
    }

    check_MethodHead(header); // constrói tabela local e empurra para a stack

    check_MethodBody(body);   // usa stack->list como tabela local

}


// semantic analysis begins here, with the AST root node
int check_program(struct node *program) {
    listaGlobal = newlist();
    stack = NULL;
    program->children->node->type = TYPE_CLASS;
    
    //Uma fase inicial que vai adicionar cabeçalhos de métodos e fiel decl, a lista de símbolos
    struct node_list *child = program->children->next;
    while(child != NULL) {
        struct node *decl = child->node;
        if(decl->category == FieldDecl) {
            struct node *type_node = nth_child(decl, 0);
            struct node *id_node   = nth_child(decl, 1);
            sem_type t = category_to_type(type_node->category);

            id_node->type = TYPE_DECL;

            if(search_symbol(listaGlobal, id_node->token) != NULL) {
                printf("Line %d, col %d: Symbol %s already defined\n",
                       id_node->line, id_node->column, id_node->token);
                semantic_errors++;
            } else {
                insert_symbol(listaGlobal, id_node->token, t, id_node, 1);
            } 
        }
        if(decl->category == MethodDecl) {
            pre_check_MethodHead(decl->children->node);
        }

        child = child->next;


    }


    //Após registar todos os métodos e field declarations, iniciar a analise das declaracoes e bodys
    child = program->children->next;
    while(child != NULL) {
        struct node *decl = child->node;

        if(decl->category == MethodDecl) {
            check_MethodDecl(decl);
        }

        child = child->next;
    }
    print_symbol_tables(program->children->node->token);
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
    char args[256];
    fill_args_from_header(node, args);
    
    struct symbol_list *sym = table->next;
    while (sym != NULL) {
        if (strcmp(sym->identifier, identifier) == 0 &&
            sym->node->args != NULL &&
            strcmp(sym->node->args, args) == 0) {
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
    return new;
}

// look up a symbol by its identifier
struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0)
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
            char params[256];
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
            
        }else{
            printf("%s\t\t%s\n", sym->identifier, type_name(sym->type));
        }
        sym = sym->next;
    }

    // Tabelas dos métodos
    struct symbol_list_stack *scope = functionsList;
    while (scope != NULL) {
        char *args = (scope->header != NULL && scope->header->args != NULL) 
                    ? scope->header->args : "()";
        printf("\n===== Method %s%s Symbol Table =====\n", scope->identifier, args);
        struct symbol_list *s = scope->list->next;
        while (s != NULL) {
            if (s->param)
                printf("%s\t\t%s\t%s\n", s->identifier, type_name(s->type), "param");
            else
                printf("%s\t\t%s\n", s->identifier, type_name(s->type));
            s = s->next;
        }
        scope = scope->next;
    }
}
