#ifndef TAD_AVL_H_INCLUDED
#define TAD_AVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TAD_TWEET.h"

typedef struct AVL_Nodo{
    char*               palavra;
    idTweets*           idl;
    struct AVL_Nodo*    esq;
    struct AVL_Nodo*    dir;
    int                 altura;
}avlNodo;

int         nodosCriadosAVL;
int         nRotAVL;

void        initAVL(avlNodo**);
avlNodo*    initNodoAVL(char* palavra, int id);
void        buscaNodoAVL(avlNodo *a, char* palavra, FILE **saida);
avlNodo*    insereNodoAVL(avlNodo* a, char* palavra, int id);
int         alturaNodoAVL(avlNodo *a);
int         fatorNodoAVL(avlNodo *a);
void        imprimeAVL(avlNodo* a, int nivel);
avlNodo*    rotDirAVL(avlNodo *nodo);
avlNodo*    rotEsqAVL(avlNodo *nodo);

//void impremeArvore(Nodo* a, int nivel);

#endif // TAD_AVL_H_INCLUDED
