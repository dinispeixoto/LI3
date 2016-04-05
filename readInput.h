#ifndef __READINPUT_H__
#define __READINPUT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "valida.h"			

#define CLIENTS_FILE "Clientes.txt"
#define	PRODUCTS_FILE "Produtos.txt"
#define SALES_FILE "Vendas.txt"

void getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,Sales*);


#endif