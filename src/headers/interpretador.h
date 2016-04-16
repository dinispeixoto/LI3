#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "readFiles.h"
#include "queries.h"

void menu();
void printTop(int);
void interpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void backInterpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime);


void readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void readCatalog(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void readCatalogIntro(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void searchPage(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,char* buffer,int actualPage);
void printCatalogProds(GROUP_PRODUCTS group,int,int,int);


void periodMonths(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printProductMonth(DADOS dataN, DADOS dataP,int isTotal,PRODUCT prod,int month);
void backToProductMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime);


void productsNSold(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void backToProductsNSold (CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime);
void printPageNSold(GROUP_PRODUCTS,int,int);
int printNSold(GROUP_PRODUCTS,int);


void productMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printDATA(DADOS,int,int);
void backToPeriodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime);


void printGROUP_PRODS(GROUP_PRODUCTS, int);
void testMemory(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*);
int calculatePages(GROUP_PRODUCTS,int);

#endif