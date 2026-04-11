/* START definitions section -- C code delimited by %{ ... %} and substitutions */

%{

#include "y.tab.h"
#include "ast.h"

// macro YY_USER_ACTION, which updates 'lex_column', is executed before every action
#define YY_USER_ACTION { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; }
#define PASS_TOKEN() yylval.lexeme = strdup(yytext);

int yyparse(void);
void yyerror(char *);

int lex_line = 1, lex_column = 1;
int syn_line = -1, syn_column = -1;
int errors = 0;

extern struct node *ast;
extern struct programs_list *handle;

const char *names[] = { 
    "Program", "Function", "Parameters", "Parameter", "Arguments", 
    "Integer", "Double", "Identifier", "Natural", "Decimal", 
    "Call", "If", "Add", "Sub", "Mul", "Div" 
};
%}

%option noyywrap

%X COMMENT

digit   [0-9]
letter  [a-zA-Z]

/* START rules section -- regular expressions for pattern matching */

%%

integer                     { return INTEGER; }
double                      { return DOUBLE; }
if                          { return IF; }
then                        { return THEN; }
else                        { return ELSE; }
{letter}({letter}|{digit})* { PASS_TOKEN(); return IDENTIFIER; }
{digit}+                    { PASS_TOKEN(); return NATURAL; }
{digit}*"."{digit}+         { PASS_TOKEN(); return DECIMAL; }

"/*"                        { BEGIN(COMMENT); }
<COMMENT>"*/"               { BEGIN(INITIAL); }
<COMMENT>\n|\r|\r\n         { lex_line++; lex_column = 1; }
<COMMENT>.                  {;}
<COMMENT><<EOF>>            { return 0; }

[\t ]+                      {;}
\n|\r|\r\n                  { lex_line++; lex_column = 1; }
[()=,*/+-]                  { return yytext[0]; }
.                           { yyerror("unrecognized character"); }
<<EOF>>                     { YY_USER_ACTION; return 0; }

%%

/* START subroutines section -- user functions */

void yyerror(char *error) {
    errors++;
    printf("Found %s '%s' (%d,%d)\n", error, yytext, syn_line, syn_column);
}


void show(struct node *no, int depth) {
    if (no == NULL) {
        return;
    }

    // Indentação
    for (int i = 0; i < 2 * depth; i++) {
        printf("_");
    }

    // Pega o nome da categoria com base no índice do enum
    const char *name = names[no->category];

    if (no->token != NULL) {
        // Substituímos %d por %s
        printf("%s(%s)\n", name, no->token);
    } else {
        printf("%s\n", name);
    }

    // Chamada recursiva para os filhos
    struct node_list *atual = no->children;
    while (atual != NULL) {
        show(atual->node, depth + 1);
        atual = atual->next;
    }
}


int main(int argc, char *argv[]) {

    // Podia estar numa funcao new_node
    handle = malloc( sizeof(struct programs_list) );
    handle->program = NULL;
    handle->next = NULL;


    yyparse();
    show(ast, 0);
    return 0;
}
