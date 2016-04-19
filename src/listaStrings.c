#include "headers/listaStrings.h"

struct lista{
	int sp;
	int size;
	int sizeElement;
	STRING* elements;
};

struct string{
	char* string;
};

LISTA_STRINGS initListaStrings(int size,int sizeElement){
	int i;
	LISTA_STRINGS lista = malloc(sizeof(struct lista));	
	lista->elements = malloc (sizeof(STRING) * size);
	for(i=0;i<size;i++){
		lista->elements[i]=malloc(sizeof(struct string));
		lista->elements[i]->string=malloc(sizeElement);
	}
	lista->sp = 0;
	lista->size = size;
	lista->sizeElement=sizeElement;
	return lista;
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

/*void setListaElement(LISTA_STRINGS lista,PRODUCT* p){
	gp->GroupProd=p;
}*/

/*
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
}*/
