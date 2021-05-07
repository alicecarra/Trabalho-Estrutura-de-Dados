#ifndef RUBRONEGRAS_H_INCLUDED
#define RUBRONEGRAS_H_INCLUDED
#include "TAD_TWEET.h"

int rbSearchComp;

typedef struct _rbNode//Struct dos n�s da rubro-negra
{
    char* word;
    idTweets* ids;
    char color;
    struct _rbNode* a;
    struct _rbNode* r;
    struct _rbNode* l;
} rbNode;

typedef struct _rbt//Struct da �rvore rubro-negra
{
    rbNode* root;//Raiz da �rvore
    int nodes;//N�mero de n�s da �rvore
    int rotations;//Rota��es realizadas na �rvore
    int comps;//Compara��es realizadas na �rvore
} rbt;


rbt* rbInitialize();//Inicializa a rubro-negra

void rbInserir(rbt* tree, char *word, int tweetId);//Insere un nodo na rubro-negra
void rbPreEsq(rbt* tree);//Imprime a rubro-negra com caminhamento pr�-fixado a esquerda
rbNode* rbFind(rbt* tree, char *word, int* comps);//Retorna o n� que contem a palavra na rubro-negra
int rbHeight(rbt* tree);//Retorna a altura da rubro-negra
void rbPrintIds(rbt* tree, char *word, int *comps, FILE **saida);//Imprime os ids dos tweets que cont�m a palabra buscada


#endif // RUBRONEGRAS_H_INCLUDED
