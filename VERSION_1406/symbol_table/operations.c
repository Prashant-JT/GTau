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
  struct TypeSymbol *integer, *decimalD, *decimalF, *character;

  if (!(integer = malloc(sizeof(struct TypeSymbol))) ||
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

  character->bytes = 1;
  character->id = 5; //CHAR
  character->qName = 'C';

  _addToTypeSymbolTable(integer);
  _addToTypeSymbolTable(decimalD);
  _addToTypeSymbolTable(decimalF);
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
