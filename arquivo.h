#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include "Lista.h"

void leituraArquivo();
void contarLetras(Lista *list);
void contarFrequencia(FILE *arquivo, Lista *list);
int contarBit();

#endif /* ARQUIVO_H */