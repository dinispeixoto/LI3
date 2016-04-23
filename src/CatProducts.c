#include "headers/CatProducts.h"

/* Estrutura com um catálogo de produtos. */
struct catp {
	MY_AVL CatProducts[SIZE_ABC];					/* Array de 26 MY_AVL's cada indice deste array corresponde a uma letra do abecedário. */
};

/* Estrutura de um produto. */
struct product {
	char* string;									/* String com o código do produto correspondente. */
};


/* Inicializa o Catálogo de Produtos. */
CATALOG_PRODUCTS initProducts(){
	
	int i;
	CATALOG_PRODUCTS Catalog = malloc (sizeof(struct catp));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatProducts[i] = initMyAvl();
	return Catalog;
}

/* Inicializa a estrutura de um produto. */
PRODUCT initProd(){
	PRODUCT prod = malloc(sizeof(struct product));
	prod->string = NULL;
	return prod;
}

/* Liberta a estrutura de um produto. */
void freeProduct(PRODUCT prod){
	free(prod->string);
	free(prod);
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
	char* new = malloc((strlen(prod->string)+1)*sizeof(char));
	strcpy(new,prod->string);
	return new;
}

MY_AVL getP(CATALOG_PRODUCTS p, int x){
	return p->CatProducts[x];
}

PRODUCT setProduct(PRODUCT p,char* string){
	if(!p->string)
		p->string = malloc((strlen(string)+1)*sizeof(char));
	strcpy(p->string,string);
	return p;
}
