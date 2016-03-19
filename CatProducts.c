#include "CatProducts.h"
#include "avl.h"

Avl* initProducts(){

	int i;

	Avl* CatProducts = malloc (sizeof(struct Avl*)*SIZE_ABC);
	for(i=0;i<SIZE_ABC;i++)	CatProducts[i]=NULL;
	return CatProducts;
}

void printCatProducts(Avl estrutura){

	if(estrutura==NULL) printf("NULL\n");
	else{
        printCatProducts(estrutura->left);        
		printf("%s\n",estrutura->code);
		printCatProducts(estrutura->right);
	}
}

Avl* valProd(FILE *file, Avl* estrutura ,int *validated){

	char buffer[SIZE_BUFFER],*line;
	int index;

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

		line=strtok(buffer,"\r\n");

		index = line[0] - 'A';
		estrutura[index] = insert(estrutura[index],line);
		(*validated)++;
	}
		
	return estrutura;
}
