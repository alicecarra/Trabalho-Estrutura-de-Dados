#ifndef TAD_AVL_H_INCLUDED
#define TAD_AVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TAD_TWEET.h"

typedef struct AVL_Nodo{
    char* palavra;
    idTweets* idl;
    struct AVL_Nodo* esq;
    struct AVL_Nodo* dir;
}avlNodo;

void initAVL(avlNodo**);
avlNodo* initNodoAVL(avlNodo* a, char* palavra);
void insereNodoAVL(avlNodo* a, char* palavra, int id);
int alturaNodoAVL(avlNodo *a);
int fatorNodoAVL(avlNodo *a);
//void impremeArvore(Nodo* a, int nivel);

#endif // TAD_AVL_H_INCLUDED
