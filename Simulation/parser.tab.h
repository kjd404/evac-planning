/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     INT = 258,
     FLOAT = 259,
     STRING = 260,
     EXIT = 261,
     QUIT = 262,
     HI = 263,
     CITY = 264,
     EDGE = 265,
     RMEDGE = 266,
     OD = 267,
     RUN = 268,
     SHOW = 269,
     STAR = 270,
     EDGES = 271,
     TOPOLOGY = 272,
     PROBABILITIES = 273,
     DOT = 274,
     EDGELOAD = 275,
     HEATMAP = 276,
     ALLPATHS = 277,
     NL = 278,
     SAFETY = 279,
     NODE = 280,
     AGENT = 281,
     DRAWABLE = 282,
     SIMULATE = 283,
     EXH = 284,
     PARAMETERS = 285,
     ES_P = 286,
     ES_C = 287,
     RANDOM = 288,
     SLANG = 289,
     PROBS = 290
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define STRING 260
#define EXIT 261
#define QUIT 262
#define HI 263
#define CITY 264
#define EDGE 265
#define RMEDGE 266
#define OD 267
#define RUN 268
#define SHOW 269
#define STAR 270
#define EDGES 271
#define TOPOLOGY 272
#define PROBABILITIES 273
#define DOT 274
#define EDGELOAD 275
#define HEATMAP 276
#define ALLPATHS 277
#define NL 278
#define SAFETY 279
#define NODE 280
#define AGENT 281
#define DRAWABLE 282
#define SIMULATE 283
#define EXH 284
#define PARAMETERS 285
#define ES_P 286
#define ES_C 287
#define RANDOM 288
#define SLANG 289
#define PROBS 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "parser.y"
{
  struct treeNode *treeptr;
}
/* Line 1529 of yacc.c.  */
#line 123 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

