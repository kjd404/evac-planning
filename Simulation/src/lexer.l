/* lexer.l v0.0.1 
 * Created by Keith Drew for Evac Planning simulation project
 * Based on the SLANG definition created by Damian Ball and Robert Heckendorn
 */

%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "spec.h"

#define MTOK makeToken

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"

/* Add function prototypes here, as needed */

void lexerr( char *s );

extern YYSTYPE yylval;
%}

%option noyywrap

intsuffix          ([uU][lL]?)|([lL][uU]?)
fracconst          ([0-9]*\.[0-9]+)|([0-9]+\.)
exppart            [eE][-+]?[0-9]+
floatsuffix        [fFlL]
chartext           ([^'])|(\\.) 
stringtext         ([^"])|(\\.)

%% 

[\t\f\v\r ]+                            { /* Ignore whitespace. */ }

\/\/[^\n]*\n                              { /* ignore inline comment */ }

"\n"                                    { return MTOK( NL, yytext ); }

"*"					{ return MTOK( STAR, yytext ); }

[0-9]+{intsuffix}?			{ return MTOK( INT, yytext ); }

{fracconst}{exppart}?{floatsuffix}?	{ return MTOK( FLOAT, yytext ); }

"exit"					{ return MTOK( EXIT, yytext ); }

"quit"					{ return MTOK( QUIT, yytext ); }

"hi"					{ return MTOK( HI, yytext ); }

"city"					{ return MTOK( CITY, yytext ); }

"edge"					{ return MTOK( EDGE, yytext ); }

"agent"                                 { return MTOK( AGENT, yytext ); }

"rmedge"				{ return MTOK( RMEDGE, yytext ); }

"run"					{ return MTOK( RUN, yytext ); }

"show"					{ return MTOK( SHOW, yytext ); }

"topology"				{ return MTOK( TOPOLOGY, yytext ); }

"probabilities"				{ return MTOK( PROBABILITIES, yytext ); }

"heatmap"				{ return MTOK( HEATMAP, yytext ); }

"dot"					{ return MTOK( DOT, yytext ); }

"allpaths"				{ return MTOK( ALLPATHS, yytext ); }

"edgeload"				{ return MTOK( EDGELOAD, yytext ); }

"edges"					{ return MTOK( EDGES, yytext ); }

"drawable"				{ return MTOK( DRAWABLE, yytext ); }

"safety"                                { return MTOK( SAFETY, yytext ); }

"node"                                  { return MTOK( NODE, yytext ); }

"parameters"                            { return MTOK( PARAMETERS, yytext ); }

"ES+"                                   { return MTOK( ES_P, yytext ); }

"ES,"                                   { return MTOK( ES_C, yytext ); }

"simulate"                              { return MTOK( SIMULATE, yytext ); }

"exhaustive"                            { return MTOK( EXH, yytext ); }

"random"                                { return MTOK( RANDOM, yytext ); }     

"slang"                                 { return MTOK( SLANG, yytext ); }

"probs"                                 { return MTOK( PROBS, yytext ); }

"sets"                                  { return MTOK( SETS, yytext ); }

"init"                                  { return MTOK( INIT, yytext ); }

[a-zA-Z_][a-zA-Z_0-9]*			{ return MTOK( STRING, yytext ); }

%%

