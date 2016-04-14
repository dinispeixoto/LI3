#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

typedef struct filial *FILIAL;
typedef struct infoClient *INFO_CLIENT;
typedef struct infoProduct *INFO_PRODUCT;

FILIAL initFilial();
FILIAL insertFilial(FILIAL f,SALES s);
INFO_PRODUCT initInfoProduct();
INFO_CLIENT initInfoClient();

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s);
INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s);

#endif