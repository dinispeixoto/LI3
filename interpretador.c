
#include "interpretador.h"

#define ELEM_PER_PAGE 20

void menu(){

	printTop(0);
	printf("	1. Fazer leitura dos ficheiros.\n");
	printf("	2. Apresentar Catálogo de Produtos.\n");
	printf("	3. Total de vendas e total facturado de um produto.\n");
	printf("	4. Produtos não comprados.\n");
	printf("	\n 									0. Sair.\n\n");
	printf("______________________________________________________________________________________________\n\n\n");
}

void interpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){

	char buffer[1]; int size_input;

	printf("\e[2J\e[H"); 
	menu();
	printf("	Introduza o número do comando desejado: ");
	size_input = scanf("%s",buffer);
	
	if(buffer[0] == '0') exit(0);

	else if(buffer[0] == '1')
		readFiles(CatClients,CatProducts,Sales,fact); 

	else if(buffer[0] == '2') 
		readCatalog(CatClients,CatProducts,Sales,fact);
			
	else if(buffer[0] == '4')
		productsNSold(CatClients,CatProducts,Sales,fact); /* FALTA DAR ERRO SE NÃO TIVERMOS LIDO PRIMEIRO && OUTROS ERROS DA FUNÇÃO && APRESENTAR POR PÁGINAS */

	else{
		printf("	Este comando não é válido!\n");
		sleep(1);
		printf("\e[2J\e[H");
		interpretador(CatClients,CatProducts,Sales,fact);
	}
}

/* QUERIE 1 */

void readFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){
	
	char rep[1];
	int size_input;

	printf("\e[2J\e[H"); 
	printTop(1);
	putchar('\n');


	getFile(CatClients,CatProducts,Sales,fact);
	putchar('\n');
	printf(" 								0.Sair\n\n");
	printf("______________________________________________________________________________________________\n");

	printf("\n	Deseja continuar (S/N)? ");
	size_input = scanf("%s",rep);

	if(rep[0] == 'S' || rep[0] == 's')
		interpretador(CatClients,CatProducts,Sales,fact);
	else exit(0);	
}

/* QUERIE 2 */

void readCatalog(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){

	GROUP_PRODUCTS group;
	char rep;
	int page,totalPages,size_input;

	printf("\e[2J\e[H");
	
	testMemory(CatClients,CatProducts,Sales,fact,"O Catálogo de Produtos");

	printTop(2);
	printf("	Letra que deseja procurar: ");
	size_input = scanf("\n%c",&rep);

	if(rep >= 'A' && rep <= 'Z'){
		
		group = productsLetter(CatProducts,rep);
		totalPages = calculatePages(group,ELEM_PER_PAGE);
		
		putchar('\n');

		printCatalogProds(group,1,totalPages,getGroupProdSize(group));

		do{
			printf("	Escolha uma página: ");
			size_input = scanf("\n%d",&page);

			if(page > 0 && page <= totalPages){
				printf("\e[2J\e[H");

				printTop(2);
				printCatalogProds(group,page,totalPages,getGroupProdSize(group));
			}
			else if(page == 0) interpretador(CatClients,CatProducts,Sales,fact);
			else{
				printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
				sleep(2);
				printf("\e[2J\e[H");
				readCatalog(CatClients,CatProducts,Sales,fact);
			}
		}
		while(page != 0);

	}
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		sleep(2);
		printf("\e[2J\e[H");
		readCatalog(CatClients,CatProducts,Sales,fact);
	}
}

void printCatalogProds(GROUP_PRODUCTS group,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<ELEM_PER_PAGE;i++){
		index = i + (ELEM_PER_PAGE*(page-1));
		if(index < totalElements)
			printf("				%s\n",getProduct(getGroupProd(group)[index]));
	}
	printf("\n	 									0. Sair\n");
}


/* QUERIE 4 */
void productsNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact){

	char rep;
	int filial,contador=0,totalPages,size_input,error,i;
	GROUP_PRODUCTS group;


	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,Sales,fact,"O Catálogo de Produtos não vendidos");

	printTop(4);

	printf("	Deseja os produtos totais ou por filial? T/F ");
	size_input = scanf("\n%c",&rep);

	if(rep == 'F'){
		printf("	Qual o filial que deseja: ");
		size_input = scanf("\n%d",&filial);
		group = querie4(fact,&contador,filial);
	}

	else if(rep == 'T'){
		group = querie4(fact,&contador,-1);
	}

	else{
		printf("	\n\n\nPor favor responda somente com T(total) ou F(filial)!\n");
		sleep(3);
		printf("\e[2J\e[H");
		productsNSold(CatClients,CatProducts,Sales,fact);
	}

	totalPages = calculatePages(group,ELEM_PER_PAGE);
	printPageNSold(group,1,totalPages);
	error = printNSold(group,totalPages);


	if(error == -1) productsNSold(CatClients,CatProducts,Sales,fact);
	else if(error == 0) interpretador(CatClients,CatProducts,Sales,fact);
}

void printPageNSold(GROUP_PRODUCTS group,int page,int totalPages){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<ELEM_PER_PAGE;i++){
		index = i+(ELEM_PER_PAGE*(page-1));
		if(index < getGroupProdSp(group))
			printf("	%d | %s\n",index+1,getProduct(getGroupProd(group)[index]));
	}
}

int printNSold(GROUP_PRODUCTS group,int totalPages){

	int rep = 1,size_input,page;

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("\n%d",&page);

		if(page > 0 && page <= totalPages){
			printf("\e[2J\e[H");
			printTop(4);
			printPageNSold(group,page,totalPages);
			}

		else if(page == 0) return 0;
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			sleep(2);
			printf("\e[2J\e[H");
			return -1;
		}
	}
	while(page != 0);
	return rep;
}


/* AUXILIARES */

void testMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,SALES Sales,FACTURACAO fact,char* menuName){
	if(!totalProducts(CatProducts)){
		printf("\n 		 %s encontra-se vazio de momento. \n",menuName);
		printf("		 Experimente usar primeiro o comando de leitura.\n\n");
		sleep(5);
		printf("\e[2J\e[H");
		interpretador(CatClients,CatProducts,Sales,fact);
	}
}

int calculatePages(GROUP_PRODUCTS group,int elemPerPage){
	int totalPages = (getGroupProdSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getGroupProdSp(group)) totalPages++;
	return totalPages;
}

void printTop(int i){

	printf("______________________________________________________________________________________________\n\n");

	switch(i){
		case 0: /* MENU */ 
			printf("	                                GEREVENDAS                                              \n");
			break;

		case 1: /* LEITURA DE FICHEIROS*/
			printf("	                                LEITURA DE FICHEIROS                                     \n");
			break;

		case 2:  /* CATÁLOGO DE PRODUTOS */
			printf("	                                CATÁLOGO DE PRODUTOS                                      \n");
			break;

		case 4:
			printf("	                                PRODUTOS NÃO VENDIDOS                                     \n");
			break;
	}
	printf("______________________________________________________________________________________________\n");
	printf("\n\n");
}