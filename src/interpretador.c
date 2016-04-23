
#include "headers/interpretador.h"

#define PAGE_SIZE 20
#define BUFFER_SIZE 512

/* FUNÇÕES PRIVADAS AO MÓDULO */
static void menu();
static int cleaningMemory();
/* QUERIE 1 */
static int runningReadFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
static int readFiles(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
/* QUERIE 2 */
static int runningReadCatalog(CATALOG_PRODUCTS);
static int readCatalogIntro(CATALOG_PRODUCTS);
static int searchPage(int*,LISTA_STRINGS,int);
static void printCatalogProds(PAGE,int,int,int);
/* QUERIE 3 */
static int runningProductMonth(CATALOG_PRODUCTS,FACTURACAO);
static int productMonth(CATALOG_PRODUCTS,FACTURACAO);
static void printProductMonth(DADOS,DADOS,int,PRODUCT,int);
/* QUERIE 4 */
static int productsNSoldFiliais(int,int,int);
static int runningProductsNSold(CATALOG_PRODUCTS,FACTURACAO);
static int productsNSold(CATALOG_PRODUCTS,FACTURACAO);
static void printPageNSold(PAGE,int,int,int);
static int printNSold(LISTA_STRINGS,int,int*);
/* QUERIE 5 */
static int runningInfoClientPurchases(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static int infoClientPurchases(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static void printClientPurchases(DADOS_FILIAL*,char*);
/* QUERIE 6 */
static int periodMonths(CATALOG_PRODUCTS,FACTURACAO);
static int runningToPeriodMonths(CATALOG_PRODUCTS,FACTURACAO);
static void printDATA(DADOS,int,int);
/* QUERIE 7 */
static int runningListClients(CATALOG_PRODUCTS,FILIAL*);
static int searchPageListClients(CATALOG_PRODUCTS,int*,LISTA_STRINGS,int);
static void printListClients(PAGE,int,int,int);
/* QUERIE 8 */ 
static int runningClientsProdFilial(CATALOG_PRODUCTS,FILIAL*);
static int listClientsProdFilial(CATALOG_PRODUCTS,FILIAL*);
static int searchPageListClientsProdFilial(int*,LISTA_STRINGS*);
static void printClientsProdFilial(PAGE,int,int,int);
/* QUERIE 9 */ 
static int runningClientMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static int infoClientMonth(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static int searchPageProducts(LISTA_STRINGS,int*);
static void printPageMostSold(PAGE,int,int,int);
/* QUERIE 10 */
static int runningMostSold(CATALOG_PRODUCTS,FILIAL*);
static int nProductsMostSold(CATALOG_PRODUCTS,FILIAL*); 
static int searchPageMostSold(int*,LISTA_STRINGS,int,int**);
/* QUERIE 11 */
static int runningThreeMostPurchased(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static int threeMostPurchased(CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*);
static void printThreeMostPurchased(LISTA_STRINGS,char*);
static void printMostSold(PAGE,int**,int,int,int);
/* QUERIE 12 */
static int inactiveClientsProducts(CATALOG_PRODUCTS,FILIAL*,FACTURACAO);
static void printClientsProducts(int,int);
/* AUXILIARES */
static int testMemory(CATALOG_PRODUCTS,char*);
static int calculatePagesProducts(LISTA_STRINGS,int);
static int calculatePagesClients(LISTA_STRINGS,int);
static void printTop(int);
static int exitGereVendas();


static void menu(){

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

int interpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char buffer[BUFFER_SIZE]; int size_input,res=1;
	int num_commando;
	printf("\e[2J\e[H"); 
	menu();
	printf("	Introduza o número do comando desejado: ");
	size_input = scanf("%s",buffer);
	num_commando = atoi(buffer);

	if(buffer[0]=='0'){
		res = exitGereVendas();
		return res;
	}

	switch(num_commando){

		case 1: 
			if(!totalProducts(CatProducts) && size_input) res = runningReadFiles(CatClients,CatProducts,arrayFiliais,fact);
			else res = cleaningMemory();
			break;

		case 2: 
			res = runningReadCatalog(CatProducts);
			break;

		case 3: 
			res = runningProductMonth(CatProducts,fact);
			break;

		case 4: 
			res = runningProductsNSold(CatProducts,fact);
			break;

		case 5:
			res = runningInfoClientPurchases(CatClients,CatProducts,arrayFiliais);
			break;

		case 6: 
			res = runningToPeriodMonths(CatProducts,fact);
			break;

		case 7:
			res = runningListClients(CatProducts,arrayFiliais);
			break;

		case 8:
			res = runningClientsProdFilial(CatProducts,arrayFiliais);
			break;

		case 9:
			res = runningClientMonth(CatClients,CatProducts,arrayFiliais);
			break;

		case 10:
			res = runningMostSold(CatProducts,arrayFiliais);
			break;

		case 11:
			res = runningThreeMostPurchased(CatClients,CatProducts,arrayFiliais);
			break;

		case 12:
			res = inactiveClientsProducts(CatProducts,arrayFiliais,fact);
			break;
			
		default:
			printf("	Este comando não é válido!\n");
			getchar();getchar();
			break;
	}

	return res;
}

static int cleaningMemory(){
	int input,res;
	char buffer[BUFFER_SIZE];
	printf("\e[2J\e[H"); 
	printTop(1);
	printf("	Já existem dados em memória, deseja libertá-los (S/N)? ");
	input = scanf("%s",buffer);
	if((buffer[0] == 'S' || buffer[0] == 's') && input ){
		printf("\e[2J\e[H"); 
		printTop(1);
		printf("		 _____________________________________________________\n");
		printf("		|                                                     |\n");
		printf("		|                                                     |\n");
		printf("		|                                                     |\n");
		printf("		|               A MEMÓRIA FOI LIBERTADA               |\n");
		printf("		|                                                     |\n");
		printf("		|                                                     |\n");
		printf("		|_____________________________________________________|\n");
		while(getchar()!='\n');
		getchar();
		res = -1;
	}
	else if((buffer[0] == 'N' || buffer[0] == 'n') && input)	
		res = 1;
	else 
		res = cleaningMemory();
	return res;
}

static int exitGereVendas(){
	printf("\e[2J\e[H"); 	
	printf(" _______________________________________________________________\n");
	printf("| 	__   __   _ _                                    _ 	|\n");
 	printf("|	\\ \\ / /__| | |_ ___   ___ ___ _ __  _ __ _ _ ___| |	|\n");
  	printf("|	 \\ V / _ \\ |  _/ -_) (_-</ -_) '  \\| '_ \\ '_/ -_)_|	|\n");
   	printf("|	  \\_/\\___/_|\\__\\___| /__/\\___|_|_|_| .__/_| \\___(_)	|\n");
    printf("|                              		   |_|	   		|\n");  		   
    printf("|_______________________________________________________________|\n");      
  	return 0;
}

/* QUERIE 1 */

static int runningReadFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	int running=1;
	while(running){
		running = readFiles(CatClients,CatProducts,arrayFiliais,fact);
	}
	return 1;
}

static int readFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	
	char rep,info[BUFFER_SIZE],clientsFile[BUFFER_SIZE],productsFile[BUFFER_SIZE],salesFile[BUFFER_SIZE];
	int size_input,r=1;

	printf("\e[2J\e[H"); 
	printTop(1);
	
	printf("							0.Voltar\n");
	printf("\n\n");
	printf("	Deseja ler os ficheiros DEFAULT (S/N)?  ");
	size_input = scanf("%s",info);
	if(info[0]=='0' || !size_input) return 0;
	else if((info[0]=='S' || info[0]=='s') && size_input) {
		printf("\e[2J\e[H"); 
		r=getFile(CatClients,CatProducts,arrayFiliais,fact,CLIENTS_FILE,PRODUCTS_FILE,SALES_FILE);
	}
	else if((info[0]=='N' || info[0]=='n') && size_input){
		printf("	Ficheiro de Clientes: ");
		size_input = scanf("%s",clientsFile);
		printf("	Ficheiro de Produtos: ");
		size_input = scanf("%s",productsFile);
		printf("	Ficheiro de Vendas: ");
		size_input = scanf("%s",salesFile);
		printf("\e[2J\e[H"); 
		r = getFile(CatClients,CatProducts,arrayFiliais,fact,clientsFile,productsFile,salesFile);
		if(!r){
			printf("\n\n\n	Os ficheiros que tentou ler não são válidos!\n");
			getchar();getchar();
		 	return 1;
		}
	}
	else{
		 printf("	Por favor responda apenas com sim (S) ou não (N)!\n");
		 getchar();getchar();
		 return 1;
	}

	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	while(getchar()!='\n'); 
	rep = getchar();
	if(rep == '0') return 0;
	return 0;
}



/* QUERIE 2 */

static int runningReadCatalog(CATALOG_PRODUCTS CatProducts){
	int running=1;
	while(running){
		running = readCatalogIntro(CatProducts);
	}
	return 1;
}

static int readCatalogIntro(CATALOG_PRODUCTS CatProducts){
	
	char buffer[BUFFER_SIZE];
	int size_input,running=1,actualPage=1,test,totalPages;
	LISTA_STRINGS group;

	printf("\e[2J\e[H");
	test = testMemory(CatProducts,"O Catálogo de Produtos");
	if(test) return 0;
	printTop(2);
	printf("							0.Voltar\n");
	printf("	Letra que deseja procurar: ");
	size_input = scanf("%s",buffer);
	buffer[0] = toupper(buffer[0]);

	if(buffer[0] >= 'A' && buffer[0] <= 'Z' && size_input){
		printf("\e[2J\e[H");
		printTop(2);
		group = querie2(CatProducts,buffer[0]);
		totalPages = calculatePagesProducts(group,PAGE_SIZE);
		while(running){
			running = searchPage(&actualPage,group,totalPages);
		}
	}
	else if(buffer[0] == '0' && size_input) return 0;
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		getchar();getchar();
		return 1;
	}
	return 0;
}

static int searchPage(int *actualPage,LISTA_STRINGS group,int totalPages){

	int page,size_input,page_begin;
	char string_page[BUFFER_SIZE];
	PAGE page_list;	

	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);

	printCatalogProds(page_list,*actualPage,totalPages,getListaSp(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		printf("%s\n",string_page);
		page = atoi(string_page);
		
		if(string_page[0]=='0' && size_input) return 0;
		else if(page > 0 && page <= totalPages){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(2);
			printCatalogProds(page_list,*actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(2);
			return 1;
		}
	}
	while(page != 0);
	return 0;
}

static void printCatalogProds(PAGE page_list,int page,int totalPages,int totalElements){
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

static int runningProductMonth(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){
	int running=1;
	while(running){
		running = productMonth(CatProducts,fact);
	}
	return 1;
}

static int productMonth(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){

	int input,month,exist=0,test;
	char c;
	char rep[BUFFER_SIZE];
	char productString[BUFFER_SIZE];
	char stringMonth[BUFFER_SIZE];
	DADOS dataN;
	DADOS dataP;

	PRODUCT prod = initProd();

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de informações sobre um produto num determinado mês");
	if(test) return 0;

	printTop(3);

	printf("							0.Voltar\n");

	printf("	Introduza o mês (1-12): ");
	input = scanf("%s",stringMonth);
	month = atoi(stringMonth);

	if(stringMonth[0]=='0' && input){
		 return 0;
	}
	else if(month <= 0 || month > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		getchar(); getchar();
		return 1;
	}

	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
	productString[6] = 0;	

	if(!strcmp(productString,"0")){
		return 0;
	}
	prod = setProduct(prod,productString);
	exist = existProduct(CatProducts,prod);

	if(!exist){
		printf("\n	Este produto não existe no Cátalogo!\n");
		getchar(); getchar();
		return 1;
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
		return 0;
	}

	else{
		printf("\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		getchar(); getchar();
		return 1;
	}

	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	while(getchar()!='\n');
	c = getchar();
	if(c!='0') return 1;
	else return 0;
}

static void printProductMonth(DADOS dataN, DADOS dataP,int isTotal,PRODUCT prod,int month){

	double totalPrice_dataN=0,totalPrice_dataP=0;
	int totalQuant_dataN=0,totalQuant_dataP=0,filial;
	char* product=getProduct(prod);
	printf("\e[2J\e[H");
	printTop(3);

	if(isTotal){
		printf("	Informação total sobre o produto '%s' no mês '%d'.\n\n",product,month);
		for(filial=0;filial<3;filial++){
			totalPrice_dataN+=getDadosP(dataN)[filial];
			totalPrice_dataP+=getDadosP(dataP)[filial];
			totalQuant_dataN+=getDadosQ(dataN)[filial]; 
			totalQuant_dataP+=getDadosQ(dataP)[filial]; 
		}
		printf("	  Normal\n");
		printf("	  Total faturado: %f\n",totalPrice_dataN);
		printf("	  Total de vendas: %d\n",totalQuant_dataN);
		putchar('\n');
		printf("	  Promoção\n");
		printf("	  Total faturado: %f\n",totalPrice_dataP);
		printf("	  Total de vendas: %d\n",totalQuant_dataP);
	}

	else{
		printf("	Informação por filial sobre o produto '%s' no mês '%d'.\n",product,month);
		for(filial=0;filial<3;filial++){
			printf("	_________________________________________\n");
			printf("	 		FILIAL %d\n",filial+1); 
			printf("	  Normal\n");
			printf("	  Total faturado: %f\n",getDadosP(dataN)[filial]);
			printf("	  Total de vendas: %d\n",getDadosQ(dataN)[filial]);
			putchar('\n');
			printf("	  Promoção\n");
			printf("	  Total faturado: %f\n",getDadosP(dataP)[filial]);
			printf("	  Total de vendas: %d\n",getDadosQ(dataP)[filial]);
		}
	}
	free(prod);
}



/* QUERIE 4 */

static int productsNSoldFiliais(int g1,int g2,int g3){
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

static int runningProductsNSold(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){
	int running=1;
	while(running){
		running = productsNSold(CatProducts,fact);
	}
	return 1;
}

static int productsNSold(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){

	char rep[BUFFER_SIZE];
	int filial,totalPages,size_input,running=1,actualPage=1,test;
	LISTA_STRINGS group1,group2,group3,group=NULL;


	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de Produtos não vendidos");
	if(test) return 0;

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
			case 0: return 1; 
		}
	}

	else if((rep[0] == 'T' || rep[0] == 't') && size_input){
		group = querie4(fact,-1);
	}
	else if(rep[0] == '0'){
		return 0;
	}
	else{
		printf("\n\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		getchar();getchar();
		return 1;
	}

	totalPages = calculatePagesProducts(group,PAGE_SIZE);
	while(running){
		if(running==-1) return 1;
		running = printNSold(group,totalPages,&actualPage);
	}

	return 0;
}

static void printPageNSold(PAGE page,int actualPage,int totalPages,int totalElements){
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

static int printNSold(LISTA_STRINGS group,int totalPages,int *actualPage){

	int size_input,page,page_begin;
	char string_page[BUFFER_SIZE];
	PAGE page_list;

	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
	printPageNSold(page_list,*actualPage,totalPages,getListaSp(group));

	do{
		printf("\n\n	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') return -1;
		else if(page > 0 && page <= totalPages && size_input){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printPageNSold(page_list,*actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(4);
			return 1;
		}
	}
	while(page != 0);
	return 0;
}



/* QUERIE 5 */

static int runningInfoClientPurchases(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running=1;
	while(running){
		running = infoClientPurchases(CatClients,CatProducts,arrayFiliais);
	}
	return 1;
}

static int infoClientPurchases(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){

	int input,exist,i,test;
	char c;
	char clientString[BUFFER_SIZE];
	CLIENT clie = initClie();

	DADOS_FILIAL df_1[3];
	
	for(i=0;i<3;i++)
		df_1[i]=initDadosFilial();

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de informações sobre as compras de um cliente");
	if(test) return 0;

	printTop(5);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")){
		return 0;
	}

	clie = setClient(clie,clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar();getchar();
		return 1;
	}

	for(i=0;i<3;i++)
		df_1[i] = querie5(arrayFiliais[i],df_1[i],clientString);

	printClientPurchases(df_1,clientString);


	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	getchar();
	c = getchar();
	if(c!='0') return 1;
	else return 0;
}

static void printClientPurchases(DADOS_FILIAL* df,char* clientString){
	int i;
	printf("\e[2J\e[H");
	printTop(5);
	printf("	Informações sobre as compras do cliente %s.\n",clientString);
	printf("	----------------------------------------------\n");
	printf("\t| Mês |  Filial 1  |  Filial 2  |  Filial 3  |\n");
	for(i=0;i<12;i++)
		printf(" \t| %2d  |\t   %5d   |    %5d   |    %5d   |\t\n",i+1,getDadosFilialQuantity(df[0],i+1),getDadosFilialQuantity(df[1],i+1),
			getDadosFilialQuantity(df[2],i+1));
}



/* QUERIE 6 */

static int periodMonths(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){

	char buff_begin[BUFFER_SIZE];
	int begin,test;
	char buff_end[BUFFER_SIZE]; 
	int end;
	int input;
	char c;

	DADOS data;

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de informações sobre um período de meses");
	if(test) return 0;

	printTop(6);
	printf("							0.Voltar\n");

	printf("	Introduza o mês inicial (1-12): ");
	input = scanf("%s",buff_begin);
	begin = atoi(buff_begin);

	if(buff_begin[0] == '0') return 0;
	else if((begin <= 0 || begin > 12) && input){
		printf("\n	Introduza um mês válido (1-12)!\n");
		getchar();getchar();
		return 1;
	}

	printf("	Introduza o mês final (1-12): ");
	input = scanf("%s",buff_end);
	end = atoi(buff_end);

	if(buff_end[0] == '0') return 0;
	if(end <= 0 || end > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		getchar();getchar();
		return 1;
	}

	if(begin >= end){
		printf("\n	Introduza um intervalo de meses válido!\n");
		getchar();getchar();
		return 1;
	}

	data = querie6(fact,begin,end);
	printDATA(data,begin,end);

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		0.Voltar\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	while(getchar()!='\n');
	c = getchar();
	if(c =='0') return 0;	
	else return 1;
}

static int runningToPeriodMonths(CATALOG_PRODUCTS CatProducts,FACTURACAO fact){
	int running=1;
	while(running){
		running = periodMonths(CatProducts,fact);
	}
	return 1;
}

static void printDATA(DADOS data,int begin,int end){

	printf("\e[2J\e[H");
	printTop(6);

	printf("	No intervalo de meses (%d-%d):\n\n",begin,end);
	printf("	Foi facturado: %f.\n",getDadosTP(data));
	printf("	Foram registadas %d vendas.\n",getDadosTV(data));
}



/* QUERIE 7 */

static int runningListClients(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running=1,actualPage=1,totalPages;
	LISTA_STRINGS group = querie7(arrayFiliais);
	totalPages = calculatePagesClients(group,PAGE_SIZE);
	while(running){
		running = searchPageListClients(CatProducts,&actualPage,group,totalPages);
	}
	return 1;
}

static int searchPageListClients(CATALOG_PRODUCTS CatProducts,int *actualPage,LISTA_STRINGS group,int totalPages){

	int page,size_input,page_begin,test;
	char string_page[BUFFER_SIZE];
	PAGE page_list;
	
	printf("\e[2J\e[H");
	test = testMemory(CatProducts,"O Catálogo de clientes que compraram em todas as filiais");
	if(test) return 0;

	printTop(7);
	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);	


	printListClients(page_list,*actualPage,totalPages,getListaSp(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		printf("%s\n",string_page);
		page = atoi(string_page);
		if(string_page[0]=='0') return 0;
		else if(page > 0 && page <= totalPages && size_input){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(7);
			printListClients(page_list,*actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			return 1;
		}
	}
	while(page != 0);
	return 0;
}

static void printListClients(PAGE page_list,int page,int totalPages,int totalElements){
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

static int runningClientsProdFilial(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running=1;
	while(running){
		running = listClientsProdFilial(CatProducts,arrayFiliais);
	}
	return 1;
}

static int listClientsProdFilial(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){

	int filial,exist,input,actualPage=1,running=1,running2=1,test;
	char productString[BUFFER_SIZE],stringFilial[BUFFER_SIZE],stringPromo[BUFFER_SIZE];
	LISTA_STRINGS group_N;
	LISTA_STRINGS group_P;

	PRODUCT prod = initProd();

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de informações sobre um produto num determinado filial");
	if(test) return 0;

	printTop(8);

	printf("							0.Voltar\n");


	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
	productString[6] = '\0';

	if(productString[0]=='0'){
		return 0;
	}

	prod = setProduct(prod,productString);
	exist = existProduct(CatProducts,prod);

	if(!exist && input){
		printf("\n	Este produto não existe no Cátalogo!\n");
		getchar();getchar();
		return 1;
	}
	
	printf("	Introduza o filial (1-3): ");
	input = scanf("%s",stringFilial);
	filial = atoi(stringFilial);

	if(stringFilial[0] == '0'){
		 return 0;
	}
	else if(filial <= 0 || filial > 3){
		getchar();
		printf("\n	Introduza um filial válido (1-3)!\n");
		getchar();getchar();
		return 1;
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

	if (stringPromo[0] == '0') return 0;
	else if(stringPromo[0] == 'P'){
		while(running){
			if(running==-1) return 1;
	 		running = searchPageListClientsProdFilial(&actualPage,&group_P);
		}
	}
	else if (stringPromo[0] == 'N'){
		while(running2){
			if(running2==-1) return 1;
			running2 = searchPageListClientsProdFilial(&actualPage,&group_N);
		}
	} 
	else {
		printf("\n 	Por favor responda somente com P(Promo) ou N(Normal)!\n");
		getchar();getchar();
		return 1;
	}
	return 0;
}

static int searchPageListClientsProdFilial(int *actualPage,LISTA_STRINGS* group){

	char string_page[BUFFER_SIZE];
	int page,totalPages,size_input,page_begin;
	PAGE page_list;
	totalPages = calculatePagesClients(*group,PAGE_SIZE);	

	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(*group,page_begin,SIZE_PRODUCT,PAGE_SIZE);

	printf("\e[2J\e[H");
	printTop(7);
	printClientsProdFilial(page_list,*actualPage,totalPages,getListaSp(*group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') return -1;
		else if(page > 0 && page <= totalPages && size_input){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(*group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(8);
			printClientsProdFilial(page_list,*actualPage,totalPages,getListaSp(*group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(8);
			return 1;
		}
	}
	while(page != 0);
	return 0;
}

static void printClientsProdFilial(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	if(totalPages){
		printf("	Página %d de %d.\n",page,totalPages);
		for(i=0;i<PAGE_SIZE;i++){
			index = i + (PAGE_SIZE*(page-1));
			if(index < totalElements)
				printf("					%s\n",getPageElement(page_list,i));
		}
	}
	else printf("		Este catálogo está vazio!\n\n\n");
	printf("							0. Voltar\n");
}


/* QUERIE 9 */

static int runningClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running = 1;
	while(running){
		running = infoClientMonth(CatClients,CatProducts,arrayFiliais);
	}
	return 1;
}

static int infoClientMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){

	char clientString[BUFFER_SIZE];
	char buff_month[BUFFER_SIZE];
	int month,input,exist,actualPage = 1,running = 1,test;
	LISTA_STRINGS group;
	CLIENT clie = initClie();

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de produtos que um cliente mais comprou");
	if(test) return 0;

	printTop(9);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")) return 0;

	clie = setClient(clie,clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar(); getchar();
		return 1;
	}

	printf("	Introduza o mês (1-12): ");
	input = scanf("%s",buff_month);
	month = atoi(buff_month);

	if(buff_month[0] == '0') return 0;
	if((month <= 0 || month > 12) && input){
		printf("\n	Introduza um mês válido (1-12)!\n");
		getchar(); getchar();
		return 1;
	}

	group = querie9(arrayFiliais,clientString,month);
	while(running){
		if(running == -1) return 1;
		running	= searchPageProducts(group,&actualPage); 
	}
	return 0;
}

static int searchPageProducts(LISTA_STRINGS group,int *actualPage){

	int page,totalPages,size_input,page_begin;
	PAGE page_list;
	char string_page[BUFFER_SIZE];

	totalPages = calculatePagesProducts(group,PAGE_SIZE);		

	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);

	printPageMostSold(page_list,*actualPage,totalPages,getListaSp(group));

	do{
		printf("\n\n");
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);

		if(string_page[0]=='0') return -1;
		else if(page > 0 && page <= totalPages && size_input){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(2);
			printPageMostSold(page_list,*actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			printf("\e[2J\e[H");
			printTop(2);
			return 1;
		}
	}
	while(page != 0);
	return 0;
}

static void printPageMostSold(PAGE page_list,int page,int totalPages,int totalElements){
	int i,index;
	printf("\e[2J\e[H");
	printTop(9);
	printf("							  0.Voltar\n");
	printf("\n	Página %d de %d.\n",page,totalPages);
	for(i=0;i<PAGE_SIZE;i++){
		index = i+(PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("\n				%2dº | %s",index+1,getPageElement(page_list,i));
	}
}


/* QUERIE 10 */

static int runningMostSold(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running = 1;
	while(running){
		running = nProductsMostSold(CatProducts,arrayFiliais);
	}
	return 1;
}

static int nProductsMostSold(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){

	LISTA_STRINGS group;
	int filial,input,quant,i,j,test,actualPage=1,running=1,totalPages;
	char buff_quant[BUFFER_SIZE],buff_filial[BUFFER_SIZE];
	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de produtos que um cliente mais comprou");
	if(test) return 0;

	printTop(10);

	printf("							0.Voltar\n");

	printf("\n	Introduza a quantidade de produtos mais vendidos que deseja ver: ");
	input = scanf("%s",buff_quant);
	quant = atoi(buff_quant);

	if(buff_quant[0] == '0' && input) return 0;
	if(quant <= 0 || quant > 171008){
		printf("\n	Introduza uma quantidade válida (1-171008)!\n");
		getchar(); getchar();
		return 1;
	}

	printf("\n	Introduza uma filial(1-3): ");
	input = scanf("%s",buff_filial);
	filial = atoi(buff_filial);

	if(buff_quant[0] == '0' && input) return 0;
	if(filial <= 0 || filial > 3){
		printf("\n	Introduza um filial válido (1-3)!\n");
		getchar(); getchar();
		return 1;
	}


	int** dados=malloc(2*sizeof(int**));

    for(i=0;i<2;i++){
        dados[i]=malloc(quant*sizeof(int));
        for(j=0;j<quant;j++)
           dados[i][j]=0;
    }

	group = querie10(arrayFiliais[filial-1],quant,dados);
	totalPages = calculatePagesProducts(group,PAGE_SIZE);

	while(running){
		running = searchPageMostSold(&actualPage,group,totalPages,dados);
	}

	for(i=0;i<2;i++)
        free(dados[i]);
	free(dados);
	return 0;
}

static int searchPageMostSold(int *actualPage,LISTA_STRINGS group,int totalPages,int **dados){

	int page,size_input,page_begin;
	char string_page[BUFFER_SIZE];
	PAGE page_list;

	printf("\e[2J\e[H");
	printTop(10);
	page_begin = (PAGE_SIZE*(*actualPage-1));
	page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);	


	printMostSold(page_list,dados,*actualPage,totalPages,getListaSp(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%s",string_page);
		page = atoi(string_page);
		if(string_page[0]=='0') return 0;
		else if(page > 0 && page <= totalPages && size_input){
			*actualPage = page;
			page_begin = (PAGE_SIZE*(page-1));
			page_list = updatePage(group,page_begin,SIZE_PRODUCT,PAGE_SIZE);
			printf("\e[2J\e[H");
			printTop(10);
			printMostSold(page_list,dados,*actualPage,totalPages,getListaSp(group));
		}
		else{
			printf("\n	Por favor insira uma página de 1 a %d.\n",totalPages);
			getchar();getchar();
			return 1;
		}
	}
	while(page != 0);
	return 0;
}

static void printMostSold(PAGE page_list,int** dados,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n\n",page,totalPages);
	printf("	|   Posição    |   Produto   | 	Quantidade  | Nº de Clientes |\n");
	for(i=0;i<PAGE_SIZE;i++){
		index = i + (PAGE_SIZE*(page-1));
		if(index < totalElements)
			printf("\n 	|	%6d |   %s    |    %5d     |   %5d        |",index+1,getPageElement(page_list,i),dados[1][index],dados[0][index]);
	}
	printf("\n\n");
	printf("								0.Sair\n");
}


/* QUERIE 11 */

static int runningThreeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){
	int running=1;
	while(running){
		running = threeMostPurchased(CatClients,CatProducts,arrayFiliais);
	}
	return 1;
}

static int threeMostPurchased(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais){

	int exist,input,test;
	char clientString[BUFFER_SIZE],c;
	LISTA_STRINGS group;
	CLIENT clie = initClie();

	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo dos três produtos em que um cliente gastou mais dinheiro");
	if(test) return 0;

	printTop(11);

	printf("							0.Voltar\n");

	printf("	Introduza um cliente: ");
	input = scanf("%s",clientString);
	clientString[5] = 0;
		
	if(!strcmp(clientString,"0")) return 0;

	clie = setClient(clie,clientString);
	exist = existClient(CatClients,clie);

	if(!exist && input){
		printf("\n	Este cliente não existe no Cátalogo!\n");
		getchar(); getchar();
		return 1;
	}

	group = querie11(arrayFiliais,clientString);
	printThreeMostPurchased(group,clientString); 

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		0.Voltar\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	getchar();
	c = getchar();
	if(c =='0') return 0;
	else return 1;
}

static void printThreeMostPurchased(LISTA_STRINGS group,char* clientString){
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

static int inactiveClientsProducts(CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int clients = 0,test;
	int products = 0;
	printf("\e[2J\e[H");

	test = testMemory(CatProducts,"O Catálogo de produtos e clientes inactivos");
	if(test) return 1;

	printTop(12);
	products = querie12(arrayFiliais,fact,&clients);

	printClientsProducts(clients,products);

	printf("\n\n");
	printf("	Pressione qualquer tecla para continuar!		\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	getchar();
	getchar();
	return 1;	
}

static void printClientsProducts(int clients,int products){
	printf("	 _____________________________________________________\n");
	printf("	|                                                     |\n");
	printf("	| Total de clientes que nunca compraram : %5d       |\n",clients);
	printf("	| Total de produtos que nunca foram comprados: %5d  |\n",products);
	printf("	|_____________________________________________________|\n\n");
}



/* AUXILIARES */

static int testMemory(CATALOG_PRODUCTS CatProducts,char* menuName){
	int r=0;
	if(!totalProducts(CatProducts)){
		putchar('\n');
		printf("		 %s\n",menuName);
		printf("		 encontra-se vazio de momento. \n");
		printf("		 Experimente usar primeiro o comando de leitura.\n\n");
		while(getchar()!='\n');
		while(getchar()!='\n');
		printf("\e[2J\e[H");
		r=1;
	}
	return r;
}

static int calculatePagesProducts(LISTA_STRINGS group,int elemPerPage){
	int totalPages = (getListaSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getListaSp(group)) totalPages++;
	return totalPages;
}

static int calculatePagesClients(LISTA_STRINGS group,int elemPerPage){   /* ESTA AGORA É IGUAL À ANTERIOR!!! */
	int totalPages = (getListaSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getListaSp(group)) totalPages++;
	return totalPages;
}

static void printTop(int i){

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
			printf("\n                       OS PRODUTOS MAIS COMPRADOS                          \n\n");
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

