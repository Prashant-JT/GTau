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
%token <type> VECT
%token <type> DICT
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

%start initial_main

%%

initial_main : /* nothing */
             | initial_main function_definition EOL 
             | initial_main EOL
             | initial_main statement EOL                                                
             ;

function_definition : FUNCTION TYPE NAME '(' ')' '{' content '}'                        
                    | FUNCTION TYPE NAME '(' parameter_function ')' '{' content '}'               
                    ;

content : /* nothing */                                                                    
        | EOL content                                                                        
        | statement EOL content                                                               
        ;

parameter_function : TYPE NAME                                                      
                   | TYPE NAME ',' parameter_function                                      
                   ;

statement : variable_declaration ';'
          | variable_definition ';'
          | expression ';'
          | IF '(' expression ')' '{' content '}'                                          
          | IF '(' expression ')' '{' content '}' ELSE '{' content '}'                        
          | IF '(' expression ')' '{' content '}' ELSIF '{' content '}'                        
          | IF '(' expression ')' '{' content '}' ELSIF '{' content '}' ELSE '{' content '}'                          
          | FOR '(' TYPE NAME '=' expression ';' expression ';' variable_definition ')' '{' content '}' 
          | WHILE '(' expression ')' '{' content '}'                                       
          | RETURN expression ';'      
          | BREAK ';'   
          | GOTO NAME ';'
          | LABEL 
          | builtin_functions ';'                                            
          ;

builtin_functions : PRINT '(' expression ')'
                  | PRINTLN '(' expression ')'
                  | SIZE '(' NAME ')'
                  | APPEND '(' NAME ',' NAME ')'
                  | APPEND '(' NAME ',' NAME ',' NAME ')'
                  | POP '(' NAME ',' NAME ')'
                  | CLEAR '(' NAME ')'
                  | GET '(' NAME ',' NAME ')'
                  | CLONE '(' NAME ')'
                  ;

variable_declaration  : TYPE NAME                                                    
                      | TYPE NAME '=' expression 
                      | VECT '[' TYPE ']' NAME '=' '[' ']'  
                      | VECT '[' TYPE ']' NAME '=' '[' parameter_to_function ']'     
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' ']'  
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' parameter_to_dict ']'                                   
                      ;

variable_definition : NAME '=' expression                                            
                    | NAME '+''=' expression                                        
                    | NAME '-''=' expression                                        
                    | NAME '*''=' expression                                         
                    | NAME '/''=' expression                                       
                    ;

expression  : NAME                                                                     
            | CHAR                                                                      
            | STRING
            | INTEGER                                                                    
            | REAL     
            | NAME '(' ')'                                                              
            | NAME '(' parameter_to_function ')'                                              
            | '(' expression ')'                                                       
            | expression '+' expression                                               
            | expression '-' expression                                                
            | expression '*' expression                                               
            | expression '/' expression                                                
            | expression '%' expression                                                 
            | expression '^' expression                                                 
            | '(' expression ')' AND '(' expression ')'                               
            | expression AND expression                                
            | '(' expression ')' OR  '(' expression ')'                                        
            | expression OR expression                               
            | NOT '(' expression ')'                                                    
            | expression COMPARE expression                                         
            ;             

parameter_to_dict : expression ':' parameter_to_dict              
                  | expression ':' parameter_to_dict ',' parameter_to_dict                                    
                  ;

parameter_to_function : expression              
                      | expression ',' parameter_to_function                                    
                      ;


%%

int main(int argc, char** argv) {
  if (argc>1) yyin=fopen(argv[1],"r");
  yyparse();
}

void yyerror(char* mens) {
  printf("Error en linea %i: %s ", numlin, mens);
}

