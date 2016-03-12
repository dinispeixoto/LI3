#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "valida.h"
#include "testes.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1

void getFile(char**,char**);



// Main
int main(){

	char* clients[MAX_CLIENTS];
	char* products[MAX_PRODUCTS];
	//estrutura  das vendas;

	getFile(clients,products);

	return 0;
}


// Abre os 3 ficheiros : Clientes.txt | Produtos.txt | Vendas.txt 
void getFile(char** clients, char** products){
	
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;

	fileClients = fopen("Clientes.txt","r");
	fileProducts = fopen("Produtos.txt","r");
	fileSales = fopen("Vendas.txt","r");

	if (fileSales == NULL || fileProducts == NULL || fileClients == NULL) 
		   printf("Não é possível ler os ficheiros.\n");
	else 
	{
		validatedClients = valClients(fileClients,clients);
		validatedProducts = valProducts(fileProducts,products);
		validatedSales = valSales(fileSales,clients,products);		
	}

	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);

	printf("CLIENTES: Foram validadas %d linhas.\n",validatedClients);
	printf("PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
	printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
}

//1. Quando dá erro a abrir um ficheiro não diz qual deles é.
//2. Não sei até que ponto este código está bonito.
//3. Corrijam erros de inglês.
//4. Se arranjarem melhores nomes para variáveis, avisem-me ou mudem. 
// :)