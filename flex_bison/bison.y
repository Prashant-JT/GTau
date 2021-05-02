%{
#include <stdio.h>
extern FILE *yyin;   /* declarado en lexico */
extern int numlin;   /* lexico le da valores */
int yydebug=1;       /* modo debug si -t */
    void yyerror(char*); 
%}

%union {
  char *name;
  char *str;
  double real;
  int function;     
  int compare;                       
  int integer;
  int type;
}

%token <real> REAL
%token <integer> INTEGER
%token <str> CHAR
%token <str> STRING
%token <name> NAME
%token <function> FUNCTION
%token <type> TYPE
%token IF ELSIF ELSE WHILE BREAK FOR GOTO LABEL
%token AND OR NOT
%token PRINT PRINTLN RETURN SIZE APPEND POP CLEAR GET CLONE
%token EOL

%nonassoc <compare> COMPARE

%right '='
%left '+' '-'
%left '*' '/' '%' '^'
%left '(' ')'

%%

%%

int main(int argc, char** argv) {
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s ", numlin, mens);
}

