#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "../symbol_table/operations.h"
#include "../symbol_table/table.h"
#include "../ErrorMessage/ErrorMessage.h"
#include "qManage.h"

#define R_SIZE 6
#define RR_SIZE 4

int R[R_SIZE];
int RR[RR_SIZE];
int label = 0;
int dir = 0x12000;

struct reg *assignRegister(struct TypeSymbol *type)
{
  struct reg *r;
  int i;
  char *label = type->bytes <= 4 ? "R" : "RR";
  int size = type->bytes <= 4 ? R_SIZE : RR_SIZE;
  if (!(r = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }

  r->label = label;
  r->type = type;
  if (type->bytes <= 4)
  {
    for (i = 0; i < R_SIZE; i++)
    {
      if (R[i] == 0)
      {
        R[i] = 1;
        break;
      }
    }
  }
  else
  {
    for (i = 0; i < RR_SIZE; i++)
    {
      if (RR[i] == 0)
      {
        RR[i] = 1;
        break;
      }
    }
  }

  if (i == size)
  {
    throwError(3);
  }

  r->index = i;
  return r;
}

int getNextFreeAddress(int bytes)
{
  dir -= bytes;
  dir = dir & 0xffffc;
  return dir;
}

int getNextLabel()
{
  return ++label;
}

void freeRegister(struct reg *r)
{
  if (r->type->bytes <= 4)
  {
    R[r->index] = 0;
  }
  else
  {
    RR[r->index] = 0;
  }
}

void freeAllRegisters()
{
  for (int i = 0; i < R_SIZE; i++)
  {
    R[i] = 0;
  }
  for (int i = 0; i < RR_SIZE; i++)
  {
    RR[i] = 0;
  }
}