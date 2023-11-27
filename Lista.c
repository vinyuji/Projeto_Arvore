#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Lista.h"
// #include "arvore.h"
#include "funcoes.h"


int contadorIteracoes = 0;
// Inicializa a lista
void Init(Lista *list) {
    list->inicio = NULL;
    list->tam = 0;
}

// Insere um elemento no início da lista
void InserirInicioLista(Lista *list, Frequencia data) {
    No *novoNo = malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->data = data;
        novoNo->proximo = list->inicio;
        list->inicio = novoNo;
    } else {
        printf("Erro na alocação de memória.\n");
        // Tratar erro na alocação, se necessário
    }
    list->tam++;
    printf("tamanho lista: %d", list->tam);
}

void InserirCrescente(Lista *list, Frequencia data) {
    No *novoNo = malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    novoNo->data = data;
    novoNo->proximo = NULL;

    if (list->inicio == NULL || data.Frequencia <= list->inicio->data.Frequencia || (data.Frequencia == list->inicio->data.Frequencia && strcmp(data.Letra, list->inicio->data.Letra) <= 0)) {
        // Inserir no início
        novoNo->proximo = list->inicio;
        list->inicio = novoNo;
    } else {
        // Procurar posição de inserção
        No *atual = list->inicio;
        No *anterior = NULL;

        while (atual != NULL && data.Frequencia > atual->data.Frequencia) {
            anterior = atual;
            atual = atual->proximo;
        }

        // Inserir no meio ou no final
        while (atual != NULL && data.Frequencia == atual->data.Frequencia && strcmp(data.Letra, atual->data.Letra) > 0) {
            anterior = atual;
            atual = atual->proximo;
        }

        novoNo->proximo = atual;
        anterior->proximo = novoNo;
    }
    list->tam++;
}

// Remove o elemento do início da lista
void RemoverInicioLista(Lista *list) {
    if (list->inicio != NULL) {
        No *temp = list->inicio;
        list->inicio = temp->proximo;
        free(temp);
    }
    list->tam--;
}

// lista os elementos da lista
void ShowLista(Lista *list) {
    No *atual = list->inicio;
    while (atual != NULL) {
            printf("Letra: %s, Frequencia: %d, frequencia Letra: %d\n", atual->data.Letra, atual->data.Frequencia, atual->data.frequenciaLetra);
            atual = atual->proximo;
    }
}

// Modificação em CriarArvoreNo
No *CriarArvoreNo(No *Esq, No *Dir, int Val, Frequencia Letras) {
    printf("Criando nó da árvore...\n");
    No *NovoNo = (No*)malloc(sizeof(No));
    if (NovoNo != NULL) {
        NovoNo->Esquerda = Esq;
        NovoNo->Direita = Dir;
        NovoNo->valor = Val;
        NovoNo->data.Frequencia = Val;
        NovoNo->data.Letra = strdup(Letras.Letra);

        if (NovoNo->data.Letra == NULL) {
            printf("Erro na alocação de memória para Letra.\n");
            free(NovoNo);
            return NULL;
        }

        NovoNo->data.frequenciaLetra = Letras.frequenciaLetra;
        NovoNo->proximo = NULL;
        printf("Nó da árvore criado com sucesso!\n");
    } else {
        printf("Erro na alocação de memória para Nó.\n");
    }
    return NovoNo;
}

void InserirNoArvoreLista(Lista *list, No *NovoNo3) {
    printf("Inserindo nó da árvore na lista...\n");
    Frequencia data = NovoNo3->data;

    if (list->inicio == NULL) {
        printf("Inserindo no início da lista...\n");
        NovoNo3->proximo = list->inicio;
        list->inicio = NovoNo3;
    } else if (data.Frequencia < list->inicio->data.Frequencia ||
               (data.Frequencia == list->inicio->data.Frequencia && data.frequenciaLetra < list->inicio->data.frequenciaLetra) ||
               (data.Frequencia == list->inicio->data.Frequencia && data.frequenciaLetra == list->inicio->data.frequenciaLetra && strcmp(data.Letra, list->inicio->data.Letra) <= 0)) {
        // Inserir no início
        printf("Inserindo no início da lista...\n");
        NovoNo3->proximo = list->inicio;
        list->inicio = NovoNo3;
    } else {
        // Procurar posição de inserção
        No *atual = list->inicio;
        No *anterior = NULL;

        while (atual != NULL &&
               (data.Frequencia > atual->data.Frequencia ||
                (data.Frequencia == atual->data.Frequencia &&
                 (data.frequenciaLetra > atual->data.frequenciaLetra ||
                  (data.frequenciaLetra == atual->data.frequenciaLetra && strcmp(data.Letra, atual->data.Letra) > 0))))) {
            anterior = atual;
            atual = atual->proximo;
        }

        // Inserir no meio ou no final
        NovoNo3->proximo = atual;
        anterior->proximo = NovoNo3;
        printf("Inserindo no meio ou no final da lista...\n");
    }
    list->tam++;
    printf("tamanho: %d", list->tam);
    printf("Nó inserido com sucesso na lista!\n");
}

// Cria a Árvore com base nos dois menores números da lista
No *NoArvoreNoLista(Lista *list) {
    if(list->tam <= 1){
        printf("list->1: %d", list->tam);
        return NULL;
    }

    No *NovoNo1 = (No*)malloc(sizeof(No));
    No *NovoNo2 = (No*)malloc(sizeof(No));
    No *NovoNo3 = (No*)malloc(sizeof(No));
    Frequencia DATA;

    if (NovoNo1 != NULL && NovoNo2 != NULL) {
        if (list->inicio != NULL) {
            memcpy(NovoNo1, list->inicio, sizeof(No));
            RemoverInicioLista(list);
        } else {
            free(NovoNo1);
            free(NovoNo2);
            return NULL;
        }

        if (list->inicio != NULL) {
            memcpy(NovoNo2, list->inicio, sizeof(No));
            RemoverInicioLista(list);
        } else {
            free(NovoNo1);
            free(NovoNo2);
            return NULL;
        }

        if (NovoNo1->data.Frequencia <= NovoNo2->data.Frequencia) {
            DATA.Letra = ConcatenarLetras(NovoNo1->data.Letra, NovoNo2->data.Letra);
            DATA.frequenciaLetra = NovoNo1->data.frequenciaLetra + NovoNo2->data.frequenciaLetra;

            NovoNo3 = CriarArvoreNo(NovoNo1, NovoNo2, NovoNo1->data.Frequencia + NovoNo2->data.Frequencia, DATA);
            if (NovoNo3 != NULL) {
                InserirNoArvoreLista(list, NovoNo3);
            } else {
                printf("Falha ao criar nó da árvore.\n");
            }
        } else {
            DATA.Letra = ConcatenarLetras(NovoNo1->data.Letra, NovoNo2->data.Letra);
            NovoNo3 = CriarArvoreNo(NovoNo2, NovoNo1, NovoNo1->data.Frequencia + NovoNo2->data.Frequencia, DATA);
            if (NovoNo3 != NULL) {
                InserirNoArvoreLista(list, NovoNo3);
            } else {
                printf("Falha ao criar nó da árvore.\n");
            }
        }
    } else {
        printf("Problemas na alocação de memória!\n");
    }
    contadorIteracoes++;
    return (No*)NovoNo3;
}

// Função para liberar a memória de um nó da árvore
void LiberarNo(No *no) {
    free(no->data.Letra);
    free(no);
}

// Função para liberar memória de forma recursiva
void LiberarMemoriaRecursiva(No *raiz) {
    if (raiz == NULL) {
        return;
    }

    LiberarMemoriaRecursiva(raiz->Esquerda);
    LiberarMemoriaRecursiva(raiz->Direita);

    LiberarNo(raiz);  // Liberar o nó
}

// Função para liberar a memória da árvore
void LiberarArvore(Lista *list) {
    LiberarMemoriaRecursiva(list->inicio);
    list->inicio = NULL;  // Certificar-se de que a lista está vazia
}

// Função para liberar a memória da lista, incluindo os dados dos nós
void EsvaziarLista(Lista *list) {
    No *atual = list->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        LiberarNo(temp);
    }
    list->inicio = NULL;
    list->tam = 0;
}

// Função para mostrar a árvore em ordem (in-order traversal)
// ...

// void AuxiliarShowArvore(Lista *list) {
//     No *AUX = list->inicio;
//     ShowArvore(AUX);
// }

void AuxiliarShowArvore(Lista *list) {
    No *AUX = list->inicio;
    ShowArvoreVisual(AUX, 0);
}

void ShowArvore(No *AUX) {
    if (AUX != NULL) {
        ShowArvore(AUX->Esquerda);
        printf("Letra: %s, Frequencia: %d, frequencia Letra: %d\n", AUX->data.Letra, AUX->data.Frequencia, AUX->data.frequenciaLetra);
        ShowArvore(AUX->Direita);
    }
}

void ShowArvoreVisual(No *AUX, int nivel) {
    if (AUX != NULL) {
        ShowArvoreVisual(AUX->Direita, nivel + 1);

        for (int i = 0; i < nivel; i++) {
            printf("    ");
        }

        printf("Letra: %s, Frequencia: %d, frequencia Letra: %d\n", AUX->data.Letra, AUX->data.Frequencia, AUX->data.frequenciaLetra);

        ShowArvoreVisual(AUX->Esquerda, nivel + 1);
    }
}


void TabelaHuffman(No *AUX, Huffman tabela[], char codigoAtual[], int TamanhoAtual) {
    if (AUX == NULL) {
        return;
    }

    if (AUX->Esquerda == NULL && AUX->Direita == NULL) {
        // Encontramos uma folha (nó que representa um caractere)
        if (isalpha(AUX->data.Letra[0])) {
            int indice = AUX->data.Letra[0];
            tabela[indice].letra = AUX->data.Letra[0];
            codigoAtual[TamanhoAtual] = '\0';  // Adiciona o caractere nulo ao final do código
            strncpy(tabela[indice].codigo, codigoAtual, TamanhoAtual + 1);  // Ajusta o tamanho da cópia
            printf("Letra: %c, Código: %s\n", tabela[indice].letra, tabela[indice].codigo);
        }
    }

    // Percorre a subárvore esquerda com um bit 0
    codigoAtual[TamanhoAtual] = '0';
    TabelaHuffman(AUX->Esquerda, tabela, codigoAtual, TamanhoAtual + 1);

    // Percorre a subárvore direita com um bit 1
    codigoAtual[TamanhoAtual] = '1';
    TabelaHuffman(AUX->Direita, tabela, codigoAtual, TamanhoAtual + 1);
}





void ExibirTabelaHuffman(Huffman tabela[], int tamanho) {
    printf("Tabela Huffman:\n");
    for (int i = 0; i < tamanho; i++) {
        if (tabela[i].letra != '\0') {
            printf("Letra: %c, Código: %s\n", tabela[i].letra, tabela[i].codigo);
        }
    }
}


// int CompararTabelaHuffman(const void *a, const void *b) {
//     const Huffman *h1 = (const Huffman *)a;
//     const Huffman *h2 = (const Huffman *)b;

//     // Compare com base no comprimento do código
//     return strlen(h1->codigo) - strlen(h2->codigo);
// }

// // Função para ordenar a tabela de Huffman
// void OrdenarTabelaHuffman(Huffman tabela[], int tamanho) {
//     // Use qsort para ordenar com base na função de comparação
//     qsort(tabela, tamanho, sizeof(Huffman), CompararTabelaHuffman);
// }

