#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include "Lista.h"

void leituraArquivo();
void contarLetras(Lista *list);
void contarFrequencia(FILE *arquivo, Lista *list);
int contarBit();

/*
aqui o unico que e muito relevante e o contar bit que conta a quantidade de bit tem um arquivo
o contarFrequencia a frequencia de uma letra dentro de um arquivo
*/

#endif /* ARQUIVO_H */