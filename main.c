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
#include <time.h>

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

	time_t begin_clients;
	time_t end_clients;
	double time_elapsed_clients = 0;
	GROUP_PRODUCTS gp;
	getchar();
	begin_clients = clock();

	Heap hp=initHeap(1);
	querie10Fact(fact,hp,1);
	printf("-----\n");
	gp=querie10(arrayFiliais[0],hp,5);

	
	for(i=0;i<getGroupProdSp(gp);i++)
		printf("%s\n",getProduct(getGroupProd(gp)[i]));	
	
	end_clients = clock();

	time_elapsed_clients = (double) (end_clients - begin_clients) / CLOCKS_PER_SEC;
	printf("	Tempo : %f s.\n",time_elapsed_clients);

	return 0;
}