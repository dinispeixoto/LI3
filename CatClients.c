#include "avl.h"
#include "CatClients.h"

struct catc {
	MY_AVL CatClients[SIZE_ABC];
};

struct conjClie{
	CLIENT* GroupClie;
};

struct client {
	char* string;
};


/* Inicializa o Catálogo de Clientes. */
CATALOG_CLIENTS initClients(){

	int i;
    CATALOG_CLIENTS Catalog = malloc (sizeof(struct catc));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatClients[i] = initMyAvl();
	return Catalog;
}

void freeClient(CLIENT clie){
	free(clie->string);
	free(clie);
}


/* Insere um cliente no respectivo catálogo. */
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS Catalog, CLIENT clie){

	int index = clie->string[0]-'A';
	Catalog->CatClients[index] = insertMyAvl(Catalog->CatClients[index],clie->string,NULL);
	return Catalog;
}

/* Verifica se um cliente existe no catálogo.*/
int existClient(CATALOG_CLIENTS Catalog, CLIENT clie){
	int exist;
	int index = clie->string[0]-'A';
	exist = existMyAvl(Catalog->CatClients[index],clie->string);
	return exist;
}

/* Conta quantos clientes existem começados por uma determinada letra no catálogo.*/
int totalClientsLetter(CATALOG_CLIENTS Catalog,char letter){
	int index = letter - 'A';
	return totalElements(Catalog->CatClients[index]);
} 

/* Conta o total de clientes no catálogo. */
int totalClients(CATALOG_CLIENTS Catalog){
	char letter; int total=0;
	for(letter = 'A'; letter <= 'Z';letter++)
		total+=totalClientsLetter(Catalog,letter);
	return total;
}

/* Limpa o catálogo de clientes. */
void removeCatClients(CATALOG_CLIENTS Catalog){
	int i;
	for(i=0;i<SIZE_ABC;i++) {
		removeMyAvl(Catalog->CatClients[i]);
		Catalog->CatClients[i] = NULL;
	}
}

/* Testa se um cliente tem a estrutura correta.*/
int testClient(CLIENT client){
	int num = atoi(client->string+LETRAS_C),r=0;
	if(isupper(client->string[0]) && (num>=1000) && (num<=5000))r++;
	return r;
}

/* GETS E SETS */

char* getClient(CLIENT clie){
	return clie->string;
}

CLIENT setClient(char* string){
	CLIENT client = malloc(sizeof(struct client));
	client->string = malloc(SIZE_CLIENTS);
	strcpy(client->string,string);
	return client;
}

/* ########################################## APAGAR ###################################################

int printCatClients(CATALOG_CLIENTS Catalog){

	int i;

	if(Catalog != NULL)
		for(i=0;i<SIZE_ABC;i++){
			printf("LETRA %c=====\n", 'A'+i); 
			printMyAvl(Catalog->CatClients[i]); 
		}
	return 0;
}

*/

/* #################################### QUERIES ######################################################## */

