#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		sleep(4);
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
}




/* DESCRIÇÃO DE COMANDOS 
	printf("1. leitura <ficheiro> <ficheiro> <ficheiro>\n");
	printf("2. produtos-letra <letra>\n");
	printf("3. vendas-facturado <mês> <produto> <info>\n"); // INFO = RESULTADO GLOBAL OU POR FILIAL
	printf("4. produtos-nao-vendidos <info>\n"); // INFO = RESULTADO GLOBAL OU POR FILIAL
	printf("5. compras-cliente <cliente>\n");
	printf("6. vendas-meses <mês-inicio> <mês-fim>\n");
	printf("7. clientes-todas-filiais\n");
	printf("8. produtos-filial <produto> <filial>\n");
	printf("9. maiores-compras <cliente> <mês>\n");
	printf("10. mais-vendidos <numero>\n");
	printf("11. maiores-despesas <cliente>\n");
	printf("12. inativos\n");

	token = strtok(buffer,"\r\n");

	token = strtok(buffer," ");
	for(i=0;token!=NULL && i<4;i++){
		switch(i){
			case 0: strcpy(command,token); break;
			case 1: strcpy(arg1,token); break;
			case 2: strcpy(arg2,token); break;
			case 3: strcpy(arg3,token); break;
		}
		token = strtok(NULL," ");
	}

	nArgs = i;


int main(){	

	int i,contador2=0;
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	SALES* Sales = initSales();

	printf("CORRER O PROGRAMA\n");
	getFile(CatClients,CatProducts,Sales);	

	putchar('\n');
	printf("LIMPEZA\n");
	removeCatClients(CatClients);
	removeCatProds(CatProducts);
	for(i=0;i<1000000;i++) if(Sales[i])freeSale(Sales[i]);
	printf("NUMERO DE CLIENTES:%d\n",totalElements(getMY_AVL(CatClients)));
	printf("NUMERO DE PRODUTOS:%d\n",totalElements(getMY_AVL2(CatProducts)));
	for(i=0;i<1000000;i++)
		if(Sales[i]==NULL) 
			contador2++;
	printf("NUMERO DE SALES:%d\n",contador2);

	putchar('\n');
	printf("CORRER NOVAMENTE\n");
	getFile(CatClients,CatProducts,Sales);	

	return 0;
}

TESTAR A GROUP_PRODUCTS POR LETRA
		for(l = 'A';l<='Z';l++){
		GROUP_PRODUCTS a = productsLetter(CatProducts,l);
		for(i=0;i<getGroupProdSize(a);i++)
			printf("%s\n",getProduct(getGroupProd(a)[i]));
	}

##########################TESTES######################################
	getchar();
	int i;
	double cont=0;
	int cont2=0;

	DADOS d=querie3(fact,5,"AF1184",1);

	for(i=0;i<3;i++){
		printf("Filial %d: Price-> %f | Quant -> %d\n",i,getDadosP(d)[i],getDadosQ(d)[i]);
		cont+=getDadosP(d)[i];
		cont2+=getDadosQ(d)[i];
	}
	printf("TotalpriceMes -> %f\n",cont );
	printf("TotalquantMes -> %d\n",cont2);
*/
