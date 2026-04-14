%{
    /* place here any C variables and definitions */

    #include "y.tab.h"
    #include "ast1.h"
    #include <string.h>

    int PrintMatch( char *word); 
    void copiarString(const char *origem);
    
    /*igual ao petit.l:
    guardar o lexema reconhecido em yyval */
    #define PASS_TOKEN() yylval.lexeme = strdup(yytext)



    int yyparse(void);
    void yyerror(char *);

    int colAtual = 1;
    int linha = 1;
    int printall = 0;
    int printerrors = 0;
    int lineBackup = 0, colBackup = 0;
    char string[1024];
    int indice = 0, flag = 0;
    
    int syn_line = -1, syn_column = -1;
    int errors = 0;

    #define YY_USER_ACTION { syn_line = linha; syn_column = colAtual; colAtual += yyleng; }


    extern struct node *ast;
    extern struct programs_list *handle;

static const char *category_names[] = {
    /* Nó raiz */
    "Program",

    /* Declarações */
    "FieldDecl",
    "VarDecl",

    /* Métodos */
    "MethodDecl",
    "MethodHeader",
    "MethodParams",
    "ParamDecl",
    "MethodBody",
    "Args",
    "Dummy", //Added to store nodes that had errors

    /* Statements */
    "Block",
    "If",
    "While",
    "Return",
    "Call",
    "Print",
    "ParseArgs",
    "Assign",

    /* Operadores binários */
    "Or",
    "And",
    "Eq",
    "Ne",
    "Lt",
    "Gt",
    "Le",
    "Ge",
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Mod",
    "Lshift",
    "Rshift",
    "Xor",

    /* Operadores unários */
    "Not",
    "Minus",
    "Plus",

    /* Outros operadores */
    "Length",

    /* Tipos */
    "Bool",
    "Int",
    "Double",
    "Void",
    "StringArray",

    /* Terminais / Literais */
    "Boollit",
    "Decimal",
    "Natural",
    "Strlit",
    "Identifier",
};


%}

digit [1-9]
digitWZero [0-9]
leter [A-Za-z_$]
escape   \\[nfrt\\"]
except    [\r\n]
IF if 
THEN then
ELSE else


%X COMMENT STRINGSTATE
%%


" " {}
\f {}
(\r\n|\n|\r) { colAtual = 1; linha ++;}
\t {}




"//"[^\n\r]*   {}

"/*"   {BEGIN(COMMENT); lineBackup = linha; colBackup = colAtual;  }
<COMMENT>(\r\n|\n|\r) {colAtual = 1; linha ++;}
<COMMENT>.  {}
<COMMENT><<EOF>> { if (printall || printerrors) printf("Line %d, col %d: unterminated comment\n", lineBackup, colBackup); BEGIN 0; }
<COMMENT>"*/" {BEGIN 0; }







\"                       { BEGIN(STRINGSTATE); lineBackup = linha; colBackup = syn_column;  flag = 0; indice = 0; string[0]= '\0'; yymore();}   /* inicia string */


<STRINGSTATE>\\[nfrt\\"]      { copiarString(yytext);  }/*escapes validos (mais especificos)*/

<STRINGSTATE>\\[^nfrt\\"\n\r]?    { flag = 1; 
                            if(yytext[1] == '\n') { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (\\)\n", linha, syn_column); }
                            else { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, syn_column, yytext); }
                             
                         }/*escapes invalidos*/

<STRINGSTATE>(\r\n|\n|\r)   { BEGIN INITIAL; if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}/*newlines*/

<STRINGSTATE><<EOF>>          {BEGIN INITIAL;  if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}

<STRINGSTATE>\" { 
    BEGIN INITIAL; 
    if (flag == 0) {
        if (printall) printf("STRLIT(\"%s\")\n", string);

        syn_column = colBackup;

        yylval.lexeme = strdup(string); 

        return STRLIT; 
    } 
    string[0] = '\0'; 
}

<STRINGSTATE>.     { copiarString(yytext); yymore(); }/*texto normal*/






"System.out.print" {  return PRINT; }
"Integer.parseInt"  {   return PARSEINT;}
".length"           {   return DOTLENGTH;}

"++"  {   }
"--"  {   }
"=="  {  return EQ; }
"!="  {  return NE; }
">="  {  return GE; }
"<="  {  return LE; }
">>"  {  return RSHIFT; }
"<<"  {  return LSHIFT; }
"&&"  {  return AND; }
"||"  {  return OR; }
"->"  {  }

"="   {  return ASSIGN; }
">"   {  return GT; }
"<"   {  return LT; }
"+"   {  return PLUS; }
"-"   {  return MINUS; }
"*"   {  return STAR; }
"/"   {  return DIV; }
"%"   {  return MOD; }
"!"   {  return NOT; }
"^"   {  return XOR;}
","   {  return COMMA; }
";"   {  return SEMICOLON; }
"{"   {  return LBRACE; }
"}"   {  return RBRACE; }
"("   {  return LPAR; }
")"   {  return RPAR; }
"["   {  return LSQ; }
"]"   {  return RSQ; }

if       {   return IF; }
else     {  return ELSE; }
while    {  return WHILE; }
return   {  return RETURN;}
static   {  return STATIC; }
public   {  return PUBLIC; }
class    {  return CLASS; }
void     {  return VOID; }
int      {  return INT; }

integer  { return INTEGER; }
double   { return DOUBLE; }

boolean  {  return BOOL; }
String   {  return STRING; }

true     {  return BOOLLIT;}
false    {  return BOOLLIT;}
null     {  }

Integer  {  }
System   {  }

break      {  }
byte       {  }
case       { }
catch      { }
char       {   }
const      {   }
enum      {  }
extends    {   }
final      {   }
finally    {   }
float      {   }
for       {  }
implements {  }
import    {  }
instanceof {   }
interface  {   }
long       {  }
native     {  }
new        {   }
protected  {   }
short      {   }
strictfp   {  }
super      {   }
this       {   }
throw      {  }
throws     {  }
transient  {   }
try        {   }
volatile   {   }
abstract     {   }
continue     {   }
switch       {   }
assert       {   }
default      {   }
package      {  }
synchronized {   }
do           {   }
goto         {   }
private      {  }




{leter}({leter}|{digitWZero})* { 
    /*texto reconhecido para yylval.lexeme*/
PASS_TOKEN();

return IDENTIFIER;
}



{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    /*DECIMAIS*/
    PASS_TOKEN();
    
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."  {
    PASS_TOKEN();
    
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?  {
    PASS_TOKEN();
    
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."({digitWZero}(({digitWZero}|_)*{digitWZero})?)?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    
    return DECIMAL;
}


0|{digit}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    
    return NATURAL; 
}


. { if (printall || printerrors) printf("Line %d, col %d: illegal character (%s)\n",  linha, syn_column, yytext); }



%%  

#include <stdio.h>


int PrintMatch(char *word){
    printf("%s\n", word);
    return 0;
}


void copiarString(const char *origem) {
    int i = 0;
    while (yytext[i] != '\0') {  // Enquanto não chegar ao fim da string
        string[indice] = yytext[i];  // Copia caractere por caractere
        i++;
        indice++;
    }
    string[indice] = '\0'; // Adiciona o terminador de string
}

void yyerror (char *s) {
    printf ("Line %d, col %d: %s: %s\n", syn_line, syn_column, s, yytext);
    errors++;
}

void show(struct node *no, int depth) {
    if (no == NULL) {
        return;
    }

    // Pega o nome da categoria com base no índice do enum
    const char *name = category_names[no->category];
        
    if(strcmp(name, "Args") != 0 ) {
        // Indentação
        for (int i = 0; i < 2 * depth; i++) {
            printf(".");
        }

    
        depth = depth + 1;
        if ( (no->token != NULL) ) {
            // Substituímos %d por %s
            printf("%s(%s)\n", name, no->token);
        } else {
            printf("%s\n", name);
        }
    }

    // Chamada recursiva para os filhos
    struct node_list *atual = no->children;
    while (atual != NULL) {
        show(atual->node, depth);
        atual = atual->next;
    }
}



int main(int argc, char *argv[]) {

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l' && argv[1][2] == '\0') {
        printall = 1;
    } else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '1' && argv[1][3] == '\0') {
        printerrors = 1;
    } else {
        printerrors = 1;
    }

    //yylex();    /* run the lexical analysis automaton */

    yyparse();

    if(errors == 0)
        show(ast, 0);
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}