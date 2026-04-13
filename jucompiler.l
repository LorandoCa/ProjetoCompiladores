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






"System.out.print" { if (printall) PrintMatch("PRINT"); incrementCol(); }
"Integer.parseInt"  { if (printall) PrintMatch("PARSEINT"); incrementCol(); }
".length"           { if (printall) PrintMatch("DOTLENGTH"); incrementCol(); }

"++"  { if (printall) PrintMatch("RESERVED(++)"); incrementCol(); }
"--"  { if (printall) PrintMatch("RESERVED(--)"); incrementCol(); }
"=="  { if (printall) PrintMatch("EQ"); incrementCol(); return EQ; }
"!="  { if (printall) PrintMatch("NE"); incrementCol(); return NE; }
">="  { if (printall) PrintMatch("GE"); incrementCol(); return GE; }
"<="  { if (printall) PrintMatch("LE"); incrementCol(); return LE; }
">>"  { if (printall) PrintMatch("RSHIFT"); incrementCol(); return RSHIFT; }
"<<"  { if (printall) PrintMatch("LSHIFT"); incrementCol(); return LSHIFT; }
"&&"  { if (printall) PrintMatch("AND"); incrementCol(); return AND; }
"||"  { if (printall) PrintMatch("OR"); incrementCol(); return OR; }
"->"  { if (printall) PrintMatch("ARROW"); incrementCol(); }

"="   { if (printall) PrintMatch("ASSIGN"); incrementCol(); return ASSIGN; }
">"   { if (printall) PrintMatch("GT"); incrementCol(); return GT; }
"<"   { if (printall) PrintMatch("LT"); incrementCol(); return LT; }
"+"   { if (printall) PrintMatch("PLUS"); incrementCol(); return PLUS; }
"-"   { if (printall) PrintMatch("MINUS"); incrementCol(); return MINUS; }
"*"   { if (printall) PrintMatch("STAR"); incrementCol(); return STAR; }
"/"   { if (printall) PrintMatch("DIV"); incrementCol(); return DIV; }
"%"   { if (printall) PrintMatch("MOD"); incrementCol(); return MOD; }
"!"   { if (printall) PrintMatch("NOT"); incrementCol(); return NOT; }
"^"   { if (printall) PrintMatch("XOR"); incrementCol(); return XOR;}
","   { if (printall) PrintMatch("COMMA"); incrementCol(); return COMMA; }
";"   { if (printall) PrintMatch("SEMICOLON"); incrementCol(); return SEMICOLON; }
"{"   { if (printall) PrintMatch("LBRACE"); incrementCol(); return LBRACE; }
"}"   { if (printall) PrintMatch("RBRACE"); incrementCol(); return RBRACE; }
"("   { if (printall) PrintMatch("LPAR"); incrementCol(); return LPAR; }
")"   { if (printall) PrintMatch("RPAR"); incrementCol(); return RPAR; }
"["   { if (printall) PrintMatch("LSQ"); incrementCol(); return LSQ; }
"]"   { if (printall) PrintMatch("RSQ"); incrementCol(); return RSQ; }

if       { if (printall) PrintMatch("IF"); incrementCol();  return IF; }
else     { if (printall) PrintMatch("ELSE"); incrementCol(); return ELSE; }
while    { if (printall) PrintMatch("WHILE"); incrementCol(); return WHILE; }
return   { if (printall) PrintMatch("RETURN"); incrementCol(); return RETURN;}
static   { if (printall) PrintMatch("STATIC"); incrementCol(); return STATIC; }
public   { if (printall) PrintMatch("PUBLIC"); incrementCol(); return PUBLIC; }
class    { if (printall) PrintMatch("CLASS"); incrementCol(); return CLASS; }
void     { if (printall) PrintMatch("VOID"); incrementCol(); return VOID; }
int      { if (printall) PrintMatch("INT"); incrementCol(); return INT; }

integer  {incrementCol(); PrintMatch("INTEGER"); return INTEGER; }
double   {incrementCol();  PrintMatch("DOUBLE"); return DOUBLE; }

boolean  { if (printall) PrintMatch("BOOL"); incrementCol(); return BOOL; }
String   { if (printall) PrintMatch("STRING"); incrementCol(); return STRING; }

true     { if (printall) PrintMatch("BOOLLIT(true)"); incrementCol(); return BOOLLIT;}
false    { if (printall) PrintMatch("BOOLLIT(false)"); incrementCol(); return BOOLLIT;}
null     { if (printall) PrintMatch("RESERVED"); incrementCol(); }

Integer  { if (printall) PrintMatch("RESERVED(Integer)"); incrementCol(); }
System   { if (printall) PrintMatch("RESERVED(System)"); incrementCol(); }

break      { if (printall) PrintMatch("RESERVED(break)"); incrementCol(); }
byte       { if (printall) PrintMatch("RESERVED(byte)"); incrementCol(); }
case       { if (printall) PrintMatch("RESERVED(case)"); incrementCol(); }
catch      { if (printall) PrintMatch("RESERVED(catch)"); incrementCol(); }
char       { if (printall) PrintMatch("RESERVED(char)"); incrementCol(); }
const      { if (printall) PrintMatch("RESERVED(const)"); incrementCol(); }
enum      { if (printall) PrintMatch("RESERVED(enum)"); incrementCol(); }
extends    { if (printall) PrintMatch("RESERVED(extends)"); incrementCol(); }
final      { if (printall) PrintMatch("RESERVED(final)"); incrementCol(); }
finally    { if (printall) PrintMatch("RESERVED(finally)"); incrementCol(); }
float      { if (printall) PrintMatch("RESERVED(float)"); incrementCol(); }
for       { if (printall) PrintMatch("RESERVED(for)"); incrementCol(); }
implements { if (printall) PrintMatch("RESERVED(implements)"); incrementCol(); }
import    { if (printall) PrintMatch("RESERVED(import)"); incrementCol(); }
instanceof { if (printall) PrintMatch("RESERVED(instanceof)"); incrementCol(); }
interface  { if (printall) PrintMatch("RESERVED(interface)"); incrementCol(); }
long       { if (printall) PrintMatch("RESERVED(long)"); incrementCol(); }
native     { if (printall) PrintMatch("RESERVED(native)"); incrementCol(); }
new        { if (printall) PrintMatch("RESERVED(new)"); incrementCol(); }
protected  { if (printall) PrintMatch("RESERVED(protected)"); incrementCol(); }
short      { if (printall) PrintMatch("RESERVED(short)"); incrementCol(); }
strictfp   { if (printall) PrintMatch("RESERVED(strictfp)"); incrementCol(); }
super      { if (printall) PrintMatch("RESERVED(super)"); incrementCol(); }
this       { if (printall) PrintMatch("RESERVED(this)"); incrementCol(); }
throw      { if (printall) PrintMatch("RESERVED(throw)"); incrementCol(); }
throws     { if (printall) PrintMatch("RESERVED(throws)"); incrementCol(); }
transient  { if (printall) PrintMatch("RESERVED(transient)"); incrementCol(); }
try        { if (printall) PrintMatch("RESERVED(try)"); incrementCol(); }
volatile   { if (printall) PrintMatch("RESERVED(volatile)"); incrementCol(); }
abstract     { if (printall) PrintMatch("RESERVED(abstract)"); incrementCol(); }
continue     { if (printall) PrintMatch("RESERVED(continue)"); incrementCol(); }
switch       { if (printall) PrintMatch("RESERVED(switch)"); incrementCol(); }
assert       { if (printall) PrintMatch("RESERVED(assert)"); incrementCol(); }
default      { if (printall) PrintMatch("RESERVED(default)"); incrementCol(); }
package      { if (printall) PrintMatch("RESERVED(package)"); incrementCol(); }
synchronized { if (printall) PrintMatch("RESERVED(synchronized)"); incrementCol(); }
do           { if (printall) PrintMatch("RESERVED(do)"); incrementCol(); }
goto         { if (printall) PrintMatch("RESERVED(goto)"); incrementCol(); }
private      { if (printall) PrintMatch("RESERVED(private)"); incrementCol(); }




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