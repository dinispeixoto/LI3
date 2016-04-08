#ifndef __READFILES_H__
#define __READFILES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"			

/* Nomes dos ficheiros DEFAULT. */
#define CLIENTS_FILE "Clientes.txt"
#define	PRODUCTS_FILE "Produtos.txt"
#define SALES_FILE "Vendas.txt"

void getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES*);
CATALOG_CLIENTS valCli(FILE *,CATALOG_CLIENTS,int *);
CATALOG_PRODUCTS valProd(FILE *,CATALOG_PRODUCTS,int *);
int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,SALES*);

#endif