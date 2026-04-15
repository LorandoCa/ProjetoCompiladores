%{
    /* place here any C variables and definitions */

    #include "y.tab.h"
    #include "ast1.h"
    #include <string.h>

    int PrintMatch( char *word); 
    void copiarString(const char origem);
    
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

"/*"   {BEGIN(COMMENT); lineBackup = syn_line; colBackup = syn_column;  }
<COMMENT>(\r\n|\n|\r) {colAtual = 1; linha ++;}
<COMMENT>.  {syn_column++;}
<COMMENT><<EOF>> { if (printall || printerrors) printf("Line %d, col %d: unterminated comment\n", lineBackup, colBackup); BEGIN 0; }
<COMMENT>"*/" {BEGIN 0; }







\"                       { BEGIN(STRINGSTATE); lineBackup = linha; colBackup = syn_column;  flag = 0; indice = 0; string[0]= '\0'; yymore();}   /* inicia string */


<STRINGSTATE>\\[nfrt\\"]      { copiarString(yytext[yyleng-1]);  }/*escapes validos (mais especificos)*/

<STRINGSTATE>\\[^nfrt\\"\n\r]?    { flag = 1; 
                            if(yytext[1] == '\n') { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (\\)\n", linha, syn_column); }
                            else { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, syn_column, yytext); }
                             
                         }/*escapes invalidos*/

<STRINGSTATE>(\r\n|\n|\r)   { BEGIN INITIAL; if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); 
                                colAtual = 1; linha ++; string[0] = '\0';
                                syn_column = colBackup;
                                syn_line = lineBackup;
                            }/*newlines*/

<STRINGSTATE><<EOF>>          {BEGIN INITIAL;  if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); 
                                syn_column = colBackup;
                                syn_line = lineBackup;
                                colAtual = 1; linha ++; string[0] = '\0';}

<STRINGSTATE>\" { 
    BEGIN INITIAL; 
    if (flag == 0) {
        if (printall) printf("STRLIT(\"%s\")\n", string);

        syn_column = colBackup;
        syn_line = lineBackup;

        yylval.lexeme = strdup(string); 

        return STRLIT; 
    } 
    string[0] = '\0'; 
}

<STRINGSTATE>.     { copiarString(yytext[yyleng-1]); yymore(); }/*texto normal*/





"System.out.print" { if (printall) PrintMatch("PRINT"); return PRINT; }
"Integer.parseInt"  { if (printall) PrintMatch("PARSEINT"); return PARSEINT;}
".length"           { if (printall) PrintMatch("DOTLENGTH"); return DOTLENGTH;}

"++"  { if (printall) PrintMatch("RESERVED(++)"); }
"--"  { if (printall) PrintMatch("RESERVED(--)"); }
"=="  { if (printall) PrintMatch("EQ"); return EQ; }
"!="  { if (printall) PrintMatch("NE"); return NE; }
">="  { if (printall) PrintMatch("GE"); return GE; }
"<="  { if (printall) PrintMatch("LE"); return LE; }
">>"  { if (printall) PrintMatch("RSHIFT"); return RSHIFT; }
"<<"  { if (printall) PrintMatch("LSHIFT"); return LSHIFT; }
"&&"  { if (printall) PrintMatch("AND"); return AND; }
"||"  { if (printall) PrintMatch("OR"); return OR; }
"->"  { if (printall) PrintMatch("ARROW"); }

"="   { if (printall) PrintMatch("ASSIGN"); return ASSIGN; }
">"   { if (printall) PrintMatch("GT"); return GT; }
"<"   { if (printall) PrintMatch("LT"); return LT; }
"+"   { if (printall) PrintMatch("PLUS"); return PLUS; }
"-"   { if (printall) PrintMatch("MINUS"); return MINUS; }
"*"   { if (printall) PrintMatch("STAR"); return STAR; }
"/"   { if (printall) PrintMatch("DIV"); return DIV; }
"%"   { if (printall) PrintMatch("MOD"); return MOD; }
"!"   { if (printall) PrintMatch("NOT"); return NOT; }
"^"   { if (printall) PrintMatch("XOR"); return XOR; }
","   { if (printall) PrintMatch("COMMA"); return COMMA; }
";"   { if (printall) PrintMatch("SEMICOLON"); return SEMICOLON; }
"{"   { if (printall) PrintMatch("LBRACE"); return LBRACE; }
"}"   { if (printall) PrintMatch("RBRACE"); return RBRACE; }
"("   { if (printall) PrintMatch("LPAR"); return LPAR; }
")"   { if (printall) PrintMatch("RPAR"); return RPAR; }
"["   { if (printall) PrintMatch("LSQ"); return LSQ; }
"]"   { if (printall) PrintMatch("RSQ"); return RSQ; }

if       { if (printall) PrintMatch("IF"); return IF; }
then     { if (printall) PrintMatch("THEN");  }
else     { if (printall) PrintMatch("ELSE"); return ELSE; }
while    { if (printall) PrintMatch("WHILE"); return WHILE; }
return   { if (printall) PrintMatch("RETURN"); return RETURN; }
static   { if (printall) PrintMatch("STATIC"); return STATIC; }
public   { if (printall) PrintMatch("PUBLIC"); return PUBLIC; }
class    { if (printall) PrintMatch("CLASS"); return CLASS; }
void     { if (printall) PrintMatch("VOID"); return VOID; }
int      { if (printall) PrintMatch("INT"); return INT; }
integer  { if (printall) PrintMatch("INTEGER"); return INTEGER; }
double   { if (printall) PrintMatch("DOUBLE"); return DOUBLE; }
boolean  { if (printall) PrintMatch("BOOL"); return BOOL; }
String   { if (printall) PrintMatch("STRING"); return STRING; }

true     { if (printall) PrintMatch("BOOLLIT(true)"); return BOOLLIT; }
false    { if (printall) PrintMatch("BOOLLIT(false)"); return BOOLLIT; }
null     { if (printall) PrintMatch("RESERVED(null)"); } 

Integer  { if (printall) PrintMatch("RESERVED(Integer)");  }
System   { if (printall) PrintMatch("RESERVED(System)"); }

break      { if (printall) PrintMatch("RESERVED(break)"); }
byte       { if (printall) PrintMatch("RESERVED(byte)"); }
case       { if (printall) PrintMatch("RESERVED(case)"); }
catch      { if (printall) PrintMatch("RESERVED(catch)"); }
char       { if (printall) PrintMatch("RESERVED(char)"); }
const      { if (printall) PrintMatch("RESERVED(const)"); }
enum      { if (printall) PrintMatch("RESERVED(enum)"); }
extends    { if (printall) PrintMatch("RESERVED(extends)"); }
final      { if (printall) PrintMatch("RESERVED(final)"); }
finally    { if (printall) PrintMatch("RESERVED(finally)"); }
float      { if (printall) PrintMatch("RESERVED(float)"); }
for       { if (printall) PrintMatch("RESERVED(for)"); }
implements { if (printall) PrintMatch("RESERVED(implements)"); }
import    { if (printall) PrintMatch("RESERVED(import)"); }
instanceof { if (printall) PrintMatch("RESERVED(instanceof)"); }
interface  { if (printall) PrintMatch("RESERVED(interface)"); }
long       { if (printall) PrintMatch("RESERVED(long)"); }
native     { if (printall) PrintMatch("RESERVED(native)"); }
new        { if (printall) PrintMatch("RESERVED(new)"); }
protected  { if (printall) PrintMatch("RESERVED(protected)"); }
short      { if (printall) PrintMatch("RESERVED(short)"); }
strictfp   { if (printall) PrintMatch("RESERVED(strictfp)"); }
super      { if (printall) PrintMatch("RESERVED(super)"); }
this       { if (printall) PrintMatch("RESERVED(this)"); }
throw      { if (printall) PrintMatch("RESERVED(throw)"); }
throws     { if (printall) PrintMatch("RESERVED(throws)"); }
transient  { if (printall) PrintMatch("RESERVED(transient)"); }
try        { if (printall) PrintMatch("RESERVED(try)"); }
volatile   { if (printall) PrintMatch("RESERVED(volatile)"); }
abstract     { if (printall) PrintMatch("RESERVED(abstract)"); }
continue     { if (printall) PrintMatch("RESERVED(continue)"); }
switch       { if (printall) PrintMatch("RESERVED(switch)"); }
assert       { if (printall) PrintMatch("RESERVED(assert)"); }
default      { if (printall) PrintMatch("RESERVED(default)"); }
package      { if (printall) PrintMatch("RESERVED(package)"); }
synchronized { if (printall) PrintMatch("RESERVED(synchronized)");  }
do           { if (printall) PrintMatch("RESERVED(do)"); }
goto         { if (printall) PrintMatch("RESERVED(goto)"); }
private      { if (printall) PrintMatch("RESERVED(private)"); }



{leter}({leter}|{digitWZero})* { 
    /*texto reconhecido para yylval.lexeme*/
PASS_TOKEN();
if( printall) printf ("IDENTIFIER(%s)\n", yytext);
return IDENTIFIER;
}



{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    /*DECIMAIS*/
    PASS_TOKEN();
    if( printall) printf ("DECIMAL(%s)\n", yytext);
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."  {
    PASS_TOKEN();
    if( printall) printf ("DECIMAL(%s)\n", yytext);
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?  {
    PASS_TOKEN();
    if( printall) printf ("DECIMAL(%s)\n", yytext);
    return DECIMAL;
}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."({digitWZero}(({digitWZero}|_)*{digitWZero})?)?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    if( printall) printf ("DECIMAL(%s)\n", yytext);
    return DECIMAL;
}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    if( printall) printf ("DECIMAL(%s)\n", yytext);
    return DECIMAL;
}


0|{digit}(({digitWZero}|_)*{digitWZero})? {
    PASS_TOKEN();
    if( printall) printf ("NATURAL(%s)\n", yytext);
    return NATURAL; 
}


. { if (printall || printerrors) printf("Line %d, col %d: illegal character (%s)\n",  linha, syn_column, yytext); }



%%  

#include <stdio.h>


int PrintMatch(char *word){
    printf("%s\n", word);
    return 0;
}


void copiarString(const char origem) {
    string[indice] = origem;  // Copia caractere por caractere
    indice++;
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
        
    if(strcmp(name, "Args") != 0 && strcmp(name, "Dummy" ) != 0) {
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

    int printTree = 0;
    int syntatic_analisis = 0;

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l' && argv[1][2] == '\0') {
        printall = 1;
        syntatic_analisis = 1;
    } else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '1' && argv[1][3] == '\0') {
        printerrors = 1;
    }else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 't' && argv[1][2] == '\0'){
        printTree = 1;
    }else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '2' && argv[1][3] == '\0'){
        printerrors = 1;
    } else {
        printerrors = 1;
    }


    if (syntatic_analisis)
        yylex();    /* run the lexical analysis automaton */
    else
        yyparse();

    if(errors == 0 && printTree)
        show(ast, 0);
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}