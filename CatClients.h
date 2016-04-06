#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_CLIENTS 6
#define LETRAS_C 1
#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

typedef struct client *CLIENT;
typedef struct catc *CATALOG_CLIENTS; 
typedef struct conjClie *GROUP_CLIENTS;

CATALOG_CLIENTS initClients();
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS, CLIENT);
CATALOG_CLIENTS valCli(FILE *,CATALOG_CLIENTS,int *);
int printCatClients(CATALOG_CLIENTS);
int existClient(CATALOG_CLIENTS, CLIENT);
int totalClientsLetter(CATALOG_CLIENTS,char);
int totalClients(CATALOG_CLIENTS);
int testClient(CLIENT);
Avl getC(CATALOG_CLIENTS, int);
char* getClientString(CLIENT clie);
CLIENT setClientString(char* string);


#endif