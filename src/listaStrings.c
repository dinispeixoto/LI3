#include "headers/listaStrings.h"

/* Estrutura de uma Lista de Strings. */
struct lista{
	int sp;						/* Número de elementos da lista. */
	int size;					/* Tamanho alocado para a lista. */
	int sizeElement;			/* Tamanho de cada string da lista. */
	STRING* elements;			/* Lista de elementos. */
};

/* Estrutura de uma Página. */
struct page{	
	int sp;						/* Número de elementos da página. */
	int pageSize;				/* Tamanho máximo de elementos numa página.*/
	int sizeElement;			/* Tamanho de cada string contida na página. */
	STRING* elements;			/* Lista de elementos da página. */
};

/* Estrutura de uma String. */
struct string{
	char* string;				/* String. */
};

/*Liberta espaço de uma estrutura LISTA_STRINGS.*/
void freeListaStr(LISTA_STRINGS ls){
	int i;

	for(i=0;i<ls->sp;i++){
		free(ls->elements[i]->string);
		free(ls->elements[i]);
	}
	free(ls->elements);
	free(ls);
	ls=NULL;
}

/* Inicializar uma Lista de Strings. */
LISTA_STRINGS initListaStrings(int size,int sizeElement){
	int i;
	LISTA_STRINGS lista = malloc(sizeof(struct lista));	
	lista->elements = malloc(sizeof(STRING) * size);
	for(i=0;i<size;i++){
		lista->elements[i]=malloc(sizeof(struct string));
		lista->elements[i]->string=malloc(sizeElement);
	}
	lista->sp = 0;
	lista->size = size;
	lista->sizeElement=sizeElement;
	return lista;
}

/* Inicializar uma Página. */
PAGE initPage(int page_size,int sizeElement){
	int i;
	PAGE page = malloc(sizeof(struct page));	
	page->elements = malloc(sizeof(STRING) * page_size);
	for(i=0;i<page_size;i++){
		page->elements[i]=malloc(sizeof(struct string));
		page->elements[i]->string=malloc(sizeElement);
	}
	page->sp = 0;
	page->pageSize = page_size;
	page->sizeElement = sizeElement;
	return page;
}

/* Actualizar uma página com parte de informação da Lista de Strings. */
PAGE updatePage(LISTA_STRINGS lista,int begin,int sizeElement,int page_size){
	int i,j = begin;
	PAGE page = initPage(page_size,sizeElement);
	for(i=0;i<page_size;i++,j++)
		if(lista->elements[j]!=NULL)
			page->elements[i] = lista->elements[j];
		else break;
	return page;
}

/* Re-alocar memória para a Lista de Strings. */
LISTA_STRINGS reallocListaStrings(LISTA_STRINGS lista){	
	int i;
	if (lista->sp > (lista->size*3)/4) {
		lista->size *= 2;
		lista->elements = realloc(lista->elements,lista->size*sizeof(STRING));
		for(i=(lista->size)/2;i<lista->size;i++){
			lista->elements[i]=malloc(sizeof(struct string));
			lista->elements[i]->string=malloc(lista->sizeElement);
		}
	}	
	return lista;
}

/* Adicionar um elemento à Lista de Strings. */
LISTA_STRINGS addListaStrings(LISTA_STRINGS ls,int posicao, char* elem){
	strcpy(ls->elements[posicao]->string,elem);
	ls->sp++;
	return ls;
}

/* Remover um elemento da Lista de Strings. */
LISTA_STRINGS removeListaStrings(LISTA_STRINGS ls,char* elem){
	int i;
	for(i=0;i<ls->sp;i++){
		if(strcmp(ls->elements[i]->string,elem)){
			strcpy(ls->elements[i]->string,ls->elements[i+1]->string);
			strcpy(elem,ls->elements[i]->string);
		}
	}
	ls->sp--;
	return ls;
}

/*Função que junta duas LISTA_STRINGS, removendo elementos iguais.*/
LISTA_STRINGS mergeList(LISTA_STRINGS ls1, LISTA_STRINGS ls2){
	int i=0,j=0,cmp;
	int tam=ls1->sp+ls2->sp;
	LISTA_STRINGS ls=initListaStrings(1,ls1->sizeElement);
	while(ls->sp<tam){
		if(i<ls1->sp && j<ls2->sp){
			cmp=strcmp(ls1->elements[i]->string,ls2->elements[j]->string);
			if(cmp==0){
				strcpy(ls->elements[ls->sp]->string,ls1->elements[i]->string);
				ls->sp++;
				reallocListaStrings(ls);
				i++;
				j++;
				tam--;
			}
			else if(cmp<0){
				strcpy(ls->elements[ls->sp]->string,ls1->elements[i]->string);
				ls->sp++;
				reallocListaStrings(ls);
				i++;
			}
			else {
				strcpy(ls->elements[ls->sp]->string,ls2->elements[j]->string);
				ls->sp++;
				reallocListaStrings(ls);
				j++;
			}
		}	
		else{ 
			if(i==ls1->sp){
				while(ls->sp<tam){
					strcpy(ls->elements[ls->sp]->string,ls2->elements[j]->string);
					ls->sp++;
					reallocListaStrings(ls);
					j++;
				}
			}
			else {
				while(ls->sp<tam){
					strcpy(ls->elements[ls->sp]->string,ls1->elements[i]->string);
					ls->sp++;
					reallocListaStrings(ls);
					i++;
				}
			}
		}
	}
	return ls;
}


/* GETS E SETS */
int getListaSize(LISTA_STRINGS lista){
	return lista->size;
}

int getListaSp(LISTA_STRINGS lista){
	return lista->sp;
}

char* getListaString(LISTA_STRINGS lista,int index){
	return lista->elements[index]->string;
}

void setListaSize(LISTA_STRINGS lista,int size){
	lista->size = size;
}

STRING* getListaElements(LISTA_STRINGS lista){
	return lista->elements;
}

void setListaSp(LISTA_STRINGS lista,int sp){
	lista->sp = sp;
}

int getPageSize(PAGE page){
	return page->pageSize;
}

char* getPageElement(PAGE page,int index){
	return page->elements[index]->string;
}
