/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CLASS = 258,                   /* CLASS  */
    LBRACE = 259,                  /* LBRACE  */
    RBRACE = 260,                  /* RBRACE  */
    PUBLIC = 261,                  /* PUBLIC  */
    STATIC = 262,                  /* STATIC  */
    SEMICOLON = 263,               /* SEMICOLON  */
    COMMA = 264,                   /* COMMA  */
    BOOL = 265,                    /* BOOL  */
    INT = 266,                     /* INT  */
    VOID = 267,                    /* VOID  */
    STRING = 268,                  /* STRING  */
    LPAR = 269,                    /* LPAR  */
    RPAR = 270,                    /* RPAR  */
    LSQ = 271,                     /* LSQ  */
    RSQ = 272,                     /* RSQ  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    RETURN = 276,                  /* RETURN  */
    PRINT = 277,                   /* PRINT  */
    PARSEINT = 278,                /* PARSEINT  */
    DOTLENGTH = 279,               /* DOTLENGTH  */
    ASSIGN = 280,                  /* ASSIGN  */
    OR = 281,                      /* OR  */
    AND = 282,                     /* AND  */
    XOR = 283,                     /* XOR  */
    EQ = 284,                      /* EQ  */
    NE = 285,                      /* NE  */
    LT = 286,                      /* LT  */
    LE = 287,                      /* LE  */
    GT = 288,                      /* GT  */
    GE = 289,                      /* GE  */
    LSHIFT = 290,                  /* LSHIFT  */
    RSHIFT = 291,                  /* RSHIFT  */
    PLUS = 292,                    /* PLUS  */
    MINUS = 293,                   /* MINUS  */
    STAR = 294,                    /* STAR  */
    DIV = 295,                     /* DIV  */
    MOD = 296,                     /* MOD  */
    NOT = 297,                     /* NOT  */
    RESERVED = 298,                /* RESERVED  */
    IDENTIFIER = 299,              /* IDENTIFIER  */
    NATURAL = 300,                 /* NATURAL  */
    DECIMAL = 301,                 /* DECIMAL  */
    INTEGER = 302,                 /* INTEGER  */
    DOUBLE = 303,                  /* DOUBLE  */
    STRLIT = 304,                  /* STRLIT  */
    BOOLLIT = 305,                 /* BOOLLIT  */
    WITHOUT_ELSE = 306             /* WITHOUT_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CLASS 258
#define LBRACE 259
#define RBRACE 260
#define PUBLIC 261
#define STATIC 262
#define SEMICOLON 263
#define COMMA 264
#define BOOL 265
#define INT 266
#define VOID 267
#define STRING 268
#define LPAR 269
#define RPAR 270
#define LSQ 271
#define RSQ 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define RETURN 276
#define PRINT 277
#define PARSEINT 278
#define DOTLENGTH 279
#define ASSIGN 280
#define OR 281
#define AND 282
#define XOR 283
#define EQ 284
#define NE 285
#define LT 286
#define LE 287
#define GT 288
#define GE 289
#define LSHIFT 290
#define RSHIFT 291
#define PLUS 292
#define MINUS 293
#define STAR 294
#define DIV 295
#define MOD 296
#define NOT 297
#define RESERVED 298
#define IDENTIFIER 299
#define NATURAL 300
#define DECIMAL 301
#define INTEGER 302
#define DOUBLE 303
#define STRLIT 304
#define BOOLLIT 305
#define WITHOUT_ELSE 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "jucompiler.y"

    char *lexeme;
    struct node *node;

#line 174 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
