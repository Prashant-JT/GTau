# Makefile basico para no andar repitiendo comandos para generar,
# compilar y ejecutar. A ampliar para testear y en siguientes fases. 

# make milex	[genera] lexico desde milex.l
# make F=n.x	[genera] y ejecuta lexico sobre n.x; via stdin: make<n.x

#F is a test file
F=pruebas.gta 
O = out.q.c

all: milex $(F)
	./milex $(F)

obj: $(O)
	less $(O)

bison:
	bison -d bison.y

milex:
	flex milex.l

delete: 
	rm -f lex.yy.c milex y.tab.* bison.tab.* output out.q.c .tmp_*

exec: 
	gcc lex.yy.c bison.tab.c ../symbol_table/table.c ../symbol_table/operations.c ../ErrorMessage/ErrorMessage.c ../code_generation/qManage.c ../code_generation/codeGeneration.c -o output -lfl

run: delete bison milex exec

test:
	./output $(F)

# "No rule to make target" T si no encuentra ni puede crear T.
# Por supuesto, no regenera milex si no es necesario.
