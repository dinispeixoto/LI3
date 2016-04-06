#include "avl.h"
#include "CatClients.h"

struct catc {
	Avl CatClients[SIZE_ABC];
};

struct conjClie{
	CLIENT* GroupClie;
};

struct client {
	char* string;
};


CATALOG_CLIENTS initClients(){

	int i;
    CATALOG_CLIENTS Catalog = malloc (sizeof(struct catc));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatClients[i] = initAvl();
	return Catalog;
}


CATALOG_CLIENTS insertClient(CATALOG_CLIENTS Catalog, CLIENT clie){

	int index = clie->string[0]-'A';
	Catalog->CatClients[index] = insert(Catalog->CatClients[index],clie->string);
	return Catalog;
}


int existClient(CATALOG_CLIENTS Catalog, CLIENT clie){
	int exist;
	int index = clie->string[0]-'A';
	exist = existAvl(Catalog->CatClients[index],clie->string);
	return exist;
}


int totalClientsLetter(CATALOG_CLIENTS Catalog,char letter){
	int index = letter - 'A';
	return totalElements(Catalog->CatClients[index]);
} 


int totalClients(CATALOG_CLIENTS Catalog){

	char letter; int total=0;
	for(letter = 'A'; letter <= 'Z';letter++)
		total+=totalClientsLetter(Catalog,letter);
	return total;
}


int printCatClients(CATALOG_CLIENTS Catalog){

	int i;

	if(Catalog == NULL) printf("piça\n");
	else 
		for(i=0;i<SIZE_ABC;i++){
			printf("LETRA %c=====\n", 'A'+i); 
			printAVL(Catalog->CatClients[i]); 
		}
	return 0;
}

void removeCatClients(CATALOG_CLIENTS Catalog){
	int i;
	for(i=0;i<SIZE_ABC;i++) {
		removeAvl(Catalog->CatClients[i]);
		Catalog->CatClients[i] = NULL;
	}
}


CATALOG_CLIENTS valCli(FILE *file, CATALOG_CLIENTS Catalog ,int *validated){

	char buffer[SIZE_BUFFER];
	CLIENT line = malloc(sizeof(struct client));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line->string = strtok(buffer,"\r\n");
		Catalog = insertClient(Catalog,line);
		(*validated)++;
	}
		
	return Catalog;
}

int testClient(CLIENT client){
	int num = atoi(client->string+LETRAS_C),r=0;
	if(isupper(client->string[0]) && (num>=1000) && (num<=5000))r++;
	return r;
}

Avl getC (CATALOG_CLIENTS Catalog, int index){
	return Catalog->CatClients[index];
}

char* getClientString(CLIENT clie){
	return clie->string;
}

CLIENT setClientString(char* string){
	CLIENT client = malloc(sizeof(struct client));
	client->string = malloc(SIZE_CLIENTS);
	strcpy(client->string,string);
	return client;
}
