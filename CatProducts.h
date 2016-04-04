#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_ABC 26 // abecedário 

#include <unistd.h>
#include <fcntl.h>
#include "avl.h"

typedef struct product *Product;
typedef struct catp *CATALOG_PRODUCTS;
typedef struct conjProds *GROUP_PRODUCTS;

CATALOG_PRODUCTS initProducts();
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, Product);
CATALOG_PRODUCTS valProd(FILE *,CATALOG_PRODUCTS,int *);
int printCatProducts(CATALOG_PRODUCTS);
int existProduct(CATALOG_PRODUCTS, Product);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);
Avl getP(CATALOG_PRODUCTS  , int );

#endif