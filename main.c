#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readFiles.h"
#include "facturacao.h"
/*#include "interpretador.h"*/
#include "filial.h"

/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	

	int i;
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO fact = initFact();
	FILIAL arrayFiliais[3];

	for(i=0;i<3;i++)
		arrayFiliais[i] = initFilial();

	/*interpretador(CatClients,CatProducts,filial,fact);*/
	getFile(CatClients,CatProducts,arrayFiliais,fact);

	int r=querie12Products(fact);
	printf("%d\n",r);

	getchar();
	

	return 0;
}