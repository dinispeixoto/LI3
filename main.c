#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readFiles.h"
#include "facturacao.h"
#include "interpretador.h"


/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	

	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO fact = initFact();
	SALES Sales = initSale();

	interpretador(CatClients,CatProducts,Sales,fact);

	return 0;
}