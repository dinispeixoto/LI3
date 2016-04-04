#ifndef __VALIDA_H__
#define __VALIDA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define LETRAS_C 1
#define LETRAS_P 2

#define SIZE_CLIENTS 6 //CONTAR COM O /0
#define SIZE_PRODUCTS 7 // CONTAR COM O /0
#define SIZE_SALES 29 // 

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

// O NOME DESTA MERDA NÃO DEVIA SER SALES??? 
typedef struct vendas{
   char client[SIZE_CLIENTS];
   char product[SIZE_PRODUCTS];
   double price;
   int quantity;
   char infoPromo;
   int filial;
   int month;
}*Vendas;

Avl* valCliProd(FILE *,Avl*,int*);
int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,Vendas* );
int exist(char*, Avl);
int partCheck(char*, CATALOG_CLIENTS,CATALOG_PRODUCTS,char** ,char** ,int *,int *,int *,double *,char *);
int sizeArray(char**);
int testProduct (char *);
int testClient(char* );
int testSales(float, int, char, int, int);

#endif