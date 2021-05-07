#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RubroNegras.h"
#include "TAD_TWEET.h"


rbt* rbInitialize()
{
    rbt *n = malloc(sizeof(rbt));
    n->root = NULL;
    n->comps = 0;
    n->nodes = 0;
    n->rotations = 0;
    return n;
}

void rDireita(rbNode* node, rbt* tree)
{
    rbNode* p = node->a;//Pai do nó
    rbNode* avo = NULL;//Avô do nó
    rbNode* r = node->r;//Filho direito do nó

    if (p->a != NULL)//Pai não é raiz
    {
        avo = p->a;
        if (avo->r == p)//Pai é filho esquerdo
        {
            avo->r = node;
        }
        else//Pai é filho direito
        {
            avo->l = node;
        }
    }
    else
    {
        tree->root = node;
    }

    node->a = avo;//Ancestral do nó vai ser seu avô antigo
    node->r = p;//Filho direito no nó vai ser seu pai antigo
    if (r != NULL)
        r->a = p;//Ancestral do filho direito antigo do nó vai ser pai antigo do nó

    p->a = node;//Ancestral do pai antigo do nó vai ser o próprio nó
    p->l = r;//Filho esquerdo do pai antigo do nó vai ser filho antigo direito do nó
}

void rEsquerda(rbNode* node, rbt* tree)
{
    rbNode* p = node->a;//Pai do nó
    rbNode* avo = NULL;//Avô do nó
    rbNode* l = node->l;//Filho esquerdo do nó
    if (p->a != NULL)//Pai não é raiz
    {
        avo = p->a;
        if (avo->r == p)//Pai é filho direito
        {
            avo->r = node;
        }
        else//Pai é filho esquerdo
        {
            avo->l = node;
        }
    }
    else
    {
        tree->root = node;
    }

    p->a = node;//Ancestral do pai antigo do nó vai ser o próprio nó
    p->r = l;//Filho direito do pai antigo do nó vai ser filho antigo esquerdo do nó
    if (l != NULL)
        l->a = p;//Ancestral do filho esquerdo antigo do nó vai ser pai antigo do nó

    node->a = avo;//Ancestral do nó vai ser seu avô antigo
    node->l = p;//Filho esquerdo no nó vai ser seu pai antigo
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
    if (node != NULL && node->a != NULL && node->a->a != NULL)
    {
        rbNode* p = node->a;//Pai do nó
        rbNode* g = node->a->a;//Avô do nó

        ////////////////////// DEBUG
        /*
        printf("node %s \n", node->word);
        printf("pai %s cor %d \n", p->word, p->color);
        printf("avo %s cor %d \n", g->word, g->color);
        */
        //////////////////////


        if (node->a->color == 1 && node->color == 1)//Pai é vermelho
        {
            if (g->r != p)//Pai é filho esquerdo
            {
                if (g->r != NULL && g->r->color == 1)//Tio é vermelho
                {
                    p->color = 0;
                    g->r->color = 0;
                    if (g->a != NULL)//Exceção se o avô for raiz
                        g->color = 1;
                }
                else//Tio é preto
                {
                    if (p->r != node)//Nó é filho esquerdo
                    {
                        //printf("rotacao direita \n");////////////////// DEBUG
                        rotacaoDireita(node, tree);
                        tree->rotations += 1;
                    }
                    else//Nó é filho direito
                    {
                        //printf("rotacao dupla direita \n");////////////////// DEBUG
                        rotacaoDuplaDireita(node, tree);
                        tree->rotations += 2;
                    }
                }
            }
            else//Pai é filho direito
            {
                if (g->l != NULL && g->l->color == 1)//Tio é vermelho
                {
                    //printf("muda cor \n");////////////////// DEBUG
                    p->color = 0;
                    g->l->color = 0;
                    if (g->a != NULL)//Exceção se o avô for raiz
                        g->color = 1;
                }
                else//Tio é preto
                {
                    if (p->r != node)//Nó é filho esquerdo
                    {
                        //printf("rotacao dupla esquerda \n");////////////////// DEBUG
                        rotacaoDuplaEsquerda(node, tree);
                        tree->rotations += 2;
                    }
                    else//Nó é filho direito
                    {
                        //printf("rotacao esquerda \n");////////////////// DEBUG
                        rotacaoEsquerda(node, tree);
                        tree->rotations += 1;
                    }
                }
            }
        }
        //preEsq(tree);
        //printf("\n\n");
        arrumarArvore(node->a, tree);
    }
    /*else////////////////// DEBUG
    {
        preEsq(tree);
        printf("\n\n");
    }*/
}

rbNode* createNode(char *word, int tweetId, rbNode* a)
{
    rbNode* node = malloc(sizeof(rbNode));
    idTweets* ids;
    initIDL(&ids);
    node->a = a;
    node->word = strdup(word);
    node->color = 1;
    node->l = NULL;
    node->r = NULL;
    node->ids = ids;
    node->ids = insereIDL(node->ids, tweetId);
    return node;
}

rbNode* rbInsert(rbNode* node, rbt* tree, rbNode* a, char* word, int tweetId, char d, rbNode** start)
{
    if (node == NULL)
    {
        rbNode* newNode = createNode(word, tweetId, a);
        tree->nodes += 1;
        if (a == NULL)
            newNode->color = 0;
        *start = newNode;
        //printf("%s \n", word);
        return newNode;
    }
    else
    {
        int cmp = strcmp(node->word, word);
        tree->comps += 1;
        if (cmp > 0)
        {
            node->l = rbInsert(node->l, tree, node, word, tweetId, 0, start);
        }
        else if (cmp < 0)
        {
            node->r = rbInsert(node->r, tree, node, word, tweetId, 0, start);
        }
        else
        {
            if (node->ids->id != tweetId)
                node->ids = insereIDL(node->ids, tweetId);
        }
        return node;
    }
}

void rbInserir(rbt* tree, char *word, int tweetId)
{
    rbNode* start = NULL;
    tree->root = rbInsert(tree->root, tree, NULL, word, tweetId, 0, &start);
    if (start != NULL)
        arrumarArvore(start, tree);
}

void peRec(rbNode* node)
{
    if (node == NULL)
        return;
    printf("%s / %d", node->word, node->color);
    if (node->a != NULL)
        printf(" / %s", node->a->word);
    printf("\n");
    peRec(node->l);
    peRec(node->r);
    return;
}

void rbPreEsq(rbt* tree)
{
    peRec(tree->root);
}

rbNode* findRecursive(rbNode* node, char *word)
{
    if (node == NULL)
        return NULL;

    int comp = strcmp(node->word, word);
    rbSearchComp += 1;
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

int rbHeightRec(rbNode* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lH, rH;
        lH = rbHeightRec(node->l);
        rH = rbHeightRec(node->r);

        if (lH > rH)
            return lH + 1;
        else
            return rH + 1;
    }
}

int rbHeight(rbt* tree)
{
    return rbHeightRec(tree->root);
}

void rbPrintIds(rbt* tree, char *word, FILE **saida)
{
    rbNode *node = rbFind(tree, word);
    if (node != NULL)
    {
        fprintf(*saida, "consulta: %s Palavra encontrada nos tweets ", word);
        imprimeIDL(node->ids, saida);
        fprintf(*saida, "\n");
    }
    else
    {
        fprintf(*saida, "consulta: %s Palavra não encontrada\n", word);
    }
}
