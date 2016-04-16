#include "headers/CatProducts.h"

struct catp {
	MY_AVL CatProducts[SIZE_ABC];
};

struct conjProds{
	int sp;
	int size;
	int jeito;
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

int getJ(GROUP_PRODUCTS a){
	return a->jeito;
}


void setJ(GROUP_PRODUCTS a,int x){
	a->jeito=x;
}

PRODUCT* getGroupProd(GROUP_PRODUCTS a){
	return a->GroupProd;
}

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
	group->jeito=0;

	return group;
}

void travessia(Avl a,int index,GROUP_PRODUCTS array){
	PRODUCT prod;
	if(a!=NULL){
		travessia(getAvlLeft(a),index,array);
		prod = setProduct(getAvlCode(a));
		array = toGroup(array,prod);
		index++;
		travessia(getAvlRight(a),index,array);
	}
}

GROUP_PRODUCTS toGroup(GROUP_PRODUCTS array,PRODUCT prod){	
	array->GroupProd[array->sp] = prod;
	array->sp++;
	return array;
}

GROUP_PRODUCTS reallocGROUP_PRODUCTS(GROUP_PRODUCTS array){	
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

PRODUCT* insertGROUP_P(PRODUCT* list,int posicao,char* c){
	strcpy(list[posicao]->string,c);
	return list;
}

PRODUCT* insertGROUP_PRODUCTS(PRODUCT* list,int* sp,int w,char* p){
	int i,cmp=0,a;
	char* string=malloc(SIZE_PRODUCTS);
	if(w>0) a=*sp;	
	else a=0;
	for(i=a;i<=(*sp);i++){
		if(i==(*sp)){
			strcpy(list[i]->string,p);
		}
		else{
			cmp=strcmp(list[i]->string,p);
			if(cmp>=0){
				strcpy(string,list[i]->string);
				strcpy(list[i]->string,p);
				strcpy(p,string);
			}
		}
	}
	(*sp)++;
	free(string);
	return list;
}
