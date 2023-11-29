// funcoes.h
#ifndef FUNCOES_H
#define FUNCOES_H

#include "Lista.h"

void MergeSort(No **list);
void DividirLista(No *inicio, No **metade1, No **metade2);
char* ConcatenarLetras(char *PalavraA, char *PalavraB);
void ShowNoArquivo(Huffman tabela[], int tamanho, const char *nomeArquivo);
void ComprimirNoArquivo(Huffman tabela[], int tamanho, const char *nomeArquivo);
void LiberarMemoriaHuffman(Huffman tabela[], int tamanho);

#endif /* FUNCOES_H */
