#ifndef TAD_TWEET_H_INCLUDED
#define TAD_TWEET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LISTA_Tweets{
    int id;
    struct LISTA_Tweets* prox;
}idTweets;

void stringToLower(char *s);

/* ==== FUNÇÕES PARA TRATAMENTO DA LISTA DE IDs === */
void initIDL(idTweets**);
void imprimeIDL(idTweets*);
void insereIDL(idTweets**, int);


#endif // TAD_TWEET_H_INCLUDED
