#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "readFiles.h"

void menu();
void interpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
FILE* openFile(char*);
void readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void readCatalog(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES,FACTURACAO);
void printCatalogProds(GROUP_PRODUCTS group,int,int,int);

#endif