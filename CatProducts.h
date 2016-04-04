#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_ABC 26 // abecedário 

#include <unistd.h>
#include <fcntl.h>
#include "avl.h"

typedef struct catp *CATOLOG_PRODUCTS;

CATOLOG_PRODUCTS initProducts();
int printCatProducts(CATOLOG_PRODUCTS);
CATOLOG_PRODUCTS valProd(FILE *, CATOLOG_PRODUCTS ,int *);
Avl getP(CATOLOG_PRODUCTS  , int );

#endif