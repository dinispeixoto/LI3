#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_ABC 26 /* abecedário */
#define SIZE_BUFFER 64

#include <unistd.h>
#include <fcntl.h>
#include "avl.h"

typedef struct client *Client;
typedef struct catc *CATALOG_CLIENTS; 
typedef struct conjClie *GROUP_CLIENTS;

CATALOG_CLIENTS initClients();
CATALOG_CLIENTS insertClient(CATALOG_CLIENTS, Client);
CATALOG_CLIENTS valCli(FILE *,CATALOG_CLIENTS,int *);
int printCatClients(CATALOG_CLIENTS);
int existClient(CATALOG_CLIENTS, Client);
int totalClientsLetter(CATALOG_CLIENTS,char);
int totalClients(CATALOG_CLIENTS);
Avl getC(CATALOG_CLIENTS, int);

#endif