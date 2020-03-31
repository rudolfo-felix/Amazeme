/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
  *AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *******************************************************************************
 * File Name: structs.c
 * COMMENTS: Estruturas de dados utilizadas neste programa.
             Funções de alocação e libertação de memória das estruturas.
             Funções de abstrações de dados necessárias para o funcionamento
             do programa.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "structs.h"

/*Estruturas de dados*/

struct _matrix{/*estrutura associada a cada bloco da matriz do problema*/

  int orig_line;/*linha do problem original*/
  int orig_col;/*coluna do problema original*/
  int prize;/*valor da linha e coluna do problema original*/
  int lamp;/*indica se um bloco ja foi visitado*/
};

struct _maze {/*estrutura associada a cada prblema*/

    MATRIX **matrix;/*matrix util*/

    int L;/*numero de linhas da matriz do problema*/
    int C;/*numero de colunas da matriz do problema*/
    int l1;/*linha da posição inicial*/
    int c1;/*coluna da posição inicial*/

    int m;/*modo de jogo*/
    int k;/*numero total de passos*/
    int k_r;/*numero restante de passo*/
    int ei;/*energia inicial*/
    int ef;/*energia final após cada passo válido*/
    int eb;/*melhor energia*/
    int solved;/*flag que indica que o problema está ou não resolvido, 1 ou 0, respetivamente*/

    /*variáveis para matriz util*/
    int new_L;/*numero de linha da matriz util*/
    int new_C;/*numero de colunas da matriz util*/
    int new_l1;/*linha da posição inicial na matriz util*/
    int new_c1;/*coluna da posição inical na matriz util*/
};

/*****************************************************************************
*Funções associadas a um vetor do tipo MATRIX
*****************************************************************************/
/*****************************************************************************
* newPath
* Arguments: int k_elementos
* Returns: MATRIX*
* COMMENTS: aloca memória para um vetor tipo MATRIX de tamanho k_elementos+1
*****************************************************************************/
MATRIX* newPath(int k_elementos)
{
  MATRIX * new =NULL;
  int i=0;

  new = (MATRIX*)malloc((k_elementos+1)*sizeof(MATRIX));
  if(new == NULL) exit(0);

  for(i=0; i<k_elementos; i++)
  {
      new[i].orig_line = 0;
      new[i].orig_col  = 0;
      new[i].prize     = 0;
      new[i].lamp      = 0;
  }

  return new;
}
/*****************************************************************************
* freePath
* Arguments: MATRIX* path
* Returns: int
* COMMENTS: Liberta a memória alocada para o vetor tipo MATRIX
*****************************************************************************/
int freePath(MATRIX* path)
{
    free(path);

    return 0;
}
/*****************************************************************************
*Funções de atualização de dados num vetor tipo MATRIX
*****************************************************************************/
/*****************************************************************************
* increasePath
* Arguments: MATRIX * path, int i, int line, int col, int prize
* Returns: void
* COMMENTS: Atualiza os dados de uma posição do vetor path, ou seja, sendo
            o path o vetor que guarda os passos que um caminho, é adicionado um
            passo na posição i do vetor.
*****************************************************************************/
void increasePath(MATRIX * path, int i, int line, int col, int prize)
{
  path[i].orig_line = line;
  path[i].orig_col  = col;
  path[i].prize     = prize;
  path[i].lamp      = 1;
}
/*****************************************************************************
* reduzePath
* Arguments: MATRIX* path, int i
* Returns: void
* COMMENTS: Repõe o dados de uma posição a zero do vetor path, ou seja, sendo
            o path o vetor que guarda os passos que um caminho, é retirado um
            passo na posição i do vetor.
*****************************************************************************/
void reduzePath(MATRIX* path, int i)
{
  path[i].orig_line = 0;
  path[i].orig_col  = 0;
  path[i].prize     = 0;
  path[i].lamp      = 0;
}
/*****************************************************************************
* subMAX
* Arguments: MATRIX*path, MATRIX*b_path, int i
* Returns: void
* COMMENTS: Copia os dados de uma posição do vetor _path para o vetor b_path
*****************************************************************************/
void subMAX(MATRIX*path, MATRIX*b_path, int i)
{
  b_path[i].orig_line = path[i].orig_line;
  b_path[i].orig_col  = path[i].orig_col;
  b_path[i].prize     = path[i].prize;
}
/*****************************************************************************
*Funções de obtenção de dados de vetor tipo MATRIX
*****************************************************************************/
int getStepLine(MATRIX* path, int i){
  return path[i].orig_line;
}
int getStepCol(MATRIX* path, int i){
  return path[i].orig_col;
}
int getStepPrize(MATRIX* path, int i){
  return path[i].prize;
}






/*****************************************************************************
*Funções associadas a uma matriz do tipo MATRIX
*****************************************************************************/
/*****************************************************************************
* createMatrix
* Arguments: int max_lines, int max_cols
* Returns: MATRIX**
* COMMENTS: alocação de memória de uma matriz do tipo MATRIX de dimensão[max_lines x max_cols]
*****************************************************************************/
MATRIX** createMatrix(int max_lines, int max_cols)
{
    int i=0;
    MATRIX** matrix = NULL;

    matrix = (MATRIX**)malloc(max_lines*sizeof(MATRIX*));
    if(matrix == NULL) exit(0);

    for(i=0; i<max_lines; i++)
    {
        matrix[i] = (MATRIX*)malloc(max_cols*sizeof(MATRIX));
        if(matrix[i] == NULL) exit(0);

        matrix[i]->orig_line = 0;
        matrix[i]->orig_col  = 0;
        matrix[i]->prize     = 0;
        matrix[i]->lamp      = 0;
    }
    return matrix;
}

/*****************************************************************************
* createMaze
* Arguments: int max_lines, int max_cols
* Returns: MAZE*
* COMMENTS: alocação de memória e iniciação das variáveis de uma estrutura MAZE
            com um matriz do tipo MATRIX de dimensão[max_lines x max_cols]
*****************************************************************************/
MAZE * createMaze (int max_lines, int max_cols)
{
    MAZE * newMaze = NULL;

    newMaze = (MAZE*) malloc(sizeof(MAZE));
    if(newMaze == NULL) exit(0);

	  newMaze->matrix = createMatrix(max_lines, max_cols);

    newMaze->L  = 1;
    newMaze->C  = 1;
    newMaze->l1 = 1;
    newMaze->c1 = 1;
    newMaze->k      = 0;
    newMaze->k_r    = 0;
    newMaze->m      = 0;
    newMaze->ei     = 0;
    newMaze->ef     = 0;
    newMaze->eb     = 0;
    newMaze->solved = 0;
    newMaze->new_L  = 0;
    newMaze->new_C  = 0;
    newMaze->new_l1 = 0;
    newMaze->new_c1 = 0;

    return newMaze;
}

/*****************************************************************************
* setupMAZE
* Arguments: MAZE *maze, int L, int C, int l1, int c1, int k, int m, int e
* Returns: MAZE*
* COMMENTS: associa os parâmetros do problema à estrutura MAZE
*****************************************************************************/
MAZE * setupMaze (MAZE *maze, int L, int C, int l1, int c1, int k, int m, int e)
{
    if(maze == NULL) exit(0);

    maze->L   = L;
    maze->C   = C;
    maze->l1  = l1;
    maze->c1  = c1;
    maze->k   = maze->k_r = k;
    maze->m   = m;
    maze->ei  = maze->ef  = e;

    return maze;
}

/*****************************************************************************
* freeMatrix
* Arguments: MAZE *maze, int max_lines
* Returns: int
* COMMENTS: liberta a memoria alocada para uma matriz do tipo MATRIX
*****************************************************************************/
int freeMatrix(MAZE *maze, int max_lines)
{
    int i = 0;

    if(maze->matrix == NULL) return 0;

    for(i = 0; i < max_lines; i++)
    {
      free(maze->matrix[i]);
    }
    free(maze->matrix);

    return 0;
}
/*****************************************************************************
* freeDadosMaze
* Arguments: MAZE *maze, int max_lines
* Returns: int
* COMMENTS: liberta a memoria alocada para os dados para uma estrutura MAZE
*****************************************************************************/
int freeDadosMaze(MAZE *maze, int max_lines)
{
  if(maze == NULL) return 0;
  freeMatrix(maze, max_lines);

  maze->matrix = NULL;
  maze->L  = 1;
  maze->C  = 1;
  maze->l1 = 1;
  maze->c1 = 1;
  maze->k      = 0;
  maze->k_r    = 0;
  maze->m      = 0;
  maze->ei     = 0;
  maze->ef     = 0;
  maze->eb     = 0;
  maze->solved = 0;
  maze->new_L  = 0;
  maze->new_C  = 0;
  maze->new_l1 = 0;
  maze->new_c1 = 0;

  return 0;
}
/*****************************************************************************
* freeMaze
* Arguments: MAZE *maze, int max_lines
* Returns: int
* COMMENTS: liberta a memoria uma estrutura MAZE
*****************************************************************************/
int freeMaze (MAZE *maze, int max_lines)
{
    freeDadosMaze(maze, max_lines);

    if( maze == NULL ) return 0;

    free(maze);
    maze = NULL;

    return 0;
}

/*****************************************************************************
*Funções de obtenção de dados de uma matriz tipo MATRIX
*****************************************************************************/
int getOrigLine  (MAZE *maze, int _l, int _c) {
    return maze->matrix[_l][_c].orig_line;
}
int getOrigCol   (MAZE *maze, int _l, int _c) {
    return maze->matrix[_l][_c].orig_col;
}
int getPrize (MAZE *maze, int _l, int _c) {
    return maze->matrix[_l][_c].prize;
}
int getLamp (MAZE *maze, int _l, int _c) {
    return maze->matrix[_l][_c].lamp;
}
/*****************************************************************************
*Funções de obtenção de dados de uma estrutura tipo MAZE
*****************************************************************************/
int getNumLines  (MAZE *maze) {
    return maze->L;
}
int getNumCols   (MAZE *maze) {
    return maze->C;
}
int getStartLine (MAZE *maze) {
    return maze->l1;
}
int getStartCol  (MAZE *maze) {
    return maze->c1;
}
int getK (MAZE *maze) {
    return maze->k;
}
int getK_r (MAZE *maze) {
    return maze->k_r;
}
int getM (MAZE *maze) {
    return maze->m;
}
int getEi (MAZE *maze) {
    return maze->ei;
}
int getEf (MAZE *maze) {
    return maze->ef;
}
int getEb (MAZE *maze) {
    return maze->eb;
}
int getSolved (MAZE *maze) {
    return maze->solved;
}
int getNewNumLines  (MAZE *maze) {
    return maze->new_L;
}
int getNewNumCols   (MAZE *maze) {
    return maze->new_C;
}
int getNewStartLine (MAZE *maze) {
    return maze->new_l1;
}
int getNewStartCol  (MAZE *maze) {
    return maze->new_c1;
}
/*****************************************************************************
*Funções de atualização de dados numa matriz do tipo MATRIX
*****************************************************************************/
void updateOrigLine  (MAZE *maze, int _l, int _c, int orig_line) {
    maze->matrix[_l][_c].orig_line = orig_line;
}
void updateOrigCol   (MAZE *maze, int _l, int _c, int orig_col) {
    maze->matrix[_l][_c].orig_col = orig_col;
}
void updatePrize (MAZE *maze, int _l, int _c, int prize) {
    maze->matrix[_l][_c].prize = prize;
}
void updateLamp (MAZE *maze, int _l, int _c, int on_off) {
    maze->matrix[_l][_c].lamp = on_off;
}
/*****************************************************************************
*Funções de atualização de dados numa estrutura tipo MAZE
*****************************************************************************/
void updateK_r (MAZE *maze, int k_restante) {
    maze->k_r = k_restante;
}
void updateEf   (MAZE *maze, int ef) {
    maze->ef = ef;
}
void updateEb (MAZE *maze, int eb) {
    maze->eb = eb;
}
void updateSolved (MAZE *maze, int solved) {
    maze->solved = solved;
}
void updateNewNumLines  (MAZE *maze, int new_lines) {
    maze->new_L = new_lines;
}
void updateNewNumCols   (MAZE *maze, int new_cols) {
    maze->new_C = new_cols;
}
void updateNewStartLine (MAZE *maze, int new_l1) {
    maze->new_l1 = new_l1;
}
void updateNewStartCol  (MAZE *maze, int new_c1) {
    maze->new_c1 = new_c1;
}
