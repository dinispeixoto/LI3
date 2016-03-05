#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "valida.h"

void getFile(char*);



// Main
int main(){
	char buffer[100];
	char doc_type[10];

	printf("Insere o nome do ficheiro:\n");
	scanf("%s",buffer);
	getFile(buffer);
	return 0;
}


// Recebe o nome do ficheiro e o tipo dele (ex: Clientes, Produtos, Vendas).
void getFile(char* filename){
	
	FILE *read_file;	
	int validated=0;

	read_file = fopen(filename,"r");
	if (read_file == NULL) printf("Não é possível ler o ficheiro %s.\n",filename);
	else {
		if(!strcmp("Clientes.txt",filename)) validated = valFile(read_file);
		else if(!strcmp("Produtos.txt",filename)) validated = valFile(read_file);
		else if(!strcmp("Vendas.txt",filename)) validated = valSales(read_file);
		else printf("Esse documento não existe!\n");	
	}
	fclose(read_file);
	printf("Foram validadas %d linhas.\n",validated);
}
