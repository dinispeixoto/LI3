#ifndef __VALIDA_H__
#define __VALIDA_H__

#include "CatClients.h"
#include "CatProducts.h"
#include "facturacao.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define LETRAS_C 1
#define LETRAS_P 2

#define SIZE_CLIENTS 6 
#define SIZE_PRODUCTS 7 
#define SIZE_SALES 29 



Avl* valCliProd(FILE *,Avl*,int*);
int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,FACTURACAO,Sales* );
int exist(char*, Avl);
int partCheck(char*, CATALOG_CLIENTS,CATALOG_PRODUCTS,char** ,char** ,int *,int *,int *,double *,char *);
int sizeArray(char**);
int testProduct (char *);
int testClient(char* );
int testSales(float, int, char, int, int);

#endif