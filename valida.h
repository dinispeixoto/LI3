#ifndef __VALIDA_H__
#define __VALIDA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
   char* client,product;
   float price;
   int quantity;
   char infoPromo;
   int filial;
   struct vendas *esq,*dir;
}Vendas[MAX_SALES];

int valCliProd(FILE *,char**,int);
int valSales(FILE *,char**,char**,char** );
int exist(char*, char*, char**,char**);
int partCheck(char*, char**,char**);
int sizeArray(char**);

#endif