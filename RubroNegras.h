#ifndef RUBRONEGRAS_H_INCLUDED
#define RUBRONEGRAS_H_INCLUDED
#include "TAD_TWEET.h"

int rbSearchComp;

typedef struct _rbNode//Struct dos nós da rubro-negra
{
    char* word;//Palavra que o nó representa
    idTweets* ids;//IDs dos tweets que contém a palavra
    char color;//Cor do nó
    struct _rbNode* a;//Ancestral do nó
    struct _rbNode* r;//Filho direito do nó
    struct _rbNode* l;//Filho esquerdo do nó
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
rbNode* rbFind(rbt* tree, char *word);//Retorna o nó que contem a palavra na rubro-negra
int rbHeight(rbt* tree);//Retorna a altura da rubro-negra
void rbPrintIds(rbt* tree, char *word, FILE **saida);//Imprime os ids dos tweets que contêm a palabra buscada


#endif // RUBRONEGRAS_H_INCLUDED
