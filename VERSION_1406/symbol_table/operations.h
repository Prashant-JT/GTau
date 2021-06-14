struct TypeSymbol
{
  int id;
  int bytes;
  char qName;
};

struct vector
{
  int length;
};

struct function
{
  int numberOfParams;
  int numberOfSpaceRequired;
  int label;
};

struct Symbol
{
  char *name;
  struct TypeSymbol *type;
  struct vector *a;
  struct function *fun;
  int address;
  int scope;
  int reference;
  int order;
};

typedef struct node
{
  struct Symbol *val;
  struct node *next;
} symbol_node;

typedef struct node_t
{
  struct TypeSymbol *val;
  struct node_t *next;
} type_node;

type_node *type_head, *type_tail;
symbol_node *symbol_head, *symbol_tail;

void loadPrimitives();
struct TypeSymbol *lookupTypeInSymbolTable(int id);
int equalTypes(struct TypeSymbol *a, struct TypeSymbol *b);
int areTypesCompatible(struct TypeSymbol *a, struct TypeSymbol *b);
void insertArrayToSymbolTable(char *name, int address, int length, struct TypeSymbol *type);
void insertVariableToSymbolTable(char *name, int address, struct TypeSymbol *type);
int isSymbolAFunction(struct Symbol *s);
int isSymbolAnArray(struct Symbol *s);
struct Symbol *lookupVariableInSymbolTable(char *id);
struct Symbol *lookupFunctionInSymbolTable(char *id);
struct Symbol *lookupLocalVariableInSymbolTable(char *name, int scope);