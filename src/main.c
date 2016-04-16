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
	FACTURACAO fact = initFact();
	FILIAL arrayFiliais[3];

	for(i=0;i<3;i++)
		arrayFiliais[i] = initFilial();

	interpretador(CatClients,CatProducts,arrayFiliais,fact);
	/*getFile(CatClients,CatProducts,arrayFiliais,fact);*/
	/*
	getchar();
	int a;
	GROUP_PRODUCTS f1;

			a=0;	
			f1 = querie4(fact,&a,1);

		for(i=0;i<getGroupProdSp(f1);i++)
			printf("%s\n",getProduct(getGroupProd(f1)[i]));
		printf("%d\n",a);
	*/

	return 0;
}