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

	/*interpretador(CatClients,CatProducts,arrayFiliais,fact);*/
	getFile(CatClients,CatProducts,arrayFiliais,fact);
	
	time_t begin_clients;
	time_t end_clients;
	double time_elapsed_clients = 0;
	getchar();
	begin_clients = clock();

	LISTA_STRINGS ls;
	ls=querie10(arrayFiliais[0],fact,5,1);

	end_clients = clock();

	time_elapsed_clients = (double) (end_clients - begin_clients) / CLOCKS_PER_SEC;
	printf("	Tempo : %f s.\n",time_elapsed_clients);

	printLS(ls);

	return 0;
}