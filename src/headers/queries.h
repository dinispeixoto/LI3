#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "facturacao.h"
#include "filial.h"
#include "heap.h"

GROUP_PRODUCTS querie2(CATALOG_PRODUCTS,char);
DADOS querie3(FACTURACAO,int,char*,int );
GROUP_PRODUCTS querie4(FACTURACAO,int*,int);
DADOS_FILIAL querie5(FILIAL,DADOS_FILIAL,char*,int);
DADOS querie6(FACTURACAO,int,int);
GROUP_CLIENTS querie7(FILIAL*);
GROUP_CLIENTS querie8(FILIAL,char*,GROUP_CLIENTS*);
GROUP_PRODUCTS querie9(FILIAL*,char*,int);

int querie12Clients(FILIAL*);
int querie12Products(FACTURACAO);

#endif