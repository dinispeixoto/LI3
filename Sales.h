#ifndef __SALES_H__
#define __SALES_H__

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128
#define SIZE_SALES 29 

typedef struct sales *SALES;
typedef int QUANTITY;
typedef double PRICE;
typedef char INFO_PROMO;
typedef int FILIAL;
typedef int MONTH;

SALES* initSales();
SALES initSale();
int partCheck(char*,CATALOG_CLIENTS,CATALOG_PRODUCTS,CLIENT,PRODUCT,MONTH*,FILIAL*,QUANTITY*,PRICE*,INFO_PROMO*); /*NÃO FICA BEM AQUI*/

/* GETS E SETS */
CLIENT getSalesClient(SALES);
PRODUCT getSalesProduct(SALES);
PRICE getSalesPrice(SALES);
QUANTITY getSalesQuantity(SALES);
INFO_PROMO getSalesInfoPromo(SALES);
MONTH getSalesMonth(SALES);
FILIAL getSalesFilial(SALES);
SALES setSalesClient(CLIENT,SALES);
SALES setSalesProduct(PRODUCT,SALES);
SALES setSalesPrice(PRICE,SALES);
SALES setSalesQuantity(QUANTITY,SALES);
SALES setSalesInfoPromo(INFO_PROMO,SALES);
SALES setSalesMonth(MONTH,SALES);
SALES setSalesFilial(FILIAL,SALES);



#endif