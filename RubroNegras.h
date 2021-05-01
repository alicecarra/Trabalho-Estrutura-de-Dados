#ifndef RUBRONEGRAS_H_INCLUDED
#define RUBRONEGRAS_H_INCLUDED
#include "TAD_TWEET.h"

typedef struct _rbNode
{
    char *word;
    idTweets* ids;
    char color;
    struct _rbNode* a;
    struct _rbNode* r;
    struct _rbNode* l;
} rbNode;

typedef struct _rbt
{
    rbNode* root;
    int nodes;
    int rotations;
} rbt;


rbt* rbInitialize();

void rbInserir(rbt* tree, char *word, int tweetId);
rbNode rbCons(rbt* tree);
void preEsq(rbt* tree);
rbNode* rbFind(rbt* tree, char *word);


#endif // RUBRONEGRAS_H_INCLUDED
