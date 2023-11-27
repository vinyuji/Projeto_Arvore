all: meu_programa

meu_programa: arquivo.o main.o Lista.o funcoes.o arvore.o
	gcc arquivo.o main.o Lista.o funcoes.o arvore.o -o meu_programa -lm

arquivo.o: arquivo.c
	gcc -c arquivo.c

main.o: main.c
	gcc -c main.c

Lista.o: Lista.c
	gcc -c Lista.c

funcoes.o: funcoes.c
	gcc -c funcoes.c

arvore.o: arvore.c
	gcc -c arvore.c

clean:
	rm -f meu_programa arquivo.o main.o 