%{
#include <stdio.h>
#include "../symbol_table/table.h"
#include "../symbol_table/operations.h"
#include "../code_generation/codeGeneration.h"
extern FILE *yyin;   /* declarado en lexico */
extern int numlin;   /* lexico le da valores */
//int yydebug=1;       /* modo debug si -t */
void yyerror(char*); 
//int yylex();
%}

%union {
  char *name;
  char *str;
  double real;
  int function;     
  int compare;                       
  int integer;
  int type;
  struct ast *node;
}

%token <real> REAL
%token <integer> INTEGER
%token <str> CHAR STRING
%token <name> NAME
%token <function> FUNCTION
%token <type> TYPE
%token IF ELSE WHILE BREAK FOR 
%token PRINT RETURN
%token EOL

%nonassoc <compare> COMPARE
%nonassoc UMINUS UPLUS

%right '='
%left '+' '-'
%left '*' '/' '%' '^'
%left '(' ')'

%type <node> function_definition leftDeclaration builtin_functions content declaration parameter_function parameter_to_function statement variable_declaration variable_definition expression

%start initial_main

%%

initial_main : /* nothing */
             | initial_main function_definition EOL                                             {
                                                                                                  eval($2);
                                                                                                  treefree($2);
                                                                                                } 
             | initial_main statement EOL                                                       {
                                                                                                  eval($2);
                                                                                                  treefree($2);
                                                                                                }       
             | initial_main EOL               
             | initial_main error EOL                                                          { yyerrok; printf("> "); }                                                                                            
             ;

function_definition : FUNCTION TYPE NAME '(' parameter_function ')' '{' EOL content '}'         { $$ = newFunction($2, $3, $5, $9); }
                    | FUNCTION NAME '(' parameter_function ')' '{' EOL content '}'              { $$ = newFunction(0, $2, $4, $8); }          
                    ;

content : statement EOL                                                                       { $$ = $1; }
        | statement EOL content                                                               { $$ = newList($1, $3); }
        | content EOL                                                                        
        | EOL                                                                                 { $$ = newNothing(); }
        ;

declaration : TYPE NAME                                                                  { $$ = newDeclaration($1, $2); }                                    
            | TYPE '[' INTEGER ']' NAME                                                  { $$ = newVectDeclaration($1, $5, $3); }
            ;

parameter_function : /*Nothing*/                                                          { $$ = NULL; }
                   | declaration                                                                                                                 
                   | declaration ',' parameter_function                                   { $$ = newList($1, $3); }
                   ;

parameter_to_function : /*Nothing*/                                                       { $$ = NULL; }
                      | expression                                                     
                      | expression ',' parameter_to_function                              { $$ = newList($1, $3); }
                      ;

statement : variable_declaration ';'                                                                                                                  
          | variable_definition ';' 
          | expression ';'
          | IF '(' expression ')' '{' EOL content '}'                                                           { $$ = newIf($3, $7, NULL); }
          | IF '(' expression ')' '{' EOL content '}' ELSE '{' EOL content '}'                                  { $$ = newIf($3, $7, $12); }
          | WHILE '(' expression ')' '{' EOL content '}'                                                        { $$ = newAST('W', $3, $7); }
          | RETURN expression ';'                                                                             { printf("RETURN\n"); }
          | NAME '(' parameter_to_function ')' ';'                                                              { $$ = newCallFunction($1, $3); }                                                             
          | BREAK ';'                                                                                           { $$ = newAST('B', NULL, NULL); } 
          | builtin_functions ';'                                                     
          ;

builtin_functions : PRINT '(' STRING ',' expression ')'                                            { $$ = newAST('P', newString($3), $5); }
                  ;

variable_declaration  : TYPE NAME                                                                  { $$ = newDeclaration($1, $2); }                                    
                      | TYPE '[' INTEGER ']' NAME                                                  { $$ = newVectDeclaration($1, $5, $3); }  
                      | TYPE NAME '=' expression                                                   { $$ = newList(newDeclaration($1, $2), newAssign(newReference($2), $4)); }                              
                      ;

variable_definition : leftDeclaration '=' expression                                               { $$ = newAssign($1, $3); }                                   
                    | leftDeclaration '+''=' expression                                            { $$ = newAssign($1, newAST('+', $1, $4)); } 
                    | leftDeclaration '-''=' expression                                            { $$ = newAssign($1, newAST('-', $1, $4)); }
                    | leftDeclaration '*''=' expression                                            { $$ = newAssign($1, newAST('*', $1, $4)); }
                    | leftDeclaration '/''=' expression                                            { $$ = newAssign($1, newAST('/', $1, $4)); }
                    ;
 
leftDeclaration : NAME                                                               { $$ = newReference($1); }
                | NAME '[' expression ']'                                            { $$ = newIndexReference($1, $3); }
                ;

expression  : leftDeclaration                                                           { $$ = newRightDeclaration($1); } 
            | NAME '(' parameter_to_function ')'                                        { $$ = newCallFunction($1, $3); }                                                            
            | CHAR                                                                      { $$ = newChar($1); }
            | STRING                                                                    { $$ = newString($1); }
            | INTEGER                                                                   { $$ = newNumber(1, $1); } 
            | REAL                                                                      { $$ = newNumber(2, $1); }
            | '(' expression ')'                                                        { $$ = $2; }
            | '-' expression %prec UMINUS                                               { $$ = newAST('M', $2, NULL); }
            | '+' expression %prec UPLUS                                                { $$ = newAST('U', $2, NULL); }                                      
            | expression '+' expression                                                 { $$ = newAST('+', $1, $3); } 
            | expression '-' expression                                                 { $$ = newAST('-', $1, $3); }
            | expression '*' expression                                                 { $$ = newAST('*', $1, $3); }
            | expression '/' expression                                                 { $$ = newAST('/', $1, $3); }
            | expression '%' expression                                                 { $$ = newAST('%', $1, $3); }
            | expression '^' expression                                                 { $$ = newAST('^', $1, $3); }
            | expression COMPARE expression                                             { $$ = newAST($2, $1, $3); }                                                                               
            ;             
%%

int main(int argc, char** argv) {
  openFiles();
  loadPrimitives();
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
  printSymbolTableContent();
  closeFiles();
  return 0;
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s \n", numlin, mens);
}

