#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

#define SIZE_ABC 26 // abecedário 

#include "avl.h"

Avl* initClients();
void printCatClients(Avl);
Avl* valCli(FILE *, Avl* ,int *);

#endif