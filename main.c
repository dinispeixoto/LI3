#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "valida.h"
#include "testes.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1000000

void getFile(char**,char**,char**,int,char**);


// Main
int main(int argc, char ** argv){

	int i;
	char* clients[MAX_CLIENTS];
	char* products[MAX_PRODUCTS];
	char** sales = malloc (MAX_SALES*sizeof(char*));


	getFile(clients,products,sales,argc,argv);

	return 0;
}

// Abrir ficheiros dados como argumentos... 
void getFile(char** clients, char** products,char** sales,int argc, char** argv){

			
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
			validatedClients = valCliProd(fileClients,clients,SIZE_CLIENTS);
			printf("CLIENTES: Foram validadas %d linhas.\n",validatedClients);
		}
	
		if(fileProducts!=NULL){
			validatedProducts = valCliProd(fileProducts,products,SIZE_PRODUCTS);
			printf("PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
		}
		if(fileSales!=NULL){
			validatedSales = valSales(fileSales,clients,products,sales);
			printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
		}		
	}

	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
	}
