#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "operations.h"
#include "../ErrorMessage/ErrorMessage.h"
#include "../code_generation/qManage.h"
#include "../code_generation/codeGeneration.h"

int actualScope = 0;
int breakLabel = 0;
int continueLabel = 0;

struct ast *newAST(int nodeType, struct ast *left, struct ast *right)
{
  struct ast *astStm = malloc(sizeof(struct ast));

  if (!astStm)
  {
    throwError(1);
  }

  astStm->nodeType = nodeType;
  astStm->left = left;
  astStm->right = right;

  return astStm;
}

struct ast *newIf(struct ast *cond, struct ast *ifBody, struct ast *elseBody)
{
  struct ifFlow *ifStm = malloc(sizeof(struct ifFlow));

  if (!ifStm)
  {
    throwError(1);
  }

  ifStm->nodeType = 'I';
  ifStm->cond = cond;
  ifStm->ifBody = ifBody;
  ifStm->elseBody = elseBody;

  return (struct ast *)ifStm;
}

struct ast *newList(struct ast *left, struct ast *right)
{
  struct ast *paramStm = malloc(sizeof(struct ast));

  if (!paramStm)
  {
    throwError(1);
  }

  paramStm->nodeType = 'L';
  paramStm->left = left;
  paramStm->right = right;

  return paramStm;
}

struct ast *newCallFunction(char *name, struct ast *params)
{
  struct callFunction *callStm = malloc(sizeof(struct ast));
  if (!callStm)
  {
    throwError(1);
  }

  callStm->nodeType = 'C';
  callStm->params = params;
  callStm->name = name;

  return (struct ast *)callStm;
}

struct ast *newDeclaration(int type, char *name)
{
  struct declaration *decStm = malloc(sizeof(struct declaration));
  if (!decStm)
  {
    throwError(1);
  }

  decStm->nodeType = 'D';
  decStm->name = name;
  decStm->type = lookupTypeInSymbolTable(type);
  decStm->length = -1;

  return (struct ast *)decStm;
}

struct ast *newVectDeclaration(int type, char *name, int length)
{
  struct declaration *decStm = (struct declaration *)(newDeclaration(type, name));
  decStm->length = length;

  return (struct ast *)decStm;
}

struct ast *newFunction(int type, char *name, struct ast *params, struct ast *content)
{
  struct functionAST *fnAST = malloc(sizeof(struct functionAST));

  if (!fnAST)
  {
    throwError(1);
  }

  fnAST->nodeType = 'P';
  fnAST->name = name;
  fnAST->type = lookupTypeInSymbolTable(type);
  fnAST->params = params;
  fnAST->content = content;

  return (struct ast *)fnAST;
}

struct ast *newNothing()
{
  struct ast *nothing = malloc(sizeof(struct ast));
  if (!nothing)
  {
    throwError(1);
  }
  nothing->nodeType = '0';
  return nothing;
}

struct ast *newAssign(struct ast *left, struct ast *right)
{
  struct ast *assign = malloc(sizeof(struct ast));
  if (!assign)
  {
    throwError(1);
  }

  assign->nodeType = '=';
  assign->left = left;
  assign->right = right;

  return assign;
}

struct ast *newReference(char *name)
{
  struct reference *ref = malloc(sizeof(struct reference));
  if (!ref)
  {
    throwError(1);
  }

  ref->nodeType = 'R';
  ref->name = name;
  ref->a = NULL;

  return (struct ast *)ref;
}

struct ast *newChar(char *charac)
{
  struct constant *cons = malloc(sizeof(struct constant));
  if (!cons)
    throwError(1);

  cons->nodeType = 'K';
  cons->stringVal = charac;
  cons->type = lookupTypeInSymbolTable(5);

  return (struct ast *)cons;
}

struct ast *newString(char *stringValue)
{
  struct constant *cons = malloc(sizeof(struct constant));
  if (!cons)
    throwError(1);

  cons->nodeType = 'K';
  cons->type = lookupTypeInSymbolTable(5);
  cons->vector = 1;
  cons->stringVal = stringValue;

  return (struct ast *)cons;
}

struct ast *newNumber(int type, double numberVal)
{
  struct constant *cons = malloc(sizeof(struct constant));
  if (!cons)
    throwError(1);

  cons->nodeType = 'K';
  cons->type = lookupTypeInSymbolTable(type);
  cons->realVal = numberVal;

  return (struct ast *)cons;
}

/* EVALUATE */

void evalBreak() {
  if (continueLabel != 0)
  {
    gcJumpToLabel(breakLabel);
  }
}

void evalWhile(struct ast *a) {
  int auxContinueLabel = continueLabel;
  int auxBreakLabel = breakLabel;
  continueLabel = getNextLabel();
  breakLabel = getNextLabel();
  
  gcWriteLabel(continueLabel);
  manageConditions(a->left, breakLabel);  
  eval(a->right);                          //----------------------------------------------AQUI CHIQUILLO---------------------- ESTO FALLA
  gcJumpToLabel(continueLabel);
  gcWriteLabel(breakLabel);

  continueLabel = auxContinueLabel;
  breakLabel = auxBreakLabel;  
}

char *invertCondition(int operation)
{
  switch (operation)
  {
  case 1:
    return "<=";
  case 2:
    return ">=";
  case 3:
    return "<";
  case 4:
    return ">";
  case 5:
    return "!=";
  case 6:
    return "==";
  default:
    throwError(14);
    break;
  }
}

void evalList(struct ast *a) {
  eval(a->left);
  eval(a->right);
}

struct reg *evalCondition(struct ast *a) {
  struct reg *left = eval(a->left);
  struct reg *right = eval(a->right);
  char *operation = invertCondition(a->nodeType);

  gcWritLogicalOperation(operation, left, right);

  freeRegister(right);
  return left;
}

void manageConditions(struct ast *cond, int label) {
  struct reg *aux = eval(cond);

  gcWriteConditionUsingRegister(aux, label);
}

void evalIf(struct ast *a) {
  struct ifFlow *ifStm = (struct ifFlow *)a;
  int label = getNextLabel();
  int elseLabel;

  manageConditions(ifStm->cond, label);
  eval(ifStm->ifBody);

  if (ifStm->elseBody != NULL) {
    elseLabel = getNextLabel();
    gcJumpToLabel(elseLabel);
    gcWriteLabel(label);
    eval(ifStm->elseBody);
    label = elseLabel;
  }

  gcWriteLabel(label);
}

struct reg *evalReference(struct ast *a) {
  struct reference *ref = (struct reference *)a;
  struct Symbol *sym;

  struct reg *reg;

  sym = !isInFunction() ? lookupVariableInSymbolTable(ref->name) : lookupLocalVariableInSymbolTable(ref->name, actualScope);

  if (!sym)
  {
    throwError(5);
  }

  if (sym->a) {
    printf("LUEGO\n");
    // reg = evalRArray(ref, sym); PADESPUES
  } else {
    if (ref->rightHand)
    {
      reg = assignRegister(sym->type);
      gcCopyContentToRegister(reg, sym);
    }
    else
    {
      reg = assignRegister(lookupTypeInSymbolTable(1));
      if (sym->a)
      {
        reg->vector = 1;
        reg->length = sym->a->length;
      }
      gcCopyAddrToRegister(reg, sym->address);
      reg->type = sym->type;
    }
  }

  return reg;
}

struct reg *evalConstant(struct ast *a)
{
  struct constant *cons = (struct constant *)a;
  struct reg *r;
  int addr;

  r = assignRegister(cons->type);

  if (equalTypes(lookupTypeInSymbolTable(5), cons->type) && cons->vector) {
    r->vector = 1;
    r->length = strlen(cons->stringVal) + 1;
    addr = getNextFreeAddress(strlen(cons->stringVal));
    gcStoreStringInMemory(addr, cons->stringVal);
    gcCopyAddrToRegister(r, addr);
  }
  else
  {
    gcNumericConstant(r, cons->realVal);
  }

  return r;
}

void evalDeclArray(struct declaration *decl)
{
  int addr;
  int space;

  space = decl->length * decl->type->bytes;

  addr = getNextFreeAddress(space);

  insertArrayToSymbolTable(decl->name, addr, decl->length, decl->type);

  gcStoreArrayInMemory(addr, space);
}

void evalDeclaration(struct ast *a)
{
  struct declaration *decl = (struct declaration *)a;
  int addr;

  if (decl->length >= 0)
  {
    evalDeclArray(decl);
  }
  else
  {
    addr = getNextFreeAddress(decl->type->bytes);
 
    insertVariableToSymbolTable(decl->name, addr, decl->type);    
    gcReservePrimitiveSpace(addr, decl->type);
  }
}

struct reg *evalAssign(struct ast *a)
{
  printf("ASSIGN\n");
  struct reg *free;
  struct reg *left = eval(a->left);
  struct reg *right = eval(a->right);

  if (!areTypesCompatible(left->type, right->type)){
    throwError(7);
  }

  if (left->vector) {
    if (!right->vector)
    {
      throwError(15);
    }
    if (!equalTypes(right->type, left->type))
    {
      throwError(7);
    }

    if (right->length > left->length)
    {
      throwError(13);
    }

    free = assignRegister(right->type);
    gcCopyArrayToArrayUsingRegister(left, right, free, right->length);
    freeRegister(free);
  }
  else
  {
    gcSaveInMemoryUsingRegister(left, right);
  }

  freeRegister(left);
  return right;
}

struct reg *eval(struct ast *a)
{
  printf("NodeType: %c\n", a->nodeType);
  struct reg *res = NULL;

  if (a->nodeType == 'L' || a->nodeType == 'P' || a->nodeType == 'W' ||
      a->nodeType == '0' || a->nodeType == 'U' || a->nodeType == 'I' ||
      a->nodeType == 'B' || a->nodeType == 'C')
  {
    freeAllRegisters();
  }

  switch (a->nodeType) {
    case 'K':
      res = evalConstant(a);
      break;
    case 'D':
      if (!isInFunction())
      {
        evalDeclaration(a);
      }
      break;
    case '0':
      break;
    case '=':
      res = evalAssign(a);      
      break;
    case 'L':
      evalList(a);
      break;
    case 'R':
      res = evalReference(a);
      break;
    case 'I':
      evalIf(a);
      break;
    case 1: // >
    case 2: // <
    case 3: // >=
    case 4: // <=
    case 5: // ==
    case 6: // !=
      res = evalCondition(a);
      break;
    case 'W':
      evalWhile(a); // -------------> While falla en la última instrucción
      break;
    case 'B':
      evalBreak();
      break;
    default:
      break;
  }
  return res;
}

void treefree(struct ast * a) {
  freeAllRegisters();
}