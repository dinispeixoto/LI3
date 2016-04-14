#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

struct clients_products{
	MY_AVL Clients[26];
	MY_AVL Products[26];
};
typedef struct clients_products *CLIENTS_PRODUCTS;

struct filiais{
	CLIENTS_PRODUCTS filial;
};
typedef struct filiais *FILIAL;

struct totalClient{
	int totalQ;
	double totalP;
 	MY_AVL prods[26];
};
typedef struct totalClient *TOTAL;

struct valores{
	int quant;
	double pago;
};
typedef struct valores *VALORES;

struct infoClients{
	TOTAL clientsMatriz[12][2];
};
typedef struct infoClients *INFO_CLIENTS;

struct infoProducts{
	TOTAL productsMatriz[12][2];
};
typedef struct infoProducts *INFO_PRODUCTS;

FILIAL initFiliais();
CLIENTS_PRODUCTS initClientsProducts();
INFO_CLIENTS initFiliaisClients();
INFO_PRODUCTS initFiliaisProducts();
TOTAL initFiliaisTotal();
FILIAL insertFiliais(FILIAIS ,SALES );
FILIAL copyC(FILIAL f,CATALOG_CLIENTS c);
FILIAL copyP(FILIAL f,CATALOG_PRODUCTS c);


#endif