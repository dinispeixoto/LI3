#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

#define SIZE_ABC 26
#define SIZE_CLIENTS 6 
#define SIZE_PRODUCTS 7 
#define SIZE_SALES 29 

#include "avl.h"


struct fact{
    Avl prod[SIZE_ABC];
    int totalElementos;
    int totalFact;
};

typedef struct fact *FACTURACAO;

struct pq {
	double totalprice;
	int totalquant;
};

typedef struct pq *PQ;

struct info{
	PQ F[6][12];
};

typedef struct info *INFO;

struct sales{
   char client[SIZE_CLIENTS];
   char product[SIZE_PRODUCTS];
   double price;
   int quantity;
   char infoPromo;
   int filial;
   int month;
};

typedef struct sales *Sales;

FACTURACAO initFact (Avl*);
FACTURACAO insereFact(FACTURACAO , Sales);


#endif