#ifndef RUBRONEGRAS_H_INCLUDED
#define RUBRONEGRAS_H_INCLUDED
#include "TAD_TWEET.h"

int rbSearchComp;

typedef struct _rbNode//Struct dos nós da rubro-negra
{
    char* word;
    idTweets* ids;
    char color;
    struct _rbNode* a;
    struct _rbNode* r;
    struct _rbNode* l;
} rbNode;

typedef struct _rbt//Struct da árvore rubro-negra
{
    rbNode* root;//Raiz da árvore
    int nodes;//Número de nós da árvore
    int rotations;//Rotações realizadas na árvore
    int comps;//Comparações realizadas na árvore
} rbt;


rbt* rbInitialize();//Inicializa a rubro-negra

void rbInserir(rbt* tree, char *word, int tweetId);//Insere un nodo na rubro-negra
void rbPreEsq(rbt* tree);//Imprime a rubro-negra com caminhamento pré-fixado a esquerda
rbNode* rbFind(rbt* tree, char *word, int* comps);//Retorna o nó que contem a palavra na rubro-negra
int rbHeight(rbt* tree);//Retorna a altura da rubro-negra
void rbPrintIds(rbt* tree, char *word, int *comps, FILE **saida);//Imprime os ids dos tweets que contêm a palabra buscada


#endif // RUBRONEGRAS_H_INCLUDED
