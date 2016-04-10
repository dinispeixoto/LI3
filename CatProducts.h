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
void freeProduct(PRODUCT);
void removeCatProds(CATALOG_PRODUCTS);
GROUP_PRODUCTS initGroupProducts(int);
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, PRODUCT);
BOOL existProduct(CATALOG_PRODUCTS, PRODUCT);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);
int testProduct (PRODUCT);

/* GETS & SETS */
char* getProduct(PRODUCT);
PRODUCT setProduct(char*);
MY_AVL getP(CATALOG_PRODUCTS, int);
void setGroupProdSize(GROUP_PRODUCTS,int);
void setGroupProd(GROUP_PRODUCTS,PRODUCT*);
int getGroupProdSize(GROUP_PRODUCTS);
int getGroupProdSp(GROUP_PRODUCTS);
void setGroupProdSp(GROUP_PRODUCTS,int);
int getJ(GROUP_PRODUCTS);
void setJ(GROUP_PRODUCTS,int);
PRODUCT* getGroupProd(GROUP_PRODUCTS);

/*QUERIES*/
GROUP_PRODUCTS productsLetter(CATALOG_PRODUCTS,char);
void travessia(Avl,int,GROUP_PRODUCTS);
GROUP_PRODUCTS toGroup(GROUP_PRODUCTS,PRODUCT);
GROUP_PRODUCTS toGroup2(GROUP_PRODUCTS);
int getGroupProdSize(GROUP_PRODUCTS);
PRODUCT* getGroupProd(GROUP_PRODUCTS);
PRODUCT* insereP(PRODUCT*,int*,int,char*);

/* APAGAR
int printCatProducts(CATALOG_PRODUCTS);
*/

#endif