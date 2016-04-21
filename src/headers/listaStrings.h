#ifndef __LISTASTRINGS_H__
#define __LISTASTRINGS_H__

#include <string.h>
#include <stdlib.h>

typedef struct lista *LISTA_STRINGS;
typedef struct page *PAGE;
typedef struct string *STRING;

LISTA_STRINGS initListaStrings(int,int);
PAGE initPage(int page_size,int sizeElement);
PAGE updatePage(LISTA_STRINGS lista,int begin,int sizeElement,int page_size);
LISTA_STRINGS reallocListaStrings(LISTA_STRINGS);
LISTA_STRINGS addListaStrings(LISTA_STRINGS,int,char*);
LISTA_STRINGS removeListaStrings(LISTA_STRINGS,char*);

int getListaSize(LISTA_STRINGS lista);
int getListaSp(LISTA_STRINGS);
char* getListaString(LISTA_STRINGS lista,int index);
void setListaSize(LISTA_STRINGS lista,int size);
STRING* getListaElements(LISTA_STRINGS lista);
int getPageSize(PAGE page);
char* getPageElement(PAGE page,int index);

#endif