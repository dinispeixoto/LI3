#ifndef __VALIDA_H__
#define __VALIDA_H__

<<<<<<< HEAD
#define LetrasC 1
#define LetrasP 2
=======
#define LETRAS_C 1
#define LETRAS_P 2
#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define SIZE_CLIENTS 6 //CONTAR COM O /0
#define SIZE_PRODUCTS 7 // CONTAR COM O /0

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1

#define MES 12
>>>>>>> master

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

<<<<<<< HEAD

int testProduct (char *);
int testClient(char* );
int valClients(FILE *);
int valProducts(FILE *);
int valSales(FILE *);
int testSales(char *, float, int, char, char *, int, int);
=======
#include "testes.h"

typedef struct vendas{
   char* client,product;
   float price;
   int quantity;
   char infoPromo;
   int filial;
   struct vendas *esq,*dir;
}*Sales[MES];


int valClients(FILE *,char**);
int valProducts(FILE *,char**);
int valSales(FILE *,char** ,char** );

>>>>>>> master

#endif