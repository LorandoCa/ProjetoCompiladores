%{
    /* place here any C variables and definitions */
    int PrintMatch( char *word); 
    int incrementCol();
    char* find_backslash_x(const char *str);
    
    int colAtual = 1;
    int linha = 1;
    int printall = 0;
    int lineBackup = 0, colBackup = 0;
%}

digit [1-9]
digitWZero [0-9]
leter [A-Za-z_$]
escape   \\[nfrt\\"]
except    [\r\n]
INTEGER integer
DOUBLE double
IF if 
THEN then
ELSE else


%X COMMENT

%%


" " {incrementCol();}

\n { colAtual = 1; linha ++;}

"//".*   {incrementCol();}

"/*"   {BEGIN(COMMENT); lineBackup = linha; colBackup = colAtual; incrementCol(); }
<COMMENT>.  {incrementCol();}
<COMMENT>"\n" {colAtual = 1; linha ++;}
<COMMENT><<EOF>> { printf("Line %d, col %d: unterminated comment\n", lineBackup, colBackup); BEGIN 0; }
<COMMENT>"*/" {BEGIN 0; incrementCol();}


\"[^\n\r"]*{except}|\"{escape}{except}  {int aux= colAtual; find_backslash_x(yytext); colAtual = aux; printf("Line %d, col %d: unterminated string literal\n", linha, colAtual); incrementCol();
                        if ( yytext[yyleng-1] == '\n'){ linha++; colAtual=1;} }

\"[^\\\"]*\\[^nfrt\\"\n\r].*\"  {find_backslash_x(yytext); }

\"([^\\\n\r\"]|{escape})*\" {if( printall) printf("STRLIT(%s)\n", yytext); incrementCol(); }


\t {;}

if      { if( printall) PrintMatch("IF"); incrementCol(); }
then    { if( printall) PrintMatch("THEN"); incrementCol(); }
else    { if( printall) PrintMatch("ELSE"); incrementCol(); }
integer { if( printall) PrintMatch("INTEGER"); incrementCol(); }
double  { if( printall) PrintMatch("DOUBLE"); incrementCol(); }

"("|")"|"*"|"+"|"-"|"/"|","|"=" {if( printall) printf ("%s\n", yytext); 
        colAtual= incrementCol() ;}


0|{digit}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("NATURAL(%s)\n", yytext ); incrementCol(); }

{digitWZero}(({digitWZero}|_)*{digitWZero})?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."{digitWZero}(({digitWZero}|_)*{digitWZero})?([eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})?)? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

({digitWZero}(({digitWZero}|_)*{digitWZero})?)?"."({digitWZero}(({digitWZero}|_)*{digitWZero})?)?[eE][+-]?{digitWZero}(({digitWZero}|_)*{digitWZero})? {if( printall) printf ("DECIMAL(%s)\n", yytext); incrementCol();}

{leter}+({leter}|{digit})* { if( printall) printf ("IDENTIFIER(%s)\n", yytext); incrementCol(); }

. { printf("Line %d, col %d: illegal character (%s)\n",  linha, colAtual++, yytext); }





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

char* find_backslash_x(const char *str) {
    if (!str) return NULL;

    while (*str) {
        if (str[0] == '\\' && (str[1] != 'n' && str[1] != 'f' && str[1] != 'r' && str[1] != 't' && str[1] != '\\' && str[1] != '"' ) ) {
            if (str[1] == '\n'){
                if( printall) printf("Line %d, col %d: invalid escape sequence (%.1s)\n", linha, colAtual, str);
            }
            else if( printall) printf("Line %d, col %d: invalid escape sequence (%.2s)\n", linha, colAtual, str);
        }
        str++;
        colAtual++;
    }
    return NULL;  // não encontrou
}


int main(int argc, char *argv[]) {

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l' && argv[1][2] == '\0') {
        printall = 1;
    }
    yylex();    /* run the lexical analysis automaton */
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}