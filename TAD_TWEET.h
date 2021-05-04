#ifndef TAD_TWEET_H_INCLUDED
#define TAD_TWEET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LISTA_Tweets{
    int id;
    struct LISTA_Tweets* prox;
    struct LISTA_Tweets* ant;

}idTweets;

void        stringToLower(char *s);
int         funcMax(int x, int y);

/* ==== FUNÇÕES PARA TRATAMENTO DA LISTA DE IDs === */
void        initIDL(idTweets**);
void        imprimeIDL(idTweets*, FILE **saida);
idTweets*   insereIDL(idTweets*, int);


#endif // TAD_TWEET_H_INCLUDED
