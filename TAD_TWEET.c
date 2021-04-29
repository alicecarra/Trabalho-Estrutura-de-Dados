#include "TAD_TWEET.h"

void stringToLower(char *s)
{
    int i;
    for (i=0; i<strlen(s); i++)
        s[i]=tolower(s[i]);
}

int funcMax(int x, int y)
{
    return (x > y)? x : y;
}

void initIDL(idTweets **id)
{
    *id = NULL;
}

void imprimeIDL(idTweets* lista, FILE **saida)
{
    //idTweets* ptAux;
	if(lista != NULL){
        imprimeIDL(lista->prox, saida);
        fprintf(*saida, "%d, ", lista->id);
	}
}

idTweets* insereIDL(idTweets* lista, int id)
{
	idTweets *novo = (idTweets*) malloc(sizeof(idTweets));

	novo->id = id;
	novo->prox = lista;

    return novo;
}
