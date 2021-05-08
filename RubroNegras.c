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
    rbNode* p = node->a;//Pai do n�
    rbNode* avo = NULL;//Av� do n�
    rbNode* r = node->r;//Filho direito do n�

    if (p->a != NULL)//Pai n�o � raiz
    {
        avo = p->a;
        if (avo->r == p)//Pai � filho direito
        {
            avo->r = node;//Atribuir n� ao filho direito do av�
        }
        else//Pai � filho esquerdo
        {
            avo->l = node;//Atribuir n� ao filho esquerdo do av�
        }
    }
    else
    {
        tree->root = node;//Se n� � nova raiz, atribuir na �rvore
    }

    node->a = avo;//Ancestral do n� vai ser seu av� antigo
    node->r = p;//Filho direito no n� vai ser seu pai antigo
    if (r != NULL)
        r->a = p;//Ancestral do filho direito antigo do n� vai ser pai antigo do n�

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
            avo->r = node;//Atribuir n� ao filho direito do av�
        }
        else//Pai � filho esquerdo
        {
            avo->l = node;//Atribuir n� ao filho esquerdo do av�
        }
    }
    else
    {
        tree->root = node;//Se n� � nova raiz, atribuir na �rvore
    }

    p->a = node;//Ancestral do pai antigo do n� vai ser o pr�prio n�
    p->r = l;//Filho direito do pai antigo do n� vai ser filho antigo esquerdo do n�
    if (l != NULL)
        l->a = p;//Ancestral do filho esquerdo antigo do n� vai ser pai antigo do n�

    node->a = avo;//Ancestral do n� vai ser seu av� antigo
    node->l = p;//Filho esquerdo no n� vai ser seu pai antigo
}

void rotacaoDireita(rbNode* node, rbt* tree)
{
    node->a->color = 0;//Muda a cor do pai
    node->a->a->color = 1;//Muda a cor do av�
    rDireita(node->a, tree);//Rota��o � direita
}

void rotacaoEsquerda(rbNode* node, rbt* tree)
{
    node->a->color = 0;//Muda a cor do pai
    node->a->a->color = 1;//Muda a cor do av�
    rEsquerda(node->a, tree);//Rota��o � esquerda
}

void rotacaoDuplaDireita(rbNode* node, rbt* tree)
{
    node->color = 0;//Muda a cor do n�
    node->a->a->color = 1;//Muda a cor do av�
    rEsquerda(node, tree);//Rota��o � esquerda
    rDireita(node, tree);//Rota��o � direita
}

void rotacaoDuplaEsquerda(rbNode* node, rbt* tree)
{
    node->color = 0;//Muda a cor do n�
    node->a->a->color = 1;//Muda a cor do av�
    rDireita(node, tree);//Rota��o � direita
    rEsquerda(node, tree);//Rota��o � esquerda
}

void arrumarArvore(rbNode* node, rbt* tree)
{
    if (node != NULL && node->a != NULL && node->a->a != NULL)//Se n�, pai do n� e av� do n� n�o s�o nulos
    {
        rbNode* p = node->a;//Pai do n�
        rbNode* g = node->a->a;//Av� do n�

        ////////////////////// DEBUG
        /*
        printf("node %s \n", node->word);
        printf("pai %s cor %d \n", p->word, p->color);
        printf("avo %s cor %d \n", g->word, g->color);
        */
        //////////////////////


        if (node->a->color == 1 && node->color == 1)//Pai � vermelho
        {
            if (g->r != p)//Pai � filho esquerdo
            {
                if (g->r != NULL && g->r->color == 1)//Tio � vermelho
                {
                    p->color = 0;//Mudar cor do pai
                    g->r->color = 0;//Mudar cor do tio
                    if (g->a != NULL)//Exce��o se o av� for raiz
                        g->color = 1;//Mudar cor do av�
                }
                else//Tio � preto
                {
                    if (p->r != node)//N� � filho esquerdo
                    {
                        //printf("rotacao direita \n");////////////////// DEBUG
                        rotacaoDireita(node, tree);//Realizar rota��o � direita
                        tree->rotations += 1;//Incrementar contador de rota��es
                    }
                    else//N� � filho direito
                    {
                        //printf("rotacao dupla direita \n");////////////////// DEBUG
                        rotacaoDuplaDireita(node, tree);//Realizar rota��o dupla � direita
                        tree->rotations += 2;//Incrementar contador de rota��es em 2
                    }
                }
            }
            else//Pai � filho direito
            {
                if (g->l != NULL && g->l->color == 1)//Tio � vermelho
                {
                    //printf("muda cor \n");////////////////// DEBUG
                    p->color = 0;//Mudar cor do pai
                    g->l->color = 0;//Mudar cor do tio
                    if (g->a != NULL)//Exce��o se o av� for raiz
                        g->color = 1;//Mudar cor do av�
                }
                else//Tio � preto
                {
                    if (p->r != node)//N� � filho esquerdo
                    {
                        //printf("rotacao dupla esquerda \n");////////////////// DEBUG
                        rotacaoDuplaEsquerda(node, tree);//Realizar rota��o dupla � esquerda
                        tree->rotations += 2;//Incrementar contador de rota��es em 2
                    }
                    else//N� � filho direito
                    {
                        //printf("rotacao esquerda \n");////////////////// DEBUG
                        rotacaoEsquerda(node, tree);//Realizar rota��o � esquerda
                        tree->rotations += 1;//Incrementar contador de rota��es
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
    rbNode* node = malloc(sizeof(rbNode));//Alocar espa�o para o n�
    idTweets* ids;//Criar lista de ids para mandar para o n�
    initIDL(&ids);//Inicializar lista de ids
    node->a = a;//Atribuir ancestral
    node->word = strdup(word);//Duplicar palavra para o n�
    node->color = 1;//Cor do n� � vermelho inicialmente
    node->l = NULL;
    node->r = NULL;//Atribuir nulo aos filhos
    node->ids = ids;//Atribuir lista nova � lista do n�
    node->ids = insereIDL(node->ids, tweetId);//Inserir id do tweet na lista do n�
    return node;//Retornar o n�
}

rbNode* rbInsert(rbNode* node, rbt* tree, rbNode* a, char* word, int tweetId, char d, rbNode** start)
{
    if (node == NULL)//Se � folha
    {
        rbNode* newNode = createNode(word, tweetId, a);//Criar n� novo
        tree->nodes += 1;//Incrementar o contador de n�s da �rvore
        if (a == NULL)//Se n� for o primeiro a ser inserido, cor � preta
            newNode->color = 0;
        *start = newNode;//Manda o endere�o do n� para fazer o reajuste da �rvore
        return newNode;//Retorna o n� novo
    }
    else//Se n� n�o � folha
    {
        int cmp = strcmp(node->word, word);//Compara a palavra do n� atual com a palavra a ser inserida
        tree->comps += 1;//Incrementa o contador de compara��es
        if (cmp > 0)//Se a palavra vem antes do n� atual em ordem alfab�tica, ir para a esquerda
        {
            node->l = rbInsert(node->l, tree, node, word, tweetId, 0, start);//Se existe um n� � esquerda, ele continua no mesmo lugar, se n�o existe n� � esquerda, novo n� tomo lugar vazio.
        }
        else if (cmp < 0)//Se a palavra vem depois do n� atual em ordem alfab�tica, ir para a direita
        {
            node->r = rbInsert(node->r, tree, node, word, tweetId, 0, start);//Se existe um n� � direita, ele continua no mesmo lugar, se n�o existe n� � direita, novo n� tomo lugar vazio.
        }
        else//Se palavras s�o iguais
        {
            if (node->ids->id != tweetId)//adiciona tweetId � lista de ids apenas se est� em tweet diferente do �ltimo adicionado
                node->ids = insereIDL(node->ids, tweetId);
        }
        return node;//Retorna o n� para manter order da �rvore
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
        fprintf(*saida, "consulta: %s Palavra n�o encontrada\n", word);
    }
}
