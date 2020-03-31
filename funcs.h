/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
 * AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *****************************************************************************
 * File Name: funcs.h
 * COMMENTS: Declaração da funções de necessários para as avaliações de dados
             e resolução de problemas
 *****************************************************************************/
#ifndef _FUNCS_H
#define _FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "file.h"

#define MODE_INVLD 0
#define MODE_MIN   1
#define MODE_MAX   2
#define CORRECT   1

/*avaliação dos parametros*/
int  first_line (FILE *, int *, int *, int *, int *, int *, int *, int *);
int  game_mode  (int, int, int, int, int, int, int);
/*modos invalidos*/
int  mode_invalid (FILE*, FILE*, int, int, int, int, int, int, int);
void only_invalids (char *);
/*matriz util*/
void getMaxSize          (FILE*, char *, int *, int *);
void min_max             (MAZE*, int *, int *, int *, int *, int);
void readFromFileToMatrix(FILE*, MAZE*, int);

/*funçoes de avaliação e resolução do problema*/
int  upper_bond     (MAZE*, int, int);
void positive_update(MAZE*, MATRIX*, int, int);
void negative_update(MAZE*, MATRIX*, int, int);

int sub_mode_min(MAZE*, MATRIX*, int, int);
int mode_min    (MAZE*, MATRIX*, int, int);

int sub_mode_max(MAZE*, MATRIX*, MATRIX*, int, int);
int mode_max    (MAZE*, MATRIX*, MATRIX*, int, int);

int unsolved (FILE*, MAZE*);
int solved   (FILE*, MAZE*, MATRIX*);

/*resolução do problema*/
int play_game(FILE*, MAZE*, int);

#endif
