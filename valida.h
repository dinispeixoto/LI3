#ifndef __VALIDA_H__
#define __VALIDA_H__

#define LetrasC 1
#define LetrasP 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int testProduct (char *);
int testClient(char* );
int valClients(FILE *);
int valProducts(FILE *);
int valSales(FILE *);
int testSales(char *, float, int, char, char *, int, int);

#endif