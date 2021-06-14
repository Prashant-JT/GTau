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
  char *label;
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
%token <label> LABEL
%token <function> FUNCTION
%token <type> TYPE
%token IF ELSIF ELSE WHILE BREAK FOR GOTO
%token AND OR NOT
%token PRINT PRINTLN RETURN SIZE APPEND POP CLEAR GET CLONE
%token EOL

%nonassoc <compare> COMPARE
%nonassoc UMINUS UPLUS

%right '='
%left '+' '-'
%left '*' '/' '%' '^'
%left '(' ')'

%type <node> function_definition content declaration parameter_function parameter_to_function statement variable_declaration variable_definition expression

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
        | EOL                                                                                 { $$ = newNothing(); }
        ;

declaration : TYPE NAME                                                                  { $$ = newDeclaration($1, $2); }                                    
            | TYPE '[' INTEGER ']' NAME                                                  { $$ = newVectDeclaration($1, $5, $3); }
            ;

parameter_function : /*Nothing*/                                                          { $$ = NULL; }
                   | declaration                                                                                                                 
                   | declaration ',' parameter_function                                   { $$ = newList($1, $3); }
                   ;

parameter_to_function :                                                                   { $$ = NULL; }
                      | expression                                                     
                      | expression ',' parameter_to_function                              { $$ = newList($1, $3); }
                      ;

statement : variable_declaration ';'                                                                                                                  
          | variable_definition ';' 
          | expression ';'
          | IF '(' expression ')' '{' EOL content '}'                                                           { $$ = newIf($3, $7, NULL); }
          | IF '(' expression ')' '{' EOL content '}' ELSE '{' EOL content '}'                                  { $$ = newIf($3, $7, $12); }
          | FOR '(' TYPE NAME '=' expression ';' expression ';' variable_definition ')' '{' EOL content '}'   { printf("FOR\n"); }
          | WHILE '(' expression ')' '{' EOL content '}'                                                        { $$ = newAST('W', $7, $3); }
          | RETURN expression ';'                                                                         { printf("RETURN\n"); }
          | NAME '(' parameter_to_function ')'                                                              { $$ = newCallFunction($1, $3); }                                                             
          | BREAK ';'                                                                                       { $$ = newAST('B', NULL, NULL); }
          | GOTO NAME ';'                                                                                 { printf("GOTO\n"); }
          | LABEL ':'                                                                                     { printf("LABEL\n"); }                                                                        
          ;

variable_declaration  : TYPE NAME                                                                  { $$ = newDeclaration($1, $2); }                                    
                      | TYPE '[' INTEGER ']' NAME                                                  { $$ = newVectDeclaration($1, $5, $3); }  
                      | TYPE NAME '=' expression                                                   { $$ = newList(newDeclaration($1, $2), newAssign(newReference($2), $4)); }                              
                      ;

variable_definition : NAME '=' expression                                               { $$ = newAssign(newReference($1), $3); }                                   
                    | NAME '+''=' expression                                            { $$ = newAssign(newReference($1), newAST('+', newReference($1), $4)); } 
                    | NAME '-''=' expression                                            { $$ = newAssign(newReference($1), newAST('-', newReference($1), $4)); }
                    | NAME '*''=' expression                                            { $$ = newAssign(newReference($1), newAST('*', newReference($1), $4)); }
                    | NAME '/''=' expression                                            { $$ = newAssign(newReference($1), newAST('/', newReference($1), $4)); }
                    ;

expression  : NAME                                                                      { $$ = newReference($1); }                                                            
            | CHAR                                                                      { $$ = newChar($1); }
            | STRING                                                                    { $$ = newString($1); }
            | INTEGER                                                                   { $$ = newNumber(1, $1); } 
            | REAL                                                                      { $$ = newNumber(2, $1); }
            | '(' expression ')'                                                        { $$ = $2; }
            | TYPE '(' expression ')'                                                   { printf("CASTING\n"); }
            | '-' expression %prec UMINUS                                               { $$ = newAST('M', $2, NULL); }
            | '+' expression %prec UPLUS                                                { $$ = newAST('U', $2, NULL); }                                      
            | expression '+' expression                                                 { $$ = newAST('+', $1, $3); } 
            | expression '-' expression                                                 { $$ = newAST('-', $1, $3); }
            | expression '*' expression                                                 { $$ = newAST('*', $1, $3); }
            | expression '/' expression                                                 { $$ = newAST('/', $1, $3); }
            | expression '%' expression                                                 { $$ = newAST('%', $1, $3); }
            | expression '^' expression                                                 { $$ = newAST('^', $1, $3); }
            | '(' expression ')' AND '(' expression ')'                                 { printf("AND()\n"); }
            | expression AND expression                                                 { printf("AND\n"); }
            | '(' expression ')' OR  '(' expression ')'                                 { printf("OR()\n"); }
            | expression OR expression                                                  { printf("OR\n"); }
            | NOT '(' expression ')'                                                    { printf("NOT\n"); }
            | expression COMPARE expression                                             { $$ = newAST($2, $1, $3); }
            ;             
%%

int main(int argc, char** argv) {
  openFiles();
  loadPrimitives();
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
  closeFiles();
  return 0;
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s \n", numlin, mens);
}

