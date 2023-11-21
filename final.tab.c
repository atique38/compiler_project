
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "final.y"

	#include <stdlib.h>
    #include <stdio.h>
    #include<string.h>
    #include<math.h>

    void yyerror(char *s);
    extern char* varType;

    int countVar=0;
    struct Symbol {
        char* name;
        char* datatype;
        int int_value;
        float float_value;
        char *string_value;
        struct Symbol* next;
    };

    struct Symbol* symbol_table = NULL;

    const char* keywords[] = {"int","float","string","ghorao_baccha","roko_jara","back","action","nothing","if","else","elif","fi","for","while","shonjog","khela shuru","khela sesh",NULL};
    //const char* datatype[] = {"int","float","char",NULL};

    int isReservedKeyword(const char* word) {
        for (int i = 0; keywords[i] != NULL; i++) {
            if (strcmp(keywords[i], word) == 0) {
                return 1;
            }
        }
        return 0;
    }

    void insertVariable(const char* name, const char* vType) {
        struct Symbol* symbol = malloc(sizeof(struct Symbol));
        symbol->name = strdup(name);
        symbol->datatype = strdup(vType);
        symbol->next = symbol_table;
        symbol_table = symbol;
        countVar++;
        printf("variable: %s, datatype: %s\n",symbol->name,symbol->datatype);
    } 

    void insertDatatype(const char* varName, const char* dType) {
        struct Symbol* current = symbol_table;

        while (current != NULL) {
            if (strcmp(current->name, varName) == 0) {
                //printf("datatype: %s var: %s\n",dType,varName);
                current->datatype = strdup(dType); // Update the value
                return ; 
            }
            current = current->next;
        }
    } 

    int isDuplicate(const char* name) {
        struct Symbol* current = symbol_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                //printf("duplicate found %s\n",current->name);
                return 1; // Symbol is already declared
            }
            current = current->next;
        }
        return 0; // Symbol is not declared
    } 

    int updateVariableValue(const char* name, const char* value) {
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                //printf("%s %s %s\n",name,value,current->datatype);
                if(strcmp(current->datatype,"int") == 0){
                    //printf("ok\n");
                    int x= atoi(value);
                    current->int_value = x;
                    printf("\nvalue of %s = %d\n",name,current->int_value);
                }
                else if(strcmp(current->datatype,"float") == 0){
                    float x= atof(value);
                    current->float_value = x;
                    printf("\nvalue of %s = %.4f\n",name,current->float_value);
                }
                else if(strcmp(current->datatype,"string") == 0){
                    //printf("%s\n",value);
                    current->string_value = value;
                    printf("\nvalue of %s = %s\n",name,current->string_value);
                }
                else {
                    printf("\n '%s' is invalid datatype\n",value,current->datatype);
                }
                return 1; 
            }
            current = current->next;
        }
        return 0;
        

    } 

    int checkValidity(const char* word){
        if(isReservedKeyword(word)){
            printf("\nReserved word '%s' can't be used as variable.\n",word);
            return 0;
        }
        else if(isDuplicate(word)){
            printf("\nvariable '%s' is already declared.\n",word);
            return 0;
        }
        //printf(word);
        return 1;
    }

    const char* getValue(const char* name){
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                if(strcmp(current->datatype,"int") == 0){
                    char* str;
                    sprintf(str, "%d", current->int_value);
                    //printf("%s\n",str);
                    return str;
                }
                else if(strcmp(current->datatype,"float") == 0){
                    char* str;
                    sprintf(str, "%.4f", current->float_value);
                    //printf("%s\n",str);
                    return str;
                }
                else if(strcmp(current->datatype,"string") == 0){
                   return current->string_value;
                }
                printf("\nno value exist for '%s'\n",name);
                return "null"; 
            }
            current = current->next;
        }
        printf("\nvariable '%s' is not declared\n",name);
        return "null";
    }

     const char* getType(const char* name){
        struct Symbol* current = symbol_table;
        while (current != NULL) {
           
            if (strcmp(current->name, name) == 0) {
                return current->datatype; 
            }
            current = current->next;
        }
        printf("\nvariable '%s' is not declared\n",name);
        return "null";
    }

   

    typedef struct Parameter {
        char* name;
        char* paramType;
        char* paramValue;
        struct Parameter* next;
    } Parameter;
 

     struct FuncDeclaration {
        char* name;
        char* return_type; 
        Parameter* parameters;
        struct FuncDeclaration* next;
    };

    struct FuncDeclaration* func_table = NULL;

     void add_function_to_table(char* name, char* has_return_type, Parameter* parameters) {
        struct FuncDeclaration* new_func = malloc(sizeof(struct FuncDeclaration));
        new_func->name = strdup(name);
        new_func->return_type = has_return_type;
        new_func->parameters = parameters;
        new_func->next = func_table;
        func_table = new_func;

        printf("\nfuntion '%s' is declared. return type: '%s' ",new_func->name,new_func->return_type);
        printf("parametrs:");
        print_parameters(new_func->parameters);
    }

    int isFunctionDeclared(char* name) {
        struct FuncDeclaration* current = func_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return 1; // Function is declared
            }
            current = current->next;
        }
        return 0; // Function is not declared
    }

    Parameter* get_parameters_for_function(char* name) {
        struct FuncDeclaration* current = func_table;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return current->parameters; // Return the parameters for the function
            }
            current = current->next;
        }
        return NULL; // Function not found
    }

    int count_parameters(Parameter* params) {
        int count = 0;
        Parameter* current = params;
        while (current != NULL) {
            if(strcmp(params->paramType,"null")){
                count++;
            }
            //count++;
            
            current = current->next;
        }
        return count;
    }

    void print_parameters(Parameter* parameters) {
        Parameter* current = parameters;
        while (current != NULL) {
            printf(" %s (%s) ", current->name,current->paramType);
            current = current->next;
        }
        printf("\n");
    }


/* Line 189 of yacc.c  */
#line 309 "final.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HEADER = 258,
     MAIN_START = 259,
     MAIN_END = 260,
     DATATYPE = 261,
     VARIABLE = 262,
     INT = 263,
     FLOAT = 264,
     STRING = 265,
     NUM = 266,
     PLUS = 267,
     MINUS = 268,
     MULTI = 269,
     DIV = 270,
     MOD = 271,
     LT = 272,
     LTE = 273,
     GT = 274,
     GTE = 275,
     E = 276,
     NE = 277,
     AND = 278,
     OR = 279,
     IF = 280,
     ELSE_IF = 281,
     ELSE = 282,
     WHILE = 283,
     START = 284,
     END = 285,
     FUN = 286,
     VOID = 287,
     BACK = 288,
     INPUT = 289,
     OUTPUT = 290,
     SIN = 291,
     COS = 292,
     TAN = 293,
     HIGH = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 236 "final.y"

    int intVal;
	double val;
	char* stringValue;
    struct Parameter* parameters;



/* Line 214 of yacc.c  */
#line 393 "final.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 405 "final.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   260

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  150

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     9,    11,    14,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    47,    50,    52,
      56,    60,    64,    68,    72,    76,    80,    84,    88,    92,
      96,   100,   104,   108,   112,   116,   120,   122,   124,   126,
     132,   142,   153,   168,   174,   176,   179,   189,   199,   200,
     201,   204,   209,   214,   215,   217,   221,   226,   228,   232,
     237,   242,   247,   252
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    57,     4,    49,     5,    -1,     3,
      -1,    48,     3,    -1,    -1,    50,    49,    -1,    52,    49,
      -1,    55,    49,    -1,    56,    49,    -1,    60,    49,    -1,
      62,    49,    -1,    64,    49,    -1,    65,    49,    -1,    66,
      49,    -1,    67,    49,    -1,    53,    -1,     6,    51,    -1,
       7,    -1,    51,    40,     7,    -1,     7,    41,    53,    -1,
       7,    41,    10,    -1,    53,    12,    53,    -1,    53,    13,
      53,    -1,    53,    14,    53,    -1,    53,    15,    53,    -1,
      53,    16,    53,    -1,    53,    17,    53,    -1,    53,    19,
      53,    -1,    53,    18,    53,    -1,    53,    20,    53,    -1,
      53,    21,    53,    -1,    53,    22,    53,    -1,    53,    23,
      53,    -1,    53,    24,    53,    -1,    42,    53,    43,    -1,
      54,    -1,     7,    -1,    11,    -1,    25,    53,    44,    49,
      45,    -1,    25,    53,    44,    49,    45,    27,    44,    49,
      45,    -1,    25,    53,    44,    49,    45,    26,    53,    44,
      49,    45,    -1,    25,    53,    44,    49,    45,    26,    53,
      44,    49,    45,    27,    44,    49,    45,    -1,    28,    53,
      29,    49,    30,    -1,    58,    -1,    58,    57,    -1,    31,
       6,     7,    42,    59,    43,    44,    49,    45,    -1,    31,
      32,     7,    42,    59,    43,    44,    49,    45,    -1,    -1,
      -1,     6,     7,    -1,    59,    40,     6,     7,    -1,     7,
      42,    61,    43,    -1,    -1,    53,    -1,    61,    40,    53,
      -1,    34,    42,    63,    43,    -1,     7,    -1,    63,    40,
       7,    -1,    35,    42,    53,    43,    -1,    35,    42,    10,
      43,    -1,    36,    42,    53,    43,    -1,    37,    42,    53,
      43,    -1,    38,    42,    53,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   255,   255,   257,   258,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   274,   276,   290,
     307,   318,   329,   338,   346,   354,   362,   369,   378,   387,
     396,   405,   414,   423,   432,   441,   445,   451,   460,   466,
     476,   485,   494,   508,   518,   519,   521,   533,   545,   548,
     554,   562,   571,   600,   606,   611,   619,   624,   646,   667,
     670,   675,   683,   691
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER", "MAIN_START", "MAIN_END",
  "DATATYPE", "VARIABLE", "INT", "FLOAT", "STRING", "NUM", "PLUS", "MINUS",
  "MULTI", "DIV", "MOD", "LT", "LTE", "GT", "GTE", "E", "NE", "AND", "OR",
  "IF", "ELSE_IF", "ELSE", "WHILE", "START", "END", "FUN", "VOID", "BACK",
  "INPUT", "OUTPUT", "SIN", "COS", "TAN", "HIGH", "','", "'='", "'('",
  "')'", "'{'", "'}'", "$accept", "start", "headers", "statement",
  "declaration", "var", "assignment", "expression", "term", "if_statement",
  "while_statement", "function_declarations", "function_declaration",
  "parameter_list", "function_call", "argument_list", "input_statement",
  "input_var", "output_statement", "sin_statement", "cos_statement",
  "tan_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      44,    61,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    51,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    55,
      55,    55,    55,    56,    57,    57,    58,    58,    58,    59,
      59,    59,    60,    61,    61,    61,    62,    63,    63,    64,
      64,    65,    66,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     2,     0,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     5,
       9,    10,    14,     5,     1,     2,     9,     9,     0,     0,
       2,     4,     4,     0,     1,     3,     4,     1,     3,     4,
       4,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,    48,     1,     4,     0,     0,    44,     0,
       0,     5,    45,     0,     0,     0,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     5,    16,
      36,     5,     5,     5,     5,     5,     5,     5,     5,    49,
      49,    18,    17,     0,    53,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,     0,    21,    20,    54,     0,     5,     5,    57,     0,
       0,     0,     0,     0,     0,    35,    22,    23,    24,    25,
      26,    27,    29,    28,    30,    31,    32,    33,    34,    50,
       0,     0,     0,    19,     0,    52,     0,     0,     0,    56,
      60,    59,    61,    62,    63,     0,     5,     5,    55,    39,
      43,    58,    51,     0,     0,     0,     0,    46,    47,     0,
       5,     5,     0,     0,    40,    41,     0,     5,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    26,    27,    42,    28,    29,    30,    31,
      32,     7,     8,    79,    33,    85,    34,    89,    35,    36,
      37,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int16 yypact[] =
{
       0,   -28,    15,    -1,   -28,   -28,     6,    22,    19,    30,
      39,     7,   -28,    33,    34,    72,    -2,   -28,    10,    10,
      51,    52,    53,    54,    55,    10,    93,     7,     7,   225,
     -28,     7,     7,     7,     7,     7,     7,     7,     7,   104,
     104,   -28,    71,     9,    10,   -28,    68,   207,   108,    67,
      10,    10,    10,   128,   -28,   -28,   -28,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   110,   -16,
     -15,   112,   -28,   225,   225,    -9,     7,     7,   -28,    -7,
      73,   142,   160,   174,   192,   -28,   236,   236,    84,    84,
      84,   225,   225,   225,   225,   225,   225,   225,   225,   -28,
     129,    90,    92,   -28,    10,   -28,   122,   107,   131,   -28,
     -28,   -28,   -28,   -28,   -28,   161,     7,     7,   225,    31,
     -28,   -28,   -28,   124,   125,    10,   155,   -28,   -28,   109,
       7,     7,   156,   157,   -28,   173,   188,     7,   189,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   -27,   -28,   -28,   -28,     4,   -28,   -28,
     -28,   210,   -28,   193,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    56,     5,     1,    70,    71,    72,    73,    74,    75,
      76,    77,     9,    15,    16,     4,    45,    45,    17,    82,
      17,    17,    46,    47,   110,   110,    11,   111,   112,    53,
       6,   114,    18,   118,   115,    19,   119,    13,    10,    43,
      44,    20,    21,    22,    23,    24,    14,    83,    84,    25,
       6,    25,    25,    91,    92,    93,    94,   135,   136,   116,
     117,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    45,    39,    40,    90,    17,    41,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    48,    49,    50,    51,    52,    54,   133,
     134,    62,    63,    64,    65,    66,    67,    68,    69,    25,
      78,    81,    86,   142,   143,    88,   120,   109,   128,   113,
     148,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,   126,   125,   127,   130,   131,   139,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   141,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   129,   132,   137,
     138,    95,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   121,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,   140,
     146,   144,   145,   122,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   123,    12,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,   147,    80,   149,   124,    87,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69
};

static const yytype_uint8 yycheck[] =
{
      27,    28,     3,     3,    31,    32,    33,    34,    35,    36,
      37,    38,     6,     6,     7,     0,     7,     7,    11,    10,
      11,    11,    18,    19,    40,    40,     4,    43,    43,    25,
      31,    40,    25,    40,    43,    28,    43,     7,    32,    41,
      42,    34,    35,    36,    37,    38,     7,    43,    44,    42,
      31,    42,    42,    49,    50,    51,    52,    26,    27,    86,
      87,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     7,    42,    42,    10,    11,     7,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    42,    42,    42,    42,    42,     5,   126,
     127,    17,    18,    19,    20,    21,    22,    23,    24,    42,
       6,    40,    44,   140,   141,     7,    43,     7,   114,     7,
     147,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    44,     6,    44,    30,     7,   135,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    44,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    45,     7,    45,
      45,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    44,
      27,    45,    45,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    43,     8,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    44,    40,    45,    43,    29,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    47,    48,     0,     3,    31,    57,    58,     6,
      32,     4,    57,     7,     7,     6,     7,    11,    25,    28,
      34,    35,    36,    37,    38,    42,    49,    50,    52,    53,
      54,    55,    56,    60,    62,    64,    65,    66,    67,    42,
      42,     7,    51,    41,    42,     7,    53,    53,    42,    42,
      42,    42,    42,    53,     5,    49,    49,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      49,    49,    49,    49,    49,    49,    49,    49,     6,    59,
      59,    40,    10,    53,    53,    61,    44,    29,     7,    63,
      10,    53,    53,    53,    53,    43,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,     7,
      40,    43,    43,     7,    40,    43,    49,    49,    40,    43,
      43,    43,    43,    43,    43,     6,    44,    44,    53,    45,
      30,     7,     7,    49,    49,    26,    27,    45,    45,    53,
      44,    44,    49,    49,    45,    45,    27,    44,    49,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 255 "final.y"
    {printf("\nvalid structure\n");;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 257 "final.y"
    {printf("Header Library Declared Here\n");;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 258 "final.y"
    {printf("Header Library Declared Here\n");;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 276 "final.y"
    {
        //printf("variable: %s\n",$1);
        int x=checkValidity((yyvsp[(1) - (1)].stringValue));
        if(x){
            insertVariable((yyvsp[(1) - (1)].stringValue),varType);
            //strcpy($$,$1);
            //$$=$1;
        }
        // else{
        //     //strcpy($$,"null");
        //     $$="null";
        // }
        
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 290 "final.y"
    {
        //printf("variable: %s\n",$3);
        int x=checkValidity((yyvsp[(3) - (3)].stringValue));
        if(x){
            insertVariable((yyvsp[(3) - (3)].stringValue),varType);
            //strcpy($$,$3);
            //$$=$3;
        }
        // else{
        //     printf("not ok\n");
        //     //$$="null";
        //     //strcpy($$,"null");
        // }
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 307 "final.y"
    {
        //printf("ass: var %s val %s\n",$1,$3);
        if(isDuplicate((yyvsp[(1) - (3)].stringValue))){

            updateVariableValue((yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
            //printf("value of %s = %s",$1,$3);
        }
        else{
            printf("\n%s is not declared before\n",(yyvsp[(1) - (3)].stringValue));
        }
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 318 "final.y"
    {
       if(isDuplicate((yyvsp[(1) - (3)].stringValue))){
            updateVariableValue((yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
            //printf("value of %s = %s",$1,$3);
        }
        else{
            printf("\n%s is not declared before\n",(yyvsp[(1) - (3)].stringValue));
        }
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 329 "final.y"
    {
       printf("%s jog %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        sprintf((yyval.stringValue), "%.4lf", num1+num2);
        //printf("%lf %lf\n",num1,num2);
        //printf("%s jog %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 338 "final.y"
    {
        printf("%s biyog %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        sprintf((yyval.stringValue), "%.4lf", num1-num2);
        //printf("%s biyog %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 346 "final.y"
    {
        printf("%s gun %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        sprintf((yyval.stringValue), "%.4lf", num1*num2);
        //printf("%s gun %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 354 "final.y"
    {
        printf("%s vag %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        sprintf((yyval.stringValue), "%.4lf", num1/num2);
        //printf("%s vag %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 362 "final.y"
    {
        printf("%s vagshesh %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        int num1=atoi((yyvsp[(1) - (3)].stringValue));
        int num2=atoi((yyvsp[(3) - (3)].stringValue));
        sprintf((yyval.stringValue), "%d", num1%num2);
        //printf("%s vagshesh %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 369 "final.y"
    {
        printf("%s less than %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue)); 
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1<num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s less than %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 378 "final.y"
    { 
        printf("%s greater than %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1>num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s greater than %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 387 "final.y"
    { 
        printf("%s less than equal %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1<=num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s less than equal %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 396 "final.y"
    { 
        printf("%s greater than equal %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1>=num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s greater than equal %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 405 "final.y"
    { 
        printf("%s equal %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1 == num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s equal %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 414 "final.y"
    { 
        printf("%s not equal %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1 != num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s not equal %s = \n",$1,$3,$$);
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 423 "final.y"
    { 
        printf("%s ebong %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1 && num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s ebong %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 432 "final.y"
    { 
        printf("%s othoba %s\n",(yyvsp[(1) - (3)].stringValue),(yyvsp[(3) - (3)].stringValue));
        char *ptr1,*ptr2;
        double num1 = strtod((yyvsp[(1) - (3)].stringValue), &ptr1);
        double num2 = strtod((yyvsp[(3) - (3)].stringValue), &ptr2);
        int x= num1||num2;
        sprintf((yyval.stringValue), "%d", x);
        //printf("%s othoba %s = %s\n",$1,$3,$$);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 441 "final.y"
    {
        (yyval.stringValue)=(yyvsp[(2) - (3)].stringValue);
        //printf("matched\n");
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 445 "final.y"
    {
        //printf("term: %s \n",$1);
        (yyval.stringValue)=(yyvsp[(1) - (1)].stringValue);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 451 "final.y"
    {
        const char* value=getValue((yyvsp[(1) - (1)].stringValue));
       // const char* dType=getType($1);
       printf("var: %s val: %s\n",(yyvsp[(1) - (1)].stringValue),value);

        if(strcmp(value,"null")){
            strcpy((yyval.stringValue),value);
        }
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 460 "final.y"
    {
        //printf("num: %s\n",$1);
        (yyval.stringValue)=(yyvsp[(1) - (1)].stringValue);
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 466 "final.y"
    {
        printf("\nif statement\n");
        //printf("exp: %s\n",$2);
        if(!strcmp((yyvsp[(2) - (5)].stringValue),"1")){
            printf("\nif statement\n");
        }
        else{
            printf("\ncondition false\n");
        }
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 476 "final.y"
    { 
        printf("\nif-else statement\n");
        if(!strcmp((yyvsp[(2) - (9)].stringValue),"1")){
            printf("\nif statement is executed\n");
        }
        else{
            printf("\nelse statement is executed\n");
        }
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 485 "final.y"
    { 
        printf("\nif-elif statement\n");
        if(!strcmp((yyvsp[(2) - (10)].stringValue),"1")){
            printf("\nif codition is true\n");
        }
        else if(!strcmp((yyvsp[(7) - (10)].stringValue),"1")){
            printf("\nelif statement is executed\n");
        }
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 494 "final.y"
    { 
        printf("\nif-else ladder statement\n");
        if(!strcmp((yyvsp[(2) - (14)].stringValue),"1")){
            printf("\nif statement is executed\n");
        }
        else if(!strcmp((yyvsp[(7) - (14)].stringValue),"1")){
            printf("\nelif statement is executed\n");
        }
        else{
            printf("\nelse statement is executed\n");
        }
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 508 "final.y"
    { 
        printf("\nwhile loop\n");
        if(strcpy((yyvsp[(2) - (5)].stringValue),"1")){
            printf("\n condition is true\n");
        }
        else{
            printf("\n condition is true\n");
        }
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 521 "final.y"
    {
        //printf("\nfun declared\n");
        //printf("\npar: %s\n",$5->name);
        //print_parameters($5);
        if(!isFunctionDeclared((yyvsp[(3) - (9)].stringValue))){
            add_function_to_table((yyvsp[(3) - (9)].stringValue),varType,(yyvsp[(5) - (9)].parameters));
        }
        else {
            printf("\nfunction '%s' is already declared\n",(yyvsp[(3) - (9)].stringValue));
        }
        
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 533 "final.y"
    {
        //printf("\nfun declared\n");
        //printf("\npar: %s\n",$5->name);
        //print_parameters($5);

        if(!isFunctionDeclared((yyvsp[(3) - (9)].stringValue))){
            add_function_to_table((yyvsp[(3) - (9)].stringValue),varType,(yyvsp[(5) - (9)].parameters));
        }
        else {
            printf("\nfunction '%s' is already declared\n",(yyvsp[(3) - (9)].stringValue));
        }
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 548 "final.y"
    { 
        (yyval.parameters) = (Parameter*)malloc(sizeof(Parameter));
        (yyval.parameters)->name = strdup("null");
        (yyval.parameters)->paramType = strdup("null");
        (yyval.parameters)->next = NULL;
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 554 "final.y"
    { 
        (yyval.parameters) = (Parameter*)malloc(sizeof(Parameter));
        (yyval.parameters)->name = strdup((yyvsp[(2) - (2)].stringValue));
        (yyval.parameters)->paramType = strdup(varType);
        (yyval.parameters)->next = NULL;
        //$$=$2;

    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 562 "final.y"
    { 
        Parameter* new_param = (Parameter*)malloc(sizeof(Parameter));
        new_param->name = strdup((yyvsp[(4) - (4)].stringValue));
        new_param->paramType = strdup(varType);
        new_param->next = (yyval.parameters);
        (yyval.parameters) = new_param;
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 571 "final.y"
    {
        if (!isFunctionDeclared((yyvsp[(1) - (4)].stringValue))) {
            printf("\nFunction '%s' not declared before use\n",(yyvsp[(1) - (4)].stringValue));
        }
        else{
            Parameter* declared_params = get_parameters_for_function((yyvsp[(1) - (4)].stringValue));
            Parameter* provided_params = (yyvsp[(3) - (4)].parameters);

            int param_count=0;
            Parameter* temp = provided_params;

            while (temp != NULL) {
                if(strcmp(temp->paramValue,"null")){
                    param_count++;
                }
                //param_count++;
                temp = temp->next;
            }

            if (param_count != 0 && param_count != count_parameters(declared_params)) {
                printf("\nIncorrect number of arguments in calling function '%s'\n",(yyvsp[(1) - (4)].stringValue));
            } 
            else {
                printf("\nFunction call to '%s' is valid\n", (yyvsp[(1) - (4)].stringValue));
            }
        }
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 600 "final.y"
    { 
        (yyval.parameters) = (Parameter*)malloc(sizeof(Parameter));
        (yyval.parameters)->paramValue = strdup("null");
        (yyval.parameters)->next = NULL;

    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 606 "final.y"
    { 
        (yyval.parameters) = (Parameter*)malloc(sizeof(Parameter));
        (yyval.parameters)->paramValue = strdup((yyvsp[(1) - (1)].stringValue));
        (yyval.parameters)->next = NULL;
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 611 "final.y"
    {
        Parameter* new_param = (Parameter*)malloc(sizeof(Parameter));
        new_param->paramValue = strdup((yyvsp[(3) - (3)].stringValue)); 
        new_param->next = (yyval.parameters);
        (yyval.parameters) = new_param;
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 619 "final.y"
    { 
        printf("is read from console \n");
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 624 "final.y"
    {
        
        int x=0;
        
        if(isReservedKeyword((yyvsp[(1) - (1)].stringValue))){
            printf("\nReserved word '%s' can't be used as variable.\n",(yyvsp[(1) - (1)].stringValue));
            x = 0;
        }
        else if(isDuplicate((yyvsp[(1) - (1)].stringValue))){
            //printf("\nvariable '%s' is already declared.\n",$1);
            x = 1;
        }
        else{
            printf("\nvariable '%s' is not declared.\n",(yyvsp[(1) - (1)].stringValue));
        }

        if(x){
            printf(" '%s' variable ",(yyvsp[(1) - (1)].stringValue));
           
        }
        
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 646 "final.y"
    {
        int x=0;
        if(isReservedKeyword((yyvsp[(3) - (3)].stringValue))){
            printf("\nReserved word '%s' can't be used as variable.\n",(yyvsp[(3) - (3)].stringValue));
            x = 0;
        }
        else if(isDuplicate((yyvsp[(3) - (3)].stringValue))){
            x = 1;
        }
        else{
            printf("\nvariable '%s' is not already declared.\n",(yyvsp[(3) - (3)].stringValue));
        }

        if(x){
            printf(" '%s' variable ",(yyvsp[(3) - (3)].stringValue));
           
        }
       
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 667 "final.y"
    { 
        printf("\n%s\n",(yyvsp[(3) - (4)].stringValue));
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 670 "final.y"
    { 
        printf("\n%s\n",(yyvsp[(3) - (4)].stringValue));
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 675 "final.y"
    {
        char *ptr1;
        double num1 = strtod((yyvsp[(3) - (4)].stringValue), &ptr1);
        double res=sin(num1*3.1416/180);
        printf("\nsin(%s)= %lf\n",(yyvsp[(3) - (4)].stringValue),res);
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 683 "final.y"
    {
        char *ptr1;
        double num1 = strtod((yyvsp[(3) - (4)].stringValue), &ptr1);
        double res=cos(num1*3.1416/180);
        printf("\ncos(%s)= %lf\n",(yyvsp[(3) - (4)].stringValue),res);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 691 "final.y"
    {
        if(!strcmp((yyvsp[(3) - (4)].stringValue),"90")){
            printf("\ntan(%s)= math error\n",(yyvsp[(3) - (4)].stringValue));
        }
        else{
            char *ptr1;
            double num1 = strtod((yyvsp[(3) - (4)].stringValue), &ptr1);
            double res=tan(num1*3.1416/180);

            printf("\ntan(%s)= %lf\n",(yyvsp[(3) - (4)].stringValue),res);
        }
        
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2419 "final.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 706 "final.y"


yyerror(char *s){  
	printf( "%s\n", s);
}

int main(){
	freopen("final_input.txt", "r",stdin);
	freopen("output.txt", "w",stdout);
	yyparse();
    printf("total variable= %d",countVar);
	return 0;
}
