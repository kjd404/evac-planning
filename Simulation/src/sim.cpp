// Copyright 2017 <University of Idaho>
#include "ga.h"
#include "parser.tab.h"

extern int yyparse();
extern YYSTYPE yylval;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

int main() {
  initRand();
  int yyparse_return_val = 0;

  if ((yyparse_return_val = yyparse()) != 0) {
    printf("Ended with some parse error. Code = %d \n",
	   yyparse_return_val);
  }
  exit(0);
}
