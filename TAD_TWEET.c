#include "TAD_TWEET.h"

void stringToLower(char *s)
{
    int i;
    for (i=0; i<strlen(s); i++)
        s[i]=tolower(s[i]);
}

void initIDL(idTweets **id)
{
    *id = NULL;
}

void imprimeIDL(idTweets* lista)
{
idTweets* ptAux;
	if(lista == NULL) // Checa se a lista está vazia
		puts("Lista IDs vazia.");
	else{
        printf("IDs: ");
		for(ptAux=lista; ptAux!=NULL; ptAux=ptAux->prox){
			printf("%d  ", ptAux->id);
		}
	}
}

void insereIDL(idTweets** lista, int id)
{
	idTweets *pA, *novo;
	novo = malloc(sizeof(idTweets));

	novo->id = id;
	novo->prox = NULL;

	if(*lista == NULL){
        *lista = novo;

        return;
	}

    for(pA=*lista; pA->prox != NULL; pA=pA->prox);
    pA->prox = novo;
}
