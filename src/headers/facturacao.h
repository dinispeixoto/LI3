#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

#define SIZE_MONTH 12
#define SIZE_CLIENTS 6 
#define SIZE_FILIAIS 3

#include "avl.h"
#include "Sales.h"


/*Estruturas para organizar a facturacao em um array de 12, com cada indice um apontador para um array de 26 
apontadores para uma avl*/

typedef struct fact *FACTURACAO;

/*Estrutura pertencente a um nodo de uma avl, que contem a informacao de um produto*/

typedef struct priceQuantity *PRICE_QUANTITY;

typedef struct info *INFO;

typedef struct dados *DADOS;

typedef struct totalMes *TOTAL_MES;

FACTURACAO initFact();
DADOS initDADOS();
FACTURACAO copyProducts(FACTURACAO,CATALOG_PRODUCTS);
FACTURACAO insereFact(FACTURACAO,SALES);
void freeFact(FACTURACAO f);
void freeInfo(void*);

/* GETS E SETS */
double getnumFilialP(INFO,int,int,int);
int getnumFilialQ(INFO,int,int,int);
double* getDadosP(DADOS);
int* getDadosQ(DADOS);
double getDadosTP(DADOS);
int getDadosTV(DADOS);
DADOS setTotalPrice(DADOS,int,double);
DADOS setTotalQuantity(DADOS,int,int);
MY_AVL getProductIndex(FACTURACAO,int);
PRICE_QUANTITY getNormalPQ(INFO,int,int);
PRICE_QUANTITY getPromoPQ(INFO,int,int);
int getTotalQuantPQ(PRICE_QUANTITY);
double getTotalMP(DADOS);
int getTotalVendas(DADOS);
DADOS setTotalMP(DADOS,double);
DADOS setTotalVendas(DADOS,int);
DADOS updateTotalMP(DADOS,double);
DADOS updateTotalVendas(DADOS,int);
TOTAL_MES getTotalMes(FACTURACAO,int);
double getTotalFacturadoMES(TOTAL_MES m);
int getTotalQuantMES(TOTAL_MES m);
int getTotalRegisto(TOTAL_MES m);

#endif