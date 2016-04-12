#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

typedef struct filiais *FILIAIS;
typedef struct clients_products *CLIENTS_PRODUCTS;
typedef struct infoClients *INFO_CLIENTS;
typedef struct infoProducts *INFO_PRODUCTS;

FILIAIS initFiliais();
CLIENTS_PRODUCTS initClientsProducts();
INFO_CLIENTS initFiliaisClients();
INFO_PRODUCTS initFiliaisProducts();


#endif