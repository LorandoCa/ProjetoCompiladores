%{

    /* Lorando Ca e Augusto Hunguana */

    /* place here any C variables and definitions */

    #include "y.tab.h"
    #include "ast1.h"
    #include <string.h>

    int PrintMatch( char *word); 
    void copiarString(char origem);
    
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
    char buffer[1024 + 3];
    int indice = 0, flag = 0;
    
    int syn_line = -1, syn_column = -1;
    int errors = 0;

    #define YY_USER_ACTION { \
        syn_line = linha; \
        syn_column = colAtual; \
        if(YYSTATE == INITIAL) colAtual += yyleng; \
        yylloc.first_line = syn_line; \
        yylloc.first_column = syn_column; 
    }

    extern struct node *ast;

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
    "BoolLit",
    "Decimal",
    "Natural",
    "StrLit",
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
<COMMENT>.  {colAtual += yyleng;}
<COMMENT><<EOF>> { if (printall || printerrors) printf("Line %d, col %d: unterminated comment\n", lineBackup, colBackup); 
                    syn_line = linha;     
                    syn_column = colAtual;
                    BEGIN 0; 
                 }
<COMMENT>"*/" {
                colAtual += yyleng; 
                syn_line = linha;     
                syn_column = colAtual;
                BEGIN 0;    }







\"                       { BEGIN(STRINGSTATE); lineBackup = linha; colBackup = syn_column;  flag = 0; indice = 0; string[0]= '\0';}   /* inicia string */


<STRINGSTATE>\\[nfrt\\"]      { char esc = yytext[yyleng - 1];
                                string[indice++] = '\\';
                                string[indice++] = esc;
                                string[indice] = '\0';
                                colAtual += 2; }/*escapes validos (mais especificos)*/

<STRINGSTATE>\\[^nfrt\\"\n\r]?    { flag = 1; 
                            if(yytext[yyleng-1] == '\\') { 
                                if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (\\)\n", linha, syn_column); 
                                colAtual += 1;
                            } else { 
                                if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, syn_column, yytext); 
                                colAtual += 2;
                            }
                            
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
    colAtual++;
    BEGIN INITIAL; 
    if (flag == 0) {
        buffer[0] = '\0';
        sprintf(buffer, "\"%s\"", string);

        if (printall) printf("STRLIT(%s)\n", buffer);

        syn_column = colBackup;
        syn_line = lineBackup;

        // Passar a string já com aspas para o yylval
        yylval.lexeme = strdup(buffer); 
        yytext = buffer;
        return STRLIT; 
    } 
    string[0] = '\0'; 
}

<STRINGSTATE>.     { copiarString(yytext[0]);  colAtual++;}/*texto normal*/






"System.out.print" { if (printall) PrintMatch("PRINT"); return PRINT; }
"Integer.parseInt"  { if (printall) PrintMatch("PARSEINT"); return PARSEINT;}
".length"           { if (printall) PrintMatch("DOTLENGTH"); return DOTLENGTH;}

"++"  { if (printall) PrintMatch("RESERVED(++)"); return RESERVED; }
"--"  { if (printall) PrintMatch("RESERVED(--)"); return RESERVED; }
"=="  { if (printall) PrintMatch("EQ"); return EQ; }
"!="  { if (printall) PrintMatch("NE"); return NE; }
">="  { if (printall) PrintMatch("GE"); return GE; }
"<="  { if (printall) PrintMatch("LE"); return LE; }
">>"  { if (printall) PrintMatch("RSHIFT"); return RSHIFT; }
"<<"  { if (printall) PrintMatch("LSHIFT"); return LSHIFT; }
"&&"  { if (printall) PrintMatch("AND"); return AND; }
"||"  { if (printall) PrintMatch("OR"); return OR; }
"->"  { if (printall) PrintMatch("ARROW"); return RESERVED; }

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
else     { if (printall) PrintMatch("ELSE"); return ELSE; }
while    { if (printall) PrintMatch("WHILE"); return WHILE; }
return   { if (printall) PrintMatch("RETURN"); return RETURN; }
static   { if (printall) PrintMatch("STATIC"); return STATIC; }
public   { if (printall) PrintMatch("PUBLIC"); return PUBLIC; }
class    { if (printall) PrintMatch("CLASS"); return CLASS; }
void     { if (printall) PrintMatch("VOID"); return VOID; }
int      { if (printall) PrintMatch("INT"); return INT; }
double   { if (printall) PrintMatch("DOUBLE"); return DOUBLE; }
boolean  { if (printall) PrintMatch("BOOL"); return BOOL; }
String   { if (printall) PrintMatch("STRING"); return STRING; }

true     { if (printall) PrintMatch("BOOLLIT(true)"); PASS_TOKEN(); return BOOLLIT; }
false    { if (printall) PrintMatch("BOOLLIT(false)"); PASS_TOKEN(); return BOOLLIT; }
null     { if (printall) PrintMatch("RESERVED(null)"); return RESERVED; }

Integer  { if (printall) PrintMatch("RESERVED(Integer)"); return RESERVED; }
System   { if (printall) PrintMatch("RESERVED(System)"); return RESERVED; }

break      { if (printall) PrintMatch("RESERVED(break)"); return RESERVED; }
byte       { if (printall) PrintMatch("RESERVED(byte)"); return RESERVED; }
case       { if (printall) PrintMatch("RESERVED(case)"); return RESERVED; }
catch      { if (printall) PrintMatch("RESERVED(catch)"); return RESERVED; }
char       { if (printall) PrintMatch("RESERVED(char)"); return RESERVED; }
const      { if (printall) PrintMatch("RESERVED(const)"); return RESERVED; }
enum       { if (printall) PrintMatch("RESERVED(enum)"); return RESERVED; }
extends    { if (printall) PrintMatch("RESERVED(extends)"); return RESERVED; }
final      { if (printall) PrintMatch("RESERVED(final)"); return RESERVED; }
finally    { if (printall) PrintMatch("RESERVED(finally)"); return RESERVED; }
float      { if (printall) PrintMatch("RESERVED(float)"); return RESERVED; }
for        { if (printall) PrintMatch("RESERVED(for)"); return RESERVED; }
implements { if (printall) PrintMatch("RESERVED(implements)"); return RESERVED; }
import     { if (printall) PrintMatch("RESERVED(import)"); return RESERVED; }
instanceof { if (printall) PrintMatch("RESERVED(instanceof)"); return RESERVED; }
interface  { if (printall) PrintMatch("RESERVED(interface)"); return RESERVED; }
long       { if (printall) PrintMatch("RESERVED(long)"); return RESERVED; }
native     { if (printall) PrintMatch("RESERVED(native)"); return RESERVED; }
new        { if (printall) PrintMatch("RESERVED(new)"); return RESERVED; }
protected  { if (printall) PrintMatch("RESERVED(protected)"); return RESERVED; }
short      { if (printall) PrintMatch("RESERVED(short)"); return RESERVED; }
strictfp   { if (printall) PrintMatch("RESERVED(strictfp)"); return RESERVED; }
super      { if (printall) PrintMatch("RESERVED(super)"); return RESERVED; }
this       { if (printall) PrintMatch("RESERVED(this)"); return RESERVED; }
throw      { if (printall) PrintMatch("RESERVED(throw)"); return RESERVED; }
throws     { if (printall) PrintMatch("RESERVED(throws)"); return RESERVED; }
transient  { if (printall) PrintMatch("RESERVED(transient)"); return RESERVED; }
try        { if (printall) PrintMatch("RESERVED(try)"); return RESERVED; }
volatile   { if (printall) PrintMatch("RESERVED(volatile)"); return RESERVED; }
abstract     { if (printall) PrintMatch("RESERVED(abstract)"); return RESERVED; }
continue     { if (printall) PrintMatch("RESERVED(continue)"); return RESERVED; }
switch       { if (printall) PrintMatch("RESERVED(switch)"); return RESERVED; }
assert       { if (printall) PrintMatch("RESERVED(assert)"); return RESERVED; }
default      { if (printall) PrintMatch("RESERVED(default)"); return RESERVED; }
package      { if (printall) PrintMatch("RESERVED(package)"); return RESERVED; }
synchronized { if (printall) PrintMatch("RESERVED(synchronized)"); return RESERVED; }
do           { if (printall) PrintMatch("RESERVED(do)"); return RESERVED; }
goto         { if (printall) PrintMatch("RESERVED(goto)"); return RESERVED; }
private      { if (printall) PrintMatch("RESERVED(private)"); return RESERVED; }


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

<<EOF>>                     { YY_USER_ACTION; return 0; }



%%  

#include <stdio.h>


int PrintMatch(char *word){
    printf("%s\n", word);
    return 0;
}


void copiarString(char c) {
    // Em vez de guardar o caractere processado
    // guarda a representação textual original
    if(c == '\\') { string[indice++] = '\\'; string[indice++] = '\\'; }
    else if(c == '"') { string[indice++] = '\\'; string[indice++] = '"'; }
    else { string[indice++] = c; }
    string[indice] = '\0';
}

void yyerror (char *s) {
    printf ("Line %d, col %d: %s: %s\n", syn_line, syn_column, s, yytext);
    errors++;
}

void show(struct node *no, int depth) {
    if (no == NULL) return;

    const char *name = category_names[no->category];

    // 2. Proteção contra string nula
    if (name == NULL) name = "UNKNOWN";

    int next_depth = depth;

    // Só imprime e aumenta a profundidade se não for Args nem Dummy
    if(strcmp(name, "Args") != 0 && strcmp(name, "Dummy") != 0) {
        
        for (int i = 0; i < 2 * depth; i++) printf(".");

        if (no->token != NULL) {
            printf("%s(%s)\n", name, no->token);
        } else {
            printf("%s\n", name);
        }
        
        next_depth = depth + 1;
    }

    // Chamada recursiva sempre usa o próximo nível de profundidade calculado
    struct node_list *atual = no->children;
    while (atual != NULL) {
        show(atual->node, next_depth);
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
        syntatic_analisis = 1;
    }else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 't' && argv[1][2] == '\0'){
        printerrors = 1;
        printTree = 1;
    }else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '2' && argv[1][3] == '\0'){
        printerrors = 1;
    } else {
        printerrors = 1;
    }


    if (syntatic_analisis) {
        while (yylex() != 0);  /* 0 = EOF */
    }
    else
        yyparse();

    if(errors == 0 && printTree)
        show(ast, 0);
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}