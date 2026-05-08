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
    LT = 283,                      /* LT  */
    LE = 284,                      /* LE  */
    GT = 285,                      /* GT  */
    GE = 286,                      /* GE  */
    LSHIFT = 287,                  /* LSHIFT  */
    RSHIFT = 288,                  /* RSHIFT  */
    STAR = 289,                    /* STAR  */
    DIV = 290,                     /* DIV  */
    MOD = 291,                     /* MOD  */
    NOT = 292,                     /* NOT  */
    RESERVED = 293,                /* RESERVED  */
    IDENTIFIER = 294,              /* IDENTIFIER  */
    NATURAL = 295,                 /* NATURAL  */
    DECIMAL = 296,                 /* DECIMAL  */
    INTEGER = 297,                 /* INTEGER  */
    DOUBLE = 298,                  /* DOUBLE  */
    STRLIT = 299,                  /* STRLIT  */
    BOOLLIT = 300,                 /* BOOLLIT  */
    XOR = 301,                     /* XOR  */
    EQ = 302,                      /* EQ  */
    NE = 303,                      /* NE  */
    PLUS = 304,                    /* PLUS  */
    MINUS = 305,                   /* MINUS  */
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
#define LT 283
#define LE 284
#define GT 285
#define GE 286
#define LSHIFT 287
#define RSHIFT 288
#define STAR 289
#define DIV 290
#define MOD 291
#define NOT 292
#define RESERVED 293
#define IDENTIFIER 294
#define NATURAL 295
#define DECIMAL 296
#define INTEGER 297
#define DOUBLE 298
#define STRLIT 299
#define BOOLLIT 300
#define XOR 301
#define EQ 302
#define NE 303
#define PLUS 304
#define MINUS 305
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
