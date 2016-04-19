#ifndef __READFILES_H__
#define __READFILES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "filial.h"

/* Nomes dos ficheiros DEFAULT. */

#define SIZE_FILE_NAME 32

int getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*,char*,char*);
FILE* openFile(char*);
int valCli(FILE *,CATALOG_CLIENTS,int*);
int valProd(FILE *,CATALOG_PRODUCTS,int*);
int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,int*);
void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);

#endif