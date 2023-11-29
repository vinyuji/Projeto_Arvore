#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arquivo.h"
#include "Lista.h"


void contarFrequencia(FILE *arquivo, Lista *list) {
    if (arquivo == NULL || list == NULL) {
        printf("Parâmetros inválidos.\n");
        return;
    }

    int frequencia[256] = {0};
    int c;
    char letra;
    char buffer[2];

    while ((c = fgetc(arquivo)) != EOF) {
        if (isalpha(c) || ispunct(c) || isspace(c)) {
            frequencia[c]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (frequencia[i] > 0) {
            if (isalpha(i)) {
                letra = i;
                buffer[0] = letra;
                buffer[1] = '\0';
                Frequencia novaFrequencia;
                novaFrequencia.Letra = strdup(buffer);
                novaFrequencia.Frequencia = frequencia[i];
                novaFrequencia.frequenciaLetra = 1;

                InserirInicioLista(list, novaFrequencia);
            } else {
                if (i >= 32 && i <= 126) {
                    Frequencia novaFrequencia;
                    novaFrequencia.Letra = strdup((char[]){i, '\0'});
                    novaFrequencia.Frequencia = frequencia[i];
                    novaFrequencia.frequenciaLetra = 1;
                    
                    InserirInicioLista(list, novaFrequencia);
                }
            }
        }
    }
}

void contarLetras(Lista *list) {
    FILE *arquivo;

    arquivo = fopen("ListaDePalavras.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    contarFrequencia(arquivo, list);
    fclose(arquivo);
}

void leituraArquivo() {
    FILE *arquivo;
    arquivo = fopen("ListaDePalavras.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    int linha = 1;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        printf("\tLinha %d: %s\n", linha, buffer);
        linha++;
    }

    fclose(arquivo);
}
