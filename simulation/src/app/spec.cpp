// Copyright 2017 <University of Idaho>
#include "spec.h"
#include "parser.tab.h"

/**
 * Reports errors.
 */
void lexerr(char *s) {
  if (s != nullptr) {
    fprintf(stderr, "%s\n", s);
  } else {
    fprintf(stderr, "POINTER ERROR. TERMINATING...\n");
    exit(1);
  }
}

int makeToken(int ID, char *yyTextString) {
  // Allocate and initialize new memory for type treeNode.
  struct treeNode *newLeaf =
    (struct treeNode *)calloc(1, sizeof(struct treeNode));

  if (newLeaf) {
    newLeaf->u.tokptr = (struct token *)calloc(1, sizeof(struct token));
    newLeaf->category = ID;
    newLeaf->u.tokptr->tokenID = ID;
    newLeaf->u.tokptr->text = strdup(yyTextString);

    // Switch on the ID value of the token, to retreive values for literals.
    switch (ID) {
    case STRING:
      newLeaf->u.tokptr->sval = strdup(yyTextString);
      break;
    case INT:
      newLeaf->u.tokptr->ival = getIntegerValue(yyTextString);
      break;
    case FLOAT:
      newLeaf->u.tokptr->fval = getFloatValue(yyTextString);
      break;
    default:
      break;
    }

    // Place the leaf into the treeNode yylval union. For passing to bison.
    yylval.treeptr = newLeaf;
  } else {
    fprintf(stderr, "Memory allocation error. Exiting.\n");
    exit(-1);
  }
  return ID;
}

struct treeNode * alcNode(int cat, char *ruleName, int nChilds, ...) {
  // Allocate a new treeNode
  va_list vParams;
  struct treeNode *newNode =
    (struct treeNode *)calloc(1, sizeof(struct treeNode));

  if (!newNode) {
    fprintf(stderr, "Memory allocation error. Exiting.\n");
    exit(-1);
  }

  // Initialize some of the data.
  newNode->category = cat;
  newNode->numChildren = nChilds;
  newNode->u.nonterm.nonTermName = strdup(ruleName);

  // Start variable argument environment
  va_start(vParams, nChilds);
  int i = 0;

  for (i = 0; i < nChilds; i++) {
    // Populate children fields with arguments provided.
    newNode->u.nonterm.children[i] = va_arg(vParams, struct treeNode *);
  }

  va_end(vParams);

  return newNode;
}

int getIntegerValue(char *theStr) {
  int theInt = -100;
  if (theStr != nullptr) {
    theInt = atoi(theStr);
  }

  return theInt;
}

float getFloatValue(char *theStr) {
  float theFloat = -100.;
  if (theStr != nullptr) {
    theFloat = atof(theStr);
  }

  return theFloat;
}
