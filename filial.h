#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "heap.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

typedef struct filial *FILIAL;
typedef struct infoMes *INFO_MES;
typedef struct infoClient *INFO_CLIENT;
typedef struct infoProduct *INFO_PRODUCT;
typedef struct dadosFilial *DADOS_FILIAL;

FILIAL initFilial();
FILIAL insertFilial(FILIAL f,SALES s);
INFO_PRODUCT initInfoProduct();
INFO_CLIENT initInfoClient();
INFO_MES initInfoMes();
DADOS_FILIAL initDadosFilial();

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s);
INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s);
FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c);

int getDadosI(DADOS_FILIAL ,int ,int );

DADOS_FILIAL querie5(FILIAL ,DADOS_FILIAL,char* ,int);
GROUP_CLIENTS querie7 (FILIAL* );
GROUP_CLIENTS querie8(FILIAL ,char* ,GROUP_CLIENTS* );
GROUP_PRODUCTS querie9(FILIAL* , char* ,int );
GROUP_PRODUCTS querie10(FILIAL ,int);
GROUP_PRODUCTS querie11(FILIAL* ,char* );
int querie12Clients(FILIAL* );

#endif