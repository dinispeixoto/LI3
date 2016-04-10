#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

#define SIZE_MONTH 12
#define SIZE_CLIENTS 6 
#define SIZE_PRODUCTS 7 
#define SIZE_SALES 29 

#include "avl.h"
#include "Sales.h"

/*Estruturas para organizar a facturacao em um array de 12, com cada indice um apontador para um array de 26 
apontadores para uma avl*/

typedef struct fact *FACTURACAO;

/*Estrutura pertencente a um nodo de uma avl, que contem a informacao de um produto*/

typedef struct pq *PQ;

typedef struct info *INFO;

typedef struct dados *DADOS;

FACTURACAO initF();
FACTURACAO initFact (FACTURACAO,CATALOG_PRODUCTS);
FACTURACAO insereFact(FACTURACAO,SALES);
DADOS querie3(FACTURACAO ,int,char*,int );
DADOS querie6(FACTURACAO, int , int);
double* getDadosP(DADOS );
int* getDadosQ(DADOS );
double getDadosTP(DADOS);
int getDadosTQ(DADOS);
#endif