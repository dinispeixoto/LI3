#ifndef __VALIDA_H__
#define __VALIDA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "avl.h"
#include "testes.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define SIZE_CLIENTS 6 //CONTAR COM O /0
#define SIZE_PRODUCTS 7 // CONTAR COM O /0
#define SIZE_SALES 29 // 

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000


typedef struct vendas{
   char client[SIZE_CLIENTS];
   char product[SIZE_PRODUCTS];
   float price;
   int quantity;
   char infoPromo;
   int filial;
   int mes;
}*Vendas;

Avl valCliProd(FILE *,Avl,int,int*);
int valSales(FILE *,Avl,Avl,Vendas* );
int exist(char*, Avl);
int partCheck(char*, Avl, Avl, char** ,char** ,int *,int *,int *,float *,char *);
int sizeArray(char**);

#endif