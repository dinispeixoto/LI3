#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

#define SIZE_MONTH 12
#define SIZE_CLIENTS 6 
#define SIZE_PRODUCTS 7 
#define SIZE_SALES 29 

#include "avl.h"
#include "Sales.h"

struct fact{
    MY_AVL prod[SIZE_MONTH];
};

typedef struct fact *FACTURACAO;

struct pq {
	double totalprice;
	int totalquant;
};

typedef struct pq *PQ;

struct info{
  PQ F[2][3];
  double totalMes;
};

typedef struct info *INFO;


FACTURACAO initFact ();
FACTURACAO insereFact(FACTURACAO,SALES );


#endif