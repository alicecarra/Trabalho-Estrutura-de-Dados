#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TAD_AVL.h"
#include "TAD_TWEET.h"
#include "RubroNegras.h"


int main (int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");                                                   //para imprimir corretamente na tela os caracteres acentuados
    FILE *base, *entrada, *saida;

    char    *palavra, linha[300], *id;                                      // linhas a serem lidas do arquivo
    char    separador[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
    int     id_num, select;
    avlNodo *raizAVL;
    rbt* arvoreRN = rbInitialize();
    rbSearchComp = 0;

    /*if (argc!=4)                                                       //testa se o numero de parametros esperado está correto
    {
        printf ("Número incorreto de parametros.\n Para chamar o programa digite: %s <aqrq_base> <arq_entrada> <arq_saida>\n",argv[0]);
        return 1;
    }*/

    // Checagem e abertura de arquivos
    if ((base = fopen("c:/base_completa.csv", "r")) == NULL)                             // testa se consegue abrir o arquivo de entrada
    {
        printf("erro ao abrir arquivo base %s \n", argv[1]);
        return 1;
    }
    if ((entrada = fopen("consulta.txt", "r")) == NULL)                           // testa se consegue abrir o arquivo de entrada
    {
        printf("erro ao abrir arquivo de entrada %s \n", argv[2]);
        return 1;
    }

    if ((saida=fopen("saida.txt", "w") )== NULL)                              // testa se consegue criar o arquivo de sa�da
    {
        printf("erro ao criar arquivo de saida %s \n", argv[3]);
        return 1;
    }

    // Criação da AVL
    initAVL(&raizAVL);                                                 // Inicialização da árvore AVL
    nodosCriadosAVL = 0;
    nRotAVL = 0;
    comparacoesAVL = 0;
    do{
        printf("Insira  1  para AVL ou  2  para ARN: ");
        scanf("%d", &select);
    }while(select != 1 && select != 2);

    // Lendo arquivo de entrada e montando árvores
    while (fgets(linha, 1000, base))                                    //lê cada linha da base de dados
    {
        id = strtok (linha, ";");                                       //pega o id do tweet
        id_num = atoi(id);                                              //converte o id para numérico

        palavra = strtok(NULL, separador);                              //pega a 1a palavra do tweet

        while (palavra != NULL)                                         //enquanto encontrar palavras no tweet
        {
            stringToLower(palavra);                                     //converte a palavra para minusculo
            if(select == 1)
                raizAVL = insereNodoAVL(raizAVL, palavra, id_num);      //Insere a palavra em AVL caso selecionada
            else
                rbInserir(arvoreRN, palavra, id_num);                     //Insere a palavra em ARN caso selecionada
            palavra = strtok(NULL, separador);                          //pega a próxima palavra do tweet
        }
    }

    comparacoesBuscaAVL = 0;
    while (fgets(linha, 1000, entrada))                                    //lê cada linha da base de dados
    {
        linha[strlen(linha)-1] = '\0';
        if(select == 1)
            buscaNodoAVL(raizAVL, linha, &saida);                          //Insere a palavra em AVL caso selecionada
        else
            rbPrintIds(arvoreRN, linha, &saida);                            //Insere a palavra em ARN caso selecionada
    }

    if(select == 1){
        fprintf(saida, "\n********** Estatísticas da Indexação AVL ***********\n");
        fprintf(saida, "Nodos = %d\n", nodosCriadosAVL);
        fprintf(saida, "Comparações = %d\n", comparacoesAVL);      // TODO
        fprintf(saida, "Rotações = %d\n", nRotAVL);
        fprintf(saida, "Altura da árvore = %d\n", raizAVL->altura);
        fprintf(saida, "\n********** Estatísticas da Busca em AVL ***********\n");
        fprintf(saida, "Comparações = %d\n", comparacoesBuscaAVL);
        }
        else{
        fprintf(saida, "\n********** Estatísticas da Indexação ARN ***********\n");
        fprintf(saida, "Nodos = %d\n", arvoreRN->nodes);
        fprintf(saida, "Comparações = %d\n", arvoreRN->comps);
        fprintf(saida, "Rotações = %d\n", arvoreRN->rotations);
        fprintf(saida, "Altura da árvore = %d\n", rbHeight(arvoreRN));
     }


    fclose(base);                                                     //fecha os arquivos
    fclose(entrada);
    fclose(saida);

    return 0;
}

