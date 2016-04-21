#ifndef __READFILES_H__
#define __READFILES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "facturacao.h"		
#include "filial.h"

int getFile(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,char*,char*,char*);
void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);

#endif