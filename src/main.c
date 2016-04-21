#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "headers/avl.h"
#include "headers/Sales.h"
#include "headers/CatClients.h"
#include "headers/CatProducts.h"
#include "headers/readFiles.h"
#include "headers/facturacao.h"
#include "headers/interpretador.h"
#include "headers/filial.h"

/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	

	int i;
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO Fact = initFact();
	FILIAL Filiais[3];

	for(i=0;i<3;i++)
		Filiais[i] = initFilial();

	interpretador(CatClients,CatProducts,Filiais,Fact);

	return 0;
}