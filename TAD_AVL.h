#ifndef TAD_AVL_H_INCLUDED
#define TAD_AVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TAD_TWEET.h"

// Struct dos nodos da AVL
typedef struct AVL_Nodo{
    char*               palavra;
    idTweets*           idl;
    struct AVL_Nodo*    esq;
    struct AVL_Nodo*    dir;
    int                 altura;
}avlNodo;

// Contadores para estatisticas
int         nodosCriadosAVL;
int         nRotAVL;
int         comparacoesAVL;
int         compara;
int         comparacoesBuscaAVL;


void        initAVL(avlNodo**);                                     //Inicia a AVL
avlNodo*    initNodoAVL(char* palavra, int id);                     //Aloca um novo nodo
void        buscaNodoAVL(avlNodo *a, char* palavra, FILE **saida);  //Busca por um nodo
avlNodo*    insereNodoAVL(avlNodo* a, char* palavra, int id);       //Insere um novo nodo
int         alturaNodoAVL(avlNodo *a);                              //Calcula a altura do nodo
int         fatorNodoAVL(avlNodo *a);                               //Calcula o fator do nodo
void        imprimeAVL(avlNodo* a, int nivel);                      //Imprime a  árvore
avlNodo*    rotDirAVL(avlNodo *nodo);                               //Rotação DIREITA
avlNodo*    rotEsqAVL(avlNodo *nodo);                               //Rotação ESQUERDA

#endif // TAD_AVL_H_INCLUDED
