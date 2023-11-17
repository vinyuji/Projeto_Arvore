#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void contarFrequencia(FILE *arquivo) {
    if (arquivo == NULL) {
        printf("Arquivo inválido.\n");
        return;
    }

    int frequencia[256] = {0};
    int c;

    while ((c = fgetc(arquivo)) != EOF) {
        if (isalpha(c) || ispunct(c) || isspace(c)) {  
            frequencia[c]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (frequencia[i] > 0) {
            if (isalpha(i)) {
                printf("%c: %d\n", i, frequencia[i]);
            } else {
                if(i >= 32 && i <= 126 )
                printf("'%c' (%d): %d\n", i, i, frequencia[i]);
            }
        }
    }
}

void contarLetras() {
    FILE *arquivo;
    arquivo = fopen("ListaDePalavras.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    contarFrequencia(arquivo);

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
        printf("Linha %d: %s", linha, buffer);
        linha++;
    }

    fclose(arquivo);
}
