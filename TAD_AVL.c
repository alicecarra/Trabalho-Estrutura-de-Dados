#include "TAD_AVL.h"

void initAVL(avlNodo **a)
{
    *a = NULL;
}

avlNodo* initNodoAVL(avlNodo* a, char* palavra)
{
    avlNodo *nodo = (avlNodo*) malloc(sizeof(avlNodo));
    nodo->esq = NULL;
    nodo->dir = NULL;
    nodo->palavra = strdup(palavra);
    nodo->idl = NULL;

    return nodo;
}

int alturaNodoAVL(avlNodo *a)
{
    int altEsq, altDir;
    if (a == NULL)
        return 0;
    else
    {
        altEsq = alturaNodoAVL(a->esq);
        altDir = alturaNodoAVL(a->dir);
        if (altEsq > altDir)
            return (1 + altEsq);
        else
            return (1 + altDir);
    }
}

int fatorNodoAVL(avlNodo *a)
{
    return (alturaNodoAVL(a->esq) - alturaNodoAVL(a->dir));
}

avlNodo* insereNodoAVL(avlNodo* a, char* palavra, int id)
{
    avlNodo *novoNodo;
    novoNodo = (avlNodo*) malloc(sizeof(avlNodo));

    // Se a raiz da �rvore for nula, quer dizer que est� vazia, logo o nodo inserido ser� a raiz
    if (a == NULL)
    {
        novoNodo->dir = NULL;
        novoNodo->esq = NULL;
        return novoNodo;
    }
    // Caso contrario ser� percorrida a �rvore at� que seja encontrado o lugar correto para inserir o valor
    // utilizando recursividade, a fun��o ir� ter reentrancia em suas subarvores com a t�cnica vista em aula
    // at� que seja encontrado um nodo onde seja poss�vel adiciona-l�
    else
    {
        if(dado < a->valor)
            a->esq = insereNodo(a->esq, dado);
        else
            a->dir = insereNodo(a->dir, dado);
        return a;
    }
}
