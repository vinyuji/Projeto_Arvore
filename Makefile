all: meu_programa

meu_programa: arquivo.o main.o 
	gcc arquivo.o main.o -o meu_programa -lm

arquivo.o: arquivo.c
	gcc -c arquivo.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f meu_programa arquivo.o main.o 