#include "avl.h"
#include "CatProducts.h"

#define DEFAULT_SIZE 10

struct catp {
	MY_AVL CatProducts[SIZE_ABC];
};

struct conjProds{
	int sp;
	int size;
	PRODUCT* GroupProd;
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

/* Insere um produto no respectivo catálogo. */
CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){

	int index = prod->string[0]-'A';
	Catalog->CatProducts[index] = insertMyAvl(Catalog->CatProducts[index],prod->string);
	return Catalog;
}

/* Verifica se um produto existe no catálogo.*/
BOOL existProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){
	int exist;
	int index = prod->string[0]-'A';
	exist = existMyAvl(Catalog->CatProducts[index],prod->string);
	return exist;
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
	for(i=0;i<SIZE_ABC;i++) {
		removeMyAvl(Catalog->CatProducts[i]);
		Catalog->CatProducts[i] = NULL;
	}
}

/* Testa se um produto tem a estrutura correta.*/
int testProduct (PRODUCT prod){
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

PRODUCT setProduct(char* string){
	PRODUCT prod = malloc(sizeof(struct product));
	prod->string = malloc(SIZE_PRODUCTS);
	strcpy(prod->string,string);
	return prod;
}

/* ########################################## APAGAR ###########################################

int printCatProducts(CATALOG_PRODUCTS Catalog){

	int i;

	if(Catalog != NULL)
		for(i=0;i<SIZE_ABC;i++)  {
			printf("LETRA %c=====\n", 'A'+i); 
			printMyAvl(Catalog->CatProducts[i]); 
	}
	return 0;
}
*/

/* #################################### QUERIES ######################################################## */

GROUP_PRODUCTS initGroupProducts(){
	
	GROUP_PRODUCTS group = malloc(sizeof(struct conjProds));	
	group->GroupProd = malloc (sizeof(PRODUCT) * DEFAULT_SIZE);
	group->sp = 0;
	group->size = DEFAULT_SIZE;

	return group;
}

GROUP_PRODUCTS productsLetter(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	GROUP_PRODUCTS group = initGroupProducts();
	MY_AVL a = Catalog->CatProducts[index];
	Avl tree = getAvl(a);
	travessia(tree,0,group);
	return group;
}

void travessia(Avl a,int index,GROUP_PRODUCTS array){
	if(a!=NULL){
		travessia(getAvlLeft(a),index,array);
		PRODUCT prod = setProduct(getAvlCode(a));
		array = toGroup(array,prod);
		index++;
		travessia(getAvlRight(a),index,array);
	}
}

GROUP_PRODUCTS toGroup(GROUP_PRODUCTS array,PRODUCT prod){	
	if (array->sp == array->size) {
		array->size *= 2;
		array->GroupProd = realloc (array->GroupProd, array->size*sizeof(PRODUCT));
	}	
	array->GroupProd[array->sp] = prod;
	array->sp++;
	return array;
}

int getGroupProdSize(GROUP_PRODUCTS a){
	return a->sp;
}

PRODUCT* getGroupProd(GROUP_PRODUCTS a){
	return a->GroupProd;
}



/*
void insertArray (char** array,Avl estrutura,int *a){
	
	if(estrutura->left==NULL && estrutura->right==NULL){
		array[*a]=estrutura->code;
		(*a)++;
	}

	else if(estrutura->left==NULL){ 
		insertArray(array,estrutura->right,a);
		array[*a]=estrutura->code;
		(*a)++;
	}

	else { 
		insertArray(array,estrutura->left,a);
		array[*a]=estrutura->code;
		(*a)++;
		if(estrutura->right!=NULL)insertArray(array,estrutura->right,a);
	}
}
*/