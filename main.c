#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

int main(){
    int op;

    do{
        printf("\n\n\t_________________________________________\n\t| 1 - Contar Letrar Individuais         |\n\t| 2 - Ler o arquivo linnha por linha    |\n\t| 0 - sair                              |\n\t|_______________________________________|\n");
        scanf("%d", &op);

        switch(op){
            case 0: 
                break;
            case 1: 
                printf("Leitura de arquivo ok\n\n");
                leituraArquivo();
                break;
            case 2: 
                printf("\n\n\tcontar as letras\n\n");
                contarLetras();
                break;
            default: 
                printf("digite uma opcao valida!!\n\n");
                break;
        }

    } while(op != 0);

    return 0;

}