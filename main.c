#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readFiles.h"
#include "facturacao.h"
#include "filiais.h"


/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	
	int i,j;
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO fact = initFact();
	for(i=0;i<3;i++)
		FILIAL filiais[3]= initFilial();

	/*interpretador(CatClients,CatProducts,filiais,fact);*/
	getFile(CatClients,CatProducts,filial,fact);
/*
	TOTAL t;
	for(i=0;i<3;i++){
		for(j=0;j<26;j++){
			t=(TOTAL)getInfo(getAvl(filiais->filiais[i]->Clients[j]));
			if(t){
			printf("%d\n", t->totalQ);
			printf("%f\n", t->totalP);
		}}
	}*/
	return 0;
}