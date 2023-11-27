#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "Lista.h"
#include "arvore.h"
#include "funcoes.h"

int main(){
    Lista list;
    Init(&list);
    Huffman tabela[256]; 
    char codigoAtual[256] = "";  
    int op;

    do{
        printf("\n\n\t____________________________________________________\n\t| 1 - Ler o arquivo linnha por linha               |\n\t| 2 - Contar letras do arquivo e por em uma lista  |\n\t| 3 - Show Lista                                   |\n\t| 4 - Ordenar                                      |\n\t| 5 - inserir de forma ordenada                    |\n\t| 6 - remover da lista e por na arvore             |\n\t| 7 - show Arvore                                  |\n\t| 8 - Huffman                                      |\n\t| 0 - sair                                         |\n\t|__________________________________________________|\n");
        scanf("%d", &op);

        switch(op){
            case 0: 
                break;
            case 1: 
                printf("Leitura de arquivo ok\n\n");
                leituraArquivo();
                break;
            case 2: 
                contarLetras(&list);
                printf("\n\tLetras contadas e inseridas na lista");
                break;
            case 3: 
                ShowLista(&list);
                printf("Lista ordenada crescente");
                break;
            case 4: 
                MergeSort(&list.inicio);
                break;
            case 5:
                Frequencia Letra = {"AB", 4};
                InserirCrescente(&list, Letra); 
                break;
            case 6:
                    NoArvoreNoLista(&list);
                break;
            case 7: 
                AuxiliarShowArvore(&list);
                break;
            case 8: 
                TabelaHuffman(list.inicio, tabela, codigoAtual, 0);
                break;
            default: 
                EsvaziarLista(&list);
                LiberarArvore(&list);
                printf("digite uma opcao valida!!\n\n");
                break;
        }

    } while(op != 0);

    return 0;

}