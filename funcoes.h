// funcoes.h
#ifndef FUNCOES_H
#define FUNCOES_H

#include "Lista.h"

void MergeSort(No **list);
void DividirLista(No *inicio, No **metade1, No **metade2);
char* ConcatenarLetras(char *PalavraA, char *PalavraB);
void ShowNoArquivo(Huffman tabela[], int tamanho, const char *ARQUI);
void SubstituirPorHuffman(char *ARQUI, Huffman tabela[]);
void LiberarMemoriaHuffman(Huffman tabela[], int tamanho);
char *ConcatenarBITS(char *destino, const char *origem);
void comprimirArquivo(char *arquivo);
void imprimirASCII();
void descomprimirArquivo(char *arquivo);
void BitHuffman(const char *arquivo);

#endif /* FUNCOES_H */
