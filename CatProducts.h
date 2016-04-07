#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_PRODUCTS 7 
#define LETRAS_P 2
#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include "avl.h"

typedef struct product *PRODUCT;
typedef struct catp *CATALOG_PRODUCTS;
typedef struct conjProds *GROUP_PRODUCTS;

CATALOG_PRODUCTS initProducts();
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, PRODUCT);
CATALOG_PRODUCTS valProd(FILE *,CATALOG_PRODUCTS,int *);
//int printCatProducts(CATALOG_PRODUCTS);
int existProduct(CATALOG_PRODUCTS, PRODUCT);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);
int testProduct (PRODUCT);
Avl getP(CATALOG_PRODUCTS ,int );
char* getProductString(PRODUCT prod);
PRODUCT setProductString(char* string);

#endif