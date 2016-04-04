#include "CatClients.h"
#include "avl.h"

struct client {
     Avl cat[SIZE_ABC];
}; 

CATOLOG_CLIENTS initClients(){

	int i;
    CATOLOG_CLIENTS catCli = malloc (sizeof(struct client));
	for(i=0;i<SIZE_ABC;i++)	(catCli->cat[i])=NULL;
	return catCli;
}



int printCatClients(CATOLOG_CLIENTS estrutura){

    char* array[171008];
    char* buf;
    int i,a=0;
    buf=malloc(2);

    for(i=0;i<SIZE_ABC;i++){
	insereArray(array,estrutura->cat[i],&a);
    }
    
    for(i=0;i<20;i++){
        printf("%s\n",array[i]);    
    }

	return 0;
}



CATOLOG_CLIENTS valCli(FILE *file, CATOLOG_CLIENTS estrutura ,int *validated){

	char buffer[SIZE_BUFFER],*line;
	int index;

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

		line=strtok(buffer,"\r\n");

		index = line[0] - 'A';
		estrutura->cat[index] = insert(estrutura->cat[index],line);
		(*validated)++;
	}
		
	return estrutura;
}


Avl getC (CATOLOG_CLIENTS c, int x){

    return c->cat[x];
}
