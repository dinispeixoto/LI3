#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "valida.h"
<<<<<<< HEAD

void getFile(char*, char*);
=======
#include "testes.h"

#define MAX_CLIENTS 20000
#define MAX_PRODUCTS 200000
#define MAX_SALES 1

void getFile(char**,char**);
>>>>>>> master



// Main
int main(){
<<<<<<< HEAD
	char buffer[100];
	char doc_type[10];

	printf("Insere o nome do ficheiro:\n");
	scanf("%s %s",buffer,doc_type);
	getFile(buffer,doc_type);
=======

	char* clients[MAX_CLIENTS];
	char* products[MAX_PRODUCTS];
	//estrutura  das vendas;

	getFile(clients,products);

>>>>>>> master
	return 0;
}


<<<<<<< HEAD
// Recebe o nome do ficheiro e o tipo dele (ex: Clientes, Produtos, Vendas).
void getFile(char* filename, char* doc_type){
	
	FILE *read_file;	
	int validated=0;

	read_file = fopen(filename,"r");
	if (read_file == NULL) printf("Não é possível ler o ficheiro %s.\n",filename);
	else {
		if(strcmp("Clientes",doc_type)==0) validated = valClients(read_file);
		else if(strcmp("Produtos",doc_type)==0) validated = valProducts(read_file);
		else if(strcmp("Vendas",doc_type)==0) validated = valSales(read_file);
		else printf("Esse doc_type não existe!\n");	
	}
	fclose(read_file);
	printf("Foram validadas %d linhas.\n",validated);
}
=======
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

//1. Não será melhor pedir o nome dos ficheiros que vamos ler??? 
//2. Quando dá erro a abrir um ficheiro não diz qual deles é.
//3. Não sei até que ponto este código está bonito.
//4. Corrijam erros de inglês.
//5. Se arranjarem melhores nomes para variáveis, avisem-me ou mudem. 
// :)
>>>>>>> master
