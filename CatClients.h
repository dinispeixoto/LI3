#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_CLIENTS 6
#define LETRAS_C 1
#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include "avl.h"

typedef struct client *CLIENT;
typedef struct catc *CATALOG_CLIENTS; 
typedef struct conjClie *GROUP_CLIENTS;

CATALOG_CLIENTS initClients();
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS, CLIENT);
int existClient(CATALOG_CLIENTS, CLIENT);
int totalClientsLetter(CATALOG_CLIENTS,char);
int totalClients(CATALOG_CLIENTS);
int testClient(CLIENT);

/* GETS & SETS */
Avl getC(CATALOG_CLIENTS, int);
char* getClient(CLIENT clie);
CLIENT setClient(char* string);

/* APAGAR
int printCatClients(CATALOG_CLIENTS);
*/

#endif