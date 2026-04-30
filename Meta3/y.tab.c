/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "jucompiler.y"


#include <stdio.h>
#include "ast1.h"

int yylex(void);
void yyerror(char *);

struct programs_list *handle;
struct node *ast;


#line 84 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 244 "y.tab.c"

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
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_LBRACE = 4,                     /* LBRACE  */
  YYSYMBOL_RBRACE = 5,                     /* RBRACE  */
  YYSYMBOL_PUBLIC = 6,                     /* PUBLIC  */
  YYSYMBOL_STATIC = 7,                     /* STATIC  */
  YYSYMBOL_SEMICOLON = 8,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_BOOL = 10,                      /* BOOL  */
  YYSYMBOL_INT = 11,                       /* INT  */
  YYSYMBOL_VOID = 12,                      /* VOID  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_LPAR = 14,                      /* LPAR  */
  YYSYMBOL_RPAR = 15,                      /* RPAR  */
  YYSYMBOL_LSQ = 16,                       /* LSQ  */
  YYSYMBOL_RSQ = 17,                       /* RSQ  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_PRINT = 22,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 23,                  /* PARSEINT  */
  YYSYMBOL_DOTLENGTH = 24,                 /* DOTLENGTH  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_XOR = 28,                       /* XOR  */
  YYSYMBOL_EQ = 29,                        /* EQ  */
  YYSYMBOL_NE = 30,                        /* NE  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_GE = 34,                        /* GE  */
  YYSYMBOL_LSHIFT = 35,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 36,                    /* RSHIFT  */
  YYSYMBOL_PLUS = 37,                      /* PLUS  */
  YYSYMBOL_MINUS = 38,                     /* MINUS  */
  YYSYMBOL_STAR = 39,                      /* STAR  */
  YYSYMBOL_DIV = 40,                       /* DIV  */
  YYSYMBOL_MOD = 41,                       /* MOD  */
  YYSYMBOL_NOT = 42,                       /* NOT  */
  YYSYMBOL_RESERVED = 43,                  /* RESERVED  */
  YYSYMBOL_IDENTIFIER = 44,                /* IDENTIFIER  */
  YYSYMBOL_NATURAL = 45,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 46,                   /* DECIMAL  */
  YYSYMBOL_INTEGER = 47,                   /* INTEGER  */
  YYSYMBOL_DOUBLE = 48,                    /* DOUBLE  */
  YYSYMBOL_STRLIT = 49,                    /* STRLIT  */
  YYSYMBOL_BOOLLIT = 50,                   /* BOOLLIT  */
  YYSYMBOL_WITHOUT_ELSE = 51,              /* WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_program = 53,                   /* program  */
  YYSYMBOL_DeclList = 54,                  /* DeclList  */
  YYSYMBOL_MethodDecl = 55,                /* MethodDecl  */
  YYSYMBOL_FieldDecl = 56,                 /* FieldDecl  */
  YYSYMBOL_IdentList = 57,                 /* IdentList  */
  YYSYMBOL_IdentListVar = 58,              /* IdentListVar  */
  YYSYMBOL_Type = 59,                      /* Type  */
  YYSYMBOL_MethodHeader = 60,              /* MethodHeader  */
  YYSYMBOL_FormalParamOpt = 61,            /* FormalParamOpt  */
  YYSYMBOL_FormalParams = 62,              /* FormalParams  */
  YYSYMBOL_NormalParams = 63,              /* NormalParams  */
  YYSYMBOL_MethodBody = 64,                /* MethodBody  */
  YYSYMBOL_StmtOrVarList = 65,             /* StmtOrVarList  */
  YYSYMBOL_VarDecl = 66,                   /* VarDecl  */
  YYSYMBOL_Statement = 67,                 /* Statement  */
  YYSYMBOL_StmtList = 68,                  /* StmtList  */
  YYSYMBOL_IfStmt = 69,                    /* IfStmt  */
  YYSYMBOL_ExprOpt = 70,                   /* ExprOpt  */
  YYSYMBOL_ExprStmt = 71,                  /* ExprStmt  */
  YYSYMBOL_Expr = 72,                      /* Expr  */
  YYSYMBOL_AssignExpr = 73,                /* AssignExpr  */
  YYSYMBOL_OrExpr = 74,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 75,                   /* AndExpr  */
  YYSYMBOL_XorExpr = 76,                   /* XorExpr  */
  YYSYMBOL_EqExpr = 77,                    /* EqExpr  */
  YYSYMBOL_RelExpr = 78,                   /* RelExpr  */
  YYSYMBOL_ShiftExpr = 79,                 /* ShiftExpr  */
  YYSYMBOL_AddExpr = 80,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 81,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 82,                 /* UnaryExpr  */
  YYSYMBOL_PostfixExpr = 83,               /* PostfixExpr  */
  YYSYMBOL_ArgListOpt = 84,                /* ArgListOpt  */
  YYSYMBOL_ArgList = 85                    /* ArgList  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    52,    52,    61,    64,    89,    91,    95,   102,   107,
     110,   117,   124,   131,   138,   139,   140,   144,   154,   165,
     166,   169,   170,   181,   190,   200,   205,   209,   234,   238,
     245,   258,   260,   263,   269,   272,   274,   278,   284,   287,
     289,   293,   302,   313,   315,   319,   327,   328,   337,   348,
     350,   353,   361,   364,   368,   371,   375,   378,   382,   385,
     389,   393,   396,   400,   404,   408,   412,   416,   420,   424,
     427,   433,   439,   443,   449,   455,   459,   463,   466,   469,
     472,   475,   483,   492,   494,   502,   505,   507,   510,   513,
     516,   522,   523,   526,   528
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "LBRACE",
  "RBRACE", "PUBLIC", "STATIC", "SEMICOLON", "COMMA", "BOOL", "INT",
  "VOID", "STRING", "LPAR", "RPAR", "LSQ", "RSQ", "IF", "ELSE", "WHILE",
  "RETURN", "PRINT", "PARSEINT", "DOTLENGTH", "ASSIGN", "OR", "AND", "XOR",
  "EQ", "NE", "LT", "LE", "GT", "GE", "LSHIFT", "RSHIFT", "PLUS", "MINUS",
  "STAR", "DIV", "MOD", "NOT", "RESERVED", "IDENTIFIER", "NATURAL",
  "DECIMAL", "INTEGER", "DOUBLE", "STRLIT", "BOOLLIT", "WITHOUT_ELSE",
  "$accept", "program", "DeclList", "MethodDecl", "FieldDecl", "IdentList",
  "IdentListVar", "Type", "MethodHeader", "FormalParamOpt", "FormalParams",
  "NormalParams", "MethodBody", "StmtOrVarList", "VarDecl", "Statement",
  "StmtList", "IfStmt", "ExprOpt", "ExprStmt", "Expr", "AssignExpr",
  "OrExpr", "AndExpr", "XorExpr", "EqExpr", "RelExpr", "ShiftExpr",
  "AddExpr", "MulExpr", "UnaryExpr", "PostfixExpr", "ArgListOpt",
  "ArgList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-93)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      38,    10,    48,    54,   -61,   -61,   108,    78,   -61,    86,
     -61,   -61,   -61,   -61,    25,   -61,   -61,    55,   -61,    57,
     106,    98,   113,    -6,   -61,   -61,    81,    81,   -61,    63,
     114,   128,   102,   145,   -61,   142,   153,   -61,   159,   -61,
     -61,   -61,   156,   157,   119,   158,   162,    -2,   133,   -61,
     -61,   -61,   171,   166,   -61,   -61,    95,   -61,   -61,     6,
     119,   119,    58,   170,   136,   136,   136,    -5,   -61,   -61,
     -61,   177,   -61,   -61,   161,   164,   160,     2,   172,     3,
      46,    26,   -61,   -61,   103,   148,     7,   119,   -61,    89,
     -61,   149,   151,   -61,   -61,   184,   185,   186,   196,    12,
     119,     1,   -61,   -61,   -61,    32,   -61,   152,   -61,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   197,   198,   199,   201,   -61,
     202,   205,   -61,   -61,   174,   -61,   -61,    67,    67,   -61,
     -61,   204,   206,   208,   209,   -61,   164,   160,     2,   172,
     172,     3,     3,     3,     3,    46,    46,    26,    26,   -61,
     -61,   -61,   212,   213,   119,   -61,   -61,   119,   -61,   207,
     -61,   -61,   119,   -61,   -61,   -61,   -61,   210,   -61,    67,
     211,   214,   -61,   215,   -61,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     2,     0,
       5,     3,     4,     9,     0,    14,    15,     0,    16,     0,
       0,     0,    11,     0,    28,     7,    20,    20,     8,     0,
       0,     0,     0,     0,    19,    21,     0,    10,     0,    40,
      25,    32,     0,     0,    44,     0,     0,     0,     0,    27,
      26,    31,     0,     0,    23,    18,     0,    17,    38,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    88,    89,
      90,     0,    43,    49,    52,    54,    56,    58,    61,    66,
      69,    72,    76,    80,     0,     0,     0,     0,    13,     0,
      35,     0,     0,    30,    39,     0,     0,     0,     0,     0,
       0,    87,    79,    77,    78,     0,    81,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,    91,    47,    29,     0,    22,    24,     0,     0,    50,
      86,     0,     0,     0,     0,    51,    53,    55,    57,    59,
      60,    62,    63,    64,    65,    67,    68,    70,    71,    73,
      74,    75,     0,     0,     0,    46,    45,     0,    12,    42,
      33,    85,     0,    83,    82,    37,    36,     0,    94,     0,
       0,     0,    41,     0,    48,    84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,   -61,   -61,   -61,   -61,     4,   -61,   216,
     -61,   -61,   -61,   -61,   -61,   -58,   -61,   -61,   -61,   -61,
     -44,   118,   -61,   122,   123,   121,    18,    93,    20,    34,
     -60,   -61,   129,   -61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,    11,    12,    23,    89,    32,    20,    33,
      34,    35,    25,    30,    49,    50,    59,    51,    71,    52,
      98,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   130,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    94,    28,    29,   102,   103,   104,    38,   128,   105,
      39,    93,    86,   141,    41,   105,    95,    96,    19,   106,
     107,    62,   -92,    87,    42,   106,    43,    44,    45,    46,
      63,   112,   113,   143,    48,    15,    16,    17,   118,   119,
     126,     1,   129,   132,    64,    65,    62,   -92,     4,    66,
      47,    67,    68,    69,     3,    63,   142,    70,     5,    97,
      92,   129,   159,   160,   161,   122,   123,   124,    38,    64,
      65,    39,    62,    18,    66,    41,    67,    68,    69,   169,
     170,    63,    70,   120,   121,    42,    13,    43,    44,    45,
      46,    15,    16,    14,    31,    64,    65,   133,   134,    21,
      66,    22,    67,    68,    69,    15,    16,    37,    70,     7,
      24,    47,    26,     8,     9,    38,    10,    62,    39,    40,
     177,   182,    41,   178,    15,    16,    63,    27,   180,    18,
     149,   150,    42,    62,    43,    44,    45,    46,   155,   156,
      64,    65,    63,    18,    53,    66,    54,    67,    68,    69,
     100,    56,   125,    70,   157,   158,    64,    65,    47,    63,
      55,    66,    18,    67,    68,    69,   100,    58,    57,    70,
      60,    61,    84,    64,    65,    63,    85,    88,    66,    90,
     101,    68,    69,    91,    99,   108,    70,   109,   111,    64,
      65,   110,   127,   135,    66,   136,    67,    68,    69,   137,
     138,   139,    70,   114,   115,   116,   117,   151,   152,   153,
     154,   140,   162,   163,   167,   164,   165,   166,   168,   171,
     175,   176,   172,   173,   174,   145,   179,   181,   183,   184,
     185,   146,   148,   147,   144,     0,     0,     0,     0,     0,
       0,     0,     0,    36
};

static const yytype_int16 yycheck[] =
{
      44,    59,     8,     9,    64,    65,    66,     1,     1,    14,
       4,     5,    14,     1,     8,    14,    60,    61,    14,    24,
      25,    14,    15,    25,    18,    24,    20,    21,    22,    23,
      23,    29,    30,     1,    30,    10,    11,    12,    35,    36,
      84,     3,    86,    87,    37,    38,    14,    15,     0,    42,
      44,    44,    45,    46,    44,    23,    44,    50,     4,     1,
      56,   105,   122,   123,   124,    39,    40,    41,     1,    37,
      38,     4,    14,    48,    42,     8,    44,    45,    46,   137,
     138,    23,    50,    37,    38,    18,     8,    20,    21,    22,
      23,    10,    11,     7,    13,    37,    38,     8,     9,    44,
      42,    44,    44,    45,    46,    10,    11,    44,    50,     1,
       4,    44,    14,     5,     6,     1,     8,    14,     4,     5,
     164,   179,     8,   167,    10,    11,    23,    14,   172,    48,
     112,   113,    18,    14,    20,    21,    22,    23,   118,   119,
      37,    38,    23,    48,    16,    42,    44,    44,    45,    46,
      14,     9,    49,    50,   120,   121,    37,    38,    44,    23,
      15,    42,    48,    44,    45,    46,    14,     8,    15,    50,
      14,    14,    14,    37,    38,    23,    14,    44,    42,     8,
      44,    45,    46,    17,    14,     8,    50,    26,    28,    37,
      38,    27,    44,    44,    42,    44,    44,    45,    46,    15,
      15,    15,    50,    31,    32,    33,    34,   114,   115,   116,
     117,    15,    15,    15,     9,    16,    15,    15,    44,    15,
       8,     8,    16,    15,    15,   107,    19,    17,    17,    15,
      15,   109,   111,   110,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    53,    44,     0,     4,    54,     1,     5,     6,
       8,    55,    56,     8,     7,    10,    11,    12,    48,    59,
      60,    44,    44,    57,     4,    64,    14,    14,     8,     9,
      65,    13,    59,    61,    62,    63,    61,    44,     1,     4,
       5,     8,    18,    20,    21,    22,    23,    44,    59,    66,
      67,    69,    71,    16,    44,    15,     9,    15,     8,    68,
      14,    14,    14,    23,    37,    38,    42,    44,    45,    46,
      50,    70,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    14,    14,    14,    25,    44,    58,
       8,    17,    59,     5,    67,    72,    72,     1,    72,    14,
      14,    44,    82,    82,    82,    14,    24,    25,     8,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    49,    72,    44,     1,    72,
      84,    85,    72,     8,     9,    44,    44,    15,    15,    15,
      15,     1,    44,     1,    84,    73,    75,    76,    77,    78,
      78,    79,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    15,    15,    16,    15,    15,     9,    44,    67,
      67,    15,    16,    15,    15,     8,     8,    72,    72,    19,
      72,    17,    67,    17,    15,    15
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    65,    65,    65,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    78,    78,    78,    78,    78,    79,    79,    79,
      80,    80,    80,    81,    81,    81,    81,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    84,    84,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     2,     2,     0,     4,     5,     2,
       3,     1,     3,     1,     1,     1,     1,     5,     5,     1,
       0,     1,     4,     2,     4,     3,     2,     2,     0,     3,
       3,     1,     1,     5,     3,     2,     5,     5,     2,     2,
       0,     7,     5,     1,     0,     4,     4,     3,     7,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       1,     2,     4,     4,     7,     4,     3,     1,     1,     1,
       1,     1,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: CLASS IDENTIFIER LBRACE DeclList RBRACE  */
#line 53 "jucompiler.y"
                                    {   ast = (yyval.node) = (yyvsp[-1].node);
                                        struct node *aux = newnode(Identifier, (yyvsp[-3].lexeme));
                                        aux->line = (yylsp[-4]).first_line;
                                        aux->column = (yylsp[-4]).first_column;
                                        addFront((yyval.node), aux );
                                       }
#line 1581 "y.tab.c"
    break;

  case 3: /* DeclList: DeclList MethodDecl  */
#line 61 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      addchild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1588 "y.tab.c"
    break;

  case 4: /* DeclList: DeclList FieldDecl  */
#line 64 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node);
                                        struct node *aux = (yyvsp[0].node);
                                        int type = 9;
                                        if( (aux != NULL) && (aux->children != NULL) && (aux->children->node != NULL) ) type = aux->children->node->category; // nodes type
                                        if(type != 9 ){ // Not dummy 
                                            struct node_list *childrenList = aux->children->next;
                                            while ((childrenList != NULL) ) {
                                                if (childrenList->node != NULL) {
                                                    struct node *parent = newnode(FieldDecl, NULL);
                                                    struct node *newtype = newnode(type , NULL); // copia o tipo
                                                    struct node *newNode = newnode( childrenList->node->category, childrenList->node->token);

                                                    // Propaga line e column do nó original copiado
                                                    newNode->line   = childrenList->node->line;
                                                    newNode->column = childrenList->node->column;

                                                    addchild(parent, newtype);
                                                    addchild(parent, newNode );
                                                    addchild((yyval.node), parent);
                                                }
                                                childrenList = childrenList->next;
                                            }
                                        }
                                      }
#line 1617 "y.tab.c"
    break;

  case 5: /* DeclList: DeclList SEMICOLON  */
#line 89 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1623 "y.tab.c"
    break;

  case 6: /* DeclList: %empty  */
#line 91 "jucompiler.y"
                                    { (yyval.node) = newnode(Program, NULL); }
#line 1629 "y.tab.c"
    break;

  case 7: /* MethodDecl: PUBLIC STATIC MethodHeader MethodBody  */
#line 96 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodDecl, NULL); 
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1638 "y.tab.c"
    break;

  case 8: /* FieldDecl: PUBLIC STATIC Type IdentList SEMICOLON  */
#line 103 "jucompiler.y"
                                    { 
                                        (yyval.node) = (yyvsp[-1].node);
                                        addFront((yyval.node), (yyvsp[-2].node)); //type fica no final
                                        }
#line 1647 "y.tab.c"
    break;

  case 9: /* FieldDecl: error SEMICOLON  */
#line 107 "jucompiler.y"
                               { (yyval.node) = newnode(Dummy, NULL); }
#line 1653 "y.tab.c"
    break;

  case 10: /* IdentList: IdentList COMMA IDENTIFIER  */
#line 111 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-2].node);
                                        struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                                        id->line   = (yylsp[0]).first_line;
                                        id->column = (yylsp[0]).first_column;
                                        addchild((yyval.node), id);
                                        }
#line 1664 "y.tab.c"
    break;

  case 11: /* IdentList: IDENTIFIER  */
#line 117 "jucompiler.y"
                                    {   (yyval.node) = newnode(FieldDecl, NULL); // Posteriormente ignorado
                                        struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                                        id->line   = (yylsp[0]).first_line;
                                        id->column = (yylsp[0]).first_column;
                                        addchild((yyval.node), id); }
#line 1674 "y.tab.c"
    break;

  case 12: /* IdentListVar: IdentListVar COMMA IDENTIFIER  */
#line 125 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-2].node);
                                        struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                                        id->line   = (yylsp[0]).first_line;
                                        id->column = (yylsp[0]).first_column;
                                        addchild((yyval.node), id);
                                        }
#line 1685 "y.tab.c"
    break;

  case 13: /* IdentListVar: IDENTIFIER  */
#line 131 "jucompiler.y"
                                    {   (yyval.node) = newnode(VarDecl, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                                        id->line   = (yylsp[0]).first_line;
                                        id->column = (yylsp[0]).first_column;
                                        addchild((yyval.node), id); }
#line 1695 "y.tab.c"
    break;

  case 14: /* Type: BOOL  */
#line 138 "jucompiler.y"
                                    { (yyval.node) = newnode(Bool, NULL); }
#line 1701 "y.tab.c"
    break;

  case 15: /* Type: INT  */
#line 139 "jucompiler.y"
                                    { (yyval.node) = newnode(Int, NULL); }
#line 1707 "y.tab.c"
    break;

  case 16: /* Type: DOUBLE  */
#line 140 "jucompiler.y"
                                    { (yyval.node) = newnode(Double, NULL); }
#line 1713 "y.tab.c"
    break;

  case 17: /* MethodHeader: Type IDENTIFIER LPAR FormalParamOpt RPAR  */
#line 145 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodHeader, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-3].lexeme));
                                        id->line   = (yylsp[-3]).first_line;
                                        id->column = (yylsp[-3]).first_column;
                                        addchild((yyval.node), (yyvsp[-4].node));
                                        addchild((yyval.node), id);
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 1726 "y.tab.c"
    break;

  case 18: /* MethodHeader: VOID IDENTIFIER LPAR FormalParamOpt RPAR  */
#line 155 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodHeader, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-3].lexeme));
                                        id->line   = (yylsp[-3]).first_line;
                                        id->column = (yylsp[-3]).first_column;
                                        addchild((yyval.node), newnode(Void, NULL));
                                        addchild((yyval.node), id);
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 1739 "y.tab.c"
    break;

  case 19: /* FormalParamOpt: FormalParams  */
#line 165 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1745 "y.tab.c"
    break;

  case 20: /* FormalParamOpt: %empty  */
#line 166 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodParams, NULL); }
#line 1751 "y.tab.c"
    break;

  case 21: /* FormalParams: NormalParams  */
#line 169 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1757 "y.tab.c"
    break;

  case 22: /* FormalParams: STRING LSQ RSQ IDENTIFIER  */
#line 171 "jucompiler.y"
                { (yyval.node) = newnode(MethodParams, NULL);
                  struct node *aux = newnode(ParamDecl, NULL);
                  struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                  id->line   = (yylsp[0]).first_line;
                  id->column = (yylsp[0]).first_column;
                  addchild(aux, newnode(StringArray, NULL));
                  addchild(aux, id);
                  addchild((yyval.node), aux); }
#line 1770 "y.tab.c"
    break;

  case 23: /* NormalParams: Type IDENTIFIER  */
#line 182 "jucompiler.y"
                { (yyval.node) = newnode(MethodParams, NULL);
                  struct node *aux = newnode(ParamDecl, NULL);
                  struct node *id = newnode(Identifier, (yyvsp[0].lexeme));
                  id->line = (yylsp[0]).first_line; id->column = (yylsp[0]).first_column;
                  addchild(aux, (yyvsp[-1].node));
                  addchild(aux, id);
                  addchild((yyval.node), aux); }
#line 1782 "y.tab.c"
    break;

  case 24: /* NormalParams: NormalParams COMMA Type IDENTIFIER  */
#line 191 "jucompiler.y"
                { (yyval.node) = (yyvsp[-3].node);
                  struct node *aux = newnode(ParamDecl, NULL);
                  addchild(aux, (yyvsp[-1].node));
                  struct node *ID_node = newnode(Identifier, (yyvsp[0].lexeme));
                  ID_node->line = (yylsp[-2]).first_line; ID_node->column = (yylsp[-2]).first_column;
                  addchild(aux,ID_node);
                  addchild((yyval.node), aux); }
#line 1794 "y.tab.c"
    break;

  case 25: /* MethodBody: LBRACE StmtOrVarList RBRACE  */
#line 201 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node);
                                        }
#line 1801 "y.tab.c"
    break;

  case 26: /* StmtOrVarList: StmtOrVarList Statement  */
#line 206 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      if( (yyvsp[0].node) != NULL) addchild((yyval.node), (yyvsp[0].node)); }
#line 1808 "y.tab.c"
    break;

  case 27: /* StmtOrVarList: StmtOrVarList VarDecl  */
#line 210 "jucompiler.y"
                                    {    (yyval.node) = (yyvsp[-1].node);
                                        struct node *aux = (yyvsp[0].node);
                                        int type = 9;
                                         if( (aux != NULL) && (aux->children != NULL) && (aux->children->node != NULL) ) type = aux->children->node->category; // nodes type
                                        if(type != 9){ // Not Dummy
                                            struct node_list *childrenList = aux->children->next;
                                            while ((childrenList != NULL) ) {
                                                if (childrenList->node != NULL) {
                                                    struct node *parent = newnode(VarDecl, NULL);
                                                    struct node *newtype = newnode(type, NULL);
                                                    struct node *newNode = newnode(childrenList->node->category, childrenList->node->token);
                                                    
                                                    // Propaga line e column do nó original copiado
                                                    newNode->line   = childrenList->node->line;
                                                    newNode->column = childrenList->node->column;
                                                    
                                                    addchild(parent, newtype);
                                                    addchild(parent, newNode);
                                                    addchild((yyval.node), parent);
                                                }
                                                childrenList = childrenList->next;
                                            }
                                        }
                                    }
#line 1837 "y.tab.c"
    break;

  case 28: /* StmtOrVarList: %empty  */
#line 234 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodBody, NULL);
                                        }
#line 1844 "y.tab.c"
    break;

  case 29: /* VarDecl: Type IdentListVar SEMICOLON  */
#line 238 "jucompiler.y"
                                       {    (yyval.node) = (yyvsp[-1].node);
                                            addFront((yyval.node), (yyvsp[-2].node));
                                        
                                        }
#line 1853 "y.tab.c"
    break;

  case 30: /* Statement: LBRACE StmtList RBRACE  */
#line 245 "jucompiler.y"
                                    { 
                                      struct node_list *children = (yyvsp[-1].node)->children;
                                      int count = 0;
                                      struct node_list *cur = children;
                                      while(cur != NULL) { count++; cur = cur->next; }

                                      if(count == 1 ) {
                                          (yyval.node) = children->node; /* passa o filho diretamente */
                                      } else {
                                          (yyval.node) = (yyvsp[-1].node); /* 0 ou 2+ filhos, mantém o Block */
                                      }
                                    }
#line 1870 "y.tab.c"
    break;

  case 31: /* Statement: IfStmt  */
#line 258 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1876 "y.tab.c"
    break;

  case 32: /* Statement: SEMICOLON  */
#line 260 "jucompiler.y"
                                    {   (yyval.node) = NULL;
                                         }
#line 1883 "y.tab.c"
    break;

  case 33: /* Statement: WHILE LPAR Expr RPAR Statement  */
#line 264 "jucompiler.y"
                                    {   (yyval.node) = newnode(While, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        if((yyvsp[0].node) != NULL) addchild((yyval.node), (yyvsp[0].node));
                                        else addchild((yyval.node), newnode(Block, NULL) );
                                        }
#line 1893 "y.tab.c"
    break;

  case 34: /* Statement: RETURN ExprOpt SEMICOLON  */
#line 269 "jucompiler.y"
                                    {   (yyval.node) = newnode(Return, NULL); 
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node)); 
                                        }
#line 1901 "y.tab.c"
    break;

  case 35: /* Statement: ExprStmt SEMICOLON  */
#line 272 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node) ; }
#line 1907 "y.tab.c"
    break;

  case 36: /* Statement: PRINT LPAR Expr RPAR SEMICOLON  */
#line 275 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        }
#line 1915 "y.tab.c"
    break;

  case 37: /* Statement: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 279 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL);
                                        struct node *aux = newnode(StrLit, (yyvsp[-2].lexeme));
                                        aux->line = (yylsp[-2]).first_line; aux->column = (yylsp[-2]).first_column;
                                        addchild((yyval.node), aux); 
                                        }
#line 1925 "y.tab.c"
    break;

  case 38: /* Statement: error SEMICOLON  */
#line 284 "jucompiler.y"
                                    { (yyval.node) = newnode(Dummy, NULL) ;}
#line 1931 "y.tab.c"
    break;

  case 39: /* StmtList: StmtList Statement  */
#line 287 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      if((yyvsp[0].node) != NULL) addchild((yyval.node), (yyvsp[0].node)); }
#line 1938 "y.tab.c"
    break;

  case 40: /* StmtList: %empty  */
#line 289 "jucompiler.y"
                                    { (yyval.node) = newnode(Block, NULL); }
#line 1944 "y.tab.c"
    break;

  case 41: /* IfStmt: IF LPAR Expr RPAR Statement ELSE Statement  */
#line 294 "jucompiler.y"
                                    {
                                        (yyval.node) = newnode(If, NULL);
                                        addchild((yyval.node), (yyvsp[-4].node));
                                        if((yyvsp[-2].node) != NULL) addchild((yyval.node), (yyvsp[-2].node));
                                        else addchild((yyval.node), newnode(Block, NULL) );
                                        if((yyvsp[0].node) != NULL) addchild((yyval.node), (yyvsp[0].node));
                                        else addchild((yyval.node), newnode(Block, NULL) );
                                    }
#line 1957 "y.tab.c"
    break;

  case 42: /* IfStmt: IF LPAR Expr RPAR Statement  */
#line 303 "jucompiler.y"
                                    {
                                        (yyval.node) = newnode(If, NULL);
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        if((yyvsp[0].node) != NULL) addchild((yyval.node), (yyvsp[0].node));
                                        else addchild((yyval.node), newnode(Block, NULL) );
                                        addchild((yyval.node), newnode(Block, NULL) );
                                    }
#line 1969 "y.tab.c"
    break;

  case 43: /* ExprOpt: Expr  */
#line 313 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ; 
                                        }
#line 1976 "y.tab.c"
    break;

  case 44: /* ExprOpt: %empty  */
#line 315 "jucompiler.y"
                                    {   (yyval.node) = NULL;
                                        }
#line 1983 "y.tab.c"
    break;

  case 45: /* ExprStmt: IDENTIFIER LPAR ArgListOpt RPAR  */
#line 320 "jucompiler.y"
                                    {   (yyval.node) = newnode(Call, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-3].lexeme));
                                        id->line   = (yylsp[-3]).first_line;
                                        id->column = (yylsp[-3]).first_column;
                                        addchild((yyval.node), id);
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node));
                                    }
#line 1995 "y.tab.c"
    break;

  case 46: /* ExprStmt: IDENTIFIER LPAR error RPAR  */
#line 327 "jucompiler.y"
                                     { (yyval.node) = newnode(Dummy, NULL); }
#line 2001 "y.tab.c"
    break;

  case 47: /* ExprStmt: IDENTIFIER ASSIGN Expr  */
#line 328 "jucompiler.y"
                                    {   (yyval.node) = newnode(Assign, NULL);
                                        (yyval.node)->line   = (yylsp[-1]).first_line;
                                        (yyval.node)->column = (yylsp[-1]).first_column;
                                        struct node *id = newnode(Identifier, (yyvsp[-2].lexeme));
                                        id->line   = (yylsp[-2]).first_line;
                                        id->column = (yylsp[-2]).first_column;
                                        addchild((yyval.node), id);
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2015 "y.tab.c"
    break;

  case 48: /* ExprStmt: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR  */
#line 338 "jucompiler.y"
                                    {   (yyval.node) = newnode(ParseArgs, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-4].lexeme));
                                        id->line   = (yylsp[-4]).first_line;
                                        id->column = (yylsp[-4]).first_column;
                                        addchild((yyval.node), id);
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        }
#line 2027 "y.tab.c"
    break;

  case 49: /* Expr: AssignExpr  */
#line 348 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ;
                                        }
#line 2034 "y.tab.c"
    break;

  case 50: /* Expr: LPAR error RPAR  */
#line 350 "jucompiler.y"
                                           { (yyval.node) = newnode(Dummy, NULL); }
#line 2040 "y.tab.c"
    break;

  case 51: /* AssignExpr: IDENTIFIER ASSIGN AssignExpr  */
#line 354 "jucompiler.y"
                                    {   (yyval.node) = newnode(Assign, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-2].lexeme));
                                        id->line   = (yylsp[-2]).first_line;
                                        id->column = (yylsp[-2]).first_column;
                                        addchild((yyval.node), id);
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2052 "y.tab.c"
    break;

  case 52: /* AssignExpr: OrExpr  */
#line 361 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node);}
#line 2058 "y.tab.c"
    break;

  case 53: /* OrExpr: OrExpr OR AndExpr  */
#line 364 "jucompiler.y"
                                    {   (yyval.node) = newnode(Or, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2067 "y.tab.c"
    break;

  case 54: /* OrExpr: AndExpr  */
#line 368 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2073 "y.tab.c"
    break;

  case 55: /* AndExpr: AndExpr AND XorExpr  */
#line 371 "jucompiler.y"
                                    {   (yyval.node) = newnode(And, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2082 "y.tab.c"
    break;

  case 56: /* AndExpr: XorExpr  */
#line 375 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2088 "y.tab.c"
    break;

  case 57: /* XorExpr: XorExpr XOR EqExpr  */
#line 378 "jucompiler.y"
                                    {   (yyval.node) = newnode(Xor, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2097 "y.tab.c"
    break;

  case 58: /* XorExpr: EqExpr  */
#line 382 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2103 "y.tab.c"
    break;

  case 59: /* EqExpr: EqExpr EQ RelExpr  */
#line 385 "jucompiler.y"
                                    {   (yyval.node) = newnode(Eq, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2112 "y.tab.c"
    break;

  case 60: /* EqExpr: EqExpr NE RelExpr  */
#line 389 "jucompiler.y"
                                    {   (yyval.node) = newnode(Ne, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2121 "y.tab.c"
    break;

  case 61: /* EqExpr: RelExpr  */
#line 393 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2127 "y.tab.c"
    break;

  case 62: /* RelExpr: RelExpr LT ShiftExpr  */
#line 396 "jucompiler.y"
                                    {   (yyval.node) = newnode(Lt, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2136 "y.tab.c"
    break;

  case 63: /* RelExpr: RelExpr LE ShiftExpr  */
#line 400 "jucompiler.y"
                                    {   (yyval.node) = newnode(Le, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2145 "y.tab.c"
    break;

  case 64: /* RelExpr: RelExpr GT ShiftExpr  */
#line 404 "jucompiler.y"
                                    {   (yyval.node) = newnode(Gt, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2154 "y.tab.c"
    break;

  case 65: /* RelExpr: RelExpr GE ShiftExpr  */
#line 408 "jucompiler.y"
                                    {   (yyval.node) = newnode(Ge, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2163 "y.tab.c"
    break;

  case 66: /* RelExpr: ShiftExpr  */
#line 412 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node);
                                        }
#line 2170 "y.tab.c"
    break;

  case 67: /* ShiftExpr: ShiftExpr LSHIFT AddExpr  */
#line 416 "jucompiler.y"
                                    {   (yyval.node) = newnode(Lshift, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2179 "y.tab.c"
    break;

  case 68: /* ShiftExpr: ShiftExpr RSHIFT AddExpr  */
#line 420 "jucompiler.y"
                                    {   (yyval.node) = newnode(Rshift, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2188 "y.tab.c"
    break;

  case 69: /* ShiftExpr: AddExpr  */
#line 424 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2194 "y.tab.c"
    break;

  case 70: /* AddExpr: AddExpr PLUS MulExpr  */
#line 427 "jucompiler.y"
                                    {   (yyval.node) = newnode(Add, NULL) ;
                                        (yyval.node)->line   = (yylsp[-1]).first_line;
                                        (yyval.node)->column = (yylsp[-1]).first_column;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2205 "y.tab.c"
    break;

  case 71: /* AddExpr: AddExpr MINUS MulExpr  */
#line 433 "jucompiler.y"
                                    {  (yyval.node) = newnode(Sub, NULL) ;
                                        (yyval.node)->line   = (yylsp[-1]).first_line;
                                        (yyval.node)->column = (yylsp[-1]).first_column;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2216 "y.tab.c"
    break;

  case 72: /* AddExpr: MulExpr  */
#line 439 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ;
                                        }
#line 2223 "y.tab.c"
    break;

  case 73: /* MulExpr: MulExpr STAR UnaryExpr  */
#line 443 "jucompiler.y"
                                    {   (yyval.node) = newnode(Mul, NULL) ;
                                        (yyval.node)->line   = (yylsp[-1]).first_line;
                                        (yyval.node)->column = (yylsp[-1]).first_column;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2234 "y.tab.c"
    break;

  case 74: /* MulExpr: MulExpr DIV UnaryExpr  */
#line 449 "jucompiler.y"
                                    {   (yyval.node) = newnode(Div, NULL) ;
                                        (yyval.node)->line   = (yylsp[-1]).first_line;
                                        (yyval.node)->column = (yylsp[-1]).first_column;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2245 "y.tab.c"
    break;

  case 75: /* MulExpr: MulExpr MOD UnaryExpr  */
#line 455 "jucompiler.y"
                                    {   (yyval.node) = newnode(Mod, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2254 "y.tab.c"
    break;

  case 76: /* MulExpr: UnaryExpr  */
#line 459 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); 
                                        }
#line 2261 "y.tab.c"
    break;

  case 77: /* UnaryExpr: MINUS UnaryExpr  */
#line 463 "jucompiler.y"
                                    {   (yyval.node) = newnode(Minus, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2269 "y.tab.c"
    break;

  case 78: /* UnaryExpr: NOT UnaryExpr  */
#line 466 "jucompiler.y"
                                    {   (yyval.node) = newnode(Not, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2277 "y.tab.c"
    break;

  case 79: /* UnaryExpr: PLUS UnaryExpr  */
#line 469 "jucompiler.y"
                                    {   (yyval.node) = newnode(Plus, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2285 "y.tab.c"
    break;

  case 80: /* UnaryExpr: PostfixExpr  */
#line 472 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2291 "y.tab.c"
    break;

  case 81: /* PostfixExpr: IDENTIFIER DOTLENGTH  */
#line 476 "jucompiler.y"
                                    {   (yyval.node) = newnode(Length, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-1].lexeme));
                                        id->line   = (yylsp[-1]).first_line;
                                        id->column = (yylsp[-1]).first_column;
                                        addchild((yyval.node), id);
                                        }
#line 2302 "y.tab.c"
    break;

  case 82: /* PostfixExpr: IDENTIFIER LPAR ArgListOpt RPAR  */
#line 484 "jucompiler.y"
                                    {   (yyval.node) = newnode(Call, NULL);
                                        struct node *id = newnode(Identifier, (yyvsp[-3].lexeme));
                                        id->line   = (yylsp[-3]).first_line;
                                        id->column = (yylsp[-3]).first_column;
                                        addchild((yyval.node), id);
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 2314 "y.tab.c"
    break;

  case 83: /* PostfixExpr: IDENTIFIER LPAR error RPAR  */
#line 492 "jucompiler.y"
                                        { (yyval.node) = newnode(Dummy, NULL); }
#line 2320 "y.tab.c"
    break;

  case 84: /* PostfixExpr: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR  */
#line 495 "jucompiler.y"
                                    {   (yyval.node) = newnode(ParseArgs, NULL);
                                        struct node *aux =  newnode(Identifier, (yyvsp[-4].lexeme));
                                        aux->line =  (yylsp[-4]).first_line; 
                                        aux->column = (yylsp[-4]).first_column;
                                        addchild((yyval.node), aux);
                                        addchild((yyval.node), (yyvsp[-2].node) );
                                        }
#line 2332 "y.tab.c"
    break;

  case 85: /* PostfixExpr: PARSEINT LPAR error RPAR  */
#line 503 "jucompiler.y"
                                    { (yyval.node) = newnode(Dummy, NULL); }
#line 2338 "y.tab.c"
    break;

  case 86: /* PostfixExpr: LPAR Expr RPAR  */
#line 505 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node); }
#line 2344 "y.tab.c"
    break;

  case 87: /* PostfixExpr: IDENTIFIER  */
#line 507 "jucompiler.y"
                                    {   (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme)); 
                                        (yyval.node)->line = (yylsp[0]).first_line; (yyval.node)->column = (yylsp[0]).first_column;
                                        }
#line 2352 "y.tab.c"
    break;

  case 88: /* PostfixExpr: NATURAL  */
#line 510 "jucompiler.y"
                                    {   (yyval.node) = newnode(Natural, (yyvsp[0].lexeme)); 
                                        (yyval.node)->line = (yylsp[0]).first_line; (yyval.node)->column = (yylsp[0]).first_column;
                                        }
#line 2360 "y.tab.c"
    break;

  case 89: /* PostfixExpr: DECIMAL  */
#line 513 "jucompiler.y"
                                    {   (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme)); 
                                        (yyval.node)->line = (yylsp[0]).first_line; (yyval.node)->column = (yylsp[0]).first_column;
                                        }
#line 2368 "y.tab.c"
    break;

  case 90: /* PostfixExpr: BOOLLIT  */
#line 516 "jucompiler.y"
                                    {   (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme)); 
                                        (yyval.node)->line = (yylsp[0]).first_line; (yyval.node)->column = (yylsp[0]).first_column;
                                        }
#line 2376 "y.tab.c"
    break;

  case 91: /* ArgListOpt: ArgList  */
#line 522 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2382 "y.tab.c"
    break;

  case 92: /* ArgListOpt: %empty  */
#line 523 "jucompiler.y"
                                    {   (yyval.node) =NULL; }
#line 2388 "y.tab.c"
    break;

  case 93: /* ArgList: Expr  */
#line 526 "jucompiler.y"
                                    { (yyval.node) = newnode(Args, NULL);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 2395 "y.tab.c"
    break;

  case 94: /* ArgList: ArgList COMMA Expr  */
#line 528 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-2].node);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 2402 "y.tab.c"
    break;


#line 2406 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 532 "jucompiler.y"
