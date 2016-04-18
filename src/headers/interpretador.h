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
void backInterpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void readCatalog(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void readCatalogIntro(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void searchPage(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*,int);
void printCatalogProds(GROUP_PRODUCTS group,int,int,int);


void periodMonths(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printProductMonth(DADOS,DADOS,int,PRODUCT,int);
void backToProductMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void productsNSold(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void backToProductsNSold (CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printPageNSold(GROUP_PRODUCTS,int,int);
void printNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,GROUP_PRODUCTS group,int totalPages,int actualPage);

void infoClientPurchases(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printClientPurchases(DADOS_FILIAL,char*);
void backToClientPurchases(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void productMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printDATA(DADOS,int,int);
void backToPeriodMonths(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void listClients(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void searchPageListClients(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,int);
void printListClients(GROUP_CLIENTS,int,int,int);


void searchPageListClientsProdFilial(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,int,GROUP_CLIENTS*);
void printClientsProdFilial(GROUP_CLIENTS,int,int,int);
void listClientsProdFilial(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void backToClientsProdFilial(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


void backToClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void infoClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void searchPageProducts(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,GROUP_PRODUCTS group,int actualPage);
void printPageMostSold(GROUP_PRODUCTS group,int page,int totalPages);


void inactiveClientsProducts(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void printClientsProducts(int clients,int products);



void printGROUP_PRODS(GROUP_PRODUCTS,int);
void testMemory(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*);
int calculatePagesProducts(GROUP_PRODUCTS,int);
int calculatePagesClients(GROUP_CLIENTS,int);

#endif