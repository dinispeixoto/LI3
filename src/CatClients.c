#include "headers/CatClients.h"

/* Estrutura com um catálogo de clientes. */
struct catc {
	MY_AVL CatClients[SIZE_ABC];						/* Array de 26 MY_AVL's cada indice deste array corresponde a uma letra do abecedário. */
};

/* Estrutura de um cliente. */
struct client {
	char* string;										/* String com o código do cliente correspondente. */
};


/* Inicializa o Catálogo de Clientes. */
CATALOG_CLIENTS initClients(){

	int i;
	CATALOG_CLIENTS Catalog = malloc (sizeof(struct catc));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatClients[i] = initMyAvl();
	return Catalog;
}

/* Inicializa a estrutura de um cliente. */
CLIENT initClie(){
	CLIENT clie = malloc(sizeof(struct client));
	clie->string = NULL;
	return clie;
}

/* Liberta a estrutura de um cliente */
void freeClient(CLIENT clie){
	free(clie->string);
	free(clie);
}

/* Limpa o catálogo de clientes. */
void removeCatClients(CATALOG_CLIENTS Catalog){
	int i;
	if(Catalog){
		for(i=0;i<SIZE_ABC;i++) {
			removeMyAvl(Catalog->CatClients[i],NULL);
			Catalog->CatClients[i] = NULL;
		}
		free(Catalog);
	}
}

/* Insere um cliente no respectivo catálogo. */
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS Catalog, CLIENT clie){

	int index = clie->string[0]-'A';
	Catalog->CatClients[index] = insertMyAvl(Catalog->CatClients[index],clie->string,NULL,1);
	return Catalog;
}

/* Verifica se um cliente existe no catálogo.*/
BOOL existClient(CATALOG_CLIENTS Catalog, CLIENT clie){
	int exist,index;
	if(clie->string[0] >= 'A' && clie->string[0] <= 'Z' ){
		index = clie->string[0]-'A';
		exist = existMyAvl(Catalog->CatClients[index],clie->string);
		return exist;
	}
	else return FALSE;
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

/* Testa se um cliente tem a estrutura correta.*/
BOOL testClient(CLIENT client){
	int num = atoi(client->string+LETRAS_C),r=0;
	if(isupper(client->string[0]) && (num>=1000) && (num<=5000))r++;
	return r;
}

/* GETS E SETS */
char* getClient(CLIENT clie){
	char* new = malloc((strlen(clie->string)+1)*sizeof(char));
	strcpy(new,clie->string);
	return new;
}

MY_AVL getC(CATALOG_CLIENTS c, int i){
	return c->CatClients[i];
}

CLIENT setClient(CLIENT c,char* string){
	if(!c->string)
		c->string = malloc((strlen(string)+1)*sizeof(char));
	
	strcpy(c->string,string);

	return c;
}