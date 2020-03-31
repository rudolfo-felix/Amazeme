/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
  *AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *******************************************************************************
 * File Name: structs.h
 * COMMENTS: Declaração das estruturas de dados utilizadas neste programa.
             Declaração das funções de alocação e libertação de memória das estruturas.
             Declaração das funções de abstrações de dados necessárias para o funcionamento
             do programa.
 *****************************************************************************/
#ifndef _MAZE_H
#define _MAZE_H

/*Estruturas de dados*/
typedef struct _matrix MATRIX;
typedef struct _maze   MAZE;

/*****************************************************************************
*Funções associadas a um vetor do tipo MATRIX
*****************************************************************************/
MATRIX *newPath (int);
int  freePath   (MATRIX*);
/*****************************************************************************
*Funções de atualização de dados num vetor tipo MATRIX
*****************************************************************************/
void increasePath (MATRIX*, int, int, int, int);
void reduzePath   (MATRIX*, int);
void subMAX       (MATRIX*, MATRIX*, int);
/*****************************************************************************
*Funções de obtenção de dados de vetor tipo MATRIX
*****************************************************************************/
int getStepLine  (MATRIX*, int);
int getStepCol   (MATRIX*, int);
int getStepPrize (MATRIX*, int);
/*****************************************************************************
*Funções associadas a uma matriz do tipo MATRIX
*****************************************************************************/
MATRIX ** createMatrix (int, int);
MAZE   *  createMaze   (int, int);
MAZE   *  setupMaze    (MAZE *, int, int, int, int, int, int, int);

int     freeMatrix    (MAZE*, int);
int     freeDadosMaze (MAZE*, int);
int     freeMaze      (MAZE*, int);
/*****************************************************************************
*Funções de obtenção de dados de uma matriz tipo MATRIX
*****************************************************************************/
int     getOrigLine (MAZE *, int, int);
int     getOrigCol  (MAZE *, int, int);
int     getPrize    (MAZE *, int, int);
int     getLamp     (MAZE *, int, int);
/*****************************************************************************
*Funções de obtenção de dados de uma estrutura tipo MAZE
*****************************************************************************/
int     getNumLines     (MAZE *);
int     getNumCols      (MAZE *);
int     getStartLine    (MAZE *);
int     getStartCol     (MAZE *);
int     getK            (MAZE *);
int     getK_r          (MAZE *);
int     getM            (MAZE *);
int     getEi           (MAZE *);
int     getEf           (MAZE *);
int     getEb           (MAZE *);
int     getSolved       (MAZE *);
int     getNewNumLines  (MAZE *);
int     getNewNumCols   (MAZE *);
int     getNewStartLine (MAZE *);
int     getNewStartCol  (MAZE *);
/*****************************************************************************
*Funções de atualização de dados numa matriz do tipo MATRIX
*****************************************************************************/
void    updateOrigLine (MAZE *, int, int, int);
void    updateOrigCol  (MAZE *, int, int, int);
void    updatePrize    (MAZE *, int, int, int);
void    updateLamp     (MAZE *, int, int, int);
/*****************************************************************************
*Funções de atualização de dados numa estrutura tipo MAZE
*****************************************************************************/
void    updateK_r          (MAZE *, int);
void    updateEf           (MAZE *, int);
void    updateEb           (MAZE *, int);
void    updateSolved       (MAZE *, int);
void    updateNewNumLines  (MAZE *, int);
void    updateNewNumCols   (MAZE *, int);
void    updateNewStartLine (MAZE *, int);
void    updateNewStartCol  (MAZE *, int);

#endif
