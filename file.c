/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
  *AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *******************************************************************************
 * File Name: file.c
 * COMMENTS: Funções necessárias para a validação, abertura,
             alocação e atribuição do nome de ficheiros.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
/*****************************************************************************
* check_file_name
* Arguments: int argc, char* argv_1
* Returns: void
* COMMENTS: se o nome do ficheiro de entrada tiver extensão válida
o programa continua normalmente, se não fecha silenciosamente
*****************************************************************************/
void check_file_name(int argc, char* argv_1)
{
  const char nome[6]=".maps";/*todos os ficheiros de entrada tem de ter a extensão ".maps" associada ao nome*/
  int n, i;

  if(argc != 2)
    exit(0);

  n=strlen(argv_1)-1;
  for (i = 0; i < 4; i++){
    if (argv_1[n-i] != nome[4-i])exit(0);
  }
  return;
}

/*****************************************************************************
* getOutputName
* Arguments: char* fileIn, char ** fileOut
* Returns: void
* COMMENTS: Produz o nome do ficheiro de saída, aloca memoria para o guardar em fileOut,
                associado ao ficheiro de entrada, mas com extensão diferente
*****************************************************************************/
void getOutputName(char* fileIn, char ** fileOut)
{
    char* aux = NULL;
    int n = 0;
    int i = 0;

    aux = (char *)malloc((strlen(fileIn) - 5 + strlen(".paths") + 1) * sizeof(char));/*aloca memoria para o nome do ficheiro de saída*/
    if(aux == NULL) exit(0);

    for (i = 0; i < (strlen(fileIn) - 5 + strlen(".paths") + 1); i++) aux[i] = 0;/*inicia o vetor auxiliar a zero*/

    n = strlen(fileIn);
    for(i = 0; i < n-5; i++) aux[i]=fileIn[i];

    strcat(aux, ".paths");
    *fileOut = aux;
    return;
}

/*****************************************************************************
* AbreFicheiro
* Arguments: char *nome, char *w_or_r
* Returns: FILE*
* COMMENTS: Abre um ficheiro e receber o argumento para o ler/escrever
*****************************************************************************/
FILE *AbreFicheiro ( char *nome, char *w_or_r )
{
	FILE *f=NULL;
	f = fopen (nome, w_or_r);

  if (f == NULL)exit(0);

  return (f);
}
