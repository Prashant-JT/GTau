%{
#include <stdio.h>
#include "../symbol_table/table.h"
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
  struct symboList *symbol;
}

%token <real> REAL
%token <integer> INTEGER
%token <str> CHAR
%token <str> STRING
%token <type> VECT
%token <type> DICT
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

%type <node> expression parameter_to_function content statement more_elsif variable_declaration variable_definition builtin_functions
%type <symbol> parameter_function
%start initial_main

%%

initial_main : /* nothing */
             | initial_main function_definition 
             | initial_main statement
             | initial_main function_definition EOL     
             | initial_main EOL
             | initial_main statement EOL                                         
             ;

function_definition : FUNCTION TYPE NAME '(' parameter_function ')' '{' content '}'     { newFunction($2, $3, $5, $8); } 
                    | FUNCTION VECT NAME '(' parameter_function ')' '{' content '}'     { newFunction(7, $3, $5, $8); }
                    | FUNCTION DICT NAME '(' parameter_function ')' '{' content '}'     { newFunction(8, $3, $5, $8); }
                    | FUNCTION NAME '(' parameter_function ')' '{' content '}'          { newFunction(0, $2, $4, $7); }          
                    ;

content : /* nothing */                                                                 { $$ = NULL; }                                                         
        | EOL content                                                                   {;}
        | statement content                                                             { if ($2 == NULL) {
                                                                                            $$ = newAST('L', NULL, $1);
                                                                                          } else {
                                                                                            $$ = newAST('L', $2, $1);
                                                                                          }
                                                                                        } 
        ;

parameter_function : /*Nothing*/                                                        { $$ = NULL; }
                   | TYPE NAME                                                          { $$ = newSymboList(newAST('L', newAssignment($2, newVariable($1, 0, "")), newReference($1, $2)), NULL); }
                   | VECT NAME                                                          { $$ = newSymboList(newAST('L', newAssignment($2, newVector(0, $2, NULL)), newReference(7, $2)), NULL); }
                   | DICT NAME                                                          
                   | VECT NAME ',' parameter_function                                   { $$ = newSymboList(newAST('L', newAssignment($2, newVector(0, $2, NULL)), newReference(7, $2)), $4); }
                   | DICT NAME ',' parameter_function                                   
                   | TYPE NAME ',' parameter_function                                   { $$ = newSymboList(newAST('L', newAssignment($2, newVariable($1, 0, "")), newReference($1, $2)), $4); }
                   ;

statement : variable_declaration ';'                                                                                                                  
          | variable_definition ';' 
          | expression ';'
          | IF '(' expression ')' '{' content '}'                                                           { $$ = newIf($3, $6, NULL); }
          | IF '(' expression ')' '{' content '}' ELSE '{' content '}'                                      { $$ = newIf($3, $6, $10); }
          | IF '(' expression ')' '{' content '}' more_elsif                                                { $$ = newIf($3, $6, $8); }
          | IF '(' expression ')' '{' content '}' more_elsif ELSE '{' content '}'                                
          | FOR '(' TYPE NAME '=' expression ';' expression ';' variable_definition ')' '{' content '}'     { $$ = newFor(newAST('L', newAssignment($4, $6), newReference($3, $4)), $8, $10, $13); }
          | WHILE '(' expression ')' '{' content '}'                                                        { $$ = newAST('W', $6, $3); }
          | RETURN expression ';'                                                                           { $$ = newAST('Z', NULL, $2); }
          | BREAK ';'                                                                                       { $$ = newAST('B', NULL, NULL); }
          | GOTO NAME ';'                                                                                   { $$ = newAST('G', NULL, newReference(0, $2)); }
          | LABEL ':'                                                                                       { $$ = newAST('T', NULL, newReference(0, $1)); }
          | builtin_functions ';'                                                                           
          ;

more_elsif : ELSIF '(' expression ')' '{' content '}'                                   { $$ = newIf($3, $6, NULL); }
           | ELSIF '(' expression ')' '{' content '}' more_elsif                        { $$ = newIf($3, $6, $8); }

builtin_functions : PRINT '(' expression ')'                                            { $$ = newAST('P', NULL, $3); }
                  | PRINTLN '(' expression ')'                                          { $$ = newAST('P', newVariable(0, 0, NULL), $3); }
                  | SIZE '(' NAME ')'                                                   { $$ = callFunction("S", newReference(0, $3)); }
                  | APPEND '(' NAME ',' expression ')'                                  { $$ = callFunction("H", newAST('L', $5, newReference(0, $3))); }
                  | APPEND '(' NAME ',' expression ',' expression ')'                   
                  | POP '(' NAME ')'                                                    { $$ = callFunction("J", newReference(0, $3)); }
                  | POP '(' NAME ',' expression ')'                                     { $$ = callFunction("J", newAST('L', $5, newReference(0, $3))); }
                  | CLEAR '(' NAME ')'                                                  { $$ = callFunction("Q", newReference(0, $3)); }
                  | GET '(' NAME ',' expression ')'                                     { $$ = callFunction("K", newAST('L', $5, newReference(0, $3))); }
                  | CLONE '(' NAME ')'                                                  { $$ = callFunction("Y", newReference(0, $3)); }
                  ;

variable_declaration  : TYPE NAME                                                       { $$ = newAST('L', newAssignment($2, newVariable($1, 0, "")), newReference($1, $2)); }
                      | TYPE NAME '=' expression                                        { $$ = newAST('L', newAssignment($2, $4), newReference($1, $2)); }
                      | VECT '[' TYPE ']' NAME '=' '[' ']'                              { $$ = newVector($3, $5, NULL); }
                      | VECT '[' TYPE ']' NAME '=' '[' parameter_to_function ']'        { $$ = newVector($3, $5, $8); } 
                      | VECT '[' TYPE ']' NAME '=' expression                           { $$ = newVector($3, $5, $7); }
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' ']'                     
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' parameter_to_dict ']'     
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' expression                                               
                      ;

variable_definition : NAME '=' expression                                               { $$ = newAssignment($1, $3); }                                   
                    | NAME '+''=' expression                                            { $$ = newAssignment($1, newAST('+', $4, newReference(0, $1))); } 
                    | NAME '-''=' expression                                            { $$ = newAssignment($1, newAST('-', $4, newReference(0, $1))); }
                    | NAME '*''=' expression                                            { $$ = newAssignment($1, newAST('*', $4, newReference(0, $1))); }
                    | NAME '/''=' expression                                            { $$ = newAssignment($1, newAST('/', $4, newReference(0, $1))); }
                    ;

expression  : NAME                                                                      { $$ = newReference(0, $1); }                                                            
            | CHAR                                                                      { $$ = newVariable(5, 0, $1); }
            | STRING                                                                    { $$ = newVariable(6, 0, $1); }
            | INTEGER                                                                   { $$ = newVariable(1, $1, NULL); } 
            | REAL                                                                      { $$ = newVariable(2, $1, NULL); } 
            | NAME '(' ')'                                                              { $$ = callFunction($1, NULL); }                                                             
            | NAME '(' parameter_to_function ')'                                        { $$ = callFunction($1, $3); }       
            | '(' expression ')'                                                        { $$ = $2; }
            | TYPE '(' expression ')'                                                   { $$ = newAST($1, NULL, $3); }
            | '-' expression %prec UMINUS                                               { $$ = newAST('M', NULL, $2); }
            | '+' expression %prec UPLUS                                                { $$ = newAST('U', NULL,  $2); }                                      
            | expression '+' expression                                                 { $$ = newAST('+', $3, $1); } 
            | expression '-' expression                                                 { $$ = newAST('-', $3, $1); }
            | expression '*' expression                                                 { $$ = newAST('*', $3, $1); }
            | expression '/' expression                                                 { $$ = newAST('/', $3, $1); }
            | expression '%' expression                                                 { $$ = newAST('%', $3, $1); }
            | expression '^' expression                                                 { $$ = newAST('^', $3, $1); }
            | '(' expression ')' AND '(' expression ')'                                 { $$ = newAST('A', $6, $2); }
            | expression AND expression                                                 { $$ = newAST('A', $3, $1); }
            | '(' expression ')' OR  '(' expression ')'                                 { $$ = newAST('O', $6, $2); }
            | expression OR expression                                                  { $$ = newAST('O', $3, $1); }
            | NOT '(' expression ')'                                                    { $$ = newAST('N', NULL, $3); }
            | expression COMPARE expression                                             { $$ = newAST($2, $3, $1); }
            | builtin_functions
            ;             

parameter_to_dict : expression ':' expression              
                  | expression ':' expression ',' parameter_to_dict                                    
                  ;

parameter_to_function : expression              
                      | expression ',' parameter_to_function                            { $$ = newAST('L', $3, $1); }
                      ;

%%

int main(int argc, char** argv) {
  initList();
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s \n", numlin, mens);
}

