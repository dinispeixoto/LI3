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
GROUP_PRODUCTS initGroupProducts();
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS, PRODUCT);
BOOL existProduct(CATALOG_PRODUCTS, PRODUCT);
int totalProductsLetter(CATALOG_PRODUCTS,char);
int totalProducts(CATALOG_PRODUCTS);
int testProduct (PRODUCT);

/* GETS & SETS */
MY_AVL getP(CATALOG_PRODUCTS ,int );
char* getProduct(PRODUCT prod);
PRODUCT setProduct(char* string);


/*QUERIES*/
GROUP_PRODUCTS toGroup2(GROUP_PRODUCTS);
int getGroupProdSize(GROUP_PRODUCTS);
int getGroupProdSp(GROUP_PRODUCTS);
void setGroupProdSp(GROUP_PRODUCTS,int);
void setGroupProdSize(GROUP_PRODUCTS,int);
PRODUCT* getGroupProd(GROUP_PRODUCTS);
void setGroupProd(GROUP_PRODUCTS,PRODUCT*);
PRODUCT* insereP(PRODUCT* ,int ,int*,char* );


//void printGP(GROUP_PRODUCTS,int);
/* APAGAR
int printCatProducts(CATALOG_PRODUCTS);
*/

#endif