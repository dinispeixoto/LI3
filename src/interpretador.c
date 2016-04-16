
#include "headers/interpretador.h"

#define ELEM_PER_PAGE 20

void menu(){

	printTop(0);
	printf("	01. Fazer leitura dos ficheiros.\n");
	printf("	02. Apresentar Catálogo de Produtos.\n");
	printf("	03. Informações sobre as vendas de um produto num determinado mês.\n");
	printf("	04. Produtos não comprados.\n");
	printf("	05. ...\n");
	printf("	06. Resultados num intervalo de meses.\n");
	printf("	07. ...\n");
	printf("	08. ...\n");
	printf("	09. ...\n");
	printf("	10. ...\n");
	printf("	11. ...\n");
	printf("	12. ...					0. Sair.\n");
	printf("________________________________________________________________________________\n\n");
}

void interpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char buffer[1]; int size_input;

	printf("\e[2J\e[H"); 
	menu();
	printf("	Introduza o número do comando desejado: ");
	size_input = scanf("%s",buffer);
	
	switch(buffer[0]){

		case '0': 
			exit(0); 
			break;

		case '1': 
			readFiles(CatClients,CatProducts,arrayFiliais,fact); 
			break;

		case '2': 
			readCatalog(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case '3': 
			productMonth(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case '4': 
			productsNSold(CatClients,CatProducts,arrayFiliais,fact);
			break;

		case '6': 
			periodMonths(CatClients,CatProducts,arrayFiliais,fact);
			break;
			
		case 'm': 
				freeMemory(CatClients,CatProducts,arrayFiliais,fact);
				interpretador(CatClients,CatProducts,arrayFiliais,fact);
				break;

		default:
			printf("	Este comando não é válido!\n");
			backInterpretador(CatClients,CatProducts,arrayFiliais,fact,1);
	}

}

void backInterpretador(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime){
	sleep(sleepTime);
	printf("\e[2J\e[H");
	interpretador(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}


/* QUERIE 1 */

void readFiles(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	
	char rep;
	int size_input;

	printf("\e[2J\e[H"); 

	getFile(CatClients,CatProducts,arrayFiliais,fact);
	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");
	while(getchar()!='\n'); 
	rep = getchar();
	if(rep == '0') exit(0);	
	else backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
}



/* QUERIE 2 */

void readCatalog(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	printf("\e[2J\e[H");
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos");
	readCatalogIntro(CatClients,CatProducts,arrayFiliais,fact);
}

void readCatalogIntro(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	
	char buffer[1];
	int size_input;

	printTop(2);
	printf("							0.Voltar\n");
	printf("	Letra que deseja procurar: ");
	size_input = scanf("%s",buffer);
	buffer[0] = toupper(buffer[0]);

	if(buffer[0] >= 'A' && buffer[0] <= 'Z' && size_input < 2){
		printf("\e[2J\e[H");
		printTop(2);
		searchPage(CatClients,CatProducts,arrayFiliais,fact,buffer,1);
	}
	else if(buffer[0] == '0') backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		sleep(2);
		printf("\e[2J\e[H");
		readCatalogIntro(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}
}

void searchPage(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,char* buffer,int actualPage){

	int page,totalPages,size_input;
	GROUP_PRODUCTS group;

	group = querie2(CatProducts,buffer[0]);
	totalPages = calculatePages(group,ELEM_PER_PAGE);		

	printCatalogProds(group,actualPage,totalPages,getGroupProdSize(group));

	do{
		printf("	Escolha uma página: ");
		size_input = scanf("%d",&page);

		if(page > 0 && page <= totalPages){
			actualPage = page;
			printf("\e[2J\e[H");
			printTop(2);
			printCatalogProds(group,actualPage,totalPages,getGroupProdSize(group));
		}
		else if(page == 0) backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			sleep(2);
			printf("\e[2J\e[H");
			printTop(2);
			searchPage(CatClients,CatProducts,arrayFiliais,fact,buffer,actualPage);
			exit(0);
		}
	}
	while(page != 0);
}

void printCatalogProds(GROUP_PRODUCTS group,int page,int totalPages,int totalElements){
	int i,index;
	printf("	Página %d de %d.\n",page,totalPages);
	for(i=0;i<ELEM_PER_PAGE;i++){
		index = i + (ELEM_PER_PAGE*(page-1));
		if(index < totalElements)
			printf("				%s\n",getProduct(getGroupProd(group)[index]));
	}
	printf("							0.Sair\n");
}



/* QUERIE 3 */

void backToProductMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime){
	sleep(sleepTime);
	printf("\e[2J\e[H");
	productMonth(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void productMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int input,input2,month,exist=0;
	char c;
	char rep[5];
	char productString[6];
	char stringMonth[2];
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

	if((month < 0 || month > 12) && input < 3){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact,2);
	}
	else if(month == 0){
		 backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
	}

	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
		
	if(!strcmp(productString,"0")){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
	}

	if(input < 7){
		prod = setProduct(productString);
		exist = existProduct(CatProducts,prod);
	}

	if(!exist){
		printf("\n	Este produto não existe no Cátalogo!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact,2);
	}

	dataN = querie3(fact,month,productString,0);
	dataP = querie3(fact,month,productString,1);

	printf("	Deseja a informação TOTAL ou por FILIAL (T/F)? ");
	
	input2 = scanf("%s",rep);

	if((rep[0] == 'F' || rep[0] == 'f') && input == 1)
		printProductMonth(dataN,dataP,0,prod,month);

	else if((rep[0] == 'T' || rep[0] == 't') && input == 1)
		printProductMonth(dataN,dataP,1,prod,month);
	
	else if(rep[0] == '0'){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
	}

	else{
		printf("\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		backToProductMonth(CatClients,CatProducts,arrayFiliais,fact,3);
	}

	putchar('\n');
	printf("	Pressione qualquer tecla para continuar!		0.Sair\n");
	printf("________________________________________________________________________________\n");
	printf("	>> ");

	while(getchar()!='\n');
	c = getchar();
	if(c!='0') productMonth(CatClients,CatProducts,arrayFiliais,fact);
	else backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
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

void productsNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char rep[2];
	int filial,contador=0,totalPages,size_input,error;
	int contador1=0,contador2=0,contador3=0;
	GROUP_PRODUCTS group1,group2,group3,group;


	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos não vendidos");

	printTop(4);

	printf("							  0.Voltar\n");

	printf("\n	Deseja os produtos totais ou por filial (T/F)? ");
	size_input = scanf("%s",rep);

	if(rep[0] == 'F' || rep[0] == 'f' && size_input<2){
		group1 = querie4(fact,&contador1,1);
		group2 = querie4(fact,&contador2,2);
		group3 = querie4(fact,&contador3,3);
		filial = productsNSoldFiliais(contador1,contador2,contador3);
		switch(filial){
			case 1: group = group1; break;
			case 2: group = group2; break;
			case 3: group = group3; break;
			case 0: backToProductsNSold(CatClients,CatProducts,arrayFiliais,fact,0);
		}
	}

	else if(rep[0] == 'T' || rep[0] == 't' && size_input<2){
		group = querie4(fact,&contador,-1);
	}
	else if(rep[0] == '0'){
		backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);
	}
	else{
		printf("\n\n\n 	Por favor responda somente com T(total) ou F(filial)!\n");
		backToProductsNSold(CatClients,CatProducts,arrayFiliais,fact,3);
	}

	totalPages = calculatePages(group,ELEM_PER_PAGE);
	printPageNSold(group,1,totalPages);
	error = printNSold(group,totalPages);

	if(!error) productsNSold(CatClients,CatProducts,arrayFiliais,fact);
}

int productsNSoldFiliais(int g1,int g2,int g3){
	int filial;
	int input;
	printf("\e[2J\e[H");
	printTop(4);
	printf("							  0.Voltar\n\n");
	printf("	 _______________________________________\n");
	printf("   	|					|\n");
	printf("   	|	FILIAL 1: %d produtos.	|\n",g1);
	printf("   	|	FILIAL 2: %d produtos.	|\n",g2);
	printf("   	|	FILIAL 3: %d produtos.	|\n",g3);
	printf("   	|_______________________________________|\n");
	printf("\n	Gostaria de ver a lista de produtos não vendidos em que filial? ");
	input = scanf("%d",&filial);
	return filial;
}

void printPageNSold(GROUP_PRODUCTS group,int page,int totalPages){
	int i,index;
	printf("\e[2J\e[H");
	printTop(4);
	printf("							  0.Voltar\n");
	printf("\n	Página %d de %d.\n",page,totalPages);
	for(i=0;i<ELEM_PER_PAGE;i++){
		index = i+(ELEM_PER_PAGE*(page-1));
		if(index < getGroupProdSp(group))
			printf("\n				%d | %s",index+1,getProduct(getGroupProd(group)[index]));
	}
}

int printNSold(GROUP_PRODUCTS group,int totalPages){

	int rep = 1,size_input,page,actualPage;

	do{
		printf("\n\n	Escolha uma página: ");
		size_input = scanf("\n%d",&page);

		if(page > 0 && page <= totalPages){
			actualPage = page;
			printPageNSold(group,actualPage,totalPages);
		}
		else if(page == 0) return 0;
		else{
			printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
			sleep(2);
			printPageNSold(group,actualPage,totalPages);
		}
	}
	while(page != 0);
}

void backToProductsNSold (CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime){
	sleep(sleepTime);
	printf("\e[2J\e[H");
	productsNSold(CatClients,CatProducts,arrayFiliais,fact);
}



/* QUERIE 6 */

void periodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char buff_begin[2];int begin;
	char buff_end[2]; int end;
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

	if(begin < 0 || begin > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact,2);
	}
	else if(begin == 0) backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);

	printf("	Introduza o mês final (1-12): ");
	input = scanf("%s",buff_end);
	end = atoi(buff_end);

	if(end < 0 || end > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact,2);
	}
	else if(end == 0) backInterpretador(CatClients,CatProducts,arrayFiliais,fact,0);

	if(begin >= end){
		printf("\n	Introduza um intervalo de meses válido!\n");
		backToPeriodMonths(CatClients,CatProducts,arrayFiliais,fact,2);
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

void backToPeriodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,int sleepTime){
	sleep(sleepTime);
	printf("\e[2J\e[H");
	periodMonths(CatClients,CatProducts,arrayFiliais,fact);
	exit(0);
}

void printDATA(DADOS data,int begin,int end){

	printf("\e[2J\e[H");
	printTop(6);

	printf("	No intervalo de meses (%d-%d):\n\n",begin,end);
	printf("	Foram facturados %f euros.\n",getDadosTP(data));
	printf("	Foram registadas %d vendas.\n",getDadosTQ(data));

}

/* AUXILIARES */

void testMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact,char* menuName){
	if(!totalProducts(CatProducts)){
		printf("\n 		 %s encontra-se vazio de momento. \n",menuName);
		printf("		 Experimente usar primeiro o comando de leitura.\n\n");
		sleep(5);
		printf("\e[2J\e[H");
		interpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
}

int calculatePages(GROUP_PRODUCTS group,int elemPerPage){
	int totalPages = (getGroupProdSp(group)/elemPerPage);
	if(totalPages*elemPerPage < getGroupProdSp(group)) totalPages++;
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

		case 2:  /* CATÁLOGO DE PRODUTOS */
			printf("\n	                        CATÁLOGO DE PRODUTOS                                      \n");
			break;

		case 3:
			printf("\n	                   PRODUTO NUM DETERMINADO MÊS                                \n");
			break;

		case 4:
			printf("\n	                        PRODUTOS NÃO VENDIDOS                                     \n");
			break;

		case 6:
			printf("\n	                        PERÍODO DE MESES                                          \n");
			break;
	}
	printf("________________________________________________________________________________\n");
	printf("\n");
}