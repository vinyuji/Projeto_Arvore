#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include "Lista.h"

void leituraArquivo();
void contarLetras(Lista *list);
void contarFrequencia(FILE *arquivo, Lista *list);

#endif /* ARQUIVO_H */