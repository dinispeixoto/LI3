#include "headers/listaStrings.h"

struct lista{
	int sp;
	int size;
	int sizeElement;
	STRING* elements;
};

struct page{
	int sp;
	int pageSize;
	int sizeElement;
	STRING* elements;
};

struct string{
	char* string;
};

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

PAGE updatePage(LISTA_STRINGS lista,int begin,int sizeElement,int page_size){
	int i,j = begin;
	PAGE page = initPage(page_size,sizeElement);
	for(i=0;i<page_size;i++,j++)
		if(lista->elements[j]!=NULL)
			page->elements[i] = lista->elements[j];
		else break;
	return page;
}


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

LISTA_STRINGS addListaStrings(LISTA_STRINGS ls,int posicao, char* elem){
	strcpy(ls->elements[posicao]->string,elem);
	ls->sp++;
	return ls;
}

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
