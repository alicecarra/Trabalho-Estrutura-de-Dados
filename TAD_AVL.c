#include "TAD_AVL.h"

void initAVL(avlNodo **a)
{
    *a = NULL;
}

avlNodo* initNodoAVL(char* palavra, int id)
{
    avlNodo *nodo   = (avlNodo*)    malloc(sizeof(avlNodo));
    nodo->idl       = NULL;
    nodo->esq       = NULL;
    nodo->dir       = NULL;
    nodo->palavra   = strdup(palavra);
    nodo->altura    = 1;

    nodo->idl = insereIDL(nodo->idl, id);
    nodosCriadosAVL += 1;

    return nodo;
}

void buscaNodoAVL(avlNodo *a, char* palavra)
{
    if(a == NULL)
            printf("\n%s - Palavra não encontrada", palavra);
    else{
       if (strcmp(a->palavra, palavra) > 0)
        buscaNodoAVL(a->esq, palavra);
        else if (strcmp(a->palavra, palavra) < 0)
        buscaNodoAVL(a->dir, palavra);

        else{
            printf("\n%s -  ", palavra);
            imprimeIDL(a->idl);
        }
    }

}

int alturaNodoAVL(avlNodo *a)
{
    if (a == NULL)
        return 0;
    else
        return a->altura;
}

int fatorNodoAVL(avlNodo *a)
{
    if (a == NULL)
        return 0;
    return (alturaNodoAVL(a->esq) - alturaNodoAVL(a->dir));
}

avlNodo* insereNodoAVL(avlNodo* nodo, char* palavra, int id)
{
    // Caso a árvore não estiver populada, insere na raiz
    if (nodo == NULL)
        return(initNodoAVL(palavra, id));

    // strcmp(,) retorna valor negativo caso a ordem lexicográfica do primeiro parametro
    //   for menor do que o do segundo. Assim podemos ordenar a árvore em ordem alfabética

    if (strcmp(nodo->palavra, palavra) > 0)
        nodo->esq  = insereNodoAVL(nodo->esq, palavra, id);

    else if (strcmp(nodo->palavra, palavra) < 0)
        nodo->dir  = insereNodoAVL(nodo->dir, palavra, id);

    else{ // Mesma palavra, acrescenta na lista de IDs caso tenha um id diferente
        if(nodo->idl->id != id)
            nodo->idl = insereIDL(nodo->idl, id);
        return nodo;
    }


    //Agora é necessário atualizar a altura e calcular o fator de balanceamento
    nodo->altura = 1 + (funcMax(alturaNodoAVL(nodo->esq), alturaNodoAVL(nodo->dir)));
    int fatorBalanceamento = fatorNodoAVL(nodo);


    // Se o nodo estiver desbalanceado, então são 4 casos

    // Rotação à direita
    if (fatorBalanceamento > 1 && fatorNodoAVL(nodo->esq) > 0)
        return rotDirAVL(nodo);


    // Rotação à esquerda
    if (fatorBalanceamento < -1 && fatorNodoAVL(nodo->dir) < 0)
        return rotEsqAVL(nodo);

    // Rotação dupla à esquerda
    if (fatorBalanceamento < -1 && fatorNodoAVL(nodo->dir) > 0)
    {
        nodo->dir = rotDirAVL(nodo->dir);
        return rotEsqAVL(nodo);
    }

    // Rotação dupla à direita
    if (fatorBalanceamento > 1 && fatorNodoAVL(nodo->esq) < 0)
    {
        nodo->esq =  rotEsqAVL(nodo->esq);
        return rotDirAVL(nodo);
    }

    // se o fator estiver entre -1 e 1, a árvore está balanceada
    return nodo;
}

void imprimeAVL(avlNodo* a, int nivel)
{
    int i;

    if (a != NULL)
    {
        for (i= 0; i<nivel; i++)
            printf("=");
        printf("%s\n", a->palavra);

        imprimeAVL(a->esq, nivel+1);
        imprimeAVL(a->dir, nivel+1);
    }/*
    else{
        for (i= 0; i<nivel; i++)
            printf("=");
        printf("[]\n");
    }*/
}

//  ================= FUNÇÕES DE ROTAÇÃO =================  //

avlNodo* rotDirAVL(avlNodo *nodo)
{
/*      nodo      u         ;ROTAÇÃO À DIREITA
        / \  ->  / \
       u  t2    t1 nodo     ;Nodos envolvidos: nodo, u e v
      / \          /  \     ;  os outros permanecem iguais
     t1  v        v    t2                                  */


    avlNodo *u = nodo->esq;
    avlNodo *v = u->dir;

    u->dir      = nodo;
    nodo->esq   = v;

    //Atualização das alturas do nodo original e u
    nodo->altura = funcMax(alturaNodoAVL(nodo->esq), alturaNodoAVL(nodo->dir))   +1;
    u->altura    = funcMax(alturaNodoAVL(u->esq)   , alturaNodoAVL(u->dir))      +1;

    nRotAVL += 1;

    return u;
}

avlNodo* rotEsqAVL(avlNodo *nodo)
{
/*  nodo          u         ;ROTAÇÃO À ESQUERDA
    / \   ->     / \
   t1  u       nodo t2      ;Nodos envolvidos: nodo, u e v
      / \      /  \         ;  os outros permanecem iguais
     v  t1    t1  v                                      */
    avlNodo *u = nodo->dir;
    avlNodo *v = u->esq;

    u->esq      = nodo;
    nodo->dir   = v;

    //Atualização das alturas do nodo original e u
    nodo->altura = funcMax(alturaNodoAVL(nodo->esq), alturaNodoAVL(nodo->dir))   +1;
    u->altura    = funcMax(alturaNodoAVL(u->esq)   , alturaNodoAVL(u->dir))      +1;

    nRotAVL += 1;

    return u;
}


