
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 236 "final.y"

    int intVal;
	double val;
	char* stringValue;
    struct Parameter* parameters;



/* Line 1676 of yacc.c  */
#line 100 "final.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


