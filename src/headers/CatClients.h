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
void setGroupClieSize(GROUP_CLIENTS ,int );
void setGroupClie(GROUP_CLIENTS ,CLIENT* );
int getGroupClieSize(GROUP_CLIENTS );
int getGroupClieSp(GROUP_CLIENTS );
void setGroupClieSp(GROUP_CLIENTS ,int );
int getJC(GROUP_CLIENTS );
void setJC(GROUP_CLIENTS ,int );
CLIENT* getGroupClie(GROUP_CLIENTS );


GROUP_CLIENTS initGroupClients(int );
GROUP_CLIENTS reallocGROUP_CLIENTS(GROUP_CLIENTS );
CLIENT* insertGROUP(CLIENT* list,int posicao,char* c);
CLIENT* insertGROUP_CLIENTS(CLIENT* ,int* ,int ,char*);
CLIENT* removeGROUP_CLIENTS(CLIENT* ,int* ,char*);

/* APAGAR
int printCatClients(CATALOG_CLIENTS);
*/

#endif