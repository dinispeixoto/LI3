#ifndef __VALIDA_H__
#define __VALIDA_H__

#define LETRAS_C 1
#define LETRAS_P 2
#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define SIZE_CLIENTS 6 //CONTAR COM O /0
#define SIZE_PRODUCTS 7 // CONTAR COM O /0
#define SIZE_VENDAS 29// 

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "testes.h"

typedef struct vendas{
   char* client,product;
   float price;
   int quantity;
   char infoPromo;
   int filial;
   struct vendas *esq,*dir;
}Vendas[MAX_SALES];

int valClientsP(FILE *,char**);
int valSales(FILE *,char** ,char**,char** );


#endif