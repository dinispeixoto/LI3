#include "CatProducts.h"
#include "avl.h"

struct catp {
    Avl cat[SIZE_ABC];
};

CATOLOG_PRODUCTS initProducts(){

	int i;
	CATOLOG_PRODUCTS CatPro = malloc (sizeof(struct catp));
	for(i=0;i<SIZE_ABC;i++)	(CatPro->cat[i])=NULL;
	return CatPro;
}


int printCatProducts(CATOLOG_PRODUCTS estrutura){

    char* array[171008];
    char* buf;
    int i,a=0;
    buf=malloc(2);

    for(i=0;i<SIZE_ABC;i++){
	insereArray(array,estrutura->cat[i],&a);
    }

    for(i=0;i<20;i++){
        printf("%s\n",array[i]);
    }

	return 0;
}

CATOLOG_PRODUCTS valProd(FILE *file, CATOLOG_PRODUCTS estrutura ,int *validated){

	char buffer[SIZE_BUFFER],*line;
	int index;

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

		line=strtok(buffer,"\r\n");
		
		index = line[0] - 'A';
		estrutura->cat[index] = insert(estrutura->cat[index],line);
		(*validated)++;
	}
		
	return estrutura;
}

Avl getP (CATOLOG_PRODUCTS c, int x){

    return c->cat[x];
}

