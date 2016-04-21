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

	int running =1,i;

	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FILIAL Filiais[3];
	FACTURACAO Fact = initFact();
	for(i=0;i<3;i++)
		Filiais[i] = initFilial();

	while(running){
		running = interpretador(CatClients,CatProducts,Filiais,Fact);
		if(running == -1){
			freeMemory(CatClients,CatProducts,Filiais,Fact);
			CatClients = initClients();
			CatProducts = initProducts();
			Fact = initFact();
			for(i=0;i<3;i++) Filiais[i] = initFilial();
			running = 1;
		}
	}
	return 0;
}
