#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RubroNegras.h"
#include "TAD_TWEET.h"


rbt* rbInitialize()
{
    rbt *n = malloc(sizeof(rbt));
    n->root = NULL;
    return n;
}

void rDireita(rbNode* node, rbt* tree)
{
    rbNode* p = node->a;//Pai do n�
    rbNode* avo = NULL;//Av� do n�
    rbNode* r = node->r;//Filho direito do n�

    if (p->a != NULL)//Pai n�o � raiz
    {
        avo = p->a;
        if (avo->r == p)//Pai � filho esquerdo
        {
            avo->r = node;
        }
        else//Pai � filho direito
        {
            avo->l = node;
        }
    }
    else
    {
        tree->root = node;
    }

    node->a = avo;//Ancestral do n� vai ser seu av� antigo
    node->r = p;//Filho direito no n� vai ser seu pai antigo

    p->a = node;//Ancestral do pai antigo do n� vai ser o pr�prio n�
    p->l = r;//Filho esquerdo do pai antigo do n� vai ser filho antigo direito do n�
}

void rEsquerda(rbNode* node, rbt* tree)
{
    rbNode* p = node->a;//Pai do n�
    rbNode* avo = NULL;//Av� do n�
    rbNode* l = node->l;//Filho esquerdo do n�
    if (p->a != NULL)//Pai n�o � raiz
    {
        avo = p->a;
        if (avo->r == p)//Pai � filho direito
        {
            avo->r = node;
        }
        else//Pai � filho esquerdo
        {
            avo->l = node;
        }
    }
    else
    {
        tree->root = node;
    }

    p->a = node;//Ancestral do pai antigo do n� vai ser o pr�prio n�
    p->r = l;//Filho direito do pai antigo do n� vai ser filho antigo esquerdo do n�

    node->a = avo;//Ancestral do n� vai ser seu av� antigo
    node->l = p;//Filho esquerdo no n� vai ser seu pai antigo
}

void rotacaoDireita(rbNode* node, rbt* tree)
{
    node->a->color = 0;
    node->a->a->color = 1;
    rDireita(node->a, tree);
}

void rotacaoEsquerda(rbNode* node, rbt* tree)
{
    node->a->color = 0;
    node->a->a->color = 1;
    rEsquerda(node->a, tree);
}

void rotacaoDuplaDireita(rbNode* node, rbt* tree)
{
    node->color = 0;
    node->a->a->color = 1;
    rEsquerda(node, tree);
    rDireita(node, tree);
}

void rotacaoDuplaEsquerda(rbNode* node, rbt* tree)
{
    node->color = 0;
    node->a->a->color = 1;
    rDireita(node, tree);
    rEsquerda(node, tree);
}

void arrumarArvore(rbNode* node, rbt* tree)
{
    if (node != NULL && node->a != NULL && node->a->a != NULL && node->color == 1)
    {
        //////////////
        //char pal[30];
        //strcpy(pal, node->word);
        //////////////
        rbNode* pai = node->a;
        rbNode* avo = pai->a;
        if (pai->color == 1)//Caso 2, pai � vermelho
        {
            if (avo->r != pai)//Pai � filho esquerdo do av�
            {
                if (avo->r != NULL && avo->r->color == 1)//Caso 2.1, tio � vermelho
                {
                    pai->color = 0;
                    avo->r->color = 0;
                    if (avo->a != NULL)//Exce��o raiz
                        avo->color = 1;
                }

                else//Caso 2.2, pai � vermelho, tio � preto
                {
                    if (pai->r != node)//N� � filho esquerdo
                    {
                        rotacaoDireita(node, tree);
                    }
                else//N� � filho direito
                    {
                        rotacaoDuplaDireita(node, tree);
                    }
                }
            }

            else//Pai � filho direito do av�
            {
                if (avo->l != NULL && avo->l->color == 1)//Caso 2.1, tio � vermelho
                {
                    pai->color = 0;
                    avo->l->color = 0;
                    if (avo->a != NULL)//Exce��o raiz
                        avo->color = 1;
                }

                else//Caso 2.2, pai � vermelho, tio � preto
                {
                    if (pai->r != node)//N� � filho esquerdo
                    {
                        rotacaoDuplaEsquerda(node, tree);
                    }
                    else//N� � filho direito
                    {
                        rotacaoEsquerda(node, tree);
                    }
                }
            }
        }
    }
    if (node->a != NULL)
        arrumarArvore(node->a, tree);
}

rbNode* createNode()
{
    rbNode* node = malloc(sizeof(rbNode));
    idTweets* ids;
    initIDL(&ids);
    node->color = 1;
    node->l = NULL;
    node->r = NULL;
    node->ids = ids;
    return node;
}

rbNode* rbInsert(rbNode* root, rbt* tree, rbNode* a, char *word, int tweetId, char d)
{

    if (root == NULL)
    {
        rbNode* node = createNode();
        strcpy(node->word, word);
        node->ids = insereIDL(node->ids, tweetId);
        node->a = a;
        if (a == NULL)
        {
            tree->root = node;
            node->color = 0;
        }
        else
        {
            if (d == 0)
                a->l = node;
            else
                a->r = node;
        }
        return node;
    }

    if (strcmp(root->word, word) > 0)
    {
        return rbInsert(root->l, tree, root, word, tweetId, 0);
    }
    else if(strcmp(root->word, word) < 0)
    {
        return rbInsert(root->r, tree, root, word, tweetId, 1);
    }
    else
    {
        root->ids = insereIDL(root->ids, tweetId);
        return NULL;
    }
}

void rbInserir(rbt* tree, char *word, int tweetId)
{
    rbNode* start = rbInsert(tree->root, tree, NULL, word, tweetId, 0);
    if (start != NULL)
        arrumarArvore(start, tree);
}

void peRec(rbNode* node)
{
    if (node == NULL)
        return;
    printf("%s \n", node->word);
    peRec(node->l);
    peRec(node->r);
    return;
}

void preEsq(rbt* tree)
{
    peRec(tree->root);
}

rbNode* findRecursive(rbNode* node, char *word)
{
    int comp = strcmp(node->word, word);
    if (comp > 0)
        return findRecursive(node->l, word);
    else if (comp < 0)
        return findRecursive(node->r, word);
    else
        return node;
}

rbNode* rbFind(rbt* tree, char *word)
{
    return findRecursive(tree->root, word);
}
