#ifndef __VALIDA_H__
#define __VALIDA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "testes.h"
#include "avl.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

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
int valSales(FILE *,Avl*,Avl*,Vendas* );
int exist(char*, Avl);
int partCheck(char*, Avl*,Avl*,char** ,char** ,int *,int *,int *,double *,char *);
int sizeArray(char**);


int priceZero(Vendas*);
double factTotal(Vendas*);
int unitSold(Vendas*);
int salesFilial(Vendas*,int);
void purchasesClient(char*, Vendas*);

#endif