
# Trabalho Árvore

Alunos : VINYCIUS YUJI MOGAMI & ANTHONY GABRIEL OLIVEIRA CRUZ 


#### Código

 - [Repositório](https://github.com/vinyuji/Projeto_Arvore)


## MAIN.C

```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "Lista.h"
#include "funcoes.h"

int main(){

    Lista list;
    Init(&list);
    Huffman *tabela = malloc(256 * sizeof(Huffman));
    char codigoAtual[256] = "";


                contarLetras(&list);
                printf("\n\n\n\tShow Lista\n\n");
                ShowLista(&list);


                MergeSort(&list.inicio);
                while(list.tam > 1)
                NoArvoreNoLista(&list);
                printf("\n\tArvore criada com sucesso");

                printf("\n\n\n\tShow Lista\n\n");
                ShowLista(&list);


                printf("\n\t\tArvore: \n\n");
                AuxiliarShowArvore(&list);


                printf("\n\n\ttabela de huffman criada\n");
                printf("\n\t_____________________________\n");
                printf("\t| Letra | codigo de Huffman |\n");
                printf("\t|_______|___________________|\n");
                TabelaHuffman(list.inicio, tabela, codigoAtual, 0);
                printf("\t|_______|___________________|\n");


                printf("\n\n\tA quantidade de bit na ListaDePalavra.txt: %d\n", list.inicio->data.Frequencia * 8);
                SubstituirPorHuffman("ListaDePalavras.txt", tabela);
                int contar = contarBit();
                printf("\tA quantidade de caracteres no arquivo é: %d\n", contar);
                printf("\tA quantidade de Bit reduzidos: %d\n", (list.inicio->data.Frequencia * 8) - contar);
                printf("\tA quantidade de bit do arquico comprimido em relacao a Lista de palavras em porcentagem: %d \n\n", (contar*100)/(list.inicio->data.Frequencia * 8));

                comprimirArquivo("Comprimido.txt");
                descomprimirArquivo("Descomprimido.txt");
                imprimirASCII();
                BitHuffman("Descomprimido.txt");
                removerPrimeiraLinha("Descomprimido.txt");
                descomprimirFinal("Descomprimido.txt", tabela);
                ShowNoArquivo(tabela, 256 , "tabela_huffman.txt" );
            

        EsvaziarLista(&list);
        LiberarArvore(&list);
    return 0;
}



```
 Realiza a compressão de arquivos de texto utilizando o algoritmo de Huffman. O código inicia uma lista, ordena-a para criar uma árvore Huffman e gera uma tabela associando letras aos seus respectivos códigos Huffman. Após contar a frequência de letras no arquivo original, o programa substitui cada letra pelo seu código Huffman, realiza a compressão e descompressão de arquivos e exibe estatísticas relacionadas à quantidade de bits. O código é concluído liberando a memória alocada dinamicamente. Essa implementação oferece uma solução completa para a compressão de dados.


## FUNÇÕES
Para as funções do código: 
``` 
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

```
Contém a declaração de várias funções utilizadas no processo de compressão e descompressão de arquivos. Essas funções incluem o algoritmo de ordenação MergeSort para organizar uma lista de letras e suas frequências, manipulação de listas para a criação da árvore Huffman, concatenação de letras, exibição da tabela Huffman em um arquivo, substituição de palavras por seus códigos Huffman, compressão e descompressão de arquivos, manipulação de bits, e leitura de arquivos. Cada função desempenha um papel específico, como ordenação, manipulação de dados, geração de arquivos comprimidos e descomprimidos, entre outros. Essas operações são essenciais para a implementação bem-sucedida do algoritmo de compressão de Huffman.


# FUNÇÕES.C

``` 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "Lista.h"
#include "arquivo.h"


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

void ShowNoArquivo(Huffman tabela[], int tamanho, const char *ARQUI){
    FILE *arquivo = fopen(ARQUI, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "\tTabela Huffman:\n");
    fprintf(arquivo,"\t_____________________________\n");
    fprintf(arquivo,"\t| Letra | codigo de Huffman |\n");
    fprintf(arquivo,"\t|_______|___________________|\n");

    for (int i = 0; i < tamanho; i++) {
        if (isprint(tabela[i].letra) || isspace(tabela[i].letra) || ispunct(tabela[i].letra)) {
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

void SubstituirPorHuffman(char *ARQUI, Huffman tabela[]) {
    FILE *arquivoEntrada = fopen(ARQUI, "r");
    FILE *arquivoSaida = fopen("Comprimido.txt", "w");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int caractere;
    while ((caractere = fgetc(arquivoEntrada)) != EOF) {
        if (isprint(caractere) || isspace(caractere) || ispunct(caractere)) {
            int indice = caractere;
            fputs(tabela[indice].codigo, arquivoSaida);
        } else {
            fputc(caractere, arquivoSaida);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);
}

void comprimirArquivo(char *arquivo) {
    FILE *ARQUIVOAUX = fopen(arquivo, "a");  // Abre o arquivo para leitura
    FILE *ARQUIVO1 = fopen("Comprimido_Final.txt", "w");  // Cria ou recria o arquivo

    if (ARQUIVO1 == NULL || ARQUIVOAUX == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int bitContado = contarBit();
    int aux = bitContado;
 
    int bitsFaltando = (8 - (bitContado % 8)) % 8;

    fprintf(ARQUIVO1, "%d\n", bitContado);

    for (int i = 0; i < bitsFaltando; i++) {
        fputc('0', ARQUIVOAUX);
    }


    fclose(ARQUIVOAUX);
    ARQUIVOAUX = fopen(arquivo, "r");

    fseek(ARQUIVOAUX, 0, SEEK_SET);

    while (aux > 0) {
        char byte = 0;

        for (int i = 0; i < 8; i++) {
            int bit = fgetc(ARQUIVOAUX);

            if (bit == EOF) {
                printf("Erro ao ler o arquivo.\n");
                fclose(ARQUIVO1);
                fclose(ARQUIVOAUX);
                return;
            }

            if (bit == '1') {
                byte |= (1 << (7 - i));
            }
        }

        printf(" ");
        fputc(byte, ARQUIVO1);
        aux -= 8;
    }

    printf("\n");
    fclose(ARQUIVO1);
    fclose(ARQUIVOAUX);
}

void imprimirASCII() {
    FILE *ARQUIVO = fopen("TabelaAsciiConhecida.txt", "w");

    for (int i = 0; i < 256; i++) {
        fprintf(ARQUIVO, "posicao: %d letra: %c\n", i, (char)i);
    }
}

void descomprimirArquivo(char *arquivo) {
    FILE *ARQUIVO1 = fopen("Comprimido_Final.txt", "r");  // Abre o arquivo comprimido para leitura
    FILE *ARQUIVO_DESCOMP = fopen(arquivo, "w");  // Cria ou recria o arquivo descomprimido

    if (ARQUIVO1 == NULL || ARQUIVO_DESCOMP == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int bitContado;
    fscanf(ARQUIVO1, "%d", &bitContado);

    fgetc(ARQUIVO1);

    fprintf(ARQUIVO_DESCOMP, "%d\n", bitContado);

    while (bitContado > 0) {
        char byte = fgetc(ARQUIVO1);

        if (byte == EOF) {
            printf("Erro ao ler o arquivo comprimido.\n");
            fclose(ARQUIVO1);
            fclose(ARQUIVO_DESCOMP);
            return;
        }

        for (int i = 7; i >= 0; i--) {
            int bit = (byte >> i) & 1;
            fprintf(ARQUIVO_DESCOMP, "%d", bit);
        }

        bitContado -= 8;
    }

    fclose(ARQUIVO1);
    fclose(ARQUIVO_DESCOMP);
}


void removerUltimoCaractere(const char *nomeArquivo, int diferenca) {
    FILE *arquivo = fopen(nomeArquivo, "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < diferenca; i++) {
        if (fseek(arquivo, -1, SEEK_END) != 0) {
            printf("Erro ao posicionar o cursor no final do arquivo.\n");
            fclose(arquivo);
            return;
        }

        fflush(arquivo);
        ftruncate(fileno(arquivo), ftell(arquivo));
    }

    fclose(arquivo);

}

void removerPrimeiraLinha(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "r");
    if (arquivoOriginal == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *arquivoTemporario = fopen("temporario.txt", "w");
    if (arquivoTemporario == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivoOriginal);
        return;
    }

    int caractere;
    while ((caractere = fgetc(arquivoOriginal)) != EOF && caractere != '\n') {
    }

    while ((caractere = fgetc(arquivoOriginal)) != EOF) {
        fputc(caractere, arquivoTemporario);
    }

    // Fechar os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    if (rename("temporario.txt", nomeArquivo) != 0) {
        printf("Erro ao substituir o arquivo original pelo temporário.\n");
    }
}

void BitHuffman(const char *arquivo) {
    FILE *ARQUIVO = fopen(arquivo, "r");

    if (ARQUIVO == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int bitOriginal;
    if (fscanf(ARQUIVO, "%d", &bitOriginal) != 1) {
        printf("Erro ao ler a quantidade original de bits.\n");
        fclose(ARQUIVO);
        return;
    }

    fgetc(ARQUIVO);

    int bitTotal = 0;
    int c;
    while ((c = fgetc(ARQUIVO)) != EOF) {
            bitTotal++;
    }


    fclose(ARQUIVO);

    int diferenca = bitTotal - bitOriginal;
    
        removerUltimoCaractere("Descomprimido.txt", diferenca);
}

void descomprimirFinal(const char *arquivoParcialDescomprimido, Huffman *tabelaHuffman) {
    FILE *arquivoParcial = fopen(arquivoParcialDescomprimido, "r");

    if (arquivoParcial == NULL) {
        printf("Erro ao abrir o arquivo parcialmente descomprimido para leitura.\n");
        return;
    }

    FILE *arquivoDescomprimidoFinal = fopen("arquivo_descomprimido.txt", "w");

    if (arquivoDescomprimidoFinal == NULL) {
        printf("Erro ao abrir o arquivo descomprimido final para escrita.\n");
        fclose(arquivoParcial);
        return;
    }

    Huffman *ponteiroTabela = tabelaHuffman;
    int bitsLidos = 0;
    char buffer[256];
    int bufferIndex = 0;
    int bitLido;
    
    while ((bitLido = fgetc(arquivoParcial)) != EOF) {
        if (bitLido == '0' || bitLido == '1') {
           
            buffer[bufferIndex++] = bitLido;

            for (int i = 0; i < 256; i++) {
                int codigoLengthAtual = strlen(ponteiroTabela[i].codigo);

                if (strncmp(buffer, ponteiroTabela[i].codigo, bufferIndex) == 0) {
                    fprintf(arquivoDescomprimidoFinal, "%c", ponteiroTabela[i].letra);

                    bitsLidos += bufferIndex;

                    bufferIndex = 0;

                    break;
                }
            }
        }
    }

    fclose(arquivoParcial);
    fclose(arquivoDescomprimidoFinal);
}

void LiberarMemoriaHuffman(Huffman tabela[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(tabela[i].codigo);
    }
}


``` 
O arquivo funcoes.c consiste em diversas funções que desempenham papéis fundamentais no programa de compressão e descompressão de arquivos usando o algoritmo de Huffman. Aqui está um resumo das principais funções contidas no arquivo:

    A função DividirLista é uma auxiliar para dividir uma lista encadeada em duas partes, utilizada no algoritmo Merge Sort para listas encadeadas.
    A função Merge mescla duas listas encadeadas ordenadas com base nas frequências e letras, sendo usada no algoritmo Merge Sort.

    1-MergeSort é a função principal do algoritmo de ordenação Merge Sort aplicado em listas encadeadas.

    2- A função ConcatenarLetras concatena duas palavras em uma nova string.

    3- ShowNoArquivo gera e exibe uma tabela Huffman em um arquivo contendo letras, códigos de Huffman e frequências.

    4- SubstituirPorHuffman substitui caracteres em um arquivo pelos códigos Huffman correspondentes.

    5-comprimirArquivo comprime um arquivo, adicionando zeros para atingir um múltiplo de 8 e agrupando os bits em bytes.

    6-imprimirASCII gera uma tabela ASCII conhecida em um arquivo.

    7- descomprimirArquivo descomprime um arquivo, lendo os bits e escrevendo os caracteres correspondentes.

    8- removerUltimoCaractere remove o último caractere de um arquivo.

    9- removerPrimeiraLinha remove a primeira linha de um arquivo.

    10- A função BitHuffman executa operações relacionadas à contagem e remoção de bits em um arquivo.

    11- descomprimirFinal descomprime um arquivo parcialmente descomprimido usando a tabela de Huffman.

    12- LiberarMemoriaHuffman libera a memória alocada dinamicamente para os códigos de Huffman.

    13- Essas funções formam a base do algoritmo de Huffman, desempenhando tarefas essenciais para a compressão e descompressão de dados.

Os arquivos gerados ao startar o codigo

    Para o arquivo original onde sera comprimido e ou jogado para a tabela de huffman

        ListaDePalavras.txt

    Para os arquivos gerados ao startar o codigo

        arquivo_descomprimido.txt
        Comprimido_Final.txt
        Comprimido.txt
        Descomprimido.txt
        tabela_huffman.txt