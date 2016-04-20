#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_PRODUCTS 7 
#define LETRAS_P 2
#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include <ctype.h>
#include "avl.h"

typedef struct product *PRODUCT;
typedef struct catp *CATALOG_PRODUCTS;


CATALOG_PRODUCTS initProducts();
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, PRODUCT);
BOOL testProduct (PRODUCT);
BOOL existProduct(CATALOG_PRODUCTS, PRODUCT);
void freeProduct(PRODUCT);
void removeCatProds(CATALOG_PRODUCTS);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);



/* GETS & SETS */
char* getProduct(PRODUCT);
PRODUCT setProduct(char*);
MY_AVL getP(CATALOG_PRODUCTS, int);

#endif