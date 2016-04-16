#include "headers/CatClients.h"

struct catc {
	MY_AVL CatClients[SIZE_ABC];
};

struct conjClie{
	int sp;
	int size;
	int jeito;
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
	Catalog->CatClients[index] = insertMyAvl(Catalog->CatClients[index],clie->string,NULL,1);
	return Catalog;
}

/* Verifica se um cliente existe no catálogo.*/
BOOL existClient(CATALOG_CLIENTS Catalog, CLIENT clie){
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
	if(Catalog){
		for(i=0;i<SIZE_ABC;i++) {
			removeMyAvl(Catalog->CatClients[i],NULL);
			Catalog->CatClients[i] = NULL;
		}
		free(Catalog);
	}
}

/* Testa se um cliente tem a estrutura correta.*/
BOOL testClient(CLIENT client){
	int num = atoi(client->string+LETRAS_C),r=0;
	if(isupper(client->string[0]) && (num>=1000) && (num<=5000))r++;
	return r;
}

/* GETS E SETS */

char* getClientIndex(CATALOG_CLIENTS c, int a){
	return getAvlCode(getAvl(c->CatClients[a]));
}

char* getClient(CLIENT clie){
	return clie->string;
}

MY_AVL getC(CATALOG_CLIENTS c, int i){
	return c->CatClients[i];
}

CLIENT setClient(char* string){
	CLIENT client = malloc(sizeof(struct client));
	client->string = malloc(SIZE_CLIENTS);
	strcpy(client->string,string);
	return client;
}


void setGroupClieSize(GROUP_CLIENTS gp,int x){
	gp->size=x;
}

void setGroupClie(GROUP_CLIENTS gp,CLIENT* p){
	gp->GroupClie=p;
}

int getGroupClieSize(GROUP_CLIENTS a){
	return a->size;
}

int getGroupClieSp(GROUP_CLIENTS a){
	return a->sp;
}

void setGroupClieSp(GROUP_CLIENTS a,int x){
	 a->sp=x;
}

int getJC(GROUP_CLIENTS a){
	return a->jeito;
}

void setJC(GROUP_CLIENTS a,int x){
	a->jeito=x;
}

CLIENT* getGroupClie(GROUP_CLIENTS a){
	return a->GroupClie;
}

/* #################################### QUERIES ######################################################## */
GROUP_CLIENTS initGroupClients(int size){
	int i;
	GROUP_CLIENTS group = malloc(sizeof(struct conjClie));	
	group->GroupClie = malloc (sizeof(CLIENT) * size);
	for(i=0;i<size;i++){
		group->GroupClie[i]=malloc(sizeof(struct client));
		group->GroupClie[i]->string=malloc(SIZE_CLIENTS);
	}
	group->sp = 0;
	group->size = size;
	group->jeito=0;

	return group;
}

GROUP_CLIENTS reallocGROUP_CLIENTS(GROUP_CLIENTS array){	
	int i;
	if (array->sp > (array->size*3)/4) {
		array->size *= 2;
		array->GroupClie = realloc(array->GroupClie,array->size*sizeof(CLIENT));
		for(i=(array->size)/2;i<array->size;i++){
			array->GroupClie[i]=malloc(sizeof(struct client));
			array->GroupClie[i]->string=malloc(SIZE_CLIENTS);
		}
	}	
	return array;
}

CLIENT* insertGROUP(CLIENT* list,int posicao,char* c){

	strcpy(list[posicao]->string,c);
	return list;
}


CLIENT* insertGROUP_CLIENTS(CLIENT* list,int* sp,int w,char* c){
	int i,cmp=0,a;
	char* string=malloc(SIZE_CLIENTS);
	if(w>0) a=*sp;	
	else a=0;
	for(i=a;i<=(*sp);i++){
		if(i==(*sp)){
			strcpy(list[i]->string,c);
		}
		else{
			cmp=strcmp(list[i]->string,c);
			if(cmp>=0){
				strcpy(string,list[i]->string);
				strcpy(list[i]->string,c);
				strcpy(c,string);
			}
		}
	}
	(*sp)++;
	free(string);
	return list;
}

CLIENT* removeGROUP_CLIENTS(CLIENT* list,int* sp,char* c){
	int i,cmp=0,a=(*sp);
	for(i=0;i<a;i++){
		cmp=strcmp(list[i]->string,c);
		if(cmp==0){
			if(i!=a-1){
			strcpy(list[i]->string,list[i+1]->string);
			strcpy(c,list[i+1]->string);
			(*sp)--;
			}
			else {
				if(a>(*sp)) free(list[i]);
			}
		}
	}
	return list;
}
