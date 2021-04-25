#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TAD_AVL.h"
#include "TAD_TWEET.h"


int main (int argc, char *argv[])
{
    setlocale(LC_ALL, "");                                                   //para imprimir corretamente na tela os caracteres acentuados
    FILE *base, *entrada, *saida;

    char    *palavra, linha[300], *id;                                      // linhas a serem lidas do arquivo
    char    separador[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
    int     id_num;
    avlNodo *raizAVL;

    /*if (argc!=4)                                                       //testa se o numero de parametros esperado está correto
    {
        printf ("Número incorreto de parametros.\n Para chamar o programa digite: %s <aqrq_base> <arq_entrada> <arq_saida>\n",argv[0]);
        return 1;
    }*/


    if ((base = fopen("c:/base_completa.csv", "r")) == NULL)                             // testa se consegue abrir o arquivo de entrada
    {
        printf("erro ao abrir arquivo base %s \n", argv[1]);
        return 1;
    }
    if ((entrada = fopen("c:/consulta_100.txt", "r")) == NULL)                           // testa se consegue abrir o arquivo de entrada
    {
        printf("erro ao abrir arquivo de entrada %s \n", argv[2]);
        return 1;
    }

    if ((saida=fopen("c:/saida_100.txt", "w") )== NULL)                              // testa se consegue criar o arquivo de sa�da
    {
        printf("erro ao criar arquivo de saida %s \n", argv[3]);
        return 1;
    }

    initAVL(&raizAVL);                                                 // Inicialização da árvore AVL
    nodosCriadosAVL = 0;
    nRotAVL = 0;


    // Montando a estrutura de dados
    while (fgets(linha, 1000, base))                                    //lê cada linha da base de dados
    {
        id = strtok (linha, ";");                                       //pega o id do tweet
        id_num = atoi(id);                                              //converte o id para numérico

        palavra = strtok(NULL, separador);                              //pega a 1a palavra do tweet

        while (palavra != NULL)                                         //enquanto encontrar palavras no tweet
        {
            stringToLower(palavra);                                     //converte a palavra para minusculo
            raizAVL = insereNodoAVL(raizAVL, palavra, id_num);                    //grava a palavra no arquivo de saída
            palavra = strtok(NULL, separador);                          //pega a próxima palavra do tweet
        }
    }


    buscaNodoAVL(raizAVL, "teste");



    fclose(base);                                                     //fecha os arquivos
    fclose(entrada);
    fclose(saida);

    return 0;
}

