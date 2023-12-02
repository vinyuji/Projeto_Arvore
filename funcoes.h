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
void comprimirArquivo(char *arquivo);
void imprimirASCII();
void descomprimirArquivo(char *arquivo);
void BitHuffman(const char *arquivo);
void removerPrimeiraLinha(const char *nomeArquivo);
void descomprimirFinal(const char *arquivoComprimido, Huffman *tabelaHuffman);
char *lerArquivo(const char *nomeArquivo);
void resumo(char *arquivo, Lista *list);

/*
mergeSort ordenar a lista uqe foi preenchida com as letras e a sua frequencia de um arquivo.

DividirLista para o merge sort

concatenar letras serve para juntar dois no da lista em um no arvore

ShowNoarquivo imprimi a tabela huffman em um arquivo

Substituirporhuffman le a lista de palavras e codifica em binario, conforme o codigo de huffman e ainda gera um arquivo Comprimido

comprimirArquivo vai pegar o arquivo comprimido ler ele, ver se ele e multiplo de 8, se nao for vai completar o arquivo com 0 ate ficar multiplo de 8
se for multiplo de 8 ele agrupa de 8 em 8 bit e troca por seu correspondente da tabela ascii. gera o arquivo Comprimido_Final.txt

imprimir ascii e so para ver se o arquivo Comprimido_Final.txt esta certo

descomprimirArquivo o proprio nome ja diz, pega o Comprimido_Final.txt decodifica conforme a tabela ascii e gera um novo arquivo Descoprimido.txt

Bithuffman gera ele le o arquivo Descomprimido.txt, na primeira linha desse arquivo tem a quantidade de bit origialmente e conta quantos bit tem apos a primeira linha
com isso calcula a diferenca e remove a "diferenca" vezes o ultimo caracter

remover a primerialinha serve para que eu possa reutilizar o arquivo Descomprimido.txt, com isso vou ter somente a sequencia binaria


descomprimirFinal serve para ler o arquivo Descomprimido.txt para  decodificar conforme a tabela ascii, no entanto nao deu certo
*/

#endif /* FUNCOES_H */
