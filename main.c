#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readFiles.h"
#include "facturacao.h"
/*#include "interpretador.h"*/
#include "filiais.h"


/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	

	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO fact = initFact();
	FILIAIS filiais = initFiliais();

	interpretador(CatClients,CatProducts,filiais,fact);
	/*getFile(CatClients,CatProducts,filiais,fact);*/
	return 0;
}