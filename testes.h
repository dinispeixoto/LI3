#ifndef __TESTES_H__
#define __TESTES_H__

#define LETRAS_C 1
#define LETRAS_P 2
#define TAM_P 64
#define TAM_C 64
#define TAM_V 128

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int testProduct (char *);
int testClient(char* );
int testSales(float, int, char, int, int);

#endif