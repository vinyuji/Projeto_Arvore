#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "Lista.h"
#include "funcoes.h"

int main(){
    Lista list;
    Lista Codigo;
    Init(&list);
    Huffman tabela[256]; 
    char codigoAtual[256] = "";
    int op;

    do{
        printf("\n\n\t____________________________________________________\n\t| 1 - Ler o arquivo linnha por linha               |\n\t| 2 - Contar letras do arquivo e por em uma lista  |\n\t| 3 - Show Lista                                   |\n\t| 4 - remover da lista e por na arvore             |\n\t| 5 - show Arvore                                  |\n\t| 6 - Huffman                                      |\n\t| 7 - Por tabela no arquivo                        |\n\t| 0 - sair                                         |\n\t|__________________________________________________|\n");
        scanf("%d", &op);

        switch(op){
            case 0: 
                break;
            case 1: 
                printf("\tLeitura de arquivo ok\n\n");
                leituraArquivo();
                printf("\tLeitura do arquivo feito\n\n");
                break;
            case 2: 
                contarLetras(&list);
                printf("\tLetras contadas e inseridas na lista com sucesso\n");
                break;
            case 3: 
                printf("\n\tShow Lista\n\n");
                ShowLista(&list);
                break;
            case 4: 
                MergeSort(&list.inicio);
                printf("%d", list.tam);
                    while(list.tam > 1)
                NoArvoreNoLista(&list);
                printf("\n\tarvore criada com sucesso\n");
                break;
            case 5: 
                printf("\n\t\tArvore\n\n");
                AuxiliarShowArvore(&list);
                break;
            case 6: 
                printf("\t_____________________________\n");
                printf("\t| Letra | codigo de Huffman |\n");
                printf("\t|_______|___________________|\n");
                TabelaHuffman(list.inicio, tabela, codigoAtual, 0);
                printf("\t|_______|___________________|\n");
                break;
            case 7: 
                ShowNoArquivo(tabela, 256, "tabela_huffman.txt");
                ComprimirNoArquivo(tabela, 256, "Codificado.txt");
                break;
            default: 
                EsvaziarLista(&list);
                LiberarArvore(&list);
                LiberarMemoriaHuffman(tabela, 256);
                printf("digite uma opcao valida!!\n\n");
                break;
        }

    } while(op != 0);

    return 0;
}