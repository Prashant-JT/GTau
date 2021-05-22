#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initList() {
  if (!head){
    free(head);
  }

  head = (node_t *)malloc(sizeof(node_t));
  
  if (head == NULL){
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  tail = head;
  head->next = NULL;
}

struct ast *newReference(int varType, char *name) {
  struct reference *ref = malloc(sizeof(struct reference));
  
  if(!ref) {
    fprintf(stderr,"Error: Out of space");
    exit(0);
  }

  ref->nodeType = 'R'; 
  struct symbol *sym = malloc(sizeof(struct symbol));

  if(!sym) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  ref->sym = sym;
  sym->type = varType;
  sym->name = name;
  
  return (struct ast *)ref;
}

struct ast *newVariable(int type, double value, char *stringVal) {
  struct variable *var = malloc(sizeof(struct variable));

  if(!var) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  var->val = value;
  var->type = type;
  var->nodeType = 'V';
  var->stringVal = stringVal;
  
  return (struct ast *)var;
}

struct ast *callFunction(char *name, struct ast *params) {
  struct callFn *calledFunction = malloc(sizeof(struct callFn));
  
  if(!calledFunction) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }
  calledFunction->nodeType = 'C';
  calledFunction->parameters = params;
  calledFunction->name = name;
  
  return (struct ast *)calledFunction;
}

struct ast *newAST(int nodeType, struct ast *left, struct ast *right) {
  struct ast *astVar = malloc(sizeof(struct ast));
  
  if(!astVar) {
    fprintf(stderr, "out of space");
    exit(0);
  }
  astVar->nodeType = nodeType;
  astVar->left = left;
  astVar->right = right;

  printf("Tipo-%d Left-%d Right-%d\n", astVar->nodeType, left->nodeType, right->nodeType);
  return astVar;
}

struct ast *newAssignment(char *name, struct ast *value) {
  struct symbolAssign *assign = malloc(sizeof(struct symbolAssign));
  
  if(!assign) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  assign->nodeType = '=';
  assign->name = name;
  assign->value = value;
  return (struct ast *)assign;
}

struct ast *newIf(struct ast *cond, struct ast *left, struct ast *right) {
  struct condition *ifVar = malloc(sizeof(struct condition));

  if(!ifVar) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  ifVar-> nodeType = 'I';
  ifVar->cond = cond;
  ifVar->left = left;
  ifVar->right = right;

  return (struct ast *)ifVar;
}

struct ast *newFor(struct ast *declaration, struct ast *cond, struct ast *increment, struct ast *left) {
  struct iterator *iter = malloc(sizeof(struct iterator));

  if(!iter){
    fprintf(stderr,"Error: Out of space");
    exit(0);
  }
  
  iter->nodeType = 'F';
  iter->declaration = declaration;
  iter->cond = cond;
  iter->increment = increment;
  iter->left = left;

  return (struct ast *)iter;
}
/*
void newFunction(int type, char *name, struct symboList *params, struct ast *content) {
  struct symbol *function = lookup_func(name);

  if (function != NULL){
    fprintf(stderr, "Error: Function %s already defined", name);
    exit(1);
  }

  set_free_scope();

  struct symbol *sym = malloc(sizeof(struct symbol));

  if(!sym) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  sym->name = name;
  sym->type = type;
  sym->syms = syms;
  sym->scope = free_scope;
  sym->funcs = funcs;

  tail->next = (node_t *)malloc(sizeof(node_t));
  tail = tail->next;
  tail->val = sym;
  free_scope = 0;
}*/