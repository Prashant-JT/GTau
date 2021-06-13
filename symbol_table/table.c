#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int scope = 0;

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

struct symbol *searchReference(char *symName) {
  if (head == NULL) {
    fprintf(stderr, "Error: Symbol table not initialized");
    exit(1);
  }

  node_t *temp = head;

  while(temp->next != NULL){
    temp = temp->next;    
    if (temp->value != NULL && temp->value->scope == scope && (strcmp(temp->value->name, symName) == 0)){
      return temp->value;
    }
  }

  return NULL;
}

struct ast *newReference(int varType, char *name) {
  /*struct symbol *newRef = searchReference(name);
  if (newRef != NULL){
    fprintf(stderr, "Error: Variable %s already defined ", name);
    exit(1);
  }*/

  struct reference *ref = malloc(sizeof(struct reference));
  
  if(!ref) {
    fprintf(stderr,"Error: Out of space");
    exit(1);
  }

  ref->nodeType = 'R'; 
  struct symbol *sym = malloc(sizeof(struct symbol));

  if(!sym) {
    fprintf(stderr, "Error: Out of space");
    exit(1);
  }

  ref->sym = sym;
  sym->type = varType;
  sym->name = name;

  eval((struct ast *)ref);

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
  var->nodeType = 'E';
  var->stringVal = stringVal;
  
  return (struct ast *)var;
}

struct ast *newVector(int type, char *name, struct ast *elements) {
  struct vector *vec = malloc(sizeof(struct vector));

  if(!vec) {
    fprintf(stderr,"Error: Out of space");
    exit(0);
  }
  
  vec->nodeType = 'V';
  vec->type = type;
  vec->name = name;
  vec->elements = elements;

  return (struct ast *)vec;
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

struct ast *newAST(int nodeType, struct ast *right, struct ast *left) {
  struct ast *astVar = malloc(sizeof(struct ast));
  
  if(!astVar) {
    fprintf(stderr, "out of space");
    exit(0);
  }
  astVar->nodeType = nodeType;
  astVar->left = left;
  astVar->right = right;

  return astVar;
}

struct symboList *newSymboList(struct ast *actual, struct symboList *next) {
  struct symboList *symList = malloc(sizeof(struct symboList));

  if(!symList) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }

  symList->actual = actual;
  symList->next = next;
  return symList;
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

  eval((struct ast *)assign);

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

static struct symbol *searchFunction(char *name) {
  if (head == NULL) {
    fprintf(stderr, "Error: Symbol table not initialized");
    exit(1);
  }

  node_t *temp = head;

  while(temp->next != NULL) {
    temp = temp->next;
    if ( temp->value != NULL && temp->value->scope > 0 && (strcmp(temp->value->name, name) == 0) ){
      return temp->value;
    }
  }
 
  return NULL;
}

void setScope() {
  if (head == NULL) {
    fprintf(stderr, "Error: Symbol table not initialized");
    exit(1);
  }

  node_t *temp = head;
  int maxScope = 0;

  while(temp->next != NULL) {
    temp = temp->next;
    if (temp->value->scope > maxScope){
      maxScope = temp->value->scope;
    }
  }

  scope = maxScope + 1;
}

void newFunction(int type, char *name, struct symboList *params, struct ast *content) {
  struct symbol *function = searchFunction(name);

  if (function != NULL){
    fprintf(stderr, "Error: Function %s already defined ", name);
    exit(1);
  }

  setScope();
  struct symbol *funcSymbol = malloc(sizeof(struct symbol));

  if(!funcSymbol) {
    fprintf(stderr, "Error: Out of space");
    exit(0);
  }
  /*
  struct symboList *temp = params;

  while(temp->next != NULL) {
    temp = temp->next;
    printf("%i\n", temp->actual->nodeType);
  }*/

  funcSymbol->name = name;
  funcSymbol->type = type;
  funcSymbol->scope = scope;
  funcSymbol->params = params;
  funcSymbol->content = content;

  tail->next = (node_t *)malloc(sizeof(node_t));
  tail = tail->next;
  tail->value = funcSymbol;
  scope = 0;
}

struct symbol *evaluateConstant(struct ast *a){
  struct symbol *sym = malloc(sizeof(struct symbol));
  struct variable *value = (struct variable *)a;

  sym->type = value->type;

  switch(value->type){
    case 1: sym->intVal = value->val;
    case 2: sym->doubleVal = value->val;
    case 3: sym->floatVal = value->val;
    case 5:
    case 6: sym->stringVal = value->stringVal;
      break;
    default:
      fprintf(stderr, "Error: Wrong variable type\n");
      exit(1);
  }

  return sym;
}

// ----------------------------- Evaluate -------------------------- //

struct symbol *lookup(char *symName) {
  if (head == NULL) {
    fprintf(stderr, "Error: Symbol table not initialized");
    exit(1);
  }

  node_t *temp = head;

  while(temp->next != NULL){
    temp = temp->next;    
    if (temp->value != NULL && temp->value->scope == scope && (strcmp(temp->value->name, symName) == 0)){
      return temp->value;
    }
  }

  return NULL;
}

struct symbol *evaluateReference(struct ast *a) {
  struct reference *ref = (struct reference *)a;
  struct symbol *sym = lookup(ref->sym->name);

  if (sym != NULL){
    if (ref->sym->type != 0) sym->type = ref->sym->type;
    return sym;
  }

  if (ref->sym->type == 0){
    fprintf(stderr, "Error: Variable %s not defined\n", ref->sym->name);
    exit(1);
  }

  ref->sym->scope = scope;
  tail->next = (node_t *)malloc(sizeof(node_t));

  if(!tail->next) {
    fprintf(stderr, "Error: Out of space\n");
    exit(0);
  }

  tail = tail->next;
  tail->value = ref->sym;

  return ref->sym;
}

void checkTypes(int lt, int rt)
{
  char* types[] = {"int", "double", "float", "boolean", "char", "string"};

  if (!((rt == 2 && (lt == 2 || lt == 3)) || (rt == 1 && (lt == 1 || lt == 2 || lt == 3)) || lt == rt)) {
    fprintf(stderr, "Error: Wrong type (%s) and value (%s)\n", types[lt-1], types[rt-1]);
    exit(1);
  }
}

struct symbol *evaluateAssign(struct ast *a)
{
  struct symbolAssign *assign = (struct symbolAssign *)a;
  struct symbol *sym = lookup(assign->name);

  if (sym == NULL){
    fprintf(stderr, "Error: Variable %s not found\n", assign->name);
    exit(1);
  }
  
  struct symbol *value = eval(assign->value);

  checkTypes(sym->type, value->type);

  switch(sym->type){
    case 1: sym->intVal = (int)(value->intVal);
    case 2: sym->doubleVal = value->doubleVal; break;
    case 3: sym->floatVal = value->floatVal; break;
    case 5:
    case 6: sym->stringVal = value->stringVal; break;
    default: fprintf(stderr, "Error: Error asigning value to %s\n", sym->name);
  }

  return sym;
}

struct symbol *eval(struct ast *a) {
    if(!a) {
        fprintf(stderr, "Error: Internal error, null evaluate");
        exit(1);
    }

    struct symbol *res = malloc(sizeof(struct symbol));

    switch(a->nodeType) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case '+': 
        case '-': 
        case '*': 
        case '/': 
        case '^':
        case '%':
          // res = calculator(a->nodeType, a->left, a->right);
          break;
        case 'E': 
          res = evaluateConstant(a);
          break;
        case 'R': 
          res = evaluateReference(a);
          break;
        case '=': 
          res = evaluateAssign(a);
          break;
    }

    return res;
}