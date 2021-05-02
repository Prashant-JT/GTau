%{
# include <string.h>
# include "bison.tab.h"
int numlin = 1;
%}

%x comment string
letter [a-zA-Z_]
digit  [0-9]
integer ("+"|-)?{digit}+
real ("+"|-)?{digit}+"."{digit}+
name {letter}+({digit}|{letter})*
char (\"[^\"]\")
string (\"[^\"]*\")
label [A-Z_]+({digit}|[A-Z_])*

%%
"+" |
"-" |
"*" |
"/" |
"^" |
"%" |
"=" |
":" |
")" |
"(" |
"[" |
"]" |
"}" |
"{" |
"," |
";"                     { return yytext[0]; }

">"                     { yylval.compare = 1; return COMPARE; }
"<"                     { yylval.compare = 2; return COMPARE; }
">="                    { yylval.compare = 3; return COMPARE; }
"<="                    { yylval.compare = 4; return COMPARE; }
"=="                    { yylval.compare = 5; return COMPARE; }
"!="                    { yylval.compare = 6; return COMPARE; }  

"and"                    { return AND; }
"or"                    { return OR; }
"not"                    { return NOT; }

"int"                   { yylval.type = 1; return TYPE; }
"double"                 { yylval.type = 2; return TYPE; }
"float"                  { yylval.type = 3; return TYPE; }
"boolean"                  { yylval.type = 4; return TYPE; }
"char"                  { yylval.type = 5; return TYPE; }
"string"                  { yylval.type = 6; return TYPE; }
"vect"                  { yylval.type = 7; return TYPE; }
"dict"                  { yylval.type = 8; return TYPE; }

"if"                    { return IF;}
"elsif"                  { return ELSE;}
"else"                  { return ELSE;}
"for"                   { return FOR;}
"while"                 { return WHILE;}
"break"                 { return BREAK; }
"goto"                 { return GOTO; }
#{label}:                 { return LABEL; }

"function"              { return FUNCTION;}
"return"                { return RETURN; }
"print"                 { return PRINT; }
"println"               { return PRINTLN; }
"size"                  { return SIZE; }
"append"                { return APPEND; }
"pop"                   { return POP; }
"clear"                 { return CLEAR; }
"get"                   { return GET; }
"clone"                 { return CLONE; }

{name}                  { yylval.name = yytext; return NAME; }

{char}                  { yylval.character = substr(yytext, 1, yyleng-1); return CHAR; }
{string}                { yylval.string = substr(yytext, 1, yyleng-1); return STRING; }
{integer}               { yylval.integer = atoi(yytext); return INTEGER; }
{real}                  { yylval.real = atoi(yytext); return REAL;}

"/*"               BEGIN(comment);
<comment>[^*\n]+   // eat comment in chunks
<comment>"*"       // eat the lone star
<comment>\n        numlin++;
<comment>"*"+"/"   BEGIN(INITIAL);

[ \t]
\n                 {numlin++; return EOL; } 
.                  { yyerror("error lexico"); }
%%
