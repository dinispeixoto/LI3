#include "headers/CatProducts.h"

struct catp {
	MY_AVL CatProducts[SIZE_ABC];
};

struct product {
	char* string;
};

/* Inicializa o Catálogo de Produtos. */
CATALOG_PRODUCTS initProducts(){
	
	int i;
	CATALOG_PRODUCTS Catalog = malloc (sizeof(struct catp));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatProducts[i] = initMyAvl();
	return Catalog;
}

void freeProduct(PRODUCT prod){
	free(prod->string);
	free(prod);
}

/* Insere um produto no respectivo catálogo. */
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){

	int index = prod->string[0]-'A';
	Catalog->CatProducts[index] = insertMyAvl(Catalog->CatProducts[index],prod->string,NULL,1);
	return Catalog;
}

/* Verifica se um produto existe no catálogo.*/
BOOL existProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){
	int exist,index;
	if(prod->string[0] >= 'A' && prod->string[0] <= 'Z' ){
		index = prod->string[0]-'A';
		exist = existMyAvl(Catalog->CatProducts[index],prod->string);
		return exist;
	} 
	else return FALSE;
}

/* Conta quantos produtos existem começados por uma determinada letra no catálogo.*/
int totalProductsLetter(CATALOG_PRODUCTS Catalog,char letter){
	int index = letter - 'A';
	return totalElements(Catalog->CatProducts[index]);
} 

/* Conta o total de produtos no catálogo. */
int totalProducts(CATALOG_PRODUCTS Catalog){
	char letter; int total=0;
	for(letter = 'A'; letter <= 'Z';letter++)
		total+=totalProductsLetter(Catalog,letter);
	return total;
}

/* Limpa o catálogo de produtos. */
void removeCatProds(CATALOG_PRODUCTS Catalog){
	int i;
	if(Catalog){
		for(i=0;i<SIZE_ABC;i++) {
			removeMyAvl(Catalog->CatProducts[i],NULL);
			Catalog->CatProducts[i] = NULL;
		}
		free(Catalog);
	}
}

/* Testa se um produto tem a estrutura correta.*/
BOOL testProduct (PRODUCT prod){
   int num = atoi(prod->string+LETRAS_P),i;
   for(i=0;i<LETRAS_P;i++)
       if(!(isupper(prod->string[i]))) return 0;
   if(!((num>=1000) && (num<=1999))) return 0;
   return 1;
}

/* GETS E SETS */

char* getProduct(PRODUCT prod){
	return prod->string;
}

MY_AVL getP(CATALOG_PRODUCTS p, int x){
	return p->CatProducts[x];
}

PRODUCT setProduct(char* string){
	PRODUCT prod = malloc(sizeof(struct product));
	prod->string = malloc(SIZE_PRODUCTS);
	strcpy(prod->string,string);
	return prod;
}
