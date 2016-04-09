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
/*
struct aux{
  MY_AVL x[26];
};

typedef struct aux *AUX;
*/
struct fact{
    MY_AVL prod[SIZE_MONTH][26];
};

typedef struct fact *FACTURACAO;


/*Estrutura pertencente a um nodo de uma avl, que contem a informacao de um produto*/
struct pq {
	double totalprice;
	int totalquant;
};

typedef struct pq *PQ;

struct info{
  PQ F[2][3];
  double totalMesP;
  int totalMesQ;
};

typedef struct info *INFO;

struct dados{
  double totalpriceF[3];
  int totalquantF[3];
};

typedef struct dados *DADOS;



//FAUX initAux();
FACTURACAO initFact ();
FACTURACAO insereFact(FACTURACAO,SALES);
DADOS querie3T(FACTURACAO ,int,char*,int );

#endif