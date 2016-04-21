
#include "headers/interpretador.h"

#define PAGE_SIZE 20
#define BUFFER_SIZE 32

void menu(){

	printTop(0);
	printf("	01. Fazer leitura dos ficheiros.\n");
	printf("	02. Apresentar Catálogo de Produtos.\n");
	printf("	03. Informações sobre as vendas de um produto num determinado mês.\n");
	printf("	04. Produtos não comprados.\n");
	printf("	05. Informações sobre as compras de um determinado cliente.\n");
	printf("	06. Resultados num intervalo de meses.\n");
	printf("	07. Lista de clientes que realizaram compras em todas as filiais.\n");
	printf("	08. Lista de clientes que compraram um produto num determinado filial.\n");
	printf("	09. Produtos mais comprados por um cliente num determinado mês.\n");
	printf("	10. Lista dos N produtos mais comprados ao longo do ano.\n");
	printf("	11. Produtos em que um cliente gastou mais dinheiro.\n");
	printf("	12. Clientes e produtos inactivos.			0. Sair.\n");
	printf("________________________________________________________________________________\n\n");
}

void interpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char buffer[BUFFER_SIZE]; int size_input;
	int num_commando;
	printf("\e[2J\e[H"); 
	menu();
	printf("	Introduza o número do comando desejado: ");
	size_input = scanf("%s",buffer);
	num_commando = atoi(buffer);

	switch(num_commando){

		case 0: 
			exit(0); 
			break;

		case 1: 
			readFiles(CatClients,CatProducts,arrayFiliais,fact); 
			break;

		case 2: 
			readCatalog(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 3: 
			productMonth(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 4: 
			productsNSold(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 5:
			infoClientPurchases(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 6: 
			periodMonths(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 7:
			listClients(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 8:
			listClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 9:
			infoClientMonth(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 10:
			nProductsMostSold(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 11:
			threeMostPurchased(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case 12:
			inactiveClientsProducts(CatClients,CatProducts,arrayFiliais,fact);
			break;
			
		case 13: 
				freeMemory(CatClients,CatProducts,arrayFiliais,fact);
				interpretador(CatClients,CatProducts,arrayFiliais,fact);
				break;

		default:
			printf("	Este comando não é válido!\n");
			backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

}

void backInterpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	printf("\e[2J\e[H");
	interpretador(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}


/* QUERIE 1 */
void backReadFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();getchar();
	printf("\e[2J\e[H");
	readFiles(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}


void readFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	
	char rep,info[BUFFER_SIZE],clientsFile[BUFFER_SIZE],productsFile[BUFFER_SIZE],salesFile[BUFFER_SIZE];
	int size_input,r=1;

	printf("\e[2J\e[H"); 
	printTop(1);
	printf("							0.Voltar\n");
	printf("\n\n");
	printf("	Deseja ler os ficheiros DEFAULT (S/N)?  ");
	size_input = scanf("%s",info);
	if(info[0]=='0' || !size_input) backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	else if(info[0]=='S' && size_input) {
		printf("\e[2J\e[H"); 
		r=getFile(CatClients,CatProducts,arrayFiliais,fact,CLIENTS_FILE,PRODUCTS_FILE,SALES_FILE);
	}
	else if(info[0]=='N' && size_input){
		printf("	Ficheiro de Clientes: ");
		size_input = scanf("%s",clientsFile);
		printf("	Ficheiro de Produtos: ");
		size_input = scanf("%s",productsFile);
		printf("	Ficheiro de Vendas: ");
		size_input = scanf("%s",salesFile);
		printf("\e[2J\e[H"); 
		r=getFile(CatClients,CatProducts,arrayFiliais,fact,clientsFile,productsFile,salesFile);
		if(!r){
			printf("\n\n\n	Os ficheiros que tentou ler não são válidos!\n");
			backReadFiles(CatClients,CatProducts,arrayFiliais,fact);
		}
	}
	else{
		 printf("	Por favor responda apenas com sim (S) ou não (N)!\n");
		 backReadFiles(CatClients,CatProducts,arrayFiliais,fact);
	}

	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n'); 
	rep = getchar();
	if(rep == '0') exit(0);	
	else backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
}



/* QUERIE 2 */

void readCatalog(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos");
	readCatalogIntro(CatClients,CatProducts,arrayFiliais,fact);
}

void readCatalogIntro(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	
	char buffer[BUFFER_SIZE];
	int size_input;

	printTop(2);
	printf("							0.Voltar\n");
	printf("	Letra que deseja procurar: ");
	size_input = scanf("%s",buffer);
	buffer[0] = toupper(buffer[0]);

	if(buffer[0] >= 'A' && buffer[0] <= 'Z' && size_input){
		printf("\e[2J\e[H");
		printTop(2);
		searchPage(CatClients,CatProducts,arrayFiliais,fact,buffer,1);
	}
	else if(buffer[0] == '0' && size_input) backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		getchar();getchar();
		printf("\e[2J\e[H");
		readCatalogIntro(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}
}

void searchPage(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,char* buffer,int actualPage){

	int page,totalPages,size_input,page_begin,page_end;
	char string_page[BUFFER_SIZE];
	LISTA_STRINGS group;
	PAGE page_list;

	group = querie2(CatProducts,buffer[0]);
	totalPages = calculatePagesProducts(group,PAGE_SIZE);		

	page_begin = (PAGE_SIZE*(actualPage-1));
	page_end = page_begin+PAGE_SIZE;
	page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);

	printCatalogProds(page_list,actualPage,totalPages,getListaSp(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);
		
		if(string_page[0]=='0' && size_input) backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
		else if(page > 0 && page <= totalPages){
			actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_end = page_begin+PAGE_SIZE;
			page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(2);
			printCatalogProds(page_list,actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(2);
			searchPage(CatClients,CatProducts,arrayFiliais,fact,buffer,actualPage);
			exit(0);
		}
	}
	while(page != 0);
}

void printCatalogProds(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i + (PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("				%s\n",getPageElement(page_list,i));
	}
	printf("							0.Sair\n");
}



/* QUERIE 3 */

void backToProductMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();getchar();
	printf("\e[2J\e[H");
	productMonth(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void productMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int input,month,exist=0;
	char c;
	char rep[BUFFER_SIZE];
	char productString[BUFFER_SIZE];
	char stringMonth[BUFFER_SIZE];
	DADOS dataN;
	DADOS dataP;

	PRODUCT prod = malloc(sizeof(PRODUCT));

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre um produto num determinado mês");

	printTop(3);

	printf("							0.Voltar\n");

	printf("	Introduza o mês (1-12): ");
	input = scanf("%s",stringMonth);
	month = atoi(stringMonth);

	if(stringMonth[0]=='0' && input){
		 backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
	else if(month <= 0 || month > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact);
	}

	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
	productString[6] = 0;	

	if(!strcmp(productString,"0")){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
	prod = setProduct(productString);
	exist = existProduct(CatProducts,prod);

	if(!exist){
		printf("\n	Este produto não existe no Cátalogo!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact);
	}

	dataN = querie3(fact,month,productString,0);
	dataP = querie3(fact,month,productString,1);

	printf("	Deseja a informação TOTAL ou por FILIAL (T/F)? ");
	
	input = scanf("%s",rep);

	if(rep[0] == 'F' || rep[0] == 'f')
		printProductMonth(dataN,dataP,0,prod,month);

	else if(rep[0] == 'T' || rep[0] == 't')
		printProductMonth(dataN,dataP,1,prod,month);
	
	else if(rep[0] == '0'){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

	else{
		printf("\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact);
	}

	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	while(getchar()!='\n');
	c = getchar();
	if(c!='0') productMonth(CatClients,CatProducts,arrayFiliais,fact);
	else backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
}

void printProductMonth(DADOS dataN, DADOS dataP,int isTotal,PRODUCT prod,int month){

	double totalPrice_dataN=0,totalPrice_dataP=0;
	int totalQuant_dataN=0,totalQuant_dataP=0,filial;

	printf("\e[2J\e[H");
	printTop(3);

	if(isTotal){
		printf("	Informação total sobre o produto '%s' no mês '%d'.\n\n",getProduct(prod),month);
		for(filial=0;filial<3;filial++){
			totalPrice_dataN+=getDadosP(dataN)[filial];
			totalPrice_dataP+=getDadosP(dataP)[filial];
			totalQuant_dataN+=getDadosQ(dataN)[filial]; 
			totalQuant_dataP+=getDadosQ(dataP)[filial]; 
		}
		printf("	  Normal\n");
		printf("	  Total faturado: %f\n",totalPrice_dataN);
		printf("	  Total vendido: %d\n",totalQuant_dataN);
		putchar('\n');
		printf("	  Promoção\n");
		printf("	  Total faturado: %f\n",totalPrice_dataP);
		printf("	  Total vendido: %d\n",totalQuant_dataP);
	}

	else{
		printf("	Informação por filial sobre o produto '%s' no mês '%d'.\n",getProduct(prod),month);
		for(filial=0;filial<3;filial++){
			printf("	_________________________________________\n");
			printf("	 		FILIAL %d\n",filial+1); 
			printf("	  Normal\n");
			printf("	  Total faturado: %f\n",getDadosP(dataN)[filial]);
			printf("	  Total vendido: %d\n",getDadosQ(dataN)[filial]);
			putchar('\n');
			printf("	  Promoção\n");
			printf("	  Total faturado: %f\n",getDadosP(dataP)[filial]);
			printf("	  Total vendido: %d\n",getDadosQ(dataP)[filial]);
		}
	}
}



/* QUERIE 4 */

int productsNSoldFiliais(int g1,int g2,int g3){
	int filial; char string_filial[BUFFER_SIZE];
	int input;
	printf("\e[2J\e[H");
	printTop(4);
	printf("							  0.Voltar\n\n");
	printf("	 _______________________________________\n");
	printf("   	|					|\n");
	printf("   	|	FILIAL 1: %6d produtos.	|\n",g1);
	printf("   	|	FILIAL 2: %6d produtos.	|\n",g2);
	printf("   	|	FILIAL 3: %6d produtos.	|\n",g3);
	printf("   	|_______________________________________|\n");
	printf("\n	Gostaria de ver a lista de produtos não vendidos em que filial? ");
	input = scanf("%s",string_filial);
	filial = atoi(string_filial);
	if(string_filial[0]=='0') return 0;
	else if(filial > 0 && filial < 4 && input) return filial;
	else{
		printf("	Por favor introduza um filial válido (1-3)!\n");
		getchar();getchar();
		return filial = productsNSoldFiliais(g1,g2,g3);
	}
}

void productsNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char rep[BUFFER_SIZE];
	int filial,totalPages,size_input;
	LISTA_STRINGS group1,group2,group3,group=NULL;


	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos não vendidos");

	printTop(4);

	printf("							  0.Voltar\n");

	printf("\n	Deseja os produtos totais ou por filial (T/F)? ");
	size_input = scanf("%s",rep);

	if((rep[0] == 'F' || rep[0] == 'f') && size_input){
		group1 = querie4(fact,1);
		group2 = querie4(fact,2);
		group3 = querie4(fact,3);
		filial = productsNSoldFiliais(getListaSp(group1),getListaSp(group2),getListaSp(group3));
		switch(filial){
			case 1: group = group1; break;
			case 2: group = group2; break;
			case 3: group = group3; break;
			case 0: backToProductsNSold(CatClients,CatProducts,arrayFiliais,fact);
		}
	}

	else if((rep[0] == 'T' || rep[0] == 't') && size_input){
		group = querie4(fact,-1);
	}
	else if(rep[0] == '0'){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
	else{
		printf("\n\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		backToProductsNSold(CatClients,CatProducts,arrayFiliais,fact);
	}

	totalPages = calculatePagesProducts(group,PAGE_SIZE);
	printNSold(CatClients,CatProducts,arrayFiliais,fact,group,totalPages,1);
}

void printPageNSold(PAGE page,int actualPage,int totalPages,int totalElements){
	int i,index;
	printf("\e[2J\e[H");
	printTop(4);
	printf("							  0.Voltar\n");
	printf("\n	Página %d de %d.\n",actualPage,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i+(PAGE_SIZE*(actualPage-1));
		if(index < totalElements)
			printf("\n				%3d | %s",index+1,getPageElement(page,i));
	}
}

void printNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,LISTA_STRINGS group,int totalPages,int actualPage){

	int size_input,page,page_begin,page_end;
	char string_page[BUFFER_SIZE];
	PAGE page_list;

	page_begin = (PAGE_SIZE*(actualPage-1));
	page_end = page_begin+PAGE_SIZE;
	page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
	printPageNSold(page_list,actualPage,totalPages,getListaSp(group));

	do{
		printf("\n\n	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') productsNSold(CatClients,CatProducts,arrayFiliais,fact);
		else if(page > 0 && page <= totalPages && size_input){
			actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_end = page_begin+PAGE_SIZE;
			page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
			printPageNSold(page_list,actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(4);
			printNSold(CatClients,CatProducts,arrayFiliais,fact,group,totalPages,actualPage);
			exit(0);
		}
	}
	while(page != 0);
}

void backToProductsNSold (CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();
	printf("\e[2J\e[H");
	productsNSold(CatClients,CatProducts,arrayFiliais,fact);
}



/* QUERIE 5 */

void infoClientPurchases(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int input,exist,i;
	char c;
	char clientString[BUFFER_SIZE];
	CLIENT clie = malloc(sizeof(CLIENT));

	DADOS_FILIAL df_1 = initDadosFilial();

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre as compras de um cliente");

	printTop(5);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

	clie = setClient(clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar();
		backToClientPurchases(CatClients,CatProducts,arrayFiliais,fact);
	}

	for(i=0;i<3;i++)
		df_1 = querie5(arrayFiliais[i],df_1,clientString,i);
	printClientPurchases(df_1,clientString);


	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	c = getchar();
	if(c!='0') backToClientPurchases(CatClients,CatProducts,arrayFiliais,fact);
	else backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
}

void printClientPurchases(DADOS_FILIAL df,char* clientString){
	int i;
	printf("\e[2J\e[H");
	printTop(5);
	printf("	Informações sobre as compras do cliente %s.\n",clientString);
	printf("	----------------------------------------------\n");
	printf("\t| Mês |  Filial 1  |  Filial 2  |  Filial 3  |\n");
	for(i=0;i<12;i++)
		printf(" \t| %2d  |\t   %5d   |    %5d   |    %5d   |\t\n",i+1,getDadosFilialQuantity(df,1,i+1),getDadosFilialQuantity(df,2,i+1),
			getDadosFilialQuantity(df,3,i+1));
}

void backToClientPurchases(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();
	printf("\e[2J\e[H");
	infoClientPurchases(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}



/* QUERIE 6 */

void periodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char buff_begin[BUFFER_SIZE];int begin;
	char buff_end[BUFFER_SIZE]; int end;
	int input;
	char c;

	DADOS data;

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre um período de meses");

	printTop(6);
	printf("							0.Voltar\n");

	printf("	Introduza o mês inicial (1-12): ");
	input = scanf("%s",buff_begin);
	begin = atoi(buff_begin);

	if(buff_begin[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	else if((begin <= 0 || begin > 12) && input){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact);
	}

	printf("	Introduza o mês final (1-12): ");
	input = scanf("%s",buff_end);
	end = atoi(buff_end);

	if(buff_end[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	if(end <= 0 || end > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact);
	}

	if(begin >= end){
		printf("\n	Introduza um intervalo de meses válido!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact);
	}

	data = querie6(fact,begin,end);
	printDATA(data,begin,end);

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		0.Voltar\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n'); 
	c = getchar();
	if(c =='0') interpretador(CatClients,CatProducts,arrayFiliais,fact);	
	else periodMonths(CatClients,CatProducts,arrayFiliais,fact);
}

void backToPeriodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();getchar();
	printf("\e[2J\e[H");
	periodMonths(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void printDATA(DADOS data,int begin,int end){

	printf("\e[2J\e[H");
	printTop(6);

	printf("	No intervalo de meses (%d-%d):\n\n",begin,end);
	printf("	Foi facturado: %f.\n",getDadosTP(data));
	printf("	Foram registadas %d vendas.\n",getDadosTV(data));
}



/* QUERIE 7 */

void listClients(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de clientes que compraram em todas as filiais");
	printTop(7);
	searchPageListClients(CatClients,CatProducts,arrayFiliais,fact,1);	
}

void searchPageListClients(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int actualPage){

	int page,totalPages,size_input,page_end,page_begin;
	char string_page[BUFFER_SIZE];
	PAGE page_list;
	LISTA_STRINGS group = querie7(arrayFiliais);
	totalPages = calculatePagesClients(group,PAGE_SIZE);

	page_begin = (PAGE_SIZE*(actualPage-1));
	page_end = page_begin+PAGE_SIZE;
	page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);	

	printListClients(page_list,actualPage,totalPages,getListaSp(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);
		if(string_page[0]=='0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
		else if(page > 0 && page <= totalPages && size_input){
			actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_end = page_begin+PAGE_SIZE;
			page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(7);
			printListClients(page_list,actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(7);
			searchPageListClients(CatClients,CatProducts,arrayFiliais,fact,actualPage);
			exit(0);
		}
	}
	while(page != 0);
}

void printListClients(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i + (PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("\n				%5d | %s",index+1,getPageElement(page_list,i));
	}
	putchar('\n');
	printf("								0.Sair\n");
}



/* QUERIE 8 */

void backToClientsProdFilial(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();
	printf("\e[2J\e[H");
	listClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void listClientsProdFilial(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int filial,exist,input;
	char productString[BUFFER_SIZE],stringFilial[BUFFER_SIZE],c,stringPromo[BUFFER_SIZE];
	LISTA_STRINGS group_N;
	LISTA_STRINGS group_P;

	PRODUCT prod = malloc(sizeof(PRODUCT));

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre um produto num determinado filial");

	printTop(8);

	printf("							0.Voltar\n");


	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
	productString[6] = '\0';

	if(productString[0]=='0'){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

	prod = setProduct(productString);
	exist = existProduct(CatProducts,prod);

	if(!exist && input){
		printf("\n	Este produto não existe no Cátalogo!\n");
		getchar();
		backToClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
	}
	
	printf("	Introduza o filial (1-3): ");
	input = scanf("%s",stringFilial);
	filial = atoi(stringFilial);

	if(stringFilial[0] == '0'){
		 backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
	else if(filial <= 0 || filial > 3){
		getchar();
		printf("\n	Introduza um filial válido (1-3)!\n");
		backToClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
	}

	group_N = querie8(arrayFiliais[filial-1],productString,&group_P);

	putchar('\n');
	printf("	 ___________________________________________________\n");
	printf("	|                                                   |\n");
	printf("	| Total de clientes que compraram sem promoção: %3d |\n",getListaSp(group_N));
	printf("	| Total de clientes que compraram com promoção: %3d |\n",getListaSp(group_P));
	printf("	|___________________________________________________|\n\n");
	printf("\n	Gostaria de ver os clientes que compram com ou sem promoção (P/N)? ");
	input = scanf("%s",stringPromo);

	if (stringPromo[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	else if(stringPromo[0] == 'P') searchPageListClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact,1,&group_P);
	else if (stringPromo[0] == 'N') searchPageListClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact,1,&group_N);
	else {
		printf("\n 	Por favor responda somente com P(Promo) ou N(Normal)!\n");
		backToClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
	}
}

void searchPageListClientsProdFilial(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int actualPage,LISTA_STRINGS* group){

	char string_page[BUFFER_SIZE];
	int page,totalPages,size_input,page_begin,page_end;
	PAGE page_list;
	totalPages = calculatePagesClients(*group,PAGE_SIZE);	

	page_begin = (PAGE_SIZE*(actualPage-1));
	page_end = page_begin+PAGE_SIZE;
	page_list = updatePage(*group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);

	printf("\e[2J\e[H");
	printTop(7);
	printClientsProdFilial(page_list,actualPage,totalPages,getListaSp(*group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') backToClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact);
		else if(page > 0 && page <= totalPages && size_input){
			actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_end = page_begin+PAGE_SIZE;
			page_list = updatePage(*group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(8);
			printClientsProdFilial(page_list,actualPage,totalPages,getListaSp(*group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(8);
			searchPageListClientsProdFilial(CatClients,CatProducts,arrayFiliais,fact,actualPage,group);
			exit(0);
		}
	}
	while(page != 0);
}

void printClientsProdFilial(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i + (PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("					%s\n",getPageElement(page_list,i));
	}
	printf("							0. Voltar\n");
}


/* QUERIE 9 */

void backToClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();getchar();
	printf("\e[2J\e[H");
	infoClientMonth(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void infoClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char clientString[BUFFER_SIZE];
	char buff_month[BUFFER_SIZE];
	int month,input,exist;
	LISTA_STRINGS group;
	CLIENT clie = malloc(sizeof(CLIENT));

	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de produtos que um cliente mais comprou");
	printTop(9);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

	clie = setClient(clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar();
		backToClientMonth(CatClients,CatProducts,arrayFiliais,fact); 
	}

	printf("	Introduza o mês (1-12): ");
	input = scanf("%s",buff_month);
	month = atoi(buff_month);

	if(buff_month[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	if((month <= 0 || month > 12) && input){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToClientMonth(CatClients,CatProducts,arrayFiliais,fact); 
	}

	group = querie9(arrayFiliais,clientString,month);
	searchPageProducts(CatClients,CatProducts,arrayFiliais,fact,group,1); 
}

void searchPageProducts(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,LISTA_STRINGS group,int actualPage){

	int page,totalPages,size_input,page_begin,page_end;
	PAGE page_list;
	char string_page[BUFFER_SIZE];

	totalPages = calculatePagesProducts(group,PAGE_SIZE);		

	page_begin = (PAGE_SIZE*(actualPage-1));
	page_end = page_begin+PAGE_SIZE;
	page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);

	printPageMostSold(page_list,actualPage,totalPages,getListaSp(group));

	do{
		printf("\n\n");
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') infoClientMonth(CatClients,CatProducts,arrayFiliais,fact);
		else if(page > 0 && page <= totalPages && size_input){
			actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_end = page_begin+PAGE_SIZE;
			page_list = updatePage(group,page_begin,page_end,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(2);
			printPageMostSold(page_list,actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(2);
			searchPageProducts(CatClients,CatProducts,arrayFiliais,fact,group,actualPage);
			exit(0);
		}
	}
	while(page != 0);
}

void printPageMostSold(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	printf("\e[2J\e[H");
	printTop(4);
	printf("							  0.Voltar\n");
	printf("\n	Página %d de %d.\n",page,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i+(PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("\n				%2dº | %s",index+1,getPageElement(page_list,i));
	}
}


/* QUERIE 10 */

void backToIdontKnow(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();
	printf("\e[2J\e[H");
	infoClientMonth(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void nProductsMostSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	LISTA_STRINGS group;
	int filial,input,quant,i,j;
	char buff_quant[BUFFER_SIZE];
	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de produtos que um cliente mais comprou");
	printTop(10);

	printf("							0.Voltar\n");

	printf("	Introduza a quantidade de produtos mais vendidos que deseja ver: ");
	input = scanf("%s",buff_quant);
	quant = atoi(buff_quant);

	if(buff_quant[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	if(quant <= 0 || quant > 171008){
		printf("\n	Introduza uma quantidade válida!\n");
		backToIdontKnow(CatClients,CatProducts,arrayFiliais,fact); 
	}

	printf("	Introduza uma filial(1-3): ");
	input = scanf("%s",buff_quant);
	filial = atoi(buff_quant);

	int** dados=malloc(2*sizeof(int**));

    for(i=0;i<2;i++){
        dados[i]=malloc(quant*sizeof(int));
        for(j=0;j<quant;j++)
           dados[i][j]=0;
    }

	group = querie10(arrayFiliais[filial-1],fact,quant,filial,dados);

	for(i=0;i<quant;i++){
	printf("\n\n");
	printf(" Produto: %s Nº de Clientes:%d Quantidade:%d										\n",getListaString(group,i),dados[0][i],dados[1][i]);
	}
	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n')
		;
	 getchar();

	for(i=0;i<2;i++)
        free(dados[i]);
	free(dados);

	interpretador(CatClients,CatProducts,arrayFiliais,fact);	
}




/* QUERIE 11 */

void backToThreeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	getchar();
	printf("\e[2J\e[H");
	threeMostPurchased(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void threeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int exist,input;
	char clientString[BUFFER_SIZE],c;
	LISTA_STRINGS group;
	CLIENT clie = malloc(sizeof(CLIENT));

	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo dos três produtos em que um cliente gastou mais dinheiro");
	printTop(11);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact);
	}

	clie = setClient(clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar();
		backToThreeMostPurchased(CatClients,CatProducts,arrayFiliais,fact); 
	}

	group = querie11(arrayFiliais,clientString);
	printThreeMostPurchased(group,clientString); 

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		0.Voltar\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n'); 
	c = getchar();
	if(c =='0') interpretador(CatClients,CatProducts,arrayFiliais,fact);	
	else threeMostPurchased(CatClients,CatProducts,arrayFiliais,fact);
}

void printThreeMostPurchased(LISTA_STRINGS group,char* clientString){
	int i;
	printf("\e[2J\e[H");
	printTop(11);
	printf("	Os produtos em que o cliente %s gastou mais dinheiro são:",clientString);
	putchar('\n');
	printf("	 _____________________________________________________\n");
	printf("	|                                                     |\n");
	for(i=0;i<3;i++)
		printf("	| 	%dº 	%s 			    	      |\n",i+1,getListaString(group,i));
	printf("	|_____________________________________________________|\n\n");
}


/* QUERIE 12 */

void inactiveClientsProducts(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char c;
	int clients = 0;
	int products = 0;
	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de produtos e clientes inactivos");

	printTop(12);
	products = querie12(arrayFiliais,fact,&clients);

	printClientsProducts(clients,products);

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n');
	c = getchar();
	interpretador(CatClients,CatProducts,arrayFiliais,fact);	
}

void printClientsProducts(int clients,int products){
	printf("	 _____________________________________________________\n");
	printf("	|                                                     |\n");
	printf("	| Total de clientes que nunca compraram : %5d       |\n",clients);
	printf("	| Total de produtos que nunca foram comprados: %5d  |\n",products);
	printf("	|_____________________________________________________|\n\n");
}



/* AUXILIARES */

void testMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,char* menuName){
	if(!totalProducts(CatProducts)){
		putchar('\n');
		printf("		 %s\n",menuName);
		printf("		 encontra-se vazio de momento. \n");
		printf("		 Experimente usar primeiro o comando de leitura.\n\n");
		while(getchar()!='\n');
		while(getchar()!='\n');
		printf("\e[2J\e[H");
		interpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
}

int calculatePagesProducts(LISTA_STRINGS group,int elemPerPage){
	int totalPages = (getListaSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getListaSp(group)) totalPages++;
	return totalPages;
}

int calculatePagesClients(LISTA_STRINGS group,int elemPerPage){   /* ESTA AGORA É IGUAL À ANTERIOR!!! */
	int totalPages = (getListaSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getListaSp(group)) totalPages++;
	return totalPages;
}

void printTop(int i){

	printf("________________________________________________________________________________\n");

	switch(i){
		case 0: /* MENU */ 	
			printf("	 	 _____             _____           _         \n");
			printf("		|   __|___ ___ ___|  |  |___ ___ _| |___ ___ \n");
			printf("		|  |  | -_|  _| -_|  |  | -_|   | . | .'|_ -|\n");
			printf("		|_____|___|_| |___|\\___/|___|_|_|___|__,|___|\n");
			break;

		case 1:  
			printf("\n	                        LEITURA DE FICHEIROS                                    \n");
			break;

		case 2:  
			printf("\n	                        CATÁLOGO DE PRODUTOS                                    \n");
			break;

		case 3:
			printf("\n	                   PRODUTO NUM DETERMINADO MÊS                              \n");
			break;

		case 4:
			printf("\n	                        PRODUTOS NÃO VENDIDOS                                   \n");
			break;

		case 5:
			printf("\n	                        COMPRAS DE UM CLIENTE                                   \n");
			break;

		case 6:
			printf("\n	                        PERÍODO DE MESES                                         \n");
			break;

		case 7:
			printf("\n	               CLIENTES QUE COMPRARAM EM TODOS OS FILIAIS                       \n");
			break; 

		case 8:
			printf("\n	                   CLIENTES QUE COMPRARAM UM PRODUTO                        \n\n");
			break;

		case 9:
			printf("\n	                 PRODUTOS MAIS COMPRADOS POR UM CLIENTE                     \n\n");
			break;

		case 10:
			printf("\n                       OS N PRODUTOS MAIS COMPRADOS                          \n\n");
			break;

		case 11:
			printf("\n	              PRODUTOS EM QUE UM CLIENTE GASTOU MAIS DINHEIRO               \n\n");
			break;

		case 12:
			printf("\n	                    CLIENTES E PRODUTOS INACTIVOS                        \n\n");
			break;
	}
	printf("________________________________________________________________________________\n");
	printf("\n");
}

