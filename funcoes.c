#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "arvore.h"
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

