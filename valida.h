#ifndef __VALIDA_H__
#define __VALIDA_H__

#define LETRAS_C 1
#define LETRAS_P 2
#define TAM_P 64
#define TAM_C 64
#define TAM_V 128

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int testProduct (char *);
int testClient(char* );
int valFile(FILE *);
int valSales(FILE *);
int testSales(char *, float, int, char, char *, int, int);

#endif