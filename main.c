#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "testes.h"
#include "CatClients.h"
#include "CatProducts.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

void getFile(Avl*,Avl*,Vendas*);


// Main -> Gerar estruturas que vão armazenar os dados em memória
int main(int argc, char ** argv){

	int i;
	Avl* CatClients = initClients();
	Avl* products= initProducts();
	Vendas* sales = malloc (MAX_SALES*sizeof(struct vendas));

	getFile(CatClients,products,sales);

	return 0;
}

// Abrir ficheiros 
void getFile(Avl* clients, Avl* products,Vendas* sales){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	
	fileClients = fopen("Clientes.txt","r");
	fileProducts = fopen("Produtos.txt","r");
	fileSales = fopen("Vendas.txt","r");

	// O que faz este if??? 
	if(0) printf("Não é possível ler os ficheiros.\n");
	
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
