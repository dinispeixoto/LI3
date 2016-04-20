#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "facturacao.h"
#include "filial.h"
#include "heap.h"
#include "listaStrings.h"

#define SIZE_ABC 26
#define SIZE_MONTH 12
#define SIZE_FILIAIS 3
#define SIZE_PRODUCT 6
#define SIZE_CLIENT 5

LISTA_STRINGS querie2(CATALOG_PRODUCTS,char);
DADOS querie3(FACTURACAO,int,char*,int );
LISTA_STRINGS querie4(FACTURACAO,int);
DADOS_FILIAL querie5(FILIAL,DADOS_FILIAL,char*,int);
DADOS querie6(FACTURACAO,int,int);
LISTA_STRINGS querie7(FILIAL*);
LISTA_STRINGS querie8(FILIAL,char*,LISTA_STRINGS*);
LISTA_STRINGS querie9(FILIAL*,char*,int);
LISTA_STRINGS querie10(FILIAL,FACTURACAO,int,int);
LISTA_STRINGS querie11(FILIAL*,char*);
int querie12(FILIAL*,FACTURACAO,int*);

#endif