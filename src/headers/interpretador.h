#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "readFiles.h"
#include "queries.h"
#include "listaStrings.h"

#define CLIENTS_FILE "files/Clientes.txt"
#define	PRODUCTS_FILE "files/Produtos.txt"
#define SALES_FILE "files/Vendas.txt"

#define PAGE_SIZE 20


void menu();
void printTop(int);
int interpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void backInterpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
int cleaningMemory();

/* QUERIE 1 */
int readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
int runningReadFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);

/* QUERIE 2 */
int runningReadCatalog(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
int readCatalogIntro(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
int searchPage(CATALOG_PRODUCTS,char*,int*);
void printCatalogProds(PAGE page_list,int page,int totalPages,int totalElements);
 

/* QUERIE 3 */
int runningProductMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int productMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printProductMonth(DADOS,DADOS,int,PRODUCT,int);


/* QUERIE 4 */
int runningProductsNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int productsNSoldFiliais(int g1,int g2,int g3);
int productsNSold(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printPageNSold(PAGE,int,int,int);
int printNSold(LISTA_STRINGS group,int totalPages,int *actualPage);


/* QUERIE 5 */
int runningInfoClientPurchases(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int infoClientPurchases(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printClientPurchases(DADOS_FILIAL,char*);


/* QUERIE 6 */
int runningToPeriodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int periodMonths(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
void printDATA(DADOS,int,int);



/* QUERIE 7 */
int runningListClients(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int searchPageListClients(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,int*);
void printListClients(PAGE,int,int,int);


/* QUERIE 8 */
int searchPageListClientsProdFilial(int*,LISTA_STRINGS*);
void printClientsProdFilial(PAGE,int,int,int);
int listClientsProdFilial(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
int runningClientsProdFilial(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);


/* QUERIE 9 */
int runningClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int infoClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int searchPageProducts(LISTA_STRINGS group,int *actualPage);
void printPageMostSold(PAGE page_list,int page,int to0talPages,int totalElements);


/* QUERIE 10*/
int runningMostSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int nProductsMostSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);

/* QUERIE 11 */
int runningThreeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
int threeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void printThreeMostPurchased(LISTA_STRINGS group,char* clientString);


/* QUERIE 12 */
int inactiveClientsProducts(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);
void printClientsProducts(int clients,int products);



void printGROUP_PRODS(LISTA_STRINGS,int);
void testMemory(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*);
int calculatePagesProducts(LISTA_STRINGS,int);
int calculatePagesClients(LISTA_STRINGS,int);

#endif