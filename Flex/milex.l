%{
//TIPOS_VALORES
#define INTEGER_V 260
#define BOOLEAN_V 261
#define CHAR_V 262
#define STRING_V 263
#define REAL_V 269

//TIPOS_NOMBRE
#define INTEGER_N 270
#define BOOLEAN_N 271
#define CHAR_N 272
#define STRING_N 273
#define VECTOR_N 274
#define DICT_N 275
#define FLOAT_N 278
#define DOUBLE_N 279

//NOMBRES
#define MAIN 280
#define FUNCTION 281
#define RETURN 282
#define NAME 283

//LOGICOS
#define NOT 290
#define AND 291
#define OR 292
#define EQUAL 293
#define NOTEQUAL 294
#define GREATEQUAL 295
#define LESSEQUAL 296

//ASIGNACION
#define ADDEQUAL 300
#define SUBEQUAL 301
#define MULTEQUAL 302
#define DIVEQUAL 303

//CONTROL
#define IF 310
#define ELSIF 311
#define ELSE 312
#define FOR 313
#define WHILE 314
#define BREAK 315
#define GOTO 316
#define LABEL 317

//FUNCIONES
#define PRINT 320
#define PRINTLN 321
#define SIZE 322
#define APPEND 323
#define POP 324
#define CLEAR 325
#define GET 326
#define CLONE 327

int numlin = 1;
void error(char*);
%}

%x comment string
letter [a-zA-Z_]
digit  [0-9]
integer ("+"|-)?{digit}+
real ("+"|-)?{digit}+"."{digit}+
boolean (TRUE|FALSE)
char (\"[^\"]\")
string (\"[^\"]*\")
label [A-Z_]+({digit}|[A-Z_])*

%%
main {return MAIN;}
function {return FUNCTION;}
return {return RETURN;}

int  {return INTEGER_N;}
double  {return DOUBLE_N;}
float  {return FLOAT_N;}
boolean {return BOOLEAN_N;}
char {return CHAR_N;}
string {return STRING_N;}
vect {return VECTOR_N;}
dict {return DICT_N;}

{integer}  {return INTEGER_V;}
{real}  {return REAL_V;}
{boolean} {return BOOLEAN_V;}
{char} {return CHAR_V;}
{string} {return STRING_V;}

if {return IF;}
elsif {return ELSIF;}
else {return ELSE;}
for {return FOR;}
while {return WHILE;}
break {return BREAK;}
goto {return GOTO;}
#{label}: {return LABEL;}

print {return PRINT;}
println {return PRINTLN;}
size {return SIZE;}
append {return APPEND;}
pop {return POP;}
clear {return CLEAR;}
get {return GET;}
clone {return CLONE;}

and {return AND;}
or {return OR;} 
not {return NOT;} 

"+=" {return ADDEQUAL;}
"-=" {return SUBEQUAL;} 
"*=" {return MULTEQUAL;} 
"/=" {return DIVEQUAL;} 

">=" {return GREATEQUAL;}
"<=" {return LESSEQUAL;} 
"==" {return EQUAL;} 
"!=" {return NOTEQUAL;} 

"/*"               BEGIN(comment);
<comment>[^*\n]+   // eat comment in chunks
<comment>"*"       // eat the lone star
<comment>\n        numlin++;
<comment>"*"+"/"   BEGIN(INITIAL);

[-+*/^%=] {return yytext[0];}
[,:;] {return yytext[0];}
[<>] {return yytext[0];}
[()\[\]{}] {return yytext[0];}

{letter}+({digit}|{letter})* {return NAME;}

\n                 {numlin++; /* continua leyendo */} 

[ \t]
.                  {char s[4]; sprintf(s, "'%c'", yytext[0]); error(s);}
<<EOF>>            {return 0; /* por defecto */}
%%

int main(int argc, char** argv) {
  int s;
  if(argc>1) yyin=fopen(argv[1],"r"); /* else yyin=stdin */ 
  do printf("%i ",s=yylex()); while(s != 0);
  return 0;
}

void error(char* mens) {
  printf("Error lexico en linea %i: %s\n",numlin,mens);
}
