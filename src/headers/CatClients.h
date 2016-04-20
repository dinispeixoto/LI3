#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_CLIENTS 6
#define LETRAS_C 1
#define SIZE_ABC 26 /* abecedário */

#include "avl.h"

typedef struct client *CLIENT;
typedef struct catc *CATALOG_CLIENTS; 

CATALOG_CLIENTS initClients();
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS, CLIENT);
BOOL testClient(CLIENT); 
BOOL existClient(CATALOG_CLIENTS, CLIENT);
void freeClient(CLIENT);
void removeCatClients(CATALOG_CLIENTS);
int totalClientsLetter(CATALOG_CLIENTS,char);
int totalClients(CATALOG_CLIENTS);

/* GETS & SETS */
char* getClientIndex(CATALOG_CLIENTS,int);
char* getClient(CLIENT);
CLIENT setClient(char*);
MY_AVL getC(CATALOG_CLIENTS,int);

#endif