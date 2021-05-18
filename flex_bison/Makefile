# Makefile basico para no andar repitiendo comandos para generar,
# compilar y ejecutar. A ampliar para testear y en siguientes fases. 

# make milex	[genera] lexico desde milex.l
# make F=n.x	[genera] y ejecuta lexico sobre n.x; via stdin: make<n.x

all: milex $(F)
	./milex $(F)

bison:
	bison -d bison.y

milex:
	flex milex.l

delete: 
	rm -f lex.yy.c milex y.tab.* bison.tab.* output

exec: 
	gcc lex.yy.c bison.tab.c -o output -lfl

run: delete bison milex exec

#F is a test file
F=pruebas.gta 
test:
	./output $(F)

# "No rule to make target" T si no encuentra ni puede crear T.
# Por supuesto, no regenera milex si no es necesario.
