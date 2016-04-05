#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readInput.h"

#define MAX_SALES 1000000

/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){
	
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	Sales* sales = malloc (MAX_SALES*sizeof(Sales));

	getFile(CatClients,CatProducts,sales);

	return 0;
}