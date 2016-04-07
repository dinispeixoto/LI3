#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "facturacao.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

void getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,FACTURACAO*,Sales*);

int main(){
	
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO f=NULL;
	Sales* sales = malloc (MAX_SALES*sizeof(struct sales));

	getFile(CatClients,CatProducts,&f,sales);
	
	/*-------------------------------------------*/
	
    INFO c = ((INFO)getInfo(f->prod[0]));
    printf("%s\n",getCode(f->prod[0]));
	printf("%f\n",(c->F[0][5]->totalprice)); //VER MELHOR!!!!
	
	return 0;
}

void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,FACTURACAO* f,Sales* sales){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	
	fileClients = fopen("Clientes.txt","r");
	fileProducts = fopen("Produtos.txt","r");
	fileSales = fopen("Vendas.txt","r");
	

	if(fileClients!=NULL){
		clients = valCli(fileClients,clients,&validatedClients);
		printf("CLIENTES: Foram validadas %d linhas.\n",validatedClients);
	}

	if(fileProducts!=NULL){
		products = valProd(fileProducts,products,&validatedProducts);
		printf("PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
	}
	
	if(fileSales!=NULL){
		*f = initFact(get2(products));
		validatedSales = valSales(fileSales,clients,products,*f,sales);
		printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
	}


	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}
