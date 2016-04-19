#ifndef __LISTASTRINGS_H__
#define __LISTASTRINGS_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct lista *LISTA_STRINGS;

typedef struct string *STRING;

LISTA_STRINGS initListaStrings(int,int);

LISTA_STRINGS reallocListaStrings(LISTA_STRINGS);

LISTA_STRINGS addListaStrings(LISTA_STRINGS,int,char*);

LISTA_STRINGS removeListaStrings(LISTA_STRINGS,char*);

int getListaSize(LISTA_STRINGS lista);
int getListaSp(LISTA_STRINGS);
char* getListaString(LISTA_STRINGS lista,int index);
void setListaSize(LISTA_STRINGS lista,int size);
STRING* getListaElements(LISTA_STRINGS lista);

void printLS(LISTA_STRINGS ls);

#endif