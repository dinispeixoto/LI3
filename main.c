#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "valida.h"

void getFile(char*, char*);



// Main
int main(){
	char buffer[100];
	char doc_type[10];

	printf("Insere o nome do ficheiro:\n");
	scanf("%s %s",buffer,doc_type);
	getFile(buffer,doc_type);
	return 0;
}


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
