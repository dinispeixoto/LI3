#ifndef __SALES_H__
#define __SALES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128
#define SIZE_SALES 29 

typedef struct sales *SALES;

SALES* initSales();
int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES*);
int partCheck(char*, CATALOG_CLIENTS,CATALOG_PRODUCTS,CLIENT,PRODUCT,int *,int *,int *,double *,char *);
int testSales(float, int, char, int, int);

#endif