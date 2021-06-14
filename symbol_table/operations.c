#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "operations.h"
#include "../ErrorMessage/ErrorMessage.h"

char* types[] = {"int", "double", "float", "boolean", "char", "string"}; //PARA DESPUES

int _functionComparator(char *name, struct Symbol *s)
{
  return (strcmp(name, s->name) == 0 && isSymbolAFunction(s));
}

int _variableComparator(char *name, struct Symbol *s)
{
  return (strcmp(name, s->name) == 0 && !isSymbolAFunction(s) && s->scope == 0);
}

struct Symbol *_geneticLookupInSymbolTable(char *id, int (*f)(char *, struct Symbol *))
{
  symbol_node *aux;
  if (!symbol_head)
  {
    return NULL;
  }

  aux = symbol_head;
  do
  {
    if ((*f)(id, aux->val))
    {
      return aux->val;
    }

    aux = aux->next;
  } while (aux);

  return NULL;
}

int _existsInSymbolTable(struct Symbol *s)
{
  if (isSymbolAFunction(s))
  {
    return lookupFunctionInSymbolTable(s->name) != NULL;
  }
  else
  {
    if (s->scope > 0)
    {

      lookupLocalVariableInSymbolTable(s->name, s->scope) != NULL;
    }
    else
    {
      return lookupVariableInSymbolTable(s->name) != NULL;
    }
  }
}

void _addToSymbolTable(struct Symbol *s)
{

  if (symbol_head)
  {
    if (_existsInSymbolTable(s))
    {
      throwError(2);
    }
    if (!(symbol_tail->next = (symbol_node *)malloc(sizeof(symbol_node))))
    {
      throwError(1);
    }
    symbol_tail = symbol_tail->next;
  }
  else
  {
    symbol_head = (symbol_node *)malloc(sizeof(symbol_node));
    if (!symbol_head)
    {
      throwError(1);
    }
    symbol_tail = symbol_head;
  }
  symbol_tail->val = s;
}


void _addToTypeSymbolTable(struct TypeSymbol *typeS)
{
  if (type_head)
  {
    if (!(type_tail->next = (type_node *)malloc(sizeof(type_node))))
    {
      throwError(1);
    }
    type_tail = type_tail->next;
  }
  else
  {
    type_head = (type_node *)malloc(sizeof(type_node));
    if (!type_head)
    {
      throwError(1);
    }
    type_tail = type_head;
  }
  type_tail->val = typeS;
}

int equalTypes(struct TypeSymbol *a, struct TypeSymbol *b)
{
  return a->id == b->id;
}

int areTypesCompatible(struct TypeSymbol *a, struct TypeSymbol *b)
{
  return ((equalTypes(a, b) || (b->id == 1 && (a->id == 2 || a->id == 3)) || a->id == 3 && b->id == 2));
}

int isSymbolAFunction(struct Symbol *s) {
  return s->fun != NULL;
}

struct Symbol *lookupFunctionInSymbolTable(char *id)
{
  return _geneticLookupInSymbolTable(id, _functionComparator);
}

struct Symbol *lookupVariableInSymbolTable(char *id)
{
  return _geneticLookupInSymbolTable(id, _variableComparator);
}

struct Symbol *lookupLocalVariableInSymbolTable(char *name, int scope)
{
  symbol_node *aux;
  if (!symbol_head)
  {
    return NULL;
  }

  aux = symbol_head;
  do
  {
    if (strcmp(name, aux->val->name) == 0 && !isSymbolAFunction(aux->val) && aux->val->scope == scope)
    {
      return aux->val;
    }

    aux = aux->next;
  } while (aux);

  return NULL;
}

void loadPrimitives()
{
  struct TypeSymbol *integer, *decimalD, *decimalF, *character, *empty;

  if (!(integer = malloc(sizeof(struct TypeSymbol))) ||
      !(empty = malloc(sizeof(struct TypeSymbol)))  ||
      !(decimalD = malloc(sizeof(struct TypeSymbol))) ||
      !(decimalF = malloc(sizeof(struct TypeSymbol))) ||
      !(character = malloc(sizeof(struct TypeSymbol))))
  {
    throwError(1);
  }

  integer->bytes = 4;
  integer->id = 1; //INTEGER
  integer->qName = 'I';

  decimalD->bytes = 8;
  decimalD->id = 2; //DOUBLE
  decimalD->qName = 'D';

  decimalF->bytes = 4;
  decimalF->id = 3; //FLOAT
  decimalF->qName = 'F';

  empty->bytes = 0;
  empty->id = 4; //VOID
  empty->qName = 'V';

  character->bytes = 1;
  character->id = 5; //STRING
  character->qName = 'S';

  _addToTypeSymbolTable(integer);
  _addToTypeSymbolTable(decimalD);
  _addToTypeSymbolTable(decimalF);
  _addToTypeSymbolTable(empty);
  _addToTypeSymbolTable(character);
}

struct TypeSymbol *lookupTypeInSymbolTable(int id)
{
  type_node *aux;
  if (!type_head)
    return NULL;

  aux = type_head;
  do
  {
    if (id == aux->val->id)
    {
      return aux->val;
    }
    aux = aux->next;
  } while (aux != NULL);

  return NULL;
}

void insertVariableToSymbolTable(char *name, int address, struct TypeSymbol *type)
{
  struct Symbol *sym;
  if (!(sym = malloc(sizeof(struct Symbol))))
  {
    throwError(1);
  }

  sym->name = name;
  sym->a = NULL;
  sym->address = address;
  sym->type = type;
  sym->fun = NULL;

  // printf("Inserting %s\n", sym->name);
  _addToSymbolTable(sym);
}

void insertArrayToSymbolTable(char *name, int address, int length, struct TypeSymbol *type)
{
  struct Symbol *sym;
  struct vector *arr;
  if (!(sym = malloc(sizeof(struct Symbol))) || !(arr = malloc(sizeof(struct vector))))
  {
    throwError(1);
  }

  sym->name = name;
  sym->a = arr;
  sym->address = address;
  sym->type = type;
  sym->fun = NULL;
  arr->length = length;

  _addToSymbolTable(sym);
}

void insertLocalVariableToSymbolTable(char *name, int address, struct TypeSymbol *type, int scope,
                                      int length, int array, int reference)
{
  struct Symbol *sym;
  if (!(sym = malloc(sizeof(struct Symbol))))
  {
    throwError(1);
  }

  sym->name = name;
  sym->address = address;
  sym->type = type;
  sym->fun = NULL;
  sym->scope = scope;
  if (array > 0) {
    sym->a = malloc(sizeof(struct vector));
    if (!sym->a) {
      throwError(1);
    }
    sym->a->length = length;
  }
  sym->reference = reference;

  // printf("Inserting Local\n");
  _addToSymbolTable(sym);
}

void insertFunctionToSymbolTable(char *name, struct TypeSymbol *type, int label, int numberOfParams, int numberOfBytesRequiered)
{
  struct Symbol *sym;
  struct function *func;
  if (!(sym = malloc(sizeof(struct Symbol))) || !(func = malloc(sizeof(struct function))))
  {
    throwError(1);
  }

  sym->name = name;
  sym->a = NULL;
  sym->address = -1;
  sym->type = type;
  sym->fun = func;
  func->label = label;
  func->numberOfParams = numberOfParams;
  func->numberOfSpaceRequired = numberOfBytesRequiered;

  _addToSymbolTable(sym);
}

void printSymbolTableContent() {
  type_node *aux = type_head;
  symbol_node *auxS = symbol_head;

  if (!type_head)
  {
    printf("TypeSymbolTable is empty\n");
  }
  else
  {
    printf("TypeSymbolTable :\n");

    do
    {
      printf("name: %d, bytes: %d, qName: %c\n", aux->val->id, aux->val->bytes, aux->val->qName);
      aux = aux->next;
    } while (aux != NULL);
  }

  if (!symbol_head)
  {
    printf("SymbolTable is empty\n");
  }
  else
  {
    printf("SymbolTable :\n");

    do
    {
      printf("name: %s, addr: 0x%x, type: %d, array: %d function: %d, local: %d\n", auxS->val->name,
             auxS->val->address, auxS->val->type->id,
             auxS->val->a != NULL, auxS->val->fun != NULL, auxS->val->scope);
      if (auxS->val->fun)
      {
        printf("\tlabel: %d, inputParams: %d, bytes: %d\n", auxS->val->fun->label,
               auxS->val->fun->numberOfParams, auxS->val->fun->numberOfSpaceRequired);
      }
      else if (auxS->val->a)
      {
        printf("\tlength: %d\n", auxS->val->a->length);
      }

      auxS = auxS->next;
    } while (auxS != NULL);
  }
}