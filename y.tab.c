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
    IDENTIFIER = 298,              /* IDENTIFIER  */
    NATURAL = 299,                 /* NATURAL  */
    DECIMAL = 300,                 /* DECIMAL  */
    INTEGER = 301,                 /* INTEGER  */
    DOUBLE = 302,                  /* DOUBLE  */
    STRLIT = 303,                  /* STRLIT  */
    BOOLLIT = 304                  /* BOOLLIT  */
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
#define IDENTIFIER 298
#define NATURAL 299
#define DECIMAL 300
#define INTEGER 301
#define DOUBLE 302
#define STRLIT 303
#define BOOLLIT 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "jucompiler.y"

    char *lexeme;
    struct node *node;

#line 240 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


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
  YYSYMBOL_IDENTIFIER = 43,                /* IDENTIFIER  */
  YYSYMBOL_NATURAL = 44,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 45,                   /* DECIMAL  */
  YYSYMBOL_INTEGER = 46,                   /* INTEGER  */
  YYSYMBOL_DOUBLE = 47,                    /* DOUBLE  */
  YYSYMBOL_STRLIT = 48,                    /* STRLIT  */
  YYSYMBOL_BOOLLIT = 49,                   /* BOOLLIT  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_DeclList = 52,                  /* DeclList  */
  YYSYMBOL_MethodDecl = 53,                /* MethodDecl  */
  YYSYMBOL_FieldDecl = 54,                 /* FieldDecl  */
  YYSYMBOL_IdentList = 55,                 /* IdentList  */
  YYSYMBOL_IdentListVar = 56,              /* IdentListVar  */
  YYSYMBOL_Type = 57,                      /* Type  */
  YYSYMBOL_MethodHeader = 58,              /* MethodHeader  */
  YYSYMBOL_FormalParamOpt = 59,            /* FormalParamOpt  */
  YYSYMBOL_FormalParams = 60,              /* FormalParams  */
  YYSYMBOL_MethodBody = 61,                /* MethodBody  */
  YYSYMBOL_StmtOrVarList = 62,             /* StmtOrVarList  */
  YYSYMBOL_VarDecl = 63,                   /* VarDecl  */
  YYSYMBOL_Statement = 64,                 /* Statement  */
  YYSYMBOL_StmtList = 65,                  /* StmtList  */
  YYSYMBOL_IfStmt = 66,                    /* IfStmt  */
  YYSYMBOL_MatchedStmt = 67,               /* MatchedStmt  */
  YYSYMBOL_ExprOpt = 68,                   /* ExprOpt  */
  YYSYMBOL_ExprStmt = 69,                  /* ExprStmt  */
  YYSYMBOL_Expr = 70,                      /* Expr  */
  YYSYMBOL_AssignExpr = 71,                /* AssignExpr  */
  YYSYMBOL_OrExpr = 72,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 73,                   /* AndExpr  */
  YYSYMBOL_XorExpr = 74,                   /* XorExpr  */
  YYSYMBOL_EqExpr = 75,                    /* EqExpr  */
  YYSYMBOL_RelExpr = 76,                   /* RelExpr  */
  YYSYMBOL_ShiftExpr = 77,                 /* ShiftExpr  */
  YYSYMBOL_AddExpr = 78,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 79,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 80,                 /* UnaryExpr  */
  YYSYMBOL_PostfixExpr = 81,               /* PostfixExpr  */
  YYSYMBOL_ArgListOpt = 82,                /* ArgListOpt  */
  YYSYMBOL_ArgList = 83                    /* ArgList  */
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    46,    46,    52,    55,    70,    72,    76,    83,    88,
      91,    95,    99,   103,   107,   108,   109,   113,   120,   128,
     129,   132,   138,   145,   154,   159,   163,   179,   183,   190,
     203,   205,   210,   213,   215,   219,   223,   226,   228,   232,
     238,   244,   246,   252,   257,   260,   261,   265,   271,   273,
     277,   282,   283,   287,   293,   297,   299,   302,   307,   310,
     314,   317,   321,   324,   328,   331,   335,   339,   342,   346,
     350,   354,   358,   362,   366,   370,   373,   377,   381,   385,
     389,   393,   397,   401,   404,   407,   410,   413,   416,   422,
     424,   429,   432,   433,   434,   435,   436,   440,   441,   444,
     446
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
  "STAR", "DIV", "MOD", "NOT", "IDENTIFIER", "NATURAL", "DECIMAL",
  "INTEGER", "DOUBLE", "STRLIT", "BOOLLIT", "$accept", "program",
  "DeclList", "MethodDecl", "FieldDecl", "IdentList", "IdentListVar",
  "Type", "MethodHeader", "FormalParamOpt", "FormalParams", "MethodBody",
  "StmtOrVarList", "VarDecl", "Statement", "StmtList", "IfStmt",
  "MatchedStmt", "ExprOpt", "ExprStmt", "Expr", "AssignExpr", "OrExpr",
  "AndExpr", "XorExpr", "EqExpr", "RelExpr", "ShiftExpr", "AddExpr",
  "MulExpr", "UnaryExpr", "PostfixExpr", "ArgListOpt", "ArgList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-136)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-99)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,   -26,    41,    44,  -136,  -136,    86,     5,  -136,    61,
    -136,  -136,  -136,  -136,    65,  -136,  -136,    31,  -136,    42,
      75,    89,   111,    63,  -136,  -136,    -1,    -1,  -136,    50,
      79,    80,    92,   114,   131,   127,  -136,   140,  -136,  -136,
     159,   170,   181,   173,   175,     9,   139,  -136,  -136,  -136,
     146,   177,  -136,  -136,    71,  -136,  -136,    15,   181,   181,
      72,   186,   197,   197,   197,     0,  -136,  -136,  -136,   193,
    -136,  -136,   189,   185,   188,    90,   136,   102,   122,   124,
    -136,  -136,   148,    10,     7,   181,  -136,   168,  -136,   174,
     178,  -136,  -136,   207,   214,   216,   217,    14,   181,    74,
    -136,  -136,  -136,    17,  -136,   213,  -136,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   218,   222,   223,   212,   228,  -136,   229,
     236,  -136,  -136,   204,  -136,  -136,   129,   135,  -136,  -136,
     233,   237,   234,   239,  -136,   185,   188,    90,   136,   136,
     102,   102,   102,   102,   122,   122,   124,   124,  -136,  -136,
    -136,   244,   251,  -136,   181,  -136,  -136,   181,  -136,  -136,
     246,   247,   181,   253,  -136,   249,   261,  -136,  -136,   181,
    -136,  -136,  -136,  -136,   254,  -136,   123,   181,   181,   262,
     165,   135,   255,   256,   257,   258,   260,   263,   264,   265,
     266,  -136,   267,  -136,   129,   129,   268,   271,  -136,   269,
    -136,   270,   272,   129,  -136
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     2,     0,
       5,     3,     4,     9,     0,    14,    15,     0,    16,     0,
       0,     0,    11,     0,    27,     7,    20,    20,     8,     0,
       0,     0,     0,     0,    19,     0,    10,     0,    38,    24,
       0,     0,    49,     0,     0,     0,     0,    26,    25,    30,
       0,     0,    21,    18,     0,    17,    36,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,    95,    96,     0,
      48,    55,    58,    60,    62,    64,    67,    72,    75,    78,
      82,    86,     0,     0,     0,     0,    13,     0,    33,     0,
       0,    29,    37,     0,     0,     0,     0,     0,     0,    93,
      85,    83,    84,     0,    87,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,     0,
      97,    52,    28,     0,    23,    22,     0,     0,    56,    92,
       0,     0,     0,     0,    57,    59,    61,    63,    65,    66,
      68,    69,    70,    71,    73,    74,    76,    77,    79,    80,
      81,     0,     0,    54,     0,    51,    50,     0,    12,    38,
       0,     0,    49,     0,    40,     0,     0,    31,    91,     0,
      89,    88,    35,    34,     0,   100,     0,     0,     0,     0,
       0,     0,    33,     0,     0,    29,     0,     0,    32,     0,
       0,    39,     0,    53,     0,     0,     0,     0,    90,     0,
      43,    35,    34,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -136,  -136,  -136,  -136,  -136,  -136,  -136,    13,  -136,   259,
    -136,  -136,  -136,  -136,   -30,   115,  -136,  -100,   113,  -135,
     -56,   182,  -136,   183,   184,   187,    70,   151,    82,    87,
     -57,  -136,   190,  -136
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,    11,    12,    23,    87,    32,    20,    33,
      34,    25,    30,    47,    92,    57,    49,   175,    69,    50,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,   129,   130
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,   176,    93,    94,    96,   100,   101,   102,   127,    15,
      16,   125,    31,    13,   103,   140,    37,     3,   142,    38,
      91,    60,   -98,    84,   104,   105,   124,    19,   128,   131,
      61,    60,   -98,    40,    85,    41,    42,    43,    44,     1,
      61,     4,    96,    46,    62,    63,    18,   128,     5,    64,
      65,    66,    67,   126,    62,    63,    68,   141,    45,    64,
      65,    66,    67,   158,   159,   160,    68,    90,    14,   176,
     176,    28,    29,    95,    21,    15,    16,    17,   176,    24,
      37,    15,    16,    38,    39,    22,    60,     7,   103,    15,
      16,     8,     9,    36,    10,    61,    51,    40,   104,    41,
      42,    43,    44,    26,   209,   210,   174,   177,   184,    62,
      63,   185,    18,   214,    64,    65,    66,    67,    18,   110,
     111,    68,    45,   193,    37,    27,    18,    38,   195,    53,
      37,   196,   197,   169,   200,    52,    37,   116,   117,    38,
      54,    40,    55,    41,    42,    43,    44,   170,    56,   171,
     172,   173,    44,    40,    88,    41,    42,    43,    44,   118,
     119,   201,    60,   120,   121,   122,    45,   112,   113,   114,
     115,    61,    45,    58,   174,   177,   132,   133,    45,    60,
     148,   149,    86,   201,    59,    62,    63,    82,    61,    83,
      64,    65,    66,    67,    89,    60,   123,    68,   154,   155,
      97,   106,    62,    63,    61,   156,   157,    64,    65,    66,
      67,    98,   108,   199,    68,   107,   109,   134,    62,    63,
      61,   135,   136,    64,    65,    66,    67,    98,   164,   137,
      68,   138,   139,   161,    62,    63,    61,   162,   163,    64,
      99,    66,    67,   165,   166,   167,    68,   168,   178,   180,
      62,    63,   182,   179,   181,    64,    65,    66,    67,   183,
     187,   188,    68,   150,   151,   152,   153,   190,   191,   192,
     198,   194,   203,   202,   -45,   204,   211,   -41,   205,   212,
     206,   207,   208,   -44,   186,   189,    35,   144,   213,   -47,
     145,   -46,   146,   143,     0,     0,   147
};

static const yytype_int16 yycheck[] =
{
      30,   136,    58,    59,    60,    62,    63,    64,     1,    10,
      11,     1,    13,     8,    14,     1,     1,    43,     1,     4,
       5,    14,    15,    14,    24,    25,    82,    14,    84,    85,
      23,    14,    15,    18,    25,    20,    21,    22,    23,     3,
      23,     0,    98,    30,    37,    38,    47,   103,     4,    42,
      43,    44,    45,    43,    37,    38,    49,    43,    43,    42,
      43,    44,    45,   120,   121,   122,    49,    54,     7,   204,
     205,     8,     9,     1,    43,    10,    11,    12,   213,     4,
       1,    10,    11,     4,     5,    43,    14,     1,    14,    10,
      11,     5,     6,    43,     8,    23,    16,    18,    24,    20,
      21,    22,    23,    14,   204,   205,   136,   137,   164,    37,
      38,   167,    47,   213,    42,    43,    44,    45,    47,    29,
      30,    49,    43,   179,     1,    14,    47,     4,     5,    15,
       1,   187,   188,     4,   190,    43,     1,    35,    36,     4,
       9,    18,    15,    20,    21,    22,    23,    18,     8,    20,
      21,    22,    23,    18,     8,    20,    21,    22,    23,    37,
      38,   191,    14,    39,    40,    41,    43,    31,    32,    33,
      34,    23,    43,    14,   204,   205,     8,     9,    43,    14,
     110,   111,    43,   213,    14,    37,    38,    14,    23,    14,
      42,    43,    44,    45,    17,    14,    48,    49,   116,   117,
      14,     8,    37,    38,    23,   118,   119,    42,    43,    44,
      45,    14,    27,    48,    49,    26,    28,    43,    37,    38,
      23,    43,    15,    42,    43,    44,    45,    14,    16,    15,
      49,    15,    15,    15,    37,    38,    23,    15,    15,    42,
      43,    44,    45,    15,    15,     9,    49,    43,    15,    15,
      37,    38,     8,    16,    15,    42,    43,    44,    45,     8,
      14,    14,    49,   112,   113,   114,   115,    14,    19,     8,
       8,    17,    15,    17,    19,    15,     8,    19,    15,     8,
      15,    15,    15,    19,   169,   172,    27,   105,    19,    19,
     107,    19,   108,   103,    -1,    -1,   109
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    43,     0,     4,    52,     1,     5,     6,
       8,    53,    54,     8,     7,    10,    11,    12,    47,    57,
      58,    43,    43,    55,     4,    61,    14,    14,     8,     9,
      62,    13,    57,    59,    60,    59,    43,     1,     4,     5,
      18,    20,    21,    22,    23,    43,    57,    63,    64,    66,
      69,    16,    43,    15,     9,    15,     8,    65,    14,    14,
      14,    23,    37,    38,    42,    43,    44,    45,    49,    68,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    14,    14,    14,    25,    43,    56,     8,    17,
      57,     5,    64,    70,    70,     1,    70,    14,    14,    43,
      80,    80,    80,    14,    24,    25,     8,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    48,    70,     1,    43,     1,    70,    82,
      83,    70,     8,     9,    43,    43,    15,    15,    15,    15,
       1,    43,     1,    82,    71,    73,    74,    75,    76,    76,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    80,
      80,    15,    15,    15,    16,    15,    15,     9,    43,     4,
      18,    20,    21,    22,    64,    67,    69,    64,    15,    16,
      15,    15,     8,     8,    70,    70,    65,    14,    14,    68,
      14,    19,     8,    70,    17,     5,    70,    70,     8,    48,
      70,    64,    17,    15,    15,    15,    15,    15,    15,    67,
      67,     8,     8,    19,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    52,    52,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    60,    61,    62,    62,    62,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    76,    76,    77,    77,    77,    78,    78,    78,    79,
      79,    79,    79,    80,    80,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    83,
      83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     2,     2,     0,     4,     5,     2,
       3,     1,     3,     1,     1,     1,     1,     5,     5,     1,
       0,     2,     4,     4,     3,     2,     2,     0,     3,     3,
       1,     5,     3,     2,     5,     5,     2,     2,     0,     7,
       5,     3,     7,     5,     3,     2,     5,     5,     1,     0,
       4,     4,     3,     7,     4,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     2,     1,     2,     4,     4,
       7,     4,     3,     1,     1,     1,     1,     1,     0,     1,
       3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: CLASS IDENTIFIER LBRACE DeclList RBRACE  */
#line 47 "jucompiler.y"
                                    {   ast = (yyval.node) = (yyvsp[-1].node);
                                        addFront((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)) );
                                       }
#line 1463 "y.tab.c"
    break;

  case 3: /* DeclList: DeclList MethodDecl  */
#line 52 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      addchild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1470 "y.tab.c"
    break;

  case 4: /* DeclList: DeclList FieldDecl  */
#line 55 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node);
                                        struct node *aux = (yyvsp[0].node);
                                        int type = aux->children->node->category; // nodes type
                                        struct node_list *childrenList = aux->children->next;
                                        while ((childrenList != NULL) ) {
                                            struct node *parent = newnode(FieldDecl, NULL);
                                            struct node *newtype = newnode(type , NULL); // copia o tipo
                                            struct node *newNode = newnode( childrenList->node->category, childrenList->node->token);
                                            addchild(parent, newtype);
                                            addchild(parent, newNode );
                                            addchild((yyval.node), parent);
                                            childrenList = childrenList->next;
                                        }
                                      }
#line 1489 "y.tab.c"
    break;

  case 5: /* DeclList: DeclList SEMICOLON  */
#line 70 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1495 "y.tab.c"
    break;

  case 6: /* DeclList: %empty  */
#line 72 "jucompiler.y"
                                    { (yyval.node) = newnode(Program, NULL); }
#line 1501 "y.tab.c"
    break;

  case 7: /* MethodDecl: PUBLIC STATIC MethodHeader MethodBody  */
#line 77 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodDecl, NULL); 
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1510 "y.tab.c"
    break;

  case 8: /* FieldDecl: PUBLIC STATIC Type IdentList SEMICOLON  */
#line 84 "jucompiler.y"
                                    { 
                                        (yyval.node) = (yyvsp[-1].node);
                                        addFront((yyval.node), (yyvsp[-2].node)); //type fica no final
                                        }
#line 1519 "y.tab.c"
    break;

  case 9: /* FieldDecl: error SEMICOLON  */
#line 88 "jucompiler.y"
                               { (yyval.node) = newnode(Dummy, NULL); }
#line 1525 "y.tab.c"
    break;

  case 10: /* IdentList: IdentList COMMA IDENTIFIER  */
#line 92 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-2].node);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)) );
                                        }
#line 1533 "y.tab.c"
    break;

  case 11: /* IdentList: IDENTIFIER  */
#line 95 "jucompiler.y"
                                    {   (yyval.node) = newnode(FieldDecl, NULL); // Posteriormente ignorado
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)) ); }
#line 1540 "y.tab.c"
    break;

  case 12: /* IdentListVar: IdentListVar COMMA IDENTIFIER  */
#line 100 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-2].node);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)) );
                                        }
#line 1548 "y.tab.c"
    break;

  case 13: /* IdentListVar: IDENTIFIER  */
#line 103 "jucompiler.y"
                                    {   (yyval.node) = newnode(VarDecl, NULL);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)) ); }
#line 1555 "y.tab.c"
    break;

  case 14: /* Type: BOOL  */
#line 107 "jucompiler.y"
                                    { (yyval.node) = newnode(Bool, NULL); }
#line 1561 "y.tab.c"
    break;

  case 15: /* Type: INT  */
#line 108 "jucompiler.y"
                                    { (yyval.node) = newnode(Int, NULL); }
#line 1567 "y.tab.c"
    break;

  case 16: /* Type: DOUBLE  */
#line 109 "jucompiler.y"
                                    { (yyval.node) = newnode(Double, NULL); }
#line 1573 "y.tab.c"
    break;

  case 17: /* MethodHeader: Type IDENTIFIER LPAR FormalParamOpt RPAR  */
#line 114 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodHeader, NULL);
                                        addchild((yyval.node), (yyvsp[-4].node));
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)) );
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 1583 "y.tab.c"
    break;

  case 18: /* MethodHeader: VOID IDENTIFIER LPAR FormalParamOpt RPAR  */
#line 121 "jucompiler.y"
                                    {   (yyval.node) = newnode(MethodHeader, NULL);
                                        addchild((yyval.node), newnode(Void, NULL) );
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)) );
                                        addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 1593 "y.tab.c"
    break;

  case 19: /* FormalParamOpt: FormalParams  */
#line 128 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1599 "y.tab.c"
    break;

  case 20: /* FormalParamOpt: %empty  */
#line 129 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodParams, NULL); }
#line 1605 "y.tab.c"
    break;

  case 21: /* FormalParams: Type IDENTIFIER  */
#line 132 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodParams, NULL);
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, (yyvsp[-1].node));
                                      addchild(aux, newnode(Identifier, (yyvsp[0].lexeme)));
                                      addchild((yyval.node), aux); }
#line 1615 "y.tab.c"
    break;

  case 22: /* FormalParams: FormalParams COMMA Type IDENTIFIER  */
#line 139 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-3].node);
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, (yyvsp[-1].node));
                                      addchild(aux, newnode(Identifier, (yyvsp[0].lexeme)));
                                      addchild((yyval.node), aux); }
#line 1625 "y.tab.c"
    break;

  case 23: /* FormalParams: STRING LSQ RSQ IDENTIFIER  */
#line 146 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodParams, NULL);
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, newnode(StringArray, NULL));
                                      addchild(aux, newnode(Identifier, (yyvsp[0].lexeme)));
                                      addchild((yyval.node), aux); }
#line 1635 "y.tab.c"
    break;

  case 24: /* MethodBody: LBRACE StmtOrVarList RBRACE  */
#line 155 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node);
                                        }
#line 1642 "y.tab.c"
    break;

  case 25: /* StmtOrVarList: StmtOrVarList Statement  */
#line 160 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 1649 "y.tab.c"
    break;

  case 26: /* StmtOrVarList: StmtOrVarList VarDecl  */
#line 164 "jucompiler.y"
                                    {    (yyval.node) = (yyvsp[-1].node);
                                        struct node *aux = (yyvsp[0].node);
                                        int type = aux->children->node->category; // nodes type
                                        struct node_list *childrenList = aux->children->next;
                                        while ((childrenList != NULL) ) {
                                            struct node *parent = newnode(VarDecl, NULL);
                                            struct node *newtype = newnode(type , NULL); // copia o tipo
                                            struct node *newNode = newnode( childrenList->node->category, childrenList->node->token);
                                            addchild(parent, newtype);
                                            addchild(parent, newNode );
                                            addchild((yyval.node), parent);
                                            childrenList = childrenList->next;
                                        }
                                    }
#line 1668 "y.tab.c"
    break;

  case 27: /* StmtOrVarList: %empty  */
#line 179 "jucompiler.y"
                                    { (yyval.node) = newnode(MethodBody, NULL);
                                        }
#line 1675 "y.tab.c"
    break;

  case 28: /* VarDecl: Type IdentListVar SEMICOLON  */
#line 183 "jucompiler.y"
                                       {    (yyval.node) = (yyvsp[-1].node);
                                            addFront((yyval.node), (yyvsp[-2].node));
                                        
                                        }
#line 1684 "y.tab.c"
    break;

  case 29: /* Statement: LBRACE StmtList RBRACE  */
#line 190 "jucompiler.y"
                                    { 
                                      struct node_list *children = (yyvsp[-1].node)->children;
                                      int count = 0;
                                      struct node_list *cur = children;
                                      while(cur != NULL) { count++; cur = cur->next; }

                                      if(count == 1) {
                                          (yyval.node) = children->node; /* passa o filho diretamente */
                                      } else {
                                          (yyval.node) = (yyvsp[-1].node); /* 0 ou 2+ filhos, mantém o Block */
                                      }
                                    }
#line 1701 "y.tab.c"
    break;

  case 30: /* Statement: IfStmt  */
#line 203 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1707 "y.tab.c"
    break;

  case 31: /* Statement: WHILE LPAR Expr RPAR Statement  */
#line 206 "jucompiler.y"
                                    {   (yyval.node) = newnode(While, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 1716 "y.tab.c"
    break;

  case 32: /* Statement: RETURN ExprOpt SEMICOLON  */
#line 210 "jucompiler.y"
                                    {   (yyval.node) = newnode(Return, NULL); 
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node)); 
                                        }
#line 1724 "y.tab.c"
    break;

  case 33: /* Statement: ExprStmt SEMICOLON  */
#line 213 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node) ; }
#line 1730 "y.tab.c"
    break;

  case 34: /* Statement: PRINT LPAR Expr RPAR SEMICOLON  */
#line 216 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        }
#line 1738 "y.tab.c"
    break;

  case 35: /* Statement: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 220 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL); 
                                        addchild((yyval.node), newnode(Strlit, (yyvsp[-2].lexeme)) ); 
                                        }
#line 1746 "y.tab.c"
    break;

  case 36: /* Statement: error SEMICOLON  */
#line 223 "jucompiler.y"
                                    { (yyval.node) = newnode(Dummy, NULL) ;}
#line 1752 "y.tab.c"
    break;

  case 37: /* StmtList: StmtList Statement  */
#line 226 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 1759 "y.tab.c"
    break;

  case 38: /* StmtList: %empty  */
#line 228 "jucompiler.y"
                                    { (yyval.node) = newnode(Block, NULL); }
#line 1765 "y.tab.c"
    break;

  case 39: /* IfStmt: IF LPAR Expr RPAR MatchedStmt ELSE Statement  */
#line 233 "jucompiler.y"
                                    {   (yyval.node) = newnode(If, NULL) ;
                                        addchild((yyval.node), (yyvsp[-4].node)); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 1775 "y.tab.c"
    break;

  case 40: /* IfStmt: IF LPAR Expr RPAR Statement  */
#line 238 "jucompiler.y"
                                    {   (yyval.node) = newnode(If, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1784 "y.tab.c"
    break;

  case 41: /* MatchedStmt: LBRACE StmtList RBRACE  */
#line 244 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node); 
                                        }
#line 1791 "y.tab.c"
    break;

  case 42: /* MatchedStmt: IF LPAR Expr RPAR MatchedStmt ELSE MatchedStmt  */
#line 247 "jucompiler.y"
                                    {   (yyval.node) = newnode(If, NULL); 
                                        addchild((yyval.node), (yyvsp[-4].node)); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1801 "y.tab.c"
    break;

  case 43: /* MatchedStmt: WHILE LPAR Expr RPAR MatchedStmt  */
#line 253 "jucompiler.y"
                                    {   (yyval.node) = newnode(While, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1810 "y.tab.c"
    break;

  case 44: /* MatchedStmt: RETURN ExprOpt SEMICOLON  */
#line 257 "jucompiler.y"
                                      { (yyval.node) = newnode(Return, NULL);
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node)); 
                                            }
#line 1818 "y.tab.c"
    break;

  case 45: /* MatchedStmt: ExprStmt SEMICOLON  */
#line 260 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node);}
#line 1824 "y.tab.c"
    break;

  case 46: /* MatchedStmt: PRINT LPAR Expr RPAR SEMICOLON  */
#line 262 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node)); 
                                        }
#line 1832 "y.tab.c"
    break;

  case 47: /* MatchedStmt: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 266 "jucompiler.y"
                                    {   (yyval.node) = newnode(Print, NULL); 
                                        addchild((yyval.node), newnode(Strlit, (yyvsp[-2].lexeme)) ); 
                                        }
#line 1840 "y.tab.c"
    break;

  case 48: /* ExprOpt: Expr  */
#line 271 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ; 
                                        }
#line 1847 "y.tab.c"
    break;

  case 49: /* ExprOpt: %empty  */
#line 273 "jucompiler.y"
                                    {   (yyval.node) = NULL;
                                        }
#line 1854 "y.tab.c"
    break;

  case 50: /* ExprStmt: IDENTIFIER LPAR ArgListOpt RPAR  */
#line 278 "jucompiler.y"
                                    {   (yyval.node) = newnode(Call, NULL) ;
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)) );
                                       if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node));
                                    }
#line 1863 "y.tab.c"
    break;

  case 51: /* ExprStmt: IDENTIFIER LPAR error RPAR  */
#line 282 "jucompiler.y"
                                     { (yyval.node) = NULL; }
#line 1869 "y.tab.c"
    break;

  case 52: /* ExprStmt: IDENTIFIER ASSIGN Expr  */
#line 283 "jucompiler.y"
                                    {   (yyval.node) = newnode(Assign, NULL);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)) );
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1878 "y.tab.c"
    break;

  case 53: /* ExprStmt: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR  */
#line 288 "jucompiler.y"
                                    {   (yyval.node) = newnode(ParseArgs, NULL);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)) );
                                        addchild((yyval.node), (yyvsp[-2].node) );
                                        }
#line 1887 "y.tab.c"
    break;

  case 54: /* ExprStmt: PARSEINT LPAR error RPAR  */
#line 293 "jucompiler.y"
                                    { (yyval.node) = newnode(Dummy, NULL); }
#line 1893 "y.tab.c"
    break;

  case 55: /* Expr: AssignExpr  */
#line 297 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ;
                                        }
#line 1900 "y.tab.c"
    break;

  case 56: /* Expr: LPAR error RPAR  */
#line 299 "jucompiler.y"
                                           { (yyval.node) = newnode(Dummy, NULL); }
#line 1906 "y.tab.c"
    break;

  case 57: /* AssignExpr: IDENTIFIER ASSIGN AssignExpr  */
#line 303 "jucompiler.y"
                                    {   (yyval.node) = newnode(Assign, NULL); 
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)) ); 
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1915 "y.tab.c"
    break;

  case 58: /* AssignExpr: OrExpr  */
#line 307 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node);}
#line 1921 "y.tab.c"
    break;

  case 59: /* OrExpr: OrExpr OR AndExpr  */
#line 310 "jucompiler.y"
                                    {   (yyval.node) = newnode(Or, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1930 "y.tab.c"
    break;

  case 60: /* OrExpr: AndExpr  */
#line 314 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1936 "y.tab.c"
    break;

  case 61: /* AndExpr: AndExpr AND XorExpr  */
#line 317 "jucompiler.y"
                                    {   (yyval.node) = newnode(And, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1945 "y.tab.c"
    break;

  case 62: /* AndExpr: XorExpr  */
#line 321 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1951 "y.tab.c"
    break;

  case 63: /* XorExpr: XorExpr XOR EqExpr  */
#line 324 "jucompiler.y"
                                    {   (yyval.node) = newnode(Xor, NULL); 
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1960 "y.tab.c"
    break;

  case 64: /* XorExpr: EqExpr  */
#line 328 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1966 "y.tab.c"
    break;

  case 65: /* EqExpr: EqExpr EQ RelExpr  */
#line 331 "jucompiler.y"
                                    {   (yyval.node) = newnode(Eq, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1975 "y.tab.c"
    break;

  case 66: /* EqExpr: EqExpr NE RelExpr  */
#line 335 "jucompiler.y"
                                    {   (yyval.node) = newnode(Ne, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1984 "y.tab.c"
    break;

  case 67: /* EqExpr: RelExpr  */
#line 339 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 1990 "y.tab.c"
    break;

  case 68: /* RelExpr: RelExpr LT ShiftExpr  */
#line 342 "jucompiler.y"
                                    {   (yyval.node) = newnode(Lt, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 1999 "y.tab.c"
    break;

  case 69: /* RelExpr: RelExpr LE ShiftExpr  */
#line 346 "jucompiler.y"
                                    {   (yyval.node) = newnode(Le, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2008 "y.tab.c"
    break;

  case 70: /* RelExpr: RelExpr GT ShiftExpr  */
#line 350 "jucompiler.y"
                                    {   (yyval.node) = newnode(Gt, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2017 "y.tab.c"
    break;

  case 71: /* RelExpr: RelExpr GE ShiftExpr  */
#line 354 "jucompiler.y"
                                    {   (yyval.node) = newnode(Ge, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2026 "y.tab.c"
    break;

  case 72: /* RelExpr: ShiftExpr  */
#line 358 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node);
                                        }
#line 2033 "y.tab.c"
    break;

  case 73: /* ShiftExpr: ShiftExpr LSHIFT AddExpr  */
#line 362 "jucompiler.y"
                                    {   (yyval.node) = newnode(Lshift, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2042 "y.tab.c"
    break;

  case 74: /* ShiftExpr: ShiftExpr RSHIFT AddExpr  */
#line 366 "jucompiler.y"
                                    {   (yyval.node) = newnode(Rshift, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2051 "y.tab.c"
    break;

  case 75: /* ShiftExpr: AddExpr  */
#line 370 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2057 "y.tab.c"
    break;

  case 76: /* AddExpr: AddExpr PLUS MulExpr  */
#line 373 "jucompiler.y"
                                    {   (yyval.node) = newnode(Add, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2066 "y.tab.c"
    break;

  case 77: /* AddExpr: AddExpr MINUS MulExpr  */
#line 377 "jucompiler.y"
                                    {  (yyval.node) = newnode(Sub, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2075 "y.tab.c"
    break;

  case 78: /* AddExpr: MulExpr  */
#line 381 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node) ;
                                        }
#line 2082 "y.tab.c"
    break;

  case 79: /* MulExpr: MulExpr STAR UnaryExpr  */
#line 385 "jucompiler.y"
                                    {   (yyval.node) = newnode(Mul, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2091 "y.tab.c"
    break;

  case 80: /* MulExpr: MulExpr DIV UnaryExpr  */
#line 389 "jucompiler.y"
                                    {   (yyval.node) = newnode(Div, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2100 "y.tab.c"
    break;

  case 81: /* MulExpr: MulExpr MOD UnaryExpr  */
#line 393 "jucompiler.y"
                                    {   (yyval.node) = newnode(Mod, NULL) ;
                                        addchild((yyval.node), (yyvsp[-2].node));
                                        addchild((yyval.node), (yyvsp[0].node));
                                        }
#line 2109 "y.tab.c"
    break;

  case 82: /* MulExpr: UnaryExpr  */
#line 397 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); 
                                        }
#line 2116 "y.tab.c"
    break;

  case 83: /* UnaryExpr: MINUS UnaryExpr  */
#line 401 "jucompiler.y"
                                    {   (yyval.node) = newnode(Minus, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2124 "y.tab.c"
    break;

  case 84: /* UnaryExpr: NOT UnaryExpr  */
#line 404 "jucompiler.y"
                                    {   (yyval.node) = newnode(Not, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2132 "y.tab.c"
    break;

  case 85: /* UnaryExpr: PLUS UnaryExpr  */
#line 407 "jucompiler.y"
                                    {   (yyval.node) = newnode(Plus, NULL);
                                        addchild((yyval.node), (yyvsp[0].node)); 
                                        }
#line 2140 "y.tab.c"
    break;

  case 86: /* UnaryExpr: PostfixExpr  */
#line 410 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2146 "y.tab.c"
    break;

  case 87: /* PostfixExpr: IDENTIFIER DOTLENGTH  */
#line 413 "jucompiler.y"
                                    {   (yyval.node) = newnode(Length, NULL) ;
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)) );
                                        }
#line 2154 "y.tab.c"
    break;

  case 88: /* PostfixExpr: IDENTIFIER LPAR ArgListOpt RPAR  */
#line 417 "jucompiler.y"
                                    {   (yyval.node) = newnode(Call, NULL);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)) ); 
                                        if((yyvsp[-1].node) != NULL) addchild((yyval.node), (yyvsp[-1].node));
                                        }
#line 2163 "y.tab.c"
    break;

  case 89: /* PostfixExpr: IDENTIFIER LPAR error RPAR  */
#line 422 "jucompiler.y"
                                        { (yyval.node) = newnode(Call, NULL); }
#line 2169 "y.tab.c"
    break;

  case 90: /* PostfixExpr: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR  */
#line 425 "jucompiler.y"
                                    {   (yyval.node) = newnode(ParseArgs, NULL);
                                        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)) );
                                        addchild((yyval.node), (yyvsp[-2].node) );
                                        }
#line 2178 "y.tab.c"
    break;

  case 91: /* PostfixExpr: PARSEINT LPAR error RPAR  */
#line 430 "jucompiler.y"
                                    { (yyval.node) = newnode(ParseArgs, NULL); }
#line 2184 "y.tab.c"
    break;

  case 92: /* PostfixExpr: LPAR Expr RPAR  */
#line 432 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[-1].node); }
#line 2190 "y.tab.c"
    break;

  case 93: /* PostfixExpr: IDENTIFIER  */
#line 433 "jucompiler.y"
                                    {   (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme)); }
#line 2196 "y.tab.c"
    break;

  case 94: /* PostfixExpr: NATURAL  */
#line 434 "jucompiler.y"
                                    {   (yyval.node) = newnode(Natural, (yyvsp[0].lexeme)); }
#line 2202 "y.tab.c"
    break;

  case 95: /* PostfixExpr: DECIMAL  */
#line 435 "jucompiler.y"
                                    {   (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme)); }
#line 2208 "y.tab.c"
    break;

  case 96: /* PostfixExpr: BOOLLIT  */
#line 436 "jucompiler.y"
                                    {   (yyval.node) = newnode(Boollit, (yyvsp[0].lexeme)); }
#line 2214 "y.tab.c"
    break;

  case 97: /* ArgListOpt: ArgList  */
#line 440 "jucompiler.y"
                                    {   (yyval.node) = (yyvsp[0].node); }
#line 2220 "y.tab.c"
    break;

  case 98: /* ArgListOpt: %empty  */
#line 441 "jucompiler.y"
                                    {   (yyval.node) = NULL; }
#line 2226 "y.tab.c"
    break;

  case 99: /* ArgList: Expr  */
#line 444 "jucompiler.y"
                                    { (yyval.node) = newnode(Args, NULL);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 2233 "y.tab.c"
    break;

  case 100: /* ArgList: ArgList COMMA Expr  */
#line 446 "jucompiler.y"
                                    { (yyval.node) = (yyvsp[-2].node);
                                      addchild((yyval.node), (yyvsp[0].node)); }
#line 2240 "y.tab.c"
    break;


#line 2244 "y.tab.c"

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 450 "jucompiler.y"
