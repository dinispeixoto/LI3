#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

#define SIZE_MONTH 12
#define SIZE_CLIENTS 6 
#define SIZE_PRODUCTS 7 
#define SIZE_SALES 29 
#define SIZE_FILIAIS 3

#include "avl.h"
#include "Sales.h"


/*Estruturas para organizar a facturacao em um array de 12, com cada indice um apontador para um array de 26 
apontadores para uma avl*/

typedef struct fact *FACTURACAO;

/*Estrutura pertencente a um nodo de uma avl, que contem a informacao de um produto*/

typedef struct pq *PQ;

typedef struct info *INFO;

typedef struct dados *DADOS;

typedef struct totalMes *TOTAL_MES;

FACTURACAO initFact();
DADOS initDADOS();
FACTURACAO copyProducts(FACTURACAO,CATALOG_PRODUCTS);
FACTURACAO insereFact(FACTURACAO,SALES);

/* GETS E SETS */
double getnumFilialP(INFO,int,int,int);
int getnumFilialQ(INFO,int,int,int);
double* getDadosP(DADOS);
int* getDadosQ(DADOS);
double getDadosTP(DADOS);
int getDadosTQ(DADOS);
double getnumTotalP(INFO);
int getnumTotalQ(INFO);
DADOS setTotalPrice(DADOS,int,double);
DADOS setTotalQuantity(DADOS,int,int);
MY_AVL getProductIndex(FACTURACAO,int);
PQ getNormalPQ(INFO,int,int);
PQ getPromoPQ(INFO,int,int);
int getTotalQuantPQ(PQ);
double getTotalMP(DADOS);
int getTotalMQ(DADOS);
DADOS setTotalMP(DADOS,double);
DADOS setTotalMQ(DADOS,int);
DADOS updateTotalMP(DADOS,double);
DADOS updateTotalMQ(DADOS,int);
TOTAL_MES getTotalMes(FACTURACAO,int);
double getTotalFacturadoMES(TOTAL_MES m);
int getTotalQuantMES(TOTAL_MES m);

/* QUERIE 4*/
/*GROUP_PRODUCTS querie4(FACTURACAO,int*,int);*/



#endif