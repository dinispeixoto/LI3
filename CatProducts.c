#include "avl.h"
#include "CatProducts.h"


struct catp {
	MY_AVL CatProducts[SIZE_ABC];
};

struct conjProds{
	PRODUCT* GroupProd;
};

struct product {
	char* string;
};


CATALOG_PRODUCTS initProducts(){
	
	int i;
	CATALOG_PRODUCTS Catalog = malloc (sizeof(struct catp));
	for(i=0;i<SIZE_ABC;i++)	Catalog->CatProducts[i] = initMyAvl();
	return Catalog;
}


CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){

	int index = prod->string[0]-'A';
	Catalog->CatProducts[index] = insertMyAvl(Catalog->CatProducts[index],prod->string);
	return Catalog;
}


/* criar um typedef BOOL */
int existProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod){
	int exist;
	int index = prod->string[0]-'A';
	exist = existMyAvl(Catalog->CatProducts[index],prod->string);
	return exist;
}

int totalProductsLetter(CATALOG_PRODUCTS Catalog,char letter){
	int index = letter - 'A';
	return totalElements(Catalog->CatProducts[index]);
} 

int totalProducts(CATALOG_PRODUCTS Catalog){

	char letter; int total=0;
	for(letter = 'A'; letter <= 'Z';letter++)
		total+=totalProductsLetter(Catalog,letter);
	return total;
}

int printCatProducts(CATALOG_PRODUCTS Catalog){

	int i;

	if(Catalog != NULL)
		for(i=0;i<SIZE_ABC;i++)  {
			printf("LETRA %c=====\n", 'A'+i); 
			printMyAvl(Catalog->CatProducts[i]); 
	}
	return 0;
}

void removeCatProds(CATALOG_PRODUCTS Catalog){
	int i;
	for(i=0;i<SIZE_ABC;i++) {
		removeMyAvl(Catalog->CatProducts[i]);
		Catalog->CatProducts[i] = NULL;
	}
}

CATALOG_PRODUCTS valProd(FILE *file, CATALOG_PRODUCTS Catalog ,int *validated){

	char buffer[SIZE_BUFFER];
	PRODUCT line = malloc(sizeof(struct product));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line->string = strtok(buffer,"\r\n");
		Catalog = insertProduct(Catalog,line);
		(*validated)++;
	}
		
	return Catalog;
}

/* Testa os produtos */
int testProduct (PRODUCT prod){
   int num = atoi(prod->string+LETRAS_P),i;

   for(i=0;i<LETRAS_P;i++)
       if(!(isupper(prod->string[i]))) return 0;

   if(!((num>=1000) && (num<=1999))) return 0;
  
   return 1;
}


char* getProductString(PRODUCT prod){
	return prod->string;
}

PRODUCT setProductString(char* string){
	PRODUCT prod = malloc(sizeof(struct product));
	prod->string = malloc(SIZE_PRODUCTS);
	strcpy(prod->string,string);
	return prod;
}
