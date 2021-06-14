#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "operations.h"
#include "../ErrorMessage/ErrorMessage.h"
#include "../code_generation/qManage.h"
#include "../code_generation/codeGeneration.h"

#define PRINT -12

int actualScope = 0;
int breakLabel = 0;
int reference = 0;

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
  
  if (!decStm) throwError(1);

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

  fnAST->nodeType = 'F';
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
  nothing->nodeType = 'Q';
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

struct ast *newRightDeclaration(struct ast *a) {
  struct reference *ref = (struct reference *)a;
  ref->rightHand = 1;

  return (struct ast *)ref;
}

struct ast *newIndexReference(char *name, struct ast *index) {
  struct reference *ref = (struct reference *) newReference(name);
  ref->a = index;

  return (struct ast *)ref;
}

struct ast *newReference(char *name) {
  struct reference *ref = malloc(sizeof(struct reference));

  if (!ref) throwError(1);

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
  gcJumpToLabel(breakLabel);
}

void evalPrint(struct ast *a) {
  struct context *cont;
  struct reg *r0, *r1, *r2;
  int label;

  cont = pushContext();
  gcWriteContext(cont);
  label = getNextLabel();

  r0 = getRegister(lookupTypeInSymbolTable(1), "R", 0);
  gcNumericConstant(r0, label);

  r1 = eval(a->left);

  if (a->right != NULL) {
    r2 = eval(a->right);
  }

  gcJumpToLabel(PRINT);
  gcWriteLabel(label);
  gcRestoreContext(cont);
  popContext(cont);
}

struct reg *evalNegativeNumber(struct ast *a){
  struct reg *r = eval(a->left);

  if (!(equalTypes(r->type, lookupTypeInSymbolTable(1)) ||
        equalTypes(r->type, lookupTypeInSymbolTable(2)) ||
        equalTypes(r->type, lookupTypeInSymbolTable(3))))
  {
    throwError(12);
  }

  gcMultiplyByConstant(r, -1);
  return r;
}

struct reg *evalPositiveNumber(struct ast *a){
  struct reg *r = eval(a->left);

  if (!(equalTypes(r->type, lookupTypeInSymbolTable(1)) ||
        equalTypes(r->type, lookupTypeInSymbolTable(2)) ||
        equalTypes(r->type, lookupTypeInSymbolTable(3))))
  {
    throwError(12);
  }

  gcMultiplyByConstant(r, 1);
  return r;
}

int _checkParams(struct ast *params, struct Symbol *func)
{
  struct ast *aux;
  int count = 0;
  aux = params;

  while (aux != NULL) {
    aux = aux->nodeType == 'L' ? aux->right : NULL;
    count++;
  }

  if (count != func->fun->numberOfParams)
  {
    throwError(11);
  }

  return count;
}

struct reg *evalOperations(struct ast *a) {
  struct reg *left = eval(a->left);
  struct reg *right = eval(a->right);
  struct reg *result, *free;

  if (!(((equalTypes(left->type, lookupTypeInSymbolTable(1))) ||
         (equalTypes(left->type, lookupTypeInSymbolTable(2))) ||
         (equalTypes(left->type, lookupTypeInSymbolTable(3)))) &&
        ((equalTypes(right->type, lookupTypeInSymbolTable(1))) ||
         (equalTypes(right->type, lookupTypeInSymbolTable(2))) ||
         (equalTypes(right->type, lookupTypeInSymbolTable(3))))))
  {
    throwError(12);
  }

  gcRegisterNumericCalculation(a->nodeType, left, right);

  freeRegister(right);
  return left;
}

int evalArgumentList(struct ast *a, int paramCounter) {
  int returnValue = 0;

  struct reg *r = NULL, *dummy;
  reference = 1;

  if (!(dummy = malloc(sizeof(struct reg)))) throwError(1);

  dummy->index = 7;
  dummy->label = "R";

  if (paramCounter == 0) {
    return 0;
  } else if (paramCounter == 1) {
    r = eval(a);
    returnValue += r->type->bytes;
    dummy->type = r->type;
    gcMoveStackPointer(-r->type->bytes);
    gcSaveInMemoryUsingRegister(dummy, r);
  } else {
    if (paramCounter >= 2) returnValue += evalArgumentList(a->right, paramCounter - 1);

    r = eval(a->left);
    returnValue += r->type->bytes;
    dummy->type = r->type;
    gcMoveStackPointer(-r->type->bytes);
    gcSaveInMemoryUsingRegister(dummy, r);
  }

  freeRegister(r);
  reference = 0;

  return returnValue;
}

void evalCallFunction(struct ast *a) {
  struct callFunction *callFn = (struct callFunction *)a;
  struct context *cont;
  int moved;
  int label;
  int paramCounter;

  struct Symbol *sym = lookupFunctionInSymbolTable(callFn->name);
  if (!sym) throwError(10);

  paramCounter = _checkParams(callFn->params, sym);
  cont = pushContext();

  gcWriteContext(cont);
  moved = evalArgumentList(callFn->params, paramCounter);
  printf("Moved : %d\n", moved);
  gcMoveStackPointer(-8);
  label = getNextLabel();

  gcSaveActualBase();
  gcSaveReturningLabel(label);
  gcJumpToLabel(sym->fun->label);
  gcWriteLabel(label);
  gcMoveStackPointer(moved + 8);
  popContext();
  gcRestoreContext(cont);
}

void insertAsLocalVariable(struct ast *a, int scope, int offset, int reference) {
  struct declaration *decl = (struct declaration *)a;
  struct constant *cons;  
  int length = decl->length;
  int array = (decl->length >= 0) ? 1 : 0;

  insertLocalVariableToSymbolTable(decl->name, offset, decl->type, scope, length, array, reference);
}

int spaceRequiredForLocalVariable(struct ast *body, int offset) {
  int aux;
  struct declaration *decl;
  int length;

  if (body->nodeType == 'L') {
    aux = spaceRequiredForLocalVariable(body->left, offset);
    aux = spaceRequiredForLocalVariable(body->right, aux);
    return aux;
  }

  if (body->nodeType == 'I' /* || body->nodeType == 'F' */ || body->nodeType == 'W') {
    return spaceRequiredForLocalVariable(((struct flow *)body)->content, offset);
  }

  if (body->nodeType == 'D') {
    decl = (struct declaration *)body;
    length = decl->length <= 0 ? 1 : decl->length;
    aux = decl->type->bytes * length;

    if ((aux % 4) != 0) aux = (int)(aux / 4) * 4 + 4;

    insertAsLocalVariable(body, getActiveLabel(), -offset - aux, 0);
    return offset + aux;
  }

  return offset;
}

void manageFunctionDeclarationInQ(int label, struct ast *params, struct ast *body,
                                  int numberOfParams, int bytesRequiered)
{
  struct reg *r;

  actualScope = label;
  inFunction();

  gcWriteLabel(label);
  gcNewBase();
  gcReserveSpaceForLocalVariables(bytesRequiered);
  eval(body);
  gcFreeLocalSpace();
  gcRestoreBase();
  r = assignRegister(lookupTypeInSymbolTable(1));
  gcStoreReturnLabelFromStackInRegister(r);
  gcPrintGTFromRegister(r);
  outsideFunction();

  actualScope = 0;
  freeRegister(r);
}

void evalFunction(struct ast *a) {
  struct functionAST *func = (struct functionAST *)a;
  struct ast *aux;
  int numberOfParams = 0, numberOfBytesRequiered, label;
  int baseDir = 8;
  int auxDir = 0;

  aux = func->params;
  label = getNextLabel();

  printf("Function declaration, params: %d\n", func->params != NULL);

  while (aux != NULL) {
    if (aux->nodeType == 'L') {
      insertAsLocalVariable(aux->left, label, baseDir, 1);
      auxDir = ((struct declaration *)aux->left)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = aux->right;
    } else {
      insertAsLocalVariable(aux, label, baseDir, 1);
      auxDir = ((struct declaration *)aux)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = NULL;
    }
    numberOfParams++;
  }

  numberOfBytesRequiered = spaceRequiredForLocalVariable(func->content, 0);

  insertFunctionToSymbolTable(func->name, func->type, label, numberOfParams, numberOfBytesRequiered);

  manageFunctionDeclarationInQ(label, func->params, func->content, numberOfParams, numberOfBytesRequiered);
}

void evalWhile(struct ast *a) {
  int auxBreakLabel = breakLabel;
  breakLabel = getNextLabel();
  
  manageConditions(a->left, breakLabel);  
  eval(a->right);                 
  gcWriteLabel(breakLabel);
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

  gcWriteLogicalOperation(operation, left, right);

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

struct reg *evalReferenceVector(struct reference *r, struct Symbol *s) {
  struct reg *reg, *free;

  if (r->a) {
    reg = eval(r->a);

    if (!equalTypes(reg->type, lookupTypeInSymbolTable(1))) throwError(8);

    gcMultiplyRegisterForNumericConstant(reg, s->type);

    if (r->rightHand) {
      free = assignRegister(reg->type);
      gcStoreArrayDataInRegister(s->address, reg, s->type, free);

      if (isInFunction() && s->reference) gcStorePointerInRegisterInTheSameRegister(reg);

      freeRegister(free);
    } else {
      free = assignRegister(reg->type);
      gcStoreArrayDirInRegister(s->address, reg, free);

      if (isInFunction() && s->reference) gcStorePointerInRegisterInTheSameRegister(reg);

      freeRegister(free);
    }
  } else {
    reg = assignRegister(s->type);
    reg->vector = 1;
    reg->length = s->a->length;
    gcStoreArrayAddressInRegister(s->address, reg);
  }

  reg->type = s->type;
  return reg;
}

struct reg *evalReference(struct ast *a) {
  struct reference *ref = (struct reference *)a;
  struct Symbol *sym;

  struct reg *reg;

  sym = !isInFunction() ? lookupVariableInSymbolTable(ref->name) : lookupLocalVariableInSymbolTable(ref->name, actualScope);

  if (!sym) throwError(5);

  if (sym->a) {
    reg = evalReferenceVector(ref, sym); 
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

void evalDeclArray(struct declaration *decl) {
  int addr, space;

  space = decl->length * decl->type->bytes;

  addr = getNextFreeAddress(space);

  insertArrayToSymbolTable(decl->name, addr, decl->length, decl->type);

  gcStoreArrayInMemory(addr, space);
}

void evalDeclaration(struct ast *a){
  struct declaration *decl = (struct declaration *)a;
  int addr;

  if (decl->length >= 0) {
    evalDeclArray(decl);
  } else {
    addr = getNextFreeAddress(decl->type->bytes);
 
    insertVariableToSymbolTable(decl->name, addr, decl->type);    
    gcReservePrimitiveSpace(addr, decl->type);
  }
}

struct reg *evalAssign(struct ast *a) {
  struct reg *free;
  struct reg *left = eval(a->left);  
  struct reg *right = eval(a->right);  

  if (!areTypesCompatible(left->type, right->type)) throwError(7);

  if (left->vector) {
    if (!right->vector) throwError(15);

    if (!equalTypes(right->type, left->type)) throwError(7);

    if (right->length > left->length) throwError(13);

    free = assignRegister(right->type);
    gcCopyArrayToArrayUsingRegister(left, right, free, right->length);
    freeRegister(free);
  } else {
    gcSaveInMemoryUsingRegister(left, right);
  }

  freeRegister(left);
  return right;
}

struct reg *eval(struct ast *a) {
  // printf("NodeType: %d (%c)\n", a->nodeType, a->nodeType);
  struct reg *res = NULL;

  if (a->nodeType == 'L' || a->nodeType == 'F' || a->nodeType == 'W' ||
      a->nodeType == 'Q' || a->nodeType == 'I' ||
      a->nodeType == 'B' || a->nodeType == 'C')
  {
    freeAllRegisters();
  }

  switch (a->nodeType) {
    case 'K':
      res = evalConstant(a);
      break;
    case 'D':
      if (!isInFunction()) evalDeclaration(a);
      break;
    case 'Q':
      break;
    case 'C':
      evalCallFunction(a);
      break;
    case 'F':
      evalFunction(a);
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
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
      res = evalOperations(a);
      break;
    case 1: // >
    case 2: // <
    case 3: // >=
    case 4: // <=
    case 5: // ==
    case 6: // !=
      res = evalCondition(a);
      break;
    case 'M':
      res = evalNegativeNumber(a);
      break;
    case 'U':
      res = evalPositiveNumber(a);
      break;
    case 'W':
      evalWhile(a);
      break;
    case 'B':
      evalBreak();
      break;
    case 'P':
      evalPrint(a);
      break;
    default:
      break;
  }
  return res;
}

void treefree(struct ast * a) {
  freeAllRegisters();
}