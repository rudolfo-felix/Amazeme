/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
 * AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *****************************************************************************
 * File Name: main.c
 * COMMENTS: ficheiro da main do programa
 *****************************************************************************/
#include "funcs.h"

/******************************************************************************
 * main
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Description: Função da Main do programa
 *****************************************************************************/
int main(int argc, char *argv[])
{
  /*iniciação da variáveis principais do programa*/
    MAZE * game     = NULL;/*estrutura de dados do programa*/
    FILE * fpIn     = NULL;/*ficheiro de entrada*/
    FILE * fpOut    = NULL;/*ficheiro de saída*/
    char * fileIn   = NULL;/*nome do ficheiro de entrada*/
    char * fileOut  = NULL;/*nome do ficheiro de saída*/

    int L=0, C=0, l1=0, c1=0, k=0, m=0, ei=0, mode=MODE_INVLD;/*parâmetros lidos na primeira linha de cada problema e o modo de jogo correpondente*/
    int max_lines=0, max_cols=0;/*linhas e colunas da maior matriz util*/

    check_file_name(argc, argv[1]);/*verifica se o ficheiro de entrada tem extensão válida*/
    fileIn = argv[1];

    fpIn  = AbreFicheiro ( fileIn, "r" );/*abre e lê o ficheiro de entrada*/
    getMaxSize(fpIn, fileIn, &max_lines, &max_cols);/*calcula as dimensões da matriz útil*/
    game = createMaze(max_lines, max_cols);/*aloca memoria para a estrutura de dados do programa*/
    fclose(fpIn);/*fecha o ficheiro de entrada*/

    fpIn  = AbreFicheiro ( fileIn, "r" );/*voltamos a abrir o ficheiro de entrada*/
    getOutputName(fileIn, &fileOut);/*produz o nome do ficheiro de saída, aloca memoria para o guardar, associado ao ficheiro de entrada, mas com extensão diferente*/
    fpOut = AbreFicheiro ( fileOut, "w" );/*abrimos o ficheiro de saída que irá conter a resolução dos problemas*/

    while(first_line(fpIn, &L, &C, &l1, &c1, &k, &m, &ei) == CORRECT)/*lê a primeira linha  de 7 parâmetros de cada problema*/
    {
      mode = game_mode(L, C, l1, c1, k, m, ei);/*modo de jogo(Mal definido - MODE_INVLD; Variante 1 - MODE_MIN; Variante 2 - MODE_MAX)*/

      if(mode==MODE_INVLD || k >= L*C)/*numero maximo de passos possiveis para um caminhos é (L*C-1)*/
      {
        mode_invalid(fpIn,fpOut, L, C, l1, c1, k, m, ei);/*problema mal definido*/
      }
      else
      {
        game = setupMaze(game, L, C, l1, c1, k, m, ei);/*associa os parâmetro da primeira linha do problema à estrutura de dados*/
        readFromFileToMatrix(fpIn, game, mode);/*escreve a a matriz util do problema à matriz já alocada*/

        play_game(fpOut, game, mode);/*resolve o problema*/
      }
    }

    if(fpIn != NULL) fclose(fpIn);/*fecha o ficheiro de entrada*/
    if(fpOut != NULL) fclose(fpOut);/*fecha o ficheiro de saída*/

    if (fileOut != NULL) free(fileOut);/*liberta a memoria associada ao nome do ficheiro de saída*/
    freeMaze(game, max_lines);/*liberta a memoria associada à estrutura de dados do problema*/

    exit(0);
}
