// Copyright 2017 <University of Idaho>
#include "ga.h"
#include "parser.tab.h"

extern int yyparse();
extern YYSTYPE yylval;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

int main(int argc, char** argv) {
  initRand();
  int yyparse_return_val = 0;

  // If a scenario file is provided, read from it; otherwise use stdin.
  if (argc > 1 && argv[1] != nullptr) {
    FILE* f = fopen(argv[1], "r");
    if (!f) {
      fprintf(stderr, "Failed to open scenario file: %s\n", argv[1]);
      return 1;
    }
    yyin = f;
  }

  yyparse_return_val = yyparse();

  if (argc > 1 && yyin) {
    fclose(yyin);
  }

  if (yyparse_return_val != 0) {
    printf("Ended with some parse error. Code = %d \n", yyparse_return_val);
  }
  return 0;
}
