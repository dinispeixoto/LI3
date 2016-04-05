#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "CatClients.h"
#include "CatProducts.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

void getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,Sales*);


/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){
	
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	Sales* sales = malloc (MAX_SALES*sizeof(Sales));

	getFile(CatClients,CatProducts,sales);

	return 0;
}

/* Abrir ficheiros */
void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,Sales* sales){

			
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
		validatedSales = valSales(fileSales,clients,products,sales);
		printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
	}


	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}
