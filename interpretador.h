#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "readFiles.h"

void menu();
void printTop(int);
void interpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
FILE* openFile(char*);
void readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void readCatalog(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void printCatalogProds(GROUP_PRODUCTS group,int,int,int);
void productsNSold(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void printGROUP_PRODS(GROUP_PRODUCTS, int);
void testMemory(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO,char*);
int calculatePages(GROUP_PRODUCTS,int);
void printPageNSold(GROUP_PRODUCTS,int,int);
int printNSold(GROUP_PRODUCTS,int);
void periodMonths(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void printDATA(DADOS);
void productMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);

#endif