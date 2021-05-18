%{
#include <stdio.h>
extern FILE *yyin;   /* declarado en lexico */
extern int numlin;   /* lexico le da valores */
//int yydebug=1;       /* modo debug si -t */
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
%nonassoc UMINUS

%right '='
%left '+' '-'
%left '*' '/' '%' '^'
%left '(' ')'

%start initial_main

%%

initial_main : /* nothing */
             | initial_main function_definition 
             | initial_main statement
             | initial_main function_definition EOL     
             | initial_main EOL
             | initial_main statement EOL                                         
             ;

function_definition : FUNCTION TYPE NAME '(' parameter_function ')' '{' content '}'     {printf("Declaracion de funcion (RETURN) con parametros\n");} 
                    | FUNCTION VECT NAME '(' parameter_function ')' '{' content '}'     {printf("Declaracion de funcion (RETURN) con parametros\n");}
                    | FUNCTION DICT NAME '(' parameter_function ')' '{' content '}'     {printf("Declaracion de funcion (RETURN) con parametros\n");}  
                    | FUNCTION NAME '(' parameter_function ')' '{' content '}'          {printf("Declaracion de funcion (NO-RETURN) con parametros\n");}          
                    ;

content : /* nothing */                                                                       
        | EOL content                                                                        
        | statement EOL content   
        | statement content                                                             
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
          | IF '(' expression ')' '{' content '}'                                                           {printf("IF simple\n");}
          | IF '(' expression ')' '{' content '}' ELSE '{' content '}'                                      {printf("IF y ELSE\n");}
          | IF '(' expression ')' '{' content '}' more_elsif                                                {printf("IF y ELSIF\n");}
          | IF '(' expression ')' '{' content '}' more_elsif ELSE '{' content '}'                           {printf("IF, ELSIF y ELSE\n");}            
          | FOR '(' TYPE NAME '=' expression ';' expression ';' variable_definition ')' '{' content '}'     {printf("Bucle FOR\n");}
          | WHILE '(' expression ')' '{' content '}'                                                        {printf("Bucle WHILE\n");}
          | RETURN expression ';'                                                                           {printf("Funcion RETURN\n");}
          | BREAK ';'                                                                                       {printf("Funcion BREAK\n");}
          | GOTO NAME ';'                                                                                   {printf("Etiqueta GOTO\n");}
          | LABEL                                                                                           {printf("Etiqueta LABEL\n");}
          | builtin_functions ';'                                                                           
          ;

more_elsif : ELSIF '(' expression ')' '{' content '}'
           | ELSIF '(' expression ')' '{' content '}' more_elsif

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

variable_declaration  : TYPE NAME                                                       {printf("Variable declarada\n");}
                      | TYPE NAME '=' expression                                    
                      | VECT '[' TYPE ']' NAME '=' '[' ']'                              {printf("Vector declarado y vacio\n");}
                      | VECT '[' TYPE ']' NAME '=' '[' parameter_to_function ']'        {printf("Vector declarado y asignado\n");}
                      | VECT '[' TYPE ']' NAME '=' expression                           {printf("Diccionario declarado y asignado\n");} 
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' ']'                     {printf("Diccionario declarado y vacio\n");}
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' '[' parameter_to_dict ']'   {printf("Diccionario declarado y asignado\n");}   
                      | DICT '[' TYPE ',' TYPE ']' NAME '=' expression                  {printf("Diccionario declarado y asignado\n");}                              
                      ;

variable_definition : NAME '=' expression                                               {printf("Variable definida\n");}                                   
                    | NAME '+''=' expression                                            {printf("Variable sumada acortada\n");}
                    | NAME '-''=' expression                                            {printf("Variable restada acortada\n");}
                    | NAME '*''=' expression                                            {printf("Variable multiplicada acortada\n");}
                    | NAME '/''=' expression                                            {printf("Variable dividida acortada\n");}
                    ;

expression  : NAME                                                                                                                                    
            | CHAR                                                                      {printf("Variable declarada y asignada (CHAR)\n");}
            | STRING                                                                    {printf("Variable declarada y asignada (STRING)\n");}
            | INTEGER                                                                   {printf("Variable declarada y asignada (INT)\n");} 
            | REAL                                                                      {printf("Variable declarada y asignada (REAL)\n");}
            | NAME '(' ')'                                                              {printf("Llamada a funcion\n");}                                                              
            | NAME '(' parameter_to_function ')'                                        {printf("Llamada a funcion con parametros\n");}       
            | '(' expression ')'  
            | TYPE '(' expression ')'                                                   {printf("Casting de variable\n");}                                                        
            | expression '+' expression                                                 {printf("Suma\n");} 
            | expression '-' expression                                                 {printf("Resta\n");}
            | expression '*' expression                                                 {printf("Multiplicacion\n");}
            | expression '/' expression                                                 {printf("Division\n");}
            | expression '%' expression                                                 {printf("Modulo\n");}
            | expression '^' expression                                                 {printf("Potencia\n");}
            | '(' expression ')' AND '(' expression ')'                                 {printf("AND logico\n");}
            | expression AND expression                                                 {printf("AND logico\n");}
            | '(' expression ')' OR  '(' expression ')'                                 {printf("OR logico\n");}       
            | expression OR expression                                                  {printf("OR logico\n");}
            | NOT '(' expression ')'                                                    {printf("NOT logico\n");}
            | expression COMPARE expression                                             {printf("Comparacion logica\n");}
            | builtin_functions
            ;             

parameter_to_dict : expression ':' expression              
                  | expression ':' expression ',' parameter_to_dict                                    
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

