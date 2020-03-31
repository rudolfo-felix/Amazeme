/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
 * AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *******************************************************************************
 * File Name: file.h
 * COMMENTS: Declaração da funçõess necessárias para a validação, abertura,
             alocação e atribuição do nome de ficheiros,
 *****************************************************************************/
#ifndef _FILE_H
#define _FILE_H

void    check_file_name (int, char*);
void    getOutputName   (char*, char**);
FILE *  AbreFicheiro    (char*, char*);

#endif
