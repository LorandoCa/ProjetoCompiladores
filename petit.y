/* START definitions section -- C code delimited by %{ ... %} and token declarations */

%{

#include <stdio.h>
#include "ast.h"

int yylex(void);
void yyerror(char *);

struct programs_list *handle;
struct node *ast;

%}

%token IF THEN ELSE
%token<lexeme> IDENTIFIER NATURAL DECIMAL INTEGER DOUBLE
%type<node> program functions function parameters parameter arguments expression

%left LOW
%left '+' '-'
%left '*' '/'

%union{
    char *lexeme;
    struct node *node;
}

/* START grammar rules section -- BNF grammar */

/* Esta solucao utiliza as funcoes que foram sugeridas no enunciado mas podia ser resolvida de outra forma em que um so nó logo teria todos os filhos "functions".
Isto podia ser conseguido, se ao inves de criar uma arvore para cada funcao que aparece, criava-se uma unica arvore no terminal de functions e na recursao adicionava-se
somente ao topo da pilha "functions" e addchild($$, $2).*/

%%

program: functions                     {
                                            $$ = $1;
                                            ast = addChildren(handle);
                                        }
    ;

functions:  function                {  //Criar um novo programa(new_list) que é o provisorio;
                                        struct node *provisorio = $$ = newnode(Program, NULL);
                                        addchild($$, $1); 
                                        append(handle, provisorio);
                                    }

            | functions function    {  struct node *provisorio = $$ = newnode(Program, NULL);
                                        addchild($$, $2); 
                                        append(handle, provisorio);
                                    }
    ;

function: IDENTIFIER '(' parameters ')' '=' expression
                                    { $$ = newnode(Function, NULL);
                                      addchild($$, newnode(Identifier, $1));
                                      addchild($$, $3);
                                      addchild($$, $6); }
    ;

parameters: parameter               { $$ = newnode(Parameters, NULL );
                                      addchild($$, $1); }
    | parameters ',' parameter      { $$ = newnode(Parameters, NULL );
                                      addchild($$, $1);
                                      addchild($$, $3); }
    ;

parameter: INTEGER IDENTIFIER       { $$ = newnode(Parameter, NULL);
                                        addchild($$, newnode(Integer, NULL)); 
                                      addchild($$, newnode(Identifier, $2)); }

    | DOUBLE IDENTIFIER             { $$ = newnode(Parameter, NULL);
                                        addchild($$, newnode(Double, NULL));
                                      addchild($$, newnode(Identifier, $2));}
    ;

arguments: expression               { $$ = newnode(Arguments, NULL);
                                      addchild($$, $1); }

    | arguments ',' expression      { $$ = newnode(Arguments, NULL);
                                      addchild($$, $1);
                                      addchild($$, $3); }
    ;

expression: IDENTIFIER              { $$ = newnode(Identifier, $1); }
    | NATURAL                       { $$ = newnode(Natural, $1); }
    | DECIMAL                       { $$ = newnode(Decimal, $1); }

    | IDENTIFIER '(' arguments ')'  { $$ = newnode(Call, NULL);
                                        addchild($$, newnode(Identifier,$1));
                                        addchild($$, $3);
                                    }

    | IF expression THEN expression ELSE expression  %prec LOW
                                    {
                                        $$ = newnode(If, NULL);
                                     addchild($$, $2); addchild($$, $4); addchild($$, $6); }

    | expression '+' expression     {
                                        $$ = newnode(Add, NULL);
                                        addchild($$, $1); addchild($$, $3);
                                     }

    | expression '-' expression     {
                                        $$ = newnode(Sub, NULL);
                                        addchild($$, $1); addchild($$, $3);
                                    }
                                    
    | expression '*' expression     {
                                        $$ = newnode(Mul, NULL);
                                        addchild($$, $1); addchild($$, $3);
                                    }

    | expression '/' expression     {
                                        $$ = newnode(Div, NULL);
                                        addchild($$, $1); addchild($$, $3);
                                    }

    | '(' expression ')'            { $$ = $2; }  
    ;

%%

/* START subroutines section */

// all needed functions are collected in the .l and ast.* files