#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

typedef struct filial *FILIAL;
typedef struct infoMes *INFO_MES;
typedef struct infoClient *INFO_CLIENT;
typedef struct infoProduct *INFO_PRODUCT;
typedef struct dadosFilial *DADOS_FILIAL;

FILIAL initFilial();
FILIAL insertFilial(FILIAL,SALES);
INFO_PRODUCT initInfoProduct();
INFO_CLIENT initInfoClient();
INFO_MES initInfoMes();
DADOS_FILIAL initDadosFilial();

INFO_CLIENT updateInfoC(INFO_CLIENT,SALES);
INFO_PRODUCT updateInfoP(INFO_PRODUCT,SALES);
FILIAL copyCPO(FILIAL,CATALOG_CLIENTS);

int getDadosI(DADOS_FILIAL,int,int);
int getComp( INFO_CLIENT);
MY_AVL getClientIndexF(FILIAL,int);
DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL,int,int,int);
INFO_MES getInfoMes(INFO_CLIENT,int);
int getInfoMesQuantity(INFO_MES);

DADOS_FILIAL querie5(FILIAL,DADOS_FILIAL,char* ,int);
GROUP_CLIENTS querie7 (FILIAL*);
GROUP_CLIENTS querie8(FILIAL,char*,GROUP_CLIENTS*);

#endif