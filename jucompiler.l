%{
    /* place here any C variables and definitions */

    #include "y.tab.h"
    #include "ast.h"
    #include <string.h>

    int PrintMatch( char *word); 
    int incrementCol();
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

    extern struct node *ast;
    extern struct programs_list *handle;

    const char *names[] = { 
    "Program", "Function", "Parameters", "Parameter", "Arguments", 
    "Integer", "Double", "Identifier", "Natural", "Decimal", 
    "Call", "If", "Add", "Sub", "Mul", "Div" 
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


" " {incrementCol();}
\f {incrementCol();}
(\r\n|\n|\r) { colAtual = 1; linha ++;}
\t {incrementCol();}




"//"[^\n\r]*   {incrementCol();}

"/*"   {BEGIN(COMMENT); lineBackup = linha; colBackup = colAtual; incrementCol(); }
<COMMENT>(\r\n|\n|\r) {colAtual = 1; linha ++;}
<COMMENT>.  {incrementCol();}
<COMMENT><<EOF>> { if (printall || printerrors) printf("Line %d, col %d: unterminated comment\n", lineBackup, colBackup); BEGIN 0; }
<COMMENT>"*/" {BEGIN 0; incrementCol();}







\"                       { BEGIN(STRINGSTATE); lineBackup = linha; colBackup = colAtual; incrementCol(); flag = 0; indice = 0; string[0]= '\0';}   /* inicia string */


<STRINGSTATE>\\[nfrt\\"]      { copiarString(yytext); incrementCol(); }/*escapes validos (mais especificos)*/

<STRINGSTATE>\\[^nfrt\\"\n\r]?    { flag = 1; 
                            if(yytext[1] == '\n') { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (\\)\n", linha, colAtual); }
                            else { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, colAtual, yytext); }
                            incrementCol(); 
                         }/*escapes invalidos*/

<STRINGSTATE>(\r\n|\n|\r)   { BEGIN INITIAL; if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}/*newlines*/

<STRINGSTATE><<EOF>>          {BEGIN INITIAL;  if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}

<STRINGSTATE>\"               { BEGIN INITIAL; if (printall && flag == 0) printf("STRLIT(\"%s\")\n", string); incrementCol(); string[0] = '\0'; }/*fim da string*/

<STRINGSTATE>.     { copiarString(yytext); incrementCol(); }/*texto normal*/






"System.out.print" { incrementCol(); return PRINT; }
"Integer.parseInt"  { incrementCol();  return PARSEINT;}
".length"           {  incrementCol(); return DOTLENGTH;}

"++"  {  incrementCol(); }
"--"  {  incrementCol(); }
"=="  { incrementCol(); return EQ; }
"!="  { incrementCol(); return NE; }
">="  { incrementCol(); return GE; }
"<="  { incrementCol(); return LE; }
">>"  { incrementCol(); return RSHIFT; }
"<<"  { incrementCol(); return LSHIFT; }
"&&"  { incrementCol(); return AND; }
"||"  { incrementCol(); return OR; }
"->"  { incrementCol(); }

"="   { incrementCol(); return ASSIGN; }
">"   { incrementCol(); return GT; }
"<"   { incrementCol(); return LT; }
"+"   { incrementCol(); return PLUS; }
"-"   { incrementCol(); return MINUS; }
"*"   { incrementCol(); return STAR; }
"/"   { incrementCol(); return DIV; }
"%"   { incrementCol(); return MOD; }
"!"   { incrementCol(); return NOT; }
"^"   { incrementCol(); return XOR;}
","   { incrementCol(); return COMMA; }
";"   { incrementCol(); return SEMICOLON; }
"{"   { incrementCol(); return LBRACE; }
"}"   { incrementCol(); return RBRACE; }
"("   { incrementCol(); return LPAR; }
")"   { incrementCol(); return RPAR; }
"["   { incrementCol(); return LSQ; }
"]"   { incrementCol(); return RSQ; }

if       { incrementCol();  return IF; }
else     { incrementCol(); return ELSE; }
while    { incrementCol(); return WHILE; }
return   { incrementCol(); return RETURN;}
static   { incrementCol(); return STATIC; }
public   { incrementCol(); return PUBLIC; }
class    { incrementCol(); return CLASS; }
void     { incrementCol(); return VOID; }
int      { incrementCol(); return INT; }

integer  {incrementCol(); return INTEGER; }
double   {incrementCol(); return DOUBLE; }

boolean  { incrementCol(); return BOOL; }
String   { incrementCol(); return STRING; }

true     { incrementCol(); return BOOLLIT;}
false    { incrementCol(); return BOOLLIT;}
null     { incrementCol(); }

Integer  { incrementCol(); }
System   { incrementCol(); }

break      { incrementCol(); }
byte       { incrementCol(); }
case       {incrementCol(); }
catch      {incrementCol(); }
char       {  incrementCol(); }
const      {  incrementCol(); }
enum      { incrementCol(); }
extends    {  incrementCol(); }
final      {  incrementCol(); }
finally    {  incrementCol(); }
float      {  incrementCol(); }
for       { incrementCol(); }
implements { incrementCol(); }
import    { incrementCol(); }
instanceof {  incrementCol(); }
interface  {  incrementCol(); }
long       { incrementCol(); }
native     { incrementCol(); }
new        {  incrementCol(); }
protected  {  incrementCol(); }
short      {  incrementCol(); }
strictfp   { incrementCol(); }
super      {  incrementCol(); }
this       {  incrementCol(); }
throw      { incrementCol(); }
throws     { incrementCol(); }
transient  {  incrementCol(); }
try        {  incrementCol(); }
volatile   {  incrementCol(); }
abstract     {  incrementCol(); }
continue     {  incrementCol(); }
switch       {  incrementCol(); }
assert       {  incrementCol(); }
default      {  incrementCol(); }
package      { incrementCol(); }
synchronized {  incrementCol(); }
do           {  incrementCol(); }
goto         {  incrementCol(); }
private      { incrementCol(); }




{leter}({leter}|{digitWZero})* { 
    /*texto reconhecido para yylval.lexeme*/
PASS_TOKEN();
incrementCol();
return IDENTIFIER;
}



{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    /*DECIMAIS*/
    PASS_TOKEN();
    incrementCol();
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."  {
    PASS_TOKEN();
    incrementCol();
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?  {
    PASS_TOKEN();
    incrementCol();
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."({digitWZero}(({digitWZero}|_)*{digitWZero})?)?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    incrementCol();
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    incrementCol();
    return DECIMAL;
}


0|{digit}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    incrementCol();
    return NATURAL; 
}


. { if (printall || printerrors) printf("Line %d, col %d: illegal character (%s)\n",  linha, colAtual++, yytext); }



%%  

#include <stdio.h>

int incrementCol(){
    colAtual+= yyleng;
    return colAtual;
}

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

void yyerror(char *s){
    fprintf(stderr, "Syntax error: %s at line %d, col %d\n", s, linha, colAtual);
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

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l' && argv[1][2] == '\0') {
        printall = 1;
    } else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '1' && argv[1][3] == '\0') {
        printerrors = 1;
    } else {
        printerrors = 1;
    }
    //yylex();    /* run the lexical analysis automaton */
    yyparse();
    show(ast, 0);
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}