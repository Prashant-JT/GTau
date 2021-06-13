/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bison.y"

#include <stdio.h>
#include "../symbol_table/table.h"
extern FILE *yyin;   /* declarado en lexico */
extern int numlin;   /* lexico le da valores */
//int yydebug=1;       /* modo debug si -t */
void yyerror(char*); 
//int yylex();

#line 80 "bison.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    REAL = 258,
    INTEGER = 259,
    CHAR = 260,
    STRING = 261,
    VECT = 262,
    DICT = 263,
    NAME = 264,
    LABEL = 265,
    FUNCTION = 266,
    TYPE = 267,
    IF = 268,
    ELSIF = 269,
    ELSE = 270,
    WHILE = 271,
    BREAK = 272,
    FOR = 273,
    GOTO = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    PRINT = 278,
    PRINTLN = 279,
    RETURN = 280,
    SIZE = 281,
    APPEND = 282,
    POP = 283,
    CLEAR = 284,
    GET = 285,
    CLONE = 286,
    EOL = 287,
    COMPARE = 288,
    UMINUS = 289,
    UPLUS = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "bison.y"

  char *name;
  char *str;
  char *label;
  double real;
  int function;     
  int compare;                       
  int integer;
  int type;
  struct ast *node;
  struct symboList *symbol;

#line 181 "bison.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   771

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  264

#define YYUNDEFTOK  2
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,     2,     2,
      43,    44,    39,    37,    47,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    48,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    53,    53,    54,    55,    56,    57,    58,    61,    62,
      63,    64,    67,    68,    69,    77,    78,    79,    80,    81,
      82,    83,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   102,   103,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   117,   118,
     119,   120,   121,   122,   123,   124,   127,   128,   129,   130,
     131,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   160,   161,   164,   165
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "REAL", "INTEGER", "CHAR", "STRING",
  "VECT", "DICT", "NAME", "LABEL", "FUNCTION", "TYPE", "IF", "ELSIF",
  "ELSE", "WHILE", "BREAK", "FOR", "GOTO", "AND", "OR", "NOT", "PRINT",
  "PRINTLN", "RETURN", "SIZE", "APPEND", "POP", "CLEAR", "GET", "CLONE",
  "EOL", "COMPARE", "UMINUS", "UPLUS", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'^'", "'('", "')'", "'{'", "'}'", "','", "';'", "':'", "'['",
  "']'", "$accept", "initial_main", "function_definition", "content",
  "parameter_function", "statement", "more_elsif", "builtin_functions",
  "variable_declaration", "variable_definition", "expression",
  "parameter_to_dict", "parameter_to_function", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    61,    43,    45,    42,
      47,    37,    94,    40,    41,   123,   125,    44,    59,    58,
      91,    93
};
# endif

#define YYPACT_NINF (-168)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -168,   313,  -168,  -168,  -168,  -168,  -168,   -28,   -26,    15,
     -19,     6,     3,    -6,     0,     8,     1,    38,    27,    28,
      33,   415,    35,    41,    43,    54,    58,    65,  -168,   415,
     415,   415,    25,    84,    69,    77,    80,   427,   106,   112,
     415,    94,    95,    96,    98,   343,  -168,   127,   129,    99,
     140,   114,   415,   415,   415,  -168,   139,   104,   415,   415,
     415,   113,   118,  -168,   441,   153,   154,   155,   156,   157,
     158,   729,   729,   546,  -168,  -168,  -168,  -168,  -168,   415,
     415,   415,   415,   415,   415,   415,   415,   415,  -168,   121,
     122,   706,   415,   415,   415,   415,  -168,   516,   131,   130,
     133,    19,   134,   415,   556,   571,   581,   169,  -168,   596,
     606,   621,  -168,   136,   135,    -2,   137,   141,   142,   -14,
     706,   706,   721,    70,    70,    -4,    -4,    -4,    -4,   174,
     172,   706,   706,   706,   706,   415,  -168,    19,    19,   181,
     182,   185,   148,    19,   706,  -168,   150,   151,   161,  -168,
    -168,  -168,  -168,   415,  -168,   415,  -168,   415,  -168,   162,
     163,   164,   147,  -168,   165,   167,   166,   170,   171,   184,
     168,   385,   385,   415,   501,   631,   646,   415,   415,   235,
     199,   186,   188,    19,    19,    19,   385,   189,   385,   173,
     385,   180,   464,  -168,   415,  -168,  -168,   656,   671,    76,
     706,   178,   385,   385,  -168,  -168,  -168,   190,   385,  -168,
      14,  -168,  -168,   415,   681,  -168,  -168,  -168,   177,   265,
     196,   200,  -168,   202,   187,   204,   230,   478,  -168,  -168,
     117,   706,  -168,  -168,  -168,   415,   385,   205,   242,  -168,
     183,   201,   696,   208,   385,    56,   212,   415,  -168,   215,
    -168,   221,   231,   531,   385,  -168,   385,   415,   229,   233,
    -168,   266,  -168,  -168
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    65,    64,    62,    63,     0,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,     0,     3,     4,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,    48,     0,     0,     0,    32,     0,     0,     0,     0,
       0,    61,     0,    84,     0,     0,     0,     0,     0,     0,
       0,    71,    70,     0,     5,     7,    35,    22,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,    56,     0,     0,     0,     0,    66,    87,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,    68,
      79,    81,    83,    72,    73,    74,    75,    76,    77,     0,
       0,    57,    58,    59,    60,     0,    67,    15,    15,     0,
       0,     0,     0,    15,    49,    69,     0,     0,     0,    82,
      38,    39,    40,     0,    43,     0,    45,     0,    47,     0,
       0,     0,     0,    88,     0,     0,    17,    18,    16,     0,
       0,    12,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    15,    15,    12,     0,    12,     0,
      12,     0,     0,    41,     0,    44,    46,     0,     0,     0,
      52,     0,    12,    12,    19,    20,    21,     0,    12,    13,
      25,    14,    30,     0,     0,    78,    80,    50,     0,     0,
       0,     0,    11,     0,     0,     0,    27,     0,    42,    51,
       0,    55,     9,    10,     8,     0,    12,     0,     0,    53,
       0,     0,     0,     0,    12,     0,     0,     0,    54,     0,
      26,     0,     0,    85,    12,    28,    12,     0,     0,     0,
      86,    36,    29,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,  -168,  -167,  -135,   280,    21,    -1,  -168,    45,
     -20,    29,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    32,   189,   142,   190,   226,    63,    35,    36,
      37,   241,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    64,   164,   165,   163,   191,   159,   160,   170,    71,
      72,    73,    51,    47,    48,    49,    79,    80,    50,   207,
      91,   209,    38,   211,    39,    97,   139,   140,   224,   225,
      46,   141,   104,   105,   106,   220,   221,    53,   109,   110,
     111,   223,   154,    54,    56,   155,    52,    57,   204,   205,
     206,    40,    41,    42,    43,    44,    55,    74,    45,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   218,   243,
      58,    59,   131,   132,   133,   134,    60,   251,    65,     3,
       4,     5,     6,   144,    66,    61,    67,   258,    62,   259,
      79,    80,    40,    41,    42,    43,    44,    68,    18,    19,
      20,    69,    22,    23,    24,    25,    26,    27,    70,    84,
      85,    86,    87,    29,    30,    97,    75,    76,    89,    31,
       3,     4,     5,     6,    90,    77,    61,   217,    78,    62,
      92,    93,    94,   174,    95,   175,    99,   176,   100,    18,
      19,    20,   101,    22,    23,    24,    25,    26,    27,   102,
     103,   107,   108,   192,    29,    30,    45,   197,   198,   200,
      31,    52,   113,   114,   115,   116,   117,   118,   239,   130,
      34,    34,   129,   137,   214,   136,   138,   143,   148,    97,
     152,   156,   153,   161,   162,    34,   158,    34,   157,    34,
     166,   167,   169,   227,   168,   171,   172,   173,   180,   231,
     179,    34,    34,    79,    80,   177,   178,    34,   201,   181,
     240,   182,   187,   183,   219,   242,    81,   184,   185,   210,
      82,    83,    84,    85,    86,    87,   212,   253,   229,   186,
     235,   202,   247,   203,   208,    34,   222,   240,     3,     4,
       5,     6,   232,    34,    61,   237,   233,    62,   234,   236,
     244,   245,   248,    34,   250,    34,   252,    18,    19,    20,
     254,    22,    23,    24,    25,    26,    27,   255,     3,     4,
       5,     6,    29,    30,    61,   261,   256,    62,    31,   262,
     224,    33,   263,   246,     0,   199,   260,    18,    19,    20,
       0,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,    29,    30,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     2,     0,   230,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,    14,
      15,    16,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     3,     4,     5,     6,
      29,    30,    61,     0,     0,    62,    31,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    19,    20,     0,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
      29,    30,     0,     0,     0,     0,    31,    96,     3,     4,
       5,     6,     7,     8,     9,    10,     0,    12,    13,     0,
       0,    14,    15,    16,    17,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   188,     3,     4,
       5,     6,    29,    30,    61,     0,     0,    62,    31,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    19,    20,
       0,    22,    23,    24,    25,    26,    27,    79,    80,     0,
       0,     0,    29,    30,     0,     0,     0,     0,    31,     0,
      81,    79,    80,     0,    82,    83,    84,    85,    86,    87,
       0,     0,     0,     0,    81,    88,     0,     0,    82,    83,
      84,    85,    86,    87,    79,    80,     0,     0,     0,   112,
       0,     0,     0,     0,     0,     0,     0,    81,    79,    80,
       0,    82,    83,    84,    85,    86,    87,     0,     0,     0,
       0,    81,   213,     0,     0,    82,    83,    84,    85,    86,
      87,    79,    80,     0,     0,     0,   238,     0,     0,     0,
       0,     0,     0,     0,    81,     0,    79,    80,    82,    83,
      84,    85,    86,    87,     0,   193,     0,     0,   194,    81,
       0,    79,    80,    82,    83,    84,    85,    86,    87,     0,
       0,     0,     0,   135,    81,     0,    79,    80,    82,    83,
      84,    85,    86,    87,     0,     0,    79,    80,   257,    81,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    81,
     119,    79,    80,    82,    83,    84,    85,    86,    87,     0,
     145,    79,    80,     0,    81,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    81,   146,    79,    80,    82,    83,
      84,    85,    86,    87,     0,   147,    79,    80,     0,    81,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    81,
     149,    79,    80,    82,    83,    84,    85,    86,    87,     0,
     150,    79,    80,     0,    81,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    81,   151,    79,    80,    82,    83,
      84,    85,    86,    87,     0,   195,    79,    80,     0,    81,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    81,
     196,    79,    80,    82,    83,    84,    85,    86,    87,     0,
     215,    79,    80,     0,    81,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    81,   216,    79,    80,    82,    83,
      84,    85,    86,    87,     0,   228,    79,    80,     0,    81,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    81,
     249,    79,    80,    82,    83,    84,    85,    86,    87,    79,
      80,     0,     0,     0,    -1,     0,     0,     0,    82,    83,
      84,    85,    86,    87,     0,     0,    82,    83,    84,    85,
      86,    87
};

static const yytype_int16 yycheck[] =
{
       1,    21,   137,   138,   135,   172,    20,    21,   143,    29,
      30,    31,     9,     7,     8,     9,    20,    21,    12,   186,
      40,   188,    50,   190,    50,    45,     7,     8,    14,    15,
      49,    12,    52,    53,    54,   202,   203,    43,    58,    59,
      60,   208,    44,    43,    43,    47,    43,     9,   183,   184,
     185,    36,    37,    38,    39,    40,    48,    32,    43,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   199,   236,
      43,    43,    92,    93,    94,    95,    43,   244,    43,     3,
       4,     5,     6,   103,    43,     9,    43,   254,    12,   256,
      20,    21,    36,    37,    38,    39,    40,    43,    22,    23,
      24,    43,    26,    27,    28,    29,    30,    31,    43,    39,
      40,    41,    42,    37,    38,   135,    32,    48,    12,    43,
       3,     4,     5,     6,    12,    48,     9,    51,    48,    12,
      36,    36,    36,   153,    36,   155,     9,   157,     9,    22,
      23,    24,    43,    26,    27,    28,    29,    30,    31,     9,
      36,    12,    48,   173,    37,    38,    43,   177,   178,   179,
      43,    43,     9,     9,     9,     9,     9,     9,    51,    47,
     171,   172,    51,    43,   194,    44,    43,    43,     9,   199,
      44,    44,    47,     9,    12,   186,    44,   188,    47,   190,
       9,     9,    44,   213,     9,    45,    45,    36,    51,   219,
      36,   202,   203,    20,    21,    43,    43,   208,     9,    44,
     230,    44,    44,    47,    36,   235,    33,    47,    47,    46,
      37,    38,    39,    40,    41,    42,    46,   247,    51,    45,
      43,    45,    49,    45,    45,   236,    46,   257,     3,     4,
       5,     6,    46,   244,     9,    15,    46,    12,    46,    45,
      45,     9,    51,   254,    46,   256,    44,    22,    23,    24,
      45,    26,    27,    28,    29,    30,    31,    46,     3,     4,
       5,     6,    37,    38,     9,    46,    45,    12,    43,    46,
      14,     1,   261,   238,    -1,    50,   257,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,     0,    -1,    50,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      17,    18,    19,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     3,     4,     5,     6,
      37,    38,     9,    -1,    -1,    12,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    -1,    -1,    -1,    43,    44,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    -1,
      -1,    16,    17,    18,    19,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     3,     4,
       5,     6,    37,    38,     9,    -1,    -1,    12,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    20,    21,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,
      33,    20,    21,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    33,    48,    -1,    -1,    37,    38,
      39,    40,    41,    42,    20,    21,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    20,    21,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    33,    48,    -1,    -1,    37,    38,    39,    40,    41,
      42,    20,    21,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    20,    21,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    47,    33,
      -1,    20,    21,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    47,    33,    -1,    20,    21,    37,    38,
      39,    40,    41,    42,    -1,    -1,    20,    21,    47,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    33,
      44,    20,    21,    37,    38,    39,    40,    41,    42,    -1,
      44,    20,    21,    -1,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    33,    44,    20,    21,    37,    38,
      39,    40,    41,    42,    -1,    44,    20,    21,    -1,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    33,
      44,    20,    21,    37,    38,    39,    40,    41,    42,    -1,
      44,    20,    21,    -1,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    33,    44,    20,    21,    37,    38,
      39,    40,    41,    42,    -1,    44,    20,    21,    -1,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    33,
      44,    20,    21,    37,    38,    39,    40,    41,    42,    -1,
      44,    20,    21,    -1,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    33,    44,    20,    21,    37,    38,
      39,    40,    41,    42,    -1,    44,    20,    21,    -1,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    33,
      44,    20,    21,    37,    38,    39,    40,    41,    42,    20,
      21,    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,    -1,    37,    38,    39,    40,
      41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    16,    17,    18,    19,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    37,
      38,    43,    54,    57,    59,    60,    61,    62,    50,    50,
      36,    37,    38,    39,    40,    43,    49,     7,     8,     9,
      12,     9,    43,    43,    43,    48,    43,     9,    43,    43,
      43,     9,    12,    59,    62,    43,    43,    43,    43,    43,
      43,    62,    62,    62,    32,    32,    48,    48,    48,    20,
      21,    33,    37,    38,    39,    40,    41,    42,    48,    12,
      12,    62,    36,    36,    36,    36,    44,    62,    64,     9,
       9,    43,     9,    36,    62,    62,    62,    12,    48,    62,
      62,    62,    48,     9,     9,     9,     9,     9,     9,    44,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    51,
      47,    62,    62,    62,    62,    47,    44,    43,    43,     7,
       8,    12,    56,    43,    62,    44,    44,    44,     9,    44,
      44,    44,    44,    47,    44,    47,    44,    47,    44,    20,
      21,     9,    12,    64,    56,    56,     9,     9,     9,    44,
      56,    45,    45,    36,    62,    62,    62,    43,    43,    36,
      51,    44,    44,    47,    47,    47,    45,    44,    32,    55,
      57,    55,    62,    44,    47,    44,    44,    62,    62,    50,
      62,     9,    45,    45,    56,    56,    56,    55,    45,    55,
      46,    55,    46,    48,    62,    44,    44,    51,    64,    36,
      55,    55,    46,    55,    14,    15,    58,    62,    44,    51,
      50,    62,    46,    46,    46,    43,    45,    15,    48,    51,
      62,    63,    62,    55,    45,     9,    61,    49,    51,    44,
      46,    55,    44,    62,    45,    46,    45,    47,    55,    55,
      63,    46,    46,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    55,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    61,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     2,     3,     9,     9,
       9,     8,     0,     2,     2,     0,     2,     2,     2,     4,
       4,     4,     2,     2,     2,     7,    11,     8,    12,    14,
       7,     3,     2,     3,     2,     2,     7,     8,     4,     4,
       4,     6,     8,     4,     6,     4,     6,     4,     2,     4,
       8,     9,     7,    10,    11,     9,     3,     4,     4,     4,
       4,     1,     1,     1,     1,     1,     3,     4,     3,     4,
       2,     2,     3,     3,     3,     3,     3,     3,     7,     3,
       7,     3,     4,     3,     1,     3,     5,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 8:
#line 61 "bison.y"
                                                                                        { newFunction((yyvsp[-7].type), (yyvsp[-6].name), (yyvsp[-4].symbol), (yyvsp[-1].node)); }
#line 1618 "bison.tab.c"
    break;

  case 9:
#line 62 "bison.y"
                                                                                        { newFunction(7, (yyvsp[-6].name), (yyvsp[-4].symbol), (yyvsp[-1].node)); }
#line 1624 "bison.tab.c"
    break;

  case 10:
#line 63 "bison.y"
                                                                                        { newFunction(8, (yyvsp[-6].name), (yyvsp[-4].symbol), (yyvsp[-1].node)); }
#line 1630 "bison.tab.c"
    break;

  case 11:
#line 64 "bison.y"
                                                                                        { newFunction(0, (yyvsp[-6].name), (yyvsp[-4].symbol), (yyvsp[-1].node)); }
#line 1636 "bison.tab.c"
    break;

  case 12:
#line 67 "bison.y"
                                                                                        { (yyval.node) = NULL; }
#line 1642 "bison.tab.c"
    break;

  case 13:
#line 68 "bison.y"
                                                                                        {;}
#line 1648 "bison.tab.c"
    break;

  case 14:
#line 69 "bison.y"
                                                                                        { if ((yyvsp[0].node) == NULL) {
                                                                                            (yyval.node) = newAST('L', NULL, (yyvsp[-1].node));
                                                                                          } else {
                                                                                            (yyval.node) = newAST('L', (yyvsp[0].node), (yyvsp[-1].node));
                                                                                          }
                                                                                        }
#line 1659 "bison.tab.c"
    break;

  case 15:
#line 77 "bison.y"
                                                                                        { (yyval.symbol) = NULL; }
#line 1665 "bison.tab.c"
    break;

  case 16:
#line 78 "bison.y"
                                                                                        { (yyval.symbol) = newSymboList(newAST('L', newAssignment((yyvsp[0].name), newVariable((yyvsp[-1].type), 0, "")), newReference((yyvsp[-1].type), (yyvsp[0].name))), NULL); }
#line 1671 "bison.tab.c"
    break;

  case 17:
#line 79 "bison.y"
                                                                                        { (yyval.symbol) = newSymboList(newAST('L', newAssignment((yyvsp[0].name), newVector(0, (yyvsp[0].name), NULL)), newReference(7, (yyvsp[0].name))), NULL); }
#line 1677 "bison.tab.c"
    break;

  case 19:
#line 81 "bison.y"
                                                                                        { (yyval.symbol) = newSymboList(newAST('L', newAssignment((yyvsp[-2].name), newVector(0, (yyvsp[-2].name), NULL)), newReference(7, (yyvsp[-2].name))), (yyvsp[0].symbol)); }
#line 1683 "bison.tab.c"
    break;

  case 21:
#line 83 "bison.y"
                                                                                        { (yyval.symbol) = newSymboList(newAST('L', newAssignment((yyvsp[-2].name), newVariable((yyvsp[-3].type), 0, "")), newReference((yyvsp[-3].type), (yyvsp[-2].name))), (yyvsp[0].symbol)); }
#line 1689 "bison.tab.c"
    break;

  case 25:
#line 89 "bison.y"
                                                                                                            { (yyval.node) = newIf((yyvsp[-4].node), (yyvsp[-1].node), NULL); }
#line 1695 "bison.tab.c"
    break;

  case 26:
#line 90 "bison.y"
                                                                                                            { (yyval.node) = newIf((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node)); }
#line 1701 "bison.tab.c"
    break;

  case 27:
#line 91 "bison.y"
                                                                                                            { (yyval.node) = newIf((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1707 "bison.tab.c"
    break;

  case 29:
#line 93 "bison.y"
                                                                                                            { (yyval.node) = newFor(newAST('L', newAssignment((yyvsp[-10].name), (yyvsp[-8].node)), newReference((yyvsp[-11].type), (yyvsp[-10].name))), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1713 "bison.tab.c"
    break;

  case 30:
#line 94 "bison.y"
                                                                                                            { (yyval.node) = newAST('W', (yyvsp[-1].node), (yyvsp[-4].node)); }
#line 1719 "bison.tab.c"
    break;

  case 31:
#line 95 "bison.y"
                                                                                                            { (yyval.node) = newAST('Z', NULL, (yyvsp[-1].node)); }
#line 1725 "bison.tab.c"
    break;

  case 32:
#line 96 "bison.y"
                                                                                                            { (yyval.node) = newAST('B', NULL, NULL); }
#line 1731 "bison.tab.c"
    break;

  case 33:
#line 97 "bison.y"
                                                                                                            { (yyval.node) = newAST('G', NULL, newReference(0, (yyvsp[-1].name))); }
#line 1737 "bison.tab.c"
    break;

  case 34:
#line 98 "bison.y"
                                                                                                            { (yyval.node) = newAST('T', NULL, newReference(0, (yyvsp[-1].label))); }
#line 1743 "bison.tab.c"
    break;

  case 36:
#line 102 "bison.y"
                                                                                        { (yyval.node) = newIf((yyvsp[-4].node), (yyvsp[-1].node), NULL); }
#line 1749 "bison.tab.c"
    break;

  case 37:
#line 103 "bison.y"
                                                                                        { (yyval.node) = newIf((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1755 "bison.tab.c"
    break;

  case 38:
#line 105 "bison.y"
                                                                                        { (yyval.node) = newAST('P', NULL, (yyvsp[-1].node)); }
#line 1761 "bison.tab.c"
    break;

  case 39:
#line 106 "bison.y"
                                                                                        { (yyval.node) = newAST('P', newVariable(0, 0, NULL), (yyvsp[-1].node)); }
#line 1767 "bison.tab.c"
    break;

  case 40:
#line 107 "bison.y"
                                                                                        { (yyval.node) = callFunction("S", newReference(0, (yyvsp[-1].name))); }
#line 1773 "bison.tab.c"
    break;

  case 41:
#line 108 "bison.y"
                                                                                        { (yyval.node) = callFunction("H", newAST('L', (yyvsp[-1].node), newReference(0, (yyvsp[-3].name)))); }
#line 1779 "bison.tab.c"
    break;

  case 43:
#line 110 "bison.y"
                                                                                        { (yyval.node) = callFunction("J", newReference(0, (yyvsp[-1].name))); }
#line 1785 "bison.tab.c"
    break;

  case 44:
#line 111 "bison.y"
                                                                                        { (yyval.node) = callFunction("J", newAST('L', (yyvsp[-1].node), newReference(0, (yyvsp[-3].name)))); }
#line 1791 "bison.tab.c"
    break;

  case 45:
#line 112 "bison.y"
                                                                                        { (yyval.node) = callFunction("Q", newReference(0, (yyvsp[-1].name))); }
#line 1797 "bison.tab.c"
    break;

  case 46:
#line 113 "bison.y"
                                                                                        { (yyval.node) = callFunction("K", newAST('L', (yyvsp[-1].node), newReference(0, (yyvsp[-3].name)))); }
#line 1803 "bison.tab.c"
    break;

  case 47:
#line 114 "bison.y"
                                                                                        { (yyval.node) = callFunction("Y", newReference(0, (yyvsp[-1].name))); }
#line 1809 "bison.tab.c"
    break;

  case 48:
#line 117 "bison.y"
                                                                                        { (yyval.node) = newAST('L', newAssignment((yyvsp[0].name), newVariable((yyvsp[-1].type), 0, "")), newReference((yyvsp[-1].type), (yyvsp[0].name))); }
#line 1815 "bison.tab.c"
    break;

  case 49:
#line 118 "bison.y"
                                                                                        { (yyval.node) = newAST('L', newAssignment((yyvsp[-2].name), (yyvsp[0].node)), newReference((yyvsp[-3].type), (yyvsp[-2].name))); }
#line 1821 "bison.tab.c"
    break;

  case 50:
#line 119 "bison.y"
                                                                                        { (yyval.node) = newVector((yyvsp[-5].type), (yyvsp[-3].name), NULL); }
#line 1827 "bison.tab.c"
    break;

  case 51:
#line 120 "bison.y"
                                                                                        { (yyval.node) = newVector((yyvsp[-6].type), (yyvsp[-4].name), (yyvsp[-1].node)); }
#line 1833 "bison.tab.c"
    break;

  case 52:
#line 121 "bison.y"
                                                                                        { (yyval.node) = newVector((yyvsp[-4].type), (yyvsp[-2].name), (yyvsp[0].node)); }
#line 1839 "bison.tab.c"
    break;

  case 56:
#line 127 "bison.y"
                                                                                        { (yyval.node) = newAssignment((yyvsp[-2].name), (yyvsp[0].node)); }
#line 1845 "bison.tab.c"
    break;

  case 57:
#line 128 "bison.y"
                                                                                        { (yyval.node) = newAssignment((yyvsp[-3].name), newAST('+', (yyvsp[0].node), newReference(0, (yyvsp[-3].name)))); }
#line 1851 "bison.tab.c"
    break;

  case 58:
#line 129 "bison.y"
                                                                                        { (yyval.node) = newAssignment((yyvsp[-3].name), newAST('-', (yyvsp[0].node), newReference(0, (yyvsp[-3].name)))); }
#line 1857 "bison.tab.c"
    break;

  case 59:
#line 130 "bison.y"
                                                                                        { (yyval.node) = newAssignment((yyvsp[-3].name), newAST('*', (yyvsp[0].node), newReference(0, (yyvsp[-3].name)))); }
#line 1863 "bison.tab.c"
    break;

  case 60:
#line 131 "bison.y"
                                                                                        { (yyval.node) = newAssignment((yyvsp[-3].name), newAST('/', (yyvsp[0].node), newReference(0, (yyvsp[-3].name)))); }
#line 1869 "bison.tab.c"
    break;

  case 61:
#line 134 "bison.y"
                                                                                        { (yyval.node) = newReference(0, (yyvsp[0].name)); }
#line 1875 "bison.tab.c"
    break;

  case 62:
#line 135 "bison.y"
                                                                                        { (yyval.node) = newVariable(5, 0, (yyvsp[0].str)); }
#line 1881 "bison.tab.c"
    break;

  case 63:
#line 136 "bison.y"
                                                                                        { (yyval.node) = newVariable(6, 0, (yyvsp[0].str)); }
#line 1887 "bison.tab.c"
    break;

  case 64:
#line 137 "bison.y"
                                                                                        { (yyval.node) = newVariable(1, (yyvsp[0].integer), NULL); }
#line 1893 "bison.tab.c"
    break;

  case 65:
#line 138 "bison.y"
                                                                                        { (yyval.node) = newVariable(2, (yyvsp[0].real), NULL); }
#line 1899 "bison.tab.c"
    break;

  case 66:
#line 139 "bison.y"
                                                                                        { (yyval.node) = callFunction((yyvsp[-2].name), NULL); }
#line 1905 "bison.tab.c"
    break;

  case 67:
#line 140 "bison.y"
                                                                                        { (yyval.node) = callFunction((yyvsp[-3].name), (yyvsp[-1].node)); }
#line 1911 "bison.tab.c"
    break;

  case 68:
#line 141 "bison.y"
                                                                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1917 "bison.tab.c"
    break;

  case 69:
#line 142 "bison.y"
                                                                                        { (yyval.node) = newAST((yyvsp[-3].type), NULL, (yyvsp[-1].node)); }
#line 1923 "bison.tab.c"
    break;

  case 70:
#line 143 "bison.y"
                                                                                        { (yyval.node) = newAST('M', NULL, (yyvsp[0].node)); }
#line 1929 "bison.tab.c"
    break;

  case 71:
#line 144 "bison.y"
                                                                                        { (yyval.node) = newAST('U', NULL,  (yyvsp[0].node)); }
#line 1935 "bison.tab.c"
    break;

  case 72:
#line 145 "bison.y"
                                                                                        { (yyval.node) = newAST('+', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1941 "bison.tab.c"
    break;

  case 73:
#line 146 "bison.y"
                                                                                        { (yyval.node) = newAST('-', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1947 "bison.tab.c"
    break;

  case 74:
#line 147 "bison.y"
                                                                                        { (yyval.node) = newAST('*', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1953 "bison.tab.c"
    break;

  case 75:
#line 148 "bison.y"
                                                                                        { (yyval.node) = newAST('/', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1959 "bison.tab.c"
    break;

  case 76:
#line 149 "bison.y"
                                                                                        { (yyval.node) = newAST('%', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1965 "bison.tab.c"
    break;

  case 77:
#line 150 "bison.y"
                                                                                        { (yyval.node) = newAST('^', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1971 "bison.tab.c"
    break;

  case 78:
#line 151 "bison.y"
                                                                                        { (yyval.node) = newAST('A', (yyvsp[-1].node), (yyvsp[-5].node)); }
#line 1977 "bison.tab.c"
    break;

  case 79:
#line 152 "bison.y"
                                                                                        { (yyval.node) = newAST('A', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1983 "bison.tab.c"
    break;

  case 80:
#line 153 "bison.y"
                                                                                        { (yyval.node) = newAST('O', (yyvsp[-1].node), (yyvsp[-5].node)); }
#line 1989 "bison.tab.c"
    break;

  case 81:
#line 154 "bison.y"
                                                                                        { (yyval.node) = newAST('O', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1995 "bison.tab.c"
    break;

  case 82:
#line 155 "bison.y"
                                                                                        { (yyval.node) = newAST('N', NULL, (yyvsp[-1].node)); }
#line 2001 "bison.tab.c"
    break;

  case 83:
#line 156 "bison.y"
                                                                                        { (yyval.node) = newAST((yyvsp[-1].compare), (yyvsp[0].node), (yyvsp[-2].node)); }
#line 2007 "bison.tab.c"
    break;

  case 88:
#line 165 "bison.y"
                                                                                        { (yyval.node) = newAST('L', (yyvsp[0].node), (yyvsp[-2].node)); }
#line 2013 "bison.tab.c"
    break;


#line 2017 "bison.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 168 "bison.y"


int main(int argc, char** argv) {
  initList();
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s \n", numlin, mens);
}

