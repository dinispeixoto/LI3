#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "testes.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

void getFile(Avl*,Avl*,Vendas*,int,char**);


// Main
int main(int argc, char ** argv){

	int i;
	Avl clients=NULL;
	Avl products=NULL;
	Vendas* sales = malloc (MAX_SALES*sizeof(struct vendas));

	getFile(&clients,&products,sales,argc,argv);

	return 0;
}

// Abrir ficheiros dados como argumentos... 
void getFile(Avl* clients, Avl* products,Vendas* sales,int argc, char** argv){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;

	int n=1;
		    
	switch(argc){

		case 2: if(strcmp(argv[n],"Vendas.txt")==0)
					fileSales = fopen("Vendas.txt","r");
				else if(strcmp(argv[n],"Clientes.txt")==0)
					fileClients = fopen("Clientes.txt","r");
				else if(strcmp(argv[n],"Produtos.txt")==0) 
					fileProducts = fopen("Produtos.txt","r");
				break;
		                    
		case 3: if(strcmp(argv[n],"Vendas.txt")==0)
					fileSales = fopen("Vendas.txt","r");
				else if(strcmp(argv[n],"Clientes.txt")==0)
					fileClients = fopen("Clientes.txt","r");
				else if(strcmp(argv[n],"Produtos.txt")==0) 
					fileProducts = fopen("Produtos.txt","r");
				n++;

				if(strcmp(argv[n],"Vendas.txt")==0)
					fileSales = fopen("Vendas.txt","r");
				else if(strcmp(argv[n],"Clientes.txt")==0)
					fileClients = fopen("Clientes.txt","r");
				else if(strcmp(argv[n],"Produtos.txt")==0) 
					fileProducts = fopen("Produtos.txt","r");
				break;

		default:fileClients = fopen("Clientes.txt","r");
				fileProducts = fopen("Produtos.txt","r");
				fileSales = fopen("Vendas.txt","r");
				break;

	}

	if(0) printf("Não é possível ler os ficheiros.\n");
				
	else{
		if(fileClients!=NULL){
			*clients = valCliProd(fileClients,*clients,SIZE_CLIENTS,&validatedClients);
			printf("CLIENTES: Foram validadas %d linhas.\n",validatedClients);
		}
	
		if(fileProducts!=NULL){
			*products = valCliProd(fileProducts,*products,SIZE_PRODUCTS,&validatedProducts);
			printf("PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
		}
		if(fileSales!=NULL){
			validatedSales = valSales(fileSales,*clients,*products,sales);
			printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
		}		
	}

	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}
