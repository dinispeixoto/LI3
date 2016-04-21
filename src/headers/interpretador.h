#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "filial.h"
#include "facturacao.h"		
#include "readFiles.h"
#include "queries.h"
#include "listaStrings.h"

#define CLIENTS_FILE "files/Clientes.txt"
#define	PRODUCTS_FILE "files/Produtos.txt"
#define SALES_FILE "files/Vendas_1M.txt"

#define PAGE_SIZE 20

int interpretador(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);

#endif