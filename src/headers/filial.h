#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "heap.h"

#define SIZE_MONTH 12
#define SIZE_FILIAIS 3
#define SIZE_INFOP 2

typedef struct filial *FILIAL;
typedef struct infoMes *INFO_MES;
typedef struct infoClient *INFO_CLIENT;
typedef struct infoProduct *INFO_PRODUCT;
typedef struct dadosFilial *DADOS_FILIAL;

typedef struct cena *CENA;


FILIAL initFilial();
FILIAL insertFilial(FILIAL,SALES);
INFO_PRODUCT initInfoProduct();
INFO_CLIENT initInfoClient();
INFO_MES initInfoMes();
DADOS_FILIAL initDadosFilial();
void freeFilial(FILIAL);
void freeInfoClient(void*);
void freeInfoMes(INFO_MES);
void freeInfoProduct(void*);

INFO_CLIENT updateInfoC(INFO_CLIENT,SALES,int*);
INFO_PRODUCT updateInfoP(INFO_PRODUCT,SALES);
FILIAL copyCPO(FILIAL,CATALOG_CLIENTS);
FILIAL copyP(FILIAL ,CATALOG_PRODUCTS );

int getDadosI(DADOS_FILIAL,int,int);
int getComp( INFO_CLIENT);
Avl getClientIndexF(FILIAL,int);
DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL,int,int,int);
INFO_MES getInfoMes(INFO_CLIENT,int);
int getInfoMesQuantity(INFO_MES);
int getInfoProductQuantity(INFO_PRODUCT,int);
double getInfoProductPrice(INFO_PRODUCT,int);
Avl getInfoMesProduct(INFO_MES,int);
int getDadosFilialQuantity(DADOS_FILIAL,int,int);
Avl getProd10(FILIAL f,int index);
int getResg(CENA);
int	getCenaQuant(CENA);

#endif