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
        if (avo->r == p)//Pai é filho direito
        {
            avo->r = node;//Atribuir nó ao filho direito do avô
        }
        else//Pai é filho esquerdo
        {
            avo->l = node;//Atribuir nó ao filho esquerdo do avô
        }
    }
    else
    {
        tree->root = node;//Se nó é nova raiz, atribuir na árvore
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
            avo->r = node;//Atribuir nó ao filho direito do avô
        }
        else//Pai é filho esquerdo
        {
            avo->l = node;//Atribuir nó ao filho esquerdo do avô
        }
    }
    else
    {
        tree->root = node;//Se nó é nova raiz, atribuir na árvore
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
    node->a->color = 0;//Muda a cor do pai
    node->a->a->color = 1;//Muda a cor do avô
    rDireita(node->a, tree);//Rotação à direita
}

void rotacaoEsquerda(rbNode* node, rbt* tree)
{
    node->a->color = 0;//Muda a cor do pai
    node->a->a->color = 1;//Muda a cor do avô
    rEsquerda(node->a, tree);//Rotação à esquerda
}

void rotacaoDuplaDireita(rbNode* node, rbt* tree)
{
    node->color = 0;//Muda a cor do nó
    node->a->a->color = 1;//Muda a cor do avô
    rEsquerda(node, tree);//Rotação à esquerda
    rDireita(node, tree);//Rotação à direita
}

void rotacaoDuplaEsquerda(rbNode* node, rbt* tree)
{
    node->color = 0;//Muda a cor do nó
    node->a->a->color = 1;//Muda a cor do avô
    rDireita(node, tree);//Rotação à direita
    rEsquerda(node, tree);//Rotação à esquerda
}

void arrumarArvore(rbNode* node, rbt* tree)
{
    if (node != NULL && node->a != NULL && node->a->a != NULL)//Se nó, pai do nó e avô do nó não são nulos
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
                    p->color = 0;//Mudar cor do pai
                    g->r->color = 0;//Mudar cor do tio
                    if (g->a != NULL)//Exceção se o avô for raiz
                        g->color = 1;//Mudar cor do avô
                }
                else//Tio é preto
                {
                    if (p->r != node)//Nó é filho esquerdo
                    {
                        //printf("rotacao direita \n");////////////////// DEBUG
                        rotacaoDireita(node, tree);//Realizar rotação à direita
                        tree->rotations += 1;//Incrementar contador de rotações
                    }
                    else//Nó é filho direito
                    {
                        //printf("rotacao dupla direita \n");////////////////// DEBUG
                        rotacaoDuplaDireita(node, tree);//Realizar rotação dupla à direita
                        tree->rotations += 2;//Incrementar contador de rotações em 2
                    }
                }
            }
            else//Pai é filho direito
            {
                if (g->l != NULL && g->l->color == 1)//Tio é vermelho
                {
                    //printf("muda cor \n");////////////////// DEBUG
                    p->color = 0;//Mudar cor do pai
                    g->l->color = 0;//Mudar cor do tio
                    if (g->a != NULL)//Exceção se o avô for raiz
                        g->color = 1;//Mudar cor do avô
                }
                else//Tio é preto
                {
                    if (p->r != node)//Nó é filho esquerdo
                    {
                        //printf("rotacao dupla esquerda \n");////////////////// DEBUG
                        rotacaoDuplaEsquerda(node, tree);//Realizar rotação dupla à esquerda
                        tree->rotations += 2;//Incrementar contador de rotações em 2
                    }
                    else//Nó é filho direito
                    {
                        //printf("rotacao esquerda \n");////////////////// DEBUG
                        rotacaoEsquerda(node, tree);//Realizar rotação à esquerda
                        tree->rotations += 1;//Incrementar contador de rotações
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
    rbNode* node = malloc(sizeof(rbNode));//Alocar espaço para o nó
    idTweets* ids;//Criar lista de ids para mandar para o nó
    initIDL(&ids);//Inicializar lista de ids
    node->a = a;//Atribuir ancestral
    node->word = strdup(word);//Duplicar palavra para o nó
    node->color = 1;//Cor do nó é vermelho inicialmente
    node->l = NULL;
    node->r = NULL;//Atribuir nulo aos filhos
    node->ids = ids;//Atribuir lista nova à lista do nó
    node->ids = insereIDL(node->ids, tweetId);//Inserir id do tweet na lista do nó
    return node;//Retornar o nó
}

rbNode* rbInsert(rbNode* node, rbt* tree, rbNode* a, char* word, int tweetId, char d, rbNode** start)
{
    if (node == NULL)//Se é folha
    {
        rbNode* newNode = createNode(word, tweetId, a);//Criar nó novo
        tree->nodes += 1;//Incrementar o contador de nós da árvore
        if (a == NULL)//Se nó for o primeiro a ser inserido, cor é preta
            newNode->color = 0;
        *start = newNode;//Manda o endereço do nó para fazer o reajuste da árvore
        return newNode;//Retorna o nó novo
    }
    else//Se nó não é folha
    {
        int cmp = strcmp(node->word, word);//Compara a palavra do nó atual com a palavra a ser inserida
        tree->comps += 1;//Incrementa o contador de comparações
        if (cmp > 0)//Se a palavra vem antes do nó atual em ordem alfabética, ir para a esquerda
        {
            node->l = rbInsert(node->l, tree, node, word, tweetId, 0, start);//Se existe um nó à esquerda, ele continua no mesmo lugar, se não existe nó à esquerda, novo nó tomo lugar vazio.
        }
        else if (cmp < 0)//Se a palavra vem depois do nó atual em ordem alfabética, ir para a direita
        {
            node->r = rbInsert(node->r, tree, node, word, tweetId, 0, start);//Se existe um nó à direita, ele continua no mesmo lugar, se não existe nó à direita, novo nó tomo lugar vazio.
        }
        else//Se palavras são iguais
        {
            if (node->ids->id != tweetId)//adiciona tweetId à lista de ids apenas se está em tweet diferente do último adicionado
                node->ids = insereIDL(node->ids, tweetId);
        }
        return node;//Retorna o nó para manter order da árvore
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
