#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_ABC 26 // abecedário 

#include "avl.h"

Avl* initProducts();
void printCatProducts(Avl);
Avl* valProd(FILE *, Avl* ,int *);

#endif