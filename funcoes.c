#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Lista.h"
#include "arquivo.h"


// Função auxiliar para dividir a lista em duas partes
void DividirLista(No *inicio, No **metade1, No **metade2) {
    No *lento, *rapido;
    lento = inicio;
    rapido = inicio->proximo;

    while (rapido != NULL) {
        rapido = rapido->proximo;
        if (rapido != NULL) {
            lento = lento->proximo;
            rapido = rapido->proximo;
        }
    }

    *metade1 = inicio;
    *metade2 = lento->proximo;
    lento->proximo = NULL;
}

// Função que mescla as duas listas ordenadas
No *Merge(No *lista1, No *lista2) {
    if (lista1 == NULL) {
        return lista2;
    }
    if (lista2 == NULL) {
        return lista1;
    }

    No *resultado = NULL;

    if (lista1->data.Frequencia < lista2->data.Frequencia ||
        (lista1->data.Frequencia == lista2->data.Frequencia && strcmp(lista1->data.Letra, lista2->data.Letra) < 0)) {
        resultado = lista1;
        resultado->proximo = Merge(lista1->proximo, lista2);
    } else {
        resultado = lista2;
        resultado->proximo = Merge(lista1, lista2->proximo);
    }

    return resultado;
}

// Função principal de Merge Sort para listas encadeadas
void MergeSort(No **list) {
    if (*list == NULL || (*list)->proximo == NULL) {
        return;
    }

    No *metade1;
    No *metade2;
    
    DividirLista(*list, &metade1, &metade2);

    MergeSort(&metade1);
    MergeSort(&metade2);

    *list = Merge(metade1, metade2);
}

char* ConcatenarLetras(char *PalavraA, char *PalavraB){
    size_t tamanhoTotal = strlen(PalavraA) + strlen(PalavraB) + 1;
    char* PalavraConcatenada = (char*)malloc(tamanhoTotal);

    if (PalavraConcatenada != NULL) {
        strcpy(PalavraConcatenada, PalavraA);
        strcat(PalavraConcatenada, PalavraB);
    }

    return PalavraConcatenada;

}

void ShowNoArquivo(Huffman tabela[], int tamanho, const char *nomeArquivo){
FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "\tTabela Huffman:\n");
    fprintf(arquivo,"\t_____________________________\n");
    fprintf(arquivo,"\t| Letra | codigo de Huffman |\n");
    fprintf(arquivo,"\t|_______|___________________|\n");

    for (int i = 0; i < tamanho; i++) {
        // Verifica se o caractere é imprimível e não é um caractere de controle
        if (isprint(tabela[i].letra) || isspace(tabela[i].letra) || ispunct(tabela[i].letra)) {
            // Verifica se a letra já foi impressa
            int duplicado = 0;
            for (int j = 0; j < i; j++) {
                if (tabela[i].letra == tabela[j].letra) {
                    duplicado = 1;
                    break;
                }
            }
            if (!duplicado) {
                fprintf(arquivo, "\t|   %c   |       %-10s  |\n", tabela[i].letra, tabela[i].codigo[0] ? tabela[i].codigo : "(vazio)");
            }
        }
    }

    fprintf(arquivo, "\t|_______|___________________|\n");
    fclose(arquivo);
}

void ComprimirNoArquivo(Huffman tabela[], int tamanho, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "Códigos ASCII:\n");

    for (int i = 0; i < tamanho; i++) {
        if (tabela[i].codigo != NULL) {
            // Calcula o número de bits que faltam para completar 8
            int bitsFaltando = 8 - strlen(tabela[i].codigo);
            // printf("%d\n", bitsFaltando);

            // Preenche os bits que faltam
            char *codigoCompleto = (char *)malloc(9);  // 8 bits + '\0'
            strncpy(codigoCompleto, tabela[i].codigo, strlen(tabela[i].codigo));
            for (int j = 0; j < bitsFaltando; j++) {
                strcat(codigoCompleto, "0");
            }
            // printf("%s\n", codigoCompleto);
            // Converte o código binário para um caractere ASCII
            int valorDecimal = strtol(codigoCompleto, NULL, 2);
            char caractereASCII = (char)valorDecimal;
            // printf("%c\n", caractereASCII);

            // Imprime no arquivo
            fprintf(arquivo, "Código: %s, Caractere ASCII: %c\n", codigoCompleto, caractereASCII);

            // Libera a memória alocada dinamicamente
            free(codigoCompleto);
        }
    }

    fclose(arquivo);
}

void LiberarMemoriaHuffman(Huffman tabela[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(tabela[i].codigo);
    }
}


