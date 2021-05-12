#ifndef TAD_TWEET_H_INCLUDED
#define TAD_TWEET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct da lista de IDs
typedef struct LISTA_Tweets{
    int     id;
    struct  LISTA_Tweets* prox;
    struct  LISTA_Tweets* ant;

}idTweets;

void        stringToLower(char *s);                 //Converte os caracteres de uma string para lower case
int         funcMax(int x, int y);

/* ==== FUNÇÕES PARA TRATAMENTO DA LISTA DE IDs === */
void        initIDL(idTweets**);                    //Inicia lista de IDs
void        imprimeIDL(idTweets*, FILE **saida);    //Imprime lista de IDs em um arquivo
idTweets*   insereIDL(idTweets*, int);              //Insere um ID numa dada lista


#endif // TAD_TWEET_H_INCLUDED
