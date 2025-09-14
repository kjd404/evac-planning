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
     RUN = 267,
     SHOW = 268,
     STAR = 269,
     EDGES = 270,
     TOPOLOGY = 271,
     PROBABILITIES = 272,
     DOT = 273,
     EDGELOAD = 274,
     HEATMAP = 275,
     ALLPATHS = 276,
     NL = 277,
     SAFETY = 278,
     NODE = 279,
     AGENT = 280,
     DRAWABLE = 281,
     SIMULATE = 282,
     EXH = 283,
     PARAMETERS = 284,
     ES_P = 285,
     ES_C = 286,
     RANDOM = 287,
     SLANG = 288,
     PROBS = 289,
     SETS = 290,
     INIT = 291
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
#define RUN 267
#define SHOW 268
#define STAR 269
#define EDGES 270
#define TOPOLOGY 271
#define PROBABILITIES 272
#define DOT 273
#define EDGELOAD 274
#define HEATMAP 275
#define ALLPATHS 276
#define NL 277
#define SAFETY 278
#define NODE 279
#define AGENT 280
#define DRAWABLE 281
#define SIMULATE 282
#define EXH 283
#define PARAMETERS 284
#define ES_P 285
#define ES_C 286
#define RANDOM 287
#define SLANG 288
#define PROBS 289
#define SETS 290
#define INIT 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 32 "simulation/src/grammar/parser.y"
{
  struct treeNode *treeptr;
}
/* Line 1529 of yacc.c.  */
#line 125 "simulation/generated/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

