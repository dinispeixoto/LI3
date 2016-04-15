
#include "interpretador.h"

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
	
	if(buffer[0] == '0') exit(0);

	else if(buffer[0] == '1')
		readFiles(CatClients,CatProducts,arrayFiliais,fact); 

	else if(buffer[0] == '2') 
		readCatalog(CatClients,CatProducts,arrayFiliais,fact);

	else if(buffer[0] == '3')
		productMonth(CatClients,CatProducts,arrayFiliais,fact);
			
	else if(buffer[0] == '4')
		productsNSold(CatClients,CatProducts,arrayFiliais,fact); /* FALTA DAR ERRO SE NÃO TIVERMOS LIDO PRIMEIRO && OUTROS ERROS DA FUNÇÃO && APRESENTAR POR PÁGINAS */

	else if(buffer[0] == '6')
		periodMonths(CatClients,CatProducts,arrayFiliais,fact);

	else{
		printf("	Este comando não é válido!\n");
		sleep(1);
		printf("\e[2J\e[H");
		interpretador(CatClients,CatProducts,arrayFiliais,fact);
	}
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
	else interpretador(CatClients,CatProducts,arrayFiliais,fact);
}



/* QUERIE 2 */

void readCatalog(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	GROUP_PRODUCTS group;
	char rep;
	int page,totalPages,size_input;

	printf("\e[2J\e[H");
	
	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos");

	printTop(2);
	printf("										0.Voltar\n");
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
			else if(page == 0) interpretador(CatClients,CatProducts,arrayFiliais,fact);
			else{
				printf("	Por favor insira uma página de 1 a %d.\n",totalPages);
				sleep(2);
				printf("\e[2J\e[H");
				readCatalog(CatClients,CatProducts,arrayFiliais,fact);
			}
		}
		while(page != 0);

	}
	else if(rep == '0') interpretador(CatClients,CatProducts,arrayFiliais,fact);
	else{
		printf("	Por favor insira uma letra de A a Z.\n");
		sleep(2);
		printf("\e[2J\e[H");
		readCatalog(CatClients,CatProducts,arrayFiliais,fact);
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

/* QUERIE 3 */

void productMonth(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int input,month,exist,filial,i;
	double totalPrice_data1=0,totalPrice_data2=0;
	int totalQuant_data1=0,totalQuant_data2=0;
	char rep,c;
	char productString[6];
	DADOS data1;
	DADOS data2;

	PRODUCT prod = malloc(sizeof(PRODUCT));

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre um produto num determinado mês");

	printTop(3);

	printf("\n										0.Voltar\n");

	printf("	Introduza o mês (1-12): ");
	input = scanf("%d",&month);

	if(month < 0 || month > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		sleep(2);
		printf("\e[2J\e[H");
		productMonth(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}
	else if(month == 0){
		 interpretador(CatClients,CatProducts,arrayFiliais,fact);
		 exit(0);
	}

	printf("	Introduza o produto: ");
	input = scanf("%s",productString);
		
	if(!strcmp(productString,"0")){
		interpretador(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}
	/*productString[7] = 0;*/
	prod = setProduct(productString);
	exist = existProduct(CatProducts,prod);

	if(!exist){
		printf("\n	Este produto não existe no Cátalogo!\n");
		sleep(2);
		printf("\e[2J\e[H");
		productMonth(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	data1 = querie3(fact,month,productString,0);
	data2 = querie3(fact,month,productString,1);

	printf("	Deseja a informação sobre o produto total ou por filial? T/F ");
	input = scanf("\n%c",&rep);

	if(rep == 'F'){
		printf("	Qual o filial que deseja: ");
		input = scanf("\n%d",&filial);
		printf("	Filial %d: Price-> %f | Quant -> %d\n",filial,getDadosP(data1)[filial],getDadosQ(data1)[filial]);
		printf("	Filial %d: Price-> %f | Quant -> %d\n",filial,getDadosP(data2)[filial],getDadosQ(data2)[filial]);
	}

	else if(rep == 'T'){
		for(i=0;i<3;i++){
			totalPrice_data1+=getDadosP(data1)[i];
			totalPrice_data2+=getDadosP(data2)[i];
			totalQuant_data1+=getDadosQ(data1)[i]; 
			totalQuant_data2+=getDadosQ(data2)[i]; 
		}

		printf("\n\n\n");
		printf("		PROMO -> N\n");
		printf("	TotalpriceMes -> %f\n",totalPrice_data1);
		printf("	TotalquantMes -> %d\n",totalQuant_data1);
		putchar('\n');
		printf("		PROMO -> P\n");
		printf("	TotalpriceMes -> %f\n",totalPrice_data2);
		printf("	TotalquantMes -> %d\n\n",totalQuant_data2);

	}
	
	else if(rep == '0'){
		interpretador(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	else{
		printf("\n\n\n 		Por favor responda somente com T(total) ou F(filial)!\n");
		sleep(3);
		printf("\e[2J\e[H");
		productMonth(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	while(getchar()!='\n');
	c = getchar();
	if(c!='0') productMonth(CatClients,CatProducts,arrayFiliais,fact);
	else interpretador(CatClients,CatProducts,arrayFiliais,fact);
	
}


/* QUERIE 4 */
void productsNSold(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	char rep;
	int filial,contador=0,totalPages,size_input,error,i;
	GROUP_PRODUCTS group;


	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de Produtos não vendidos");

	printTop(4);

	printf("	Deseja os produtos totais ou por filial? T/F ");
	size_input = scanf("\n%c",&rep);

	if(rep == 'F'){
		printf("	Qual o filial que deseja: ");
		size_input = scanf("\n%d",&filial);
		/* fazer o caso em que é 0 -> voltar.*/
		group = querie4(fact,&contador,filial);
	}

	else if(rep == 'T'){
		group = querie4(fact,&contador,-1);
	}

	else{
		printf("\n\n\n 		Por favor responda somente com T(total) ou F(filial)!\n");
		sleep(3);
		printf("\e[2J\e[H");
		productsNSold(CatClients,CatProducts,arrayFiliais,fact);
	}

	totalPages = calculatePages(group,ELEM_PER_PAGE);
	printPageNSold(group,1,totalPages);
	error = printNSold(group,totalPages);


	if(error == -1) productsNSold(CatClients,CatProducts,arrayFiliais,fact);
	else if(error == 0) interpretador(CatClients,CatProducts,arrayFiliais,fact);
}

void printPageNSold(GROUP_PRODUCTS group,int page,int totalPages){
	int i,index;
	printf("\n	Página %d de %d.\n",page,totalPages);
	for(i=0;i<ELEM_PER_PAGE;i++){
		index = i+(ELEM_PER_PAGE*(page-1));
		if(index < getGroupProdSp(group))
			printf("\n	%d | %s",index+1,getProduct(getGroupProd(group)[index]));
	}
}

int printNSold(GROUP_PRODUCTS group,int totalPages){

	int rep = 1,size_input,page;

	do{
		
		printf("\n\n	Escolha uma página: ");
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


/* QUERIE 6 */

void periodMonths(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){

	int begin;
	int end;
	int input;
	char c;

	DADOS data;

	printf("\e[2J\e[H");

	testMemory(CatClients,CatProducts,arrayFiliais,fact,"O Catálogo de informações sobre um período de meses");

	printTop(6);

	printf("	Introduza o mês inicial (1-12): ");
	input = scanf("%d",&begin);

	if(begin <= 0 || begin > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		sleep(2);
		printf("\e[2J\e[H");
		periodMonths(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	printf("	Introduza o mês final (1-12): ");
	input = scanf("%d",&end);

	if(end <= 0 || end > 12){
		printf("\n	Introduza um mês válido (1-12)!\n");
		sleep(2);
		printf("\e[2J\e[H");
		periodMonths(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	if(begin >= end){
		printf("\n	Introduza um intervalo de meses válido!\n");
		sleep(2);
		printf("\e[2J\e[H");
		periodMonths(CatClients,CatProducts,arrayFiliais,fact);
		exit(0);
	}

	data = querie6(fact,begin,end);
	printDATA(data,begin,end);

	while(getchar()!='\n');
	c = getchar();
	if(c!='0') periodMonths(CatClients,CatProducts,arrayFiliais,fact);
	else interpretador(CatClients,CatProducts,arrayFiliais,fact);

}

void printDATA(DADOS data,int begin,int end){

	printf("\e[2J\e[H");
	printTop(6);

	printf("	No intervalo de meses (%d-%d):\n\n",begin,end);
	printf("	Total facturado -> %f\n",getDadosTP(data));
	printf("	Total de vendas registadas -> %d\n",getDadosTQ(data));

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

void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	/* LIMPAR MEMÓRIA */
	removeCatClients(CatClients);
	removeCatProds(CatProducts);
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
			printf("\n	                            CATÁLOGO DE PRODUTOS                                      \n");
			break;

		case 3:
			printf("\n	                            PRODUTO NUM DETERMINADO MÊS                                \n");
			break;

		case 4:
			printf("\n	                            PRODUTOS NÃO VENDIDOS                                     \n");
			break;

		case 6:
			printf("\n	                            PERÍODO DE MESES                                          \n");
			break;
	}
	printf("________________________________________________________________________________\n");
	printf("\n\n");
}