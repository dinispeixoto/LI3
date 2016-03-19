#include "CatClients.h"
#include "avl.h"

Avl* initClients(){

	int i;

	Avl* CatClients = malloc (sizeof(struct Avl*)*SIZE_ABC);
	for(i=0;i<SIZE_ABC;i++)	CatClients[i]=NULL;
	return CatClients;
}

void printCatClients(Avl estrutura){

	if(estrutura==NULL) printf("NULL\n");
	else{
        printCatClients(estrutura->left);        
		printf("%s\n",estrutura->code);
		printCatClients(estrutura->right);
	}
}

Avl* valCli(FILE *file, Avl* estrutura ,int *validated){

	char buffer[SIZE_BUFFER],*line;
	int index;

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

		line=strtok(buffer,"\r\n");

		index = line[0] - 'A';
		estrutura[index] = insert(estrutura[index],line);
		(*validated)++;
	}
		
	return estrutura;
}
