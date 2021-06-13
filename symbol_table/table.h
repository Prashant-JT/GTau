extern int numlin;
void initList();

struct symbol {
  char *name;
  int type;
  int scope;
  int intVal;
  float floatVal;
  double doubleVal;
  char *stringVal;
  struct symboList *params;
  struct ast *content;
};

struct ast {
  int nodeType;
  struct ast *left;
  struct ast *right;
};

struct reference {
  int nodeType;
  struct symbol *sym;
};

struct variable {
  int nodeType;
  int type;
  double val;
  char *stringVal;
};

struct vector {
  int nodeType;
  int type;
  char *name;
  struct ast *elements;
};

struct symbolAssign {
  int nodeType;                 
  char *name;
  struct ast *value;                
};

struct condition {
  int nodeType;
  struct ast *cond; 
  struct ast *left;
  struct ast *right;
};

struct iterator {
  int nodeType;
  struct ast *declaration;
  struct ast *cond;
  struct ast *increment;
  struct ast *left;
};

struct callFn {                
  int nodeType;                 
  struct ast *parameters;               
  char *name;
};

struct symboList {
  struct ast *actual;
  struct symboList *next;
};

typedef struct node {
  struct symbol *value;
  struct node *next;
}node_t;

node_t *head;
node_t *tail;

struct ast *newReference(int varType, char *name);
struct ast *newVariable(int type, double value, char *stringVal);
struct ast *newVector(int type, char *name, struct ast *elements);
struct ast *callFunction(char *name, struct ast *params);
struct ast *newAST(int nodeType, struct ast *left, struct ast *right);
struct symboList *newSymboList(struct ast *actual, struct symboList *next);
struct ast *newAssignment(char *name, struct ast *value);
struct ast *newIf(struct ast *cond, struct ast *left, struct ast *right);
struct ast *newFor(struct ast *declaration, struct ast *cond, struct ast *increment, struct ast *left);
void newFunction(int type, char *name, struct symboList *params, struct ast *content);


struct symbol *lookup(char *symName);
struct symbol *evaluateReference(struct ast *a);
struct symbol *eval(struct ast *a);