
#include "interpretador.h"

void menu(){

	printf("______________________________________________________________________________________________\n");
	putchar('\n');
	printf("	                                    MENU                                                  \n");
	putchar('\n'); 
	printf("______________________________________________________________________________________________\n");
	putchar('\n');
	printf("	1. Fazer leitura dos ficheiros.\n");
	printf("	2. Apresentar Catálogo de Produtos.\n");
	printf("	0. Sair.\n");
	putchar('\n');

}

void interpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){

	char buffer;

	system("clear");
	menu();
	printf("	Introduza o número do comando desejado: ");
	scanf("\n%c",&buffer);
	
	if(buffer == '0') exit(1);

	else if(buffer == '1'){
		readFiles(CatClients,CatProducts,Sales,fact); 
	}

	else if(buffer == '2') 
		readCatalog(CatClients,CatProducts,Sales,fact);
			

	else{
		printf("	Este comando não é válido!\n");
		sleep(1);
		system("clear");
		menu();
		interpretador(CatClients,CatProducts,Sales,fact);
	}

}


void readFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){
	
	char rep;
	putchar('\n');
	getFile(CatClients,CatProducts,Sales,fact);

	putchar('\n');
	printf("	Deseja continuar? S ou N? ");
	scanf("\n%c",&rep);

	if(rep == 'S')
		interpretador(CatClients,CatProducts,Sales,fact);	
}

void readCatalog(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){

	GROUP_PRODUCTS group;
	char rep;
	int page,totalPages;

	system("clear");
	
	if(!totalProducts(CatProducts)){
		printf("\n	O Catálogo de Produtos encontra-se vazio de momento. Experimente usar primeiro o comando de leitura.\n");
		sleep(5);
		system("clear");
		interpretador(CatClients,CatProducts,Sales,fact);
	}

	printf("______________________________________________________________________________________________\n");
	putchar('\n');
	printf("	                                CATÁLOGO DE PRODUTOS                                      \n");
	putchar('\n'); 
	printf("______________________________________________________________________________________________\n");
	putchar('\n');
	printf("	Letra que deseja procurar: ");
	scanf("\n%c",&rep);

	if(rep >= 'A' && rep <= 'Z'){
		group = productsLetter(CatProducts,rep);
		totalPages = (getGroupProdSize(group)/20);
		if(totalPages*20 < getGroupProdSize(group)) totalPages++;
		putchar('\n');

		printCatalogProds(group,1,totalPages,getGroupProdSize(group));

		do{
			printf("	Escolha uma página: ");
			scanf("\n%d",&page);

			if(page > 0 && page <= totalPages){
				system("clear");
				printf("______________________________________________________________________________________________\n");
				putchar('\n');
				printf("	                                CATÁLOGO DE PRODUTOS                                      \n");
				putchar('\n'); 
				printf("______________________________________________________________________________________________\n");
				putchar('\n');
				printCatalogProds(group,page,totalPages,getGroupProdSize(group));
			}
			else if(page == 0) interpretador(CatClients,CatProducts,Sales,fact);
			else{
				printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
				sleep(2);
				system("clear");
				readCatalog(CatClients,CatProducts,Sales,fact);
			}
		}
		while(page != 0);

	}
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		sleep(2);
		system("clear");
		readCatalog(CatClients,CatProducts,Sales,fact);
	}
}


void printCatalogProds(GROUP_PRODUCTS group,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<20;i++){
		index = i + (20*(page-1));
		if(index < totalElements)
			printf("				%s\n",getProduct(getGroupProd(group)[index]));
	}
	printf("\n	 									0. Sair\n");
}

