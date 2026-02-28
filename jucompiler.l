%{
    /* place here any C variables and definitions */
    int PrintMatch( char *word); 
    int incrementCol();
    char* find_backslash_x(const char *str);
    
    int colAtual = 1;
    int linha = 1;
%}

digit [0-9]
leter [A-Za-z]
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

"/*"   {BEGIN(COMMENT); incrementCol(); }
<COMMENT>.  {incrementCol();}
<COMMENT>"\n" {colAtual = 1; linha ++;}
<COMMENT>"*/" {BEGIN 0; incrementCol();}


\"[^\n\r"]*{except}|\"{escape}{except}  {printf("Line %d, column %d: unterminated string literal\n", linha, colAtual); incrementCol();
                        if ( yytext[yyleng-1] == '\n'){ linha++; colAtual=1;} }

\"[^\\]*\\[^nfrt\\"].*\"  {find_backslash_x(yytext);  }

\"[^\n\r]*\" {printf("STRLIT(%s)\n", yytext); incrementCol(); }



\t {;}

if      { PrintMatch("IF"); incrementCol(); }
then    { PrintMatch("THEN"); incrementCol(); }
else    { PrintMatch("ELSE"); incrementCol(); }
integer { PrintMatch("INTEGER"); incrementCol(); }
double  { PrintMatch("DOUBLE"); incrementCol(); }

"("|")"|"*"|"+"|"-"|"/"|","|"=" { printf ("%s\n", yytext); 
        colAtual= incrementCol() ;}

{digit}+ {printf ("NATURAL(%s)\n", yytext ); incrementCol(); }

{digit}*"."{digit}+ {printf ("DECIMAL(%s)\n", yytext); incrementCol();}

{leter}+({leter}|{digit})* { printf ("IDENTIFIER(%s)\n", yytext); incrementCol(); }

. { printf("Line %d, column %d: unrecognized character (%s)\n",  linha, colAtual++, yytext); }





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
            printf("Line %d, column %d: invalid escape sequence (%.2s)\n", linha, colAtual, str);
        }
        str++;
        colAtual++;
    }
    return NULL;  // não encontrou
}


int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}