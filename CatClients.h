#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_ABC 26 // abecedário 

#include <unistd.h>
#include <fcntl.h>
#include "avl.h"

typedef struct client *CATOLOG_CLIENTS; 

CATOLOG_CLIENTS initClients();
int printCatClients(CATOLOG_CLIENTS);
CATOLOG_CLIENTS valCli(FILE *, CATOLOG_CLIENTS ,int *);
Avl getC(CATOLOG_CLIENTS , int );

#endif