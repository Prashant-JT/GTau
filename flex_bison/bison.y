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

%type <node> expression parameter_to_function content statement more_elsif variable_declaration variable_definition
%start initial_main

%%

initial_main : /* nothing */
             | initial_main function_definition 
             | initial_main statement
             | initial_main function_definition EOL     
             | initial_main EOL
             | initial_main statement EOL                                         
             ;

function_definition : FUNCTION TYPE NAME '(' parameter_function ')' '{' content '}'     { newfundef($2, $3, NULL, $7); } 
                    | FUNCTION VECT NAME '(' parameter_function ')' '{' content '}'     {printf("Declaracion de funcion (RETURN) con parametros\n");}
                    | FUNCTION DICT NAME '(' parameter_function ')' '{' content '}'     {printf("Declaracion de funcion (RETURN) con parametros\n");}  
                    | FUNCTION NAME '(' parameter_function ')' '{' content '}'          {printf("Declaracion de funcion (NO-RETURN) con parametros\n");}          
                    ;

content : /* nothing */                                                                 { $$ = NULL; }                                                         
        | EOL content                                                                   {;}
        | statement content                                                             { if ($2 == NULL) {
                                                                                            $$ = newAST('L', $1, NULL);
                                                                                          } else {
                                                                                            $$ = newAST('L', $1, $2);
                                                                                          }
                                                                                        } 
        ;

parameter_function : /*Nothing*/ 
                   | TYPE NAME  
                   | VECT NAME 
                   | DICT NAME   
                   | VECT NAME ',' parameter_function 
                   | DICT NAME ',' parameter_function                                                  
                   | TYPE NAME ',' parameter_function                                      
                   ;

statement : variable_declaration ';'                                                    
          | variable_definition ';'
          | expression ';'
          | IF '(' expression ')' '{' content '}'                                                           { $$ = newIf($3, $6, NULL); }
          | IF '(' expression ')' '{' content '}' ELSE '{' content '}'                                      { $$ = newIf($3, $6, $10); }
          | IF '(' expression ')' '{' content '}' more_elsif                                                { $$ = newIf($3, $6, $8); }
          | IF '(' expression ')' '{' content '}' more_elsif ELSE '{' content '}'                                
          | FOR '(' TYPE NAME '=' expression ';' expression ';' variable_definition ')' '{' content '}'     { $$ = newFor(newAST('L', newReference($3, $4), 
                                                                                                            newAssignment($4, $6)), $8, $10, $13); }
          | WHILE '(' expression ')' '{' content '}'                                                        { $$ = newAST('W', $3, $6); }
          | RETURN expression ';'                                                                           { $$ = newAST('Z', $2, NULL); }
          | BREAK ';'                                                                                       { $$ = newAST('B', NULL, NULL); }
          | GOTO NAME ';'                                                                                   { $$ = newAST('G', newReference(0, $2), NULL); }
          | LABEL ':'                                                                                       { $$ = newAST('T', newReference(0, $1), NULL); }
          | builtin_functions ';'                                                                           
          ;

more_elsif : ELSIF '(' expression ')' '{' content '}'                                   { $$ = newIf($3, $6, NULL); }
           | ELSIF '(' expression ')' '{' content '}' more_elsif                        { $$ = newIf($3, $6, $8); }

builtin_functions : PRINT '(' expression ')'                                            {printf("Funcion PRINT\n");}
                  | PRINTLN '(' expression ')'                                          {printf("Funcion PRINTLN\n");}
                  | SIZE '(' NAME ')'                                                   {printf("Funcion SIZE\n");}
                  | APPEND '(' NAME ',' expression ')'                                  {printf("Funcion APPEND vectores\n");}
                  | APPEND '(' NAME ',' expression ',' expression ')'                   {printf("Funcion APPEND diccionarios\n");}
                  | POP '(' NAME ')'                                                    {printf("Funcion POP\n");}
                  | POP '(' NAME ',' expression ')'                                     {printf("Funcion POP\n");}
                  | CLEAR '(' NAME ')'                                                  {printf("Funcion CLEAR\n");}
                  | GET '(' NAME ',' expression ')'                                     {printf("Funcion GET\n");}
                  | CLONE '(' NAME ')'                                                  {printf("Funcion CLONE\n");}
                  ;

variable_declaration  : TYPE NAME                                                       { $$ = newAST('L', newReference($1, $2), newAssignment($2, newVariable($1, 0, ""))); }
                      | TYPE NAME '=' expression                                        { $$ = newAST('L', newReference($1, $2), newAssignment($2, $4)); }
                      | VECT '[' TYPE ']' NAME '=' '[' ']'                              
                      | VECT '[' TYPE ']' NAME '=' '[' parameter_to_function ']'        
                      | VECT '[' TYPE ']' NAME '=' expression                           
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
            | TYPE '(' expression ')'                                                   { $$ = newAST($1, $3, NULL); }
            | '-' expression %prec UMINUS                                               { $$ = newAST('M', $2, NULL); }
            | '+' expression %prec UPLUS                                                { $$ = newAST('P', $2, NULL); }                                      
            | expression '+' expression                                                 { $$ = newAST('+', $1, $3); } 
            | expression '-' expression                                                 { $$ = newAST('-', $1, $3); }
            | expression '*' expression                                                 { $$ = newAST('*', $1, $3); }
            | expression '/' expression                                                 { $$ = newAST('/', $1, $3); }
            | expression '%' expression                                                 { $$ = newAST('%', $1, $3); }
            | expression '^' expression                                                 { $$ = newAST('^', $1, $3); }
            | '(' expression ')' AND '(' expression ')'                                 { $$ = newAST('A', $2, $6); }
            | expression AND expression                                                 { $$ = newAST('A', $1, $3); }
            | '(' expression ')' OR  '(' expression ')'                                 { $$ = newAST('O', $2, $6); }
            | expression OR expression                                                  { $$ = newAST('O', $1, $3); }
            | NOT '(' expression ')'                                                    { $$ = newAST('N', $3, NULL); }
            | expression COMPARE expression                                             { $$ = newAST($2, $1, $3); }
            | builtin_functions
            ;             

parameter_to_dict : expression ':' expression              
                  | expression ':' expression ',' parameter_to_dict                                    
                  ;

parameter_to_function : expression              
                      | expression ',' parameter_to_function                            { $$ = newAST('L', $1, $3); }
                      ;

%%

int main(int argc, char** argv) {
  initList();
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s ", numlin, mens);
}

