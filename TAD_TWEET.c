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
    idTweets* aux;
    for(aux = lista->ant ; aux != lista; aux = aux->ant)
        fprintf(*saida, "%d, ", aux->id);
    fprintf(*saida, "%d, ", aux->id);

}

idTweets* insereIDL(idTweets* lista, int id)
{
    idTweets* aux;
	idTweets *novo = (idTweets*) malloc(sizeof(idTweets));  //Inicia novo elemento da lista

    novo->id = id;

    //Inserção do item
	if(lista == NULL){
        novo->prox      = novo;
        novo->ant       = novo;
	}
	else{
        aux = lista->ant;

        //Atualização de ponteiros
        novo->prox      = lista;
        lista->ant      = novo;
        novo->ant       = aux;
        aux->prox       = novo;
	}

    return novo;
}

