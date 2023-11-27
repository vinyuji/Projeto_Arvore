#ifndef LISTA_H
#define LISTA_H

typedef struct {
    char *Letra;
    int Frequencia;
    int frequenciaLetra;
} Frequencia;

typedef struct No {
    int valor;
    Frequencia data;
    struct No *proximo;
    struct No *Esquerda;
    struct No *Direita;
} No;

typedef struct Huffman {
    char letra;
    char codigo[256];
} Huffman;

typedef struct {
    No *inicio;
    int tam;
} Lista;

void Init(Lista *list);
void InserirInicioLista(Lista *list, Frequencia data);
void InserirCrescente(Lista *list, Frequencia data);
void RemoverInicioLista(Lista *list);
void ShowLista(Lista *list);
void EsvaziarLista(Lista *list);
void InserirNoArvoreLista(Lista *list, No *NovoNo3);
No *NoArvoreNoLista(Lista *list);
void LiberarNo(No *no);
void LiberarArvore(Lista *list);
void LiberarMemoriaRecursiva(No *raiz);
No *CriarArvoreNo(No *Esq, No *Dir, int Val, Frequencia Letras);
void ShowArvore(No *AUX);
void AuxiliarShowArvore(Lista *list);
void ShowArvoreVisual(No *AUX, int nivel);
void ExibirTabelaHuffman(Huffman tabela[], int tamanho);
void TabelaHuffman(No *AUX, Huffman tabela[], char codigoAtual[], int TamanhoAtual);

#endif /* LISTA_H */
