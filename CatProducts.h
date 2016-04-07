#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

#define SIZE_PRODUCTS 7 
#define LETRAS_P 2
#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include "avl.h"
#include <stdio.h>

typedef struct product *PRODUCT;
typedef struct catp *CATALOG_PRODUCTS;
typedef struct conjProds *GROUP_PRODUCTS;

CATALOG_PRODUCTS initProducts();
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, PRODUCT);
int existProduct(CATALOG_PRODUCTS, PRODUCT);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);
int testProduct (PRODUCT);
Avl getP(CATALOG_PRODUCTS ,int );
char* getProduct(PRODUCT prod);
PRODUCT setProduct(char* string);

/* APAGAR
int printCatProducts(CATALOG_PRODUCTS);
*/

#endif