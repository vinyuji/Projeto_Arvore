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
            

        EsvaziarLista(&list);
        LiberarArvore(&list);
    return 0;
}

