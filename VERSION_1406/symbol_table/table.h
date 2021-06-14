extern int numlin;

struct ast
{
  int nodeType;
  struct ast *left;
  struct ast *right;
};

struct reg
{
  int vector;
  int length;
  int reference;
  struct TypeSymbol *type;
  char *label;
  int index;
};

struct ifFlow
{
  int nodeType;
  struct ast *cond;
  struct ast *ifBody;
  struct ast *elseBody;
};

struct callFunction
{
  int nodeType;
  char *name;
  struct ast *params;
};

struct declaration
{
  int nodeType;
  char *name;
  struct TypeSymbol *type;
  int length;
};

struct functionAST
{
  int nodeType;
  char *name;
  struct TypeSymbol *type;
  struct ast *params;
  struct ast *content;
};

struct reference
{
  int nodeType;
  int rightHand;
  char *name;
  struct ast *a;
};

struct constant
{
  int nodeType;
  struct TypeSymbol *type;
  double realVal;
  char *stringVal;
  int vector;
};

struct ast *newAST(int nodeType, struct ast *left, struct ast *right);
struct ast *newIf(struct ast *cond, struct ast *ifBody, struct ast *elseBody);
struct ast *newList(struct ast *left, struct ast *right);
struct ast *newCallFunction(char *name, struct ast *params);
struct ast *newDeclaration(int type, char *name);
struct ast *newVectDeclaration(int type, char *name, int length);
struct ast *newFunction(int type, char *name, struct ast *params, struct ast *content);
struct ast *newNothing();
struct ast *newAssign(struct ast *left, struct ast *right);
struct ast *newReference(char *name);
struct ast *newChar(char *charac);
struct ast *newString(char *stringValue);
struct ast *newNumber(int type, double numberVal);
void manageConditions(struct ast *cond, int label);

struct reg * eval(struct ast *a);
void treefree(struct ast *a);
