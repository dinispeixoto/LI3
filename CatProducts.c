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
	Catalog->CatProducts[index] = insertMyAvl(Catalog->CatProducts[index],prod->string,NULL);
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
MY_AVL getP(CATALOG_PRODUCTS p, int x){
	return p->CatProducts[x];
}

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

void printGP(GROUP_PRODUCTS gp, int size){
	int i;
	for(i=0;i<size;i++)  
			printf("%s\n",gp->GroupProd[i]->string); 
}*/


/* #################################### QUERIES ######################################################## */

GROUP_PRODUCTS initGroupProducts(int size){
	int i;
	GROUP_PRODUCTS group = malloc(sizeof(struct conjProds));	
	group->GroupProd = malloc (sizeof(PRODUCT) * size);
	for(i=0;i<size;i++){
		group->GroupProd[i]=malloc(sizeof(struct product));
		group->GroupProd[i]->string=malloc(SIZE_PRODUCTS);
	}
	group->sp = 0;
	group->size = size;

	return group;
}


GROUP_PRODUCTS toGroup2(GROUP_PRODUCTS array){	
	int i;
	if (array->sp > (array->size*3)/4) {
		array->size *= 2;
		array->GroupProd = realloc(array->GroupProd,array->size*sizeof(PRODUCT));
		for(i=(array->size)/2;i<array->size;i++){
			array->GroupProd[i]=malloc(sizeof(struct product));
			array->GroupProd[i]->string=malloc(SIZE_PRODUCTS);
		}
	}	
	return array;
}

PRODUCT* insereP(PRODUCT* list,int size,int* sp,char* p){
	int i,cmp=0;
	PRODUCT aux=malloc(sizeof(struct product));
	aux->string=malloc(SIZE_PRODUCTS);
	for(i=0;i<=(*sp);i++){
		if(i==(*sp)){
			strcpy(list[i]->string,p);
		}
		else{
			cmp=strcmp(list[i]->string,p);
			if(cmp>=0){
				strcpy(aux->string,list[i]->string);
				strcpy(list[i]->string,p);
				strcpy(p,aux->string);
			}
		}
	}
	(*sp)++;
	free(aux);
	return list;
}

void setGroupProdSize(GROUP_PRODUCTS gp,int x){
	gp->size=x;
}

void setGroupProd(GROUP_PRODUCTS gp,PRODUCT* p){
	gp->GroupProd=p;
}

int getGroupProdSize(GROUP_PRODUCTS a){
	return a->size;
}

int getGroupProdSp(GROUP_PRODUCTS a){
	return a->sp;
}

void setGroupProdSp(GROUP_PRODUCTS a,int x){
	 a->sp=x;
}

PRODUCT* getGroupProd(GROUP_PRODUCTS a){
	return a->GroupProd;
}
