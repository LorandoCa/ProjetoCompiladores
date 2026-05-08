%{
    /* Lorando Ca e Augusto Hunguana */
    /* place here any C variables and definitions */
    int PrintMatch( char *word); 
    int incrementCol();
    void copiarString(const char *origem);
    
    int colAtual = 1;
    int linha = 1;
    int printall = 0;
    int printerrors = 0;
    int lineBackup = 0, colBackup = 0;
    char string[1024];
    int indice = 0, flag = 0;
%}

digit [1-9]
digitWZero [0-9]
leter [A-Za-z_$]
escape   \\[nfrt\\"]
except    [\r\n]
IF if 
THEN then
ELSE else


%X COMMENT STRING
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







\"                       { BEGIN(STRING); lineBackup = linha; colBackup = colAtual; incrementCol(); flag = 0; indice = 0; string[0]= '\0';}   /* inicia string */


<STRING>\\[nfrt\\"]      { copiarString(yytext); incrementCol(); }/*escapes validos (mais especificos)*/

<STRING>\\[^nfrt\\"\n\r]?    { flag = 1; 
                            if(yytext[1] == '\n') { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (\\)\n", linha, colAtual); }
                            else { if (printall || printerrors) printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, colAtual, yytext); }
                            incrementCol(); 
                         }/*escapes invalidos*/

<STRING>(\r\n|\n|\r)   { BEGIN INITIAL; if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}/*newlines*/

<STRING><<EOF>>          {BEGIN INITIAL;  if (printall || printerrors) printf("Line %d, col %d: unterminated string literal\n", lineBackup, colBackup); colAtual = 1; linha ++; string[0] = '\0';}

<STRING>\"               { BEGIN INITIAL; if (printall && flag == 0) printf("STRLIT(\"%s\")\n", string); incrementCol(); string[0] = '\0'; }/*fim da string*/

<STRING>.     { copiarString(yytext); incrementCol(); }/*texto normal*/






"System.out.print" { if (printall) PrintMatch("PRINT"); incrementCol(); }
"Integer.parseInt"  { if (printall) PrintMatch("PARSEINT"); incrementCol(); }
".length"           { if (printall) PrintMatch("DOTLENGTH"); incrementCol(); }

"++"  { if (printall) PrintMatch("RESERVED(++)"); incrementCol(); }
"--"  { if (printall) PrintMatch("RESERVED(--)"); incrementCol(); }
"=="  { if (printall) PrintMatch("EQ"); incrementCol(); }
"!="  { if (printall) PrintMatch("NE"); incrementCol(); }
">="  { if (printall) PrintMatch("GE"); incrementCol(); }
"<="  { if (printall) PrintMatch("LE"); incrementCol(); }
">>"  { if (printall) PrintMatch("RSHIFT"); incrementCol(); }
"<<"  { if (printall) PrintMatch("LSHIFT"); incrementCol(); }
"&&"  { if (printall) PrintMatch("AND"); incrementCol(); }
"||"  { if (printall) PrintMatch("OR"); incrementCol(); }
"->"  { if (printall) PrintMatch("ARROW"); incrementCol(); }

"="   { if (printall) PrintMatch("ASSIGN"); incrementCol(); }
">"   { if (printall) PrintMatch("GT"); incrementCol(); }
"<"   { if (printall) PrintMatch("LT"); incrementCol(); }
"+"   { if (printall) PrintMatch("PLUS"); incrementCol(); }
"-"   { if (printall) PrintMatch("MINUS"); incrementCol(); }
"*"   { if (printall) PrintMatch("STAR"); incrementCol(); }
"/"   { if (printall) PrintMatch("DIV"); incrementCol(); }
"%"   { if (printall) PrintMatch("MOD"); incrementCol(); }
"!"   { if (printall) PrintMatch("NOT"); incrementCol(); }
"^"   { if (printall) PrintMatch("XOR"); incrementCol(); }
","   { if (printall) PrintMatch("COMMA"); incrementCol(); }
";"   { if (printall) PrintMatch("SEMICOLON"); incrementCol(); }
"{"   { if (printall) PrintMatch("LBRACE"); incrementCol(); }
"}"   { if (printall) PrintMatch("RBRACE"); incrementCol(); }
"("   { if (printall) PrintMatch("LPAR"); incrementCol(); }
")"   { if (printall) PrintMatch("RPAR"); incrementCol(); }
"["   { if (printall) PrintMatch("LSQ"); incrementCol(); }
"]"   { if (printall) PrintMatch("RSQ"); incrementCol(); }

if       { if (printall) PrintMatch("IF"); incrementCol(); }
else     { if (printall) PrintMatch("ELSE"); incrementCol(); }
while    { if (printall) PrintMatch("WHILE"); incrementCol(); }
return   { if (printall) PrintMatch("RETURN"); incrementCol(); }
static   { if (printall) PrintMatch("STATIC"); incrementCol(); }
public   { if (printall) PrintMatch("PUBLIC"); incrementCol(); }
class    { if (printall) PrintMatch("CLASS"); incrementCol(); }
void     { if (printall) PrintMatch("VOID"); incrementCol(); }
int      { if (printall) PrintMatch("INT"); incrementCol(); }
double   { if (printall) PrintMatch("DOUBLE"); incrementCol(); }
boolean  { if (printall) PrintMatch("BOOL"); incrementCol(); }
String   { if (printall) PrintMatch("STRING"); incrementCol(); }

true     { if (printall) PrintMatch("BOOLLIT(true)"); incrementCol(); }
false    { if (printall) PrintMatch("BOOLLIT(false)"); incrementCol(); }
null     { if (printall) PrintMatch("RESERVED(null)"); incrementCol(); }

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



{leter}({leter}|{digitWZero})* { if( printall) printf ("IDENTIFIER(%s)\n", yytext); incrementCol(); }



{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."  {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?  {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

{digitWZero}(({digitWZero}|_)*{digitWZero})?"."({digitWZero}(({digitWZero}|_)*{digitWZero})?)?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}


0|{digit}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("NATURAL(%s)\n", yytext ); incrementCol(); }


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



int main(int argc, char *argv[]) {

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l' && argv[1][2] == '\0') {
        printall = 1;
    } else if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == '1' && argv[1][3] == '\0') {
        printerrors = 1;
    } else {
        printerrors = 1;
    }
    yylex();    /* run the lexical analysis automaton */
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}