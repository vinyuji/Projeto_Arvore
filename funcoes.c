#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
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
            // Caractere é imprimível, espaço ou pontuação
            int indice = caractere;
            // fprintf(arquivoSaida,"%s", tabela[indice].codigo);
            fputs(tabela[indice].codigo, arquivoSaida);
        } else {
            // Caractere não é imprimível, espaço ou pontuação
            // fprintf(arquivoSaida,"amem");
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
 
    // Encontrar o próximo múltiplo de 8
    int bitsFaltando = (8 - (bitContado % 8)) % 8;

    // Escrever o número de bits no arquivo comprimido
    fprintf(ARQUIVO1, "%d\n", bitContado);

    // Adicionar zeros até atingir o próximo múltiplo de 8
    for (int i = 0; i < bitsFaltando; i++) {
        fputc('0', ARQUIVOAUX);
    }


    fclose(ARQUIVOAUX);
    ARQUIVOAUX = fopen(arquivo, "r");

    // Voltar ao início do arquivo para ler os bits adicionados
    fseek(ARQUIVOAUX, 0, SEEK_SET);

    // Processar os bits de 8 em 8 e escrever os caracteres correspondentes
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

            printf("%c", bit);  // Exibindo os bits (0 ou 1)

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

    // Ler o número de bits do arquivo comprimido
    int bitContado;
    fscanf(ARQUIVO1, "%d", &bitContado);

    // Ignorar o caractere de nova linha
    fgetc(ARQUIVO1);

    // Escrever a quantidade original de bits no arquivo descomprimido
    fprintf(ARQUIVO_DESCOMP, "%d\n", bitContado);

    // Processar os bits de 8 em 8 e escrever os caracteres correspondentes no arquivo descomprimido
    while (bitContado > 0) {
        char byte = fgetc(ARQUIVO1);

        if (byte == EOF) {
            printf("Erro ao ler o arquivo comprimido.\n");
            fclose(ARQUIVO1);
            fclose(ARQUIVO_DESCOMP);
            return;
        }

        // Escrever os bits do byte no arquivo descomprimido
        for (int i = 7; i >= 0; i--) {
            int bit = (byte >> i) & 1;
            fprintf(ARQUIVO_DESCOMP, "%d", bit);
        }

        bitContado -= 8;
    }

    fclose(ARQUIVO1);
    fclose(ARQUIVO_DESCOMP);
}


void BitHuffman(const char *arquivo) {
    FILE *ARQUIVO = fopen(arquivo, "r");

    if (ARQUIVO == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Ler a quantidade total de bits originalmente
    int bitOriginal;
    if (fscanf(ARQUIVO, "%d", &bitOriginal) != 1) {
        printf("Erro ao ler a quantidade original de bits.\n");
        fclose(ARQUIVO);
        return;
    }

    // Ignorar o caractere de nova linha
    fgetc(ARQUIVO);

    // Ler as linhas restantes e contar a quantidade total de bits
    int bitTotal = 0;
    int bitAtual;
    while (fscanf(ARQUIVO, "%d", &bitAtual) == 1) {
        // Somar a quantidade de bits na linha atual
        bitTotal += bitAtual;

        // Ignorar o caractere de nova linha
        fgetc(ARQUIVO);
    }

    fclose(ARQUIVO);

    // Calcular a diferença
    int diferenca = bitTotal - bitOriginal;

    if (diferenca > 0) {
        // Reabrir o arquivo para remoção dos bits do final
        ARQUIVO = fopen(arquivo, "r+");
        if (ARQUIVO == NULL) {
            printf("Erro ao reabrir o arquivo para remoção de bits.\n");
            return;
        }

        // Posicionar o cursor para o início do último byte
        fseek(ARQUIVO, -1, SEEK_END);

        // Ler o último byte
        int ultimoByte;
        fread(&ultimoByte, 1, 1, ARQUIVO);

        // Zerar os bits extras no último byte
        ultimoByte &= ~(0xFF >> (8 - diferenca));

        // Posicionar o cursor para o início do último byte novamente
        fseek(ARQUIVO, -1, SEEK_END);

        // Escrever o último byte modificado
        fwrite(&ultimoByte, 1, 1, ARQUIVO);

        // Truncar o arquivo para remover os bits excedentes
        fflush(ARQUIVO);
        ftruncate(fileno(ARQUIVO), ftell(ARQUIVO));

        fclose(ARQUIVO);
    }
}




void LiberarMemoriaHuffman(Huffman tabela[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(tabela[i].codigo);
    }
}