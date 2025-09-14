// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_SPEC_H_
#define SIMULATION_INCLUDE_SPEC_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "parser.tab.h"

struct token {
  int tokenID;
  char *text;
  int ival;
  float fval;
  char *sval;
};

struct treeNode {
  /* the corresponding integer code */
  int category;

  /* 0 if no children - up to max */
  int numChildren;

  /* Union prevents memory allocation until needed */
  union {
    /* Holds values for terminals */
    struct token *tokptr;

    /* Holds values for nonterminals */
    struct nonterminal {
      char *nonTermName;
      struct treeNode *children[8];
    } nonterm;
  } u;
};

int makeToken(int ID, char *yyTextString);
void printTree(struct treeNode *root, int level);
struct treeNode * alcNode(int cat, char *ruleName, int nChilds, ...);

char * getStringValue(char *theStr);
int getIntegerValue(char *theStr);
float getFloatValue(char *theStr);

#endif  // SIMULATION_INCLUDE_SPEC_H_
