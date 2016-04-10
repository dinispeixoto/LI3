#include "readFiles.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"			


/* Faz o cálculo do número de validações em cada um dos ficheiros, em simultâneo guarda o que é
validado em memória, na respectiva estrutura. */
void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,SALES sales,FACTURACAO fact){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	int invalidatedSales = 0;
	
	/* TEMPOS */
	time_t begin_clients;
	time_t begin_products;
	time_t begin_sales;
	time_t end_clients;
	time_t end_products;
	time_t end_sales;
	long time_elapsed_clients;
	long time_elapsed_products;
	long time_elapsed_sales;

	/*
	fileClients = openFile();	
	fileProducts = openFile();	
	fileSales = openFile();	
	*/
	
	fileClients = fopen(CLIENTS_FILE,"r");	
	fileProducts = fopen(PRODUCTS_FILE,"r");
	fileSales = fopen(SALES_FILE,"r");
	
	
	begin_clients = clock();
	if(fileClients!=NULL){
		clients = valCli(fileClients,clients,&validatedClients);
		printf("	CLIENTES: Foram validadas %d linhas.\n",validatedClients);
	}
	end_clients = clock();


	begin_products = clock();
	if(fileProducts!=NULL){
		products = valProd(fileProducts,products,&validatedProducts);
		printf("	PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
		fact = copyProducts(fact,products);
	}
	end_products = clock();
	

	begin_sales = clock();
	if(fileSales!=NULL){
		sales = valSales(fileSales,clients,products,sales,fact,&validatedSales,&invalidatedSales);
		printf("	VENDAS: Foram validadas %d linhas.\n",validatedSales);
	}
	end_sales = clock();


	time_elapsed_clients = (double)end_clients - begin_clients / (CLOCKS_PER_SEC);
	time_elapsed_products = (double)end_products - begin_products / (CLOCKS_PER_SEC);
	time_elapsed_sales = (double)end_sales - begin_sales / (CLOCKS_PER_SEC);

	putchar('\n');
	printf("	Tempo de leitura dos CLIENTES: %ld ms.\n",time_elapsed_clients/1000);
	printf("	Tempo de leitura dos PRODUTOS: %ld ms.\n",time_elapsed_products/1000);
	printf("	Tempo de leitura das VENDAS: %ld ms.\n",time_elapsed_sales/1000);

	
	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}


FILE* openFile(char* fileName){ 
	FILE* file;                        
	file = fopen(fileName,"r");
	if(!file) printf("Não consegui ler o ficheiro: %s.\n",fileName); 
	return file;
}


/* Faz a validação dos clientes. */
CATALOG_CLIENTS valCli(FILE *file, CATALOG_CLIENTS Catalog ,int *validated){

	char buffer[SIZE_BUFFER];
	CLIENT line = malloc(sizeof(CLIENT));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setClient(strtok(buffer,"\r\n"));
		Catalog = insertClient(Catalog,line);
		(*validated)++;
	}
		
	return Catalog;
}

/* Faz a validação dos produtos. */
CATALOG_PRODUCTS valProd(FILE *file, CATALOG_PRODUCTS Catalog ,int *validated){

	char buffer[SIZE_BUFFER];
	PRODUCT line = malloc(sizeof(PRODUCT));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setProduct(strtok(buffer,"\r\n"));
		Catalog = insertProduct(Catalog,line);
		(*validated)++;
	}
		
	return Catalog;
}

/* Conta quantas linhas do ficheiro com as vendas são válidas. */
SALES valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,SALES sales,FACTURACAO fact,int *validated, int *invalidated){

	char buffer[SIZE_BUF_SALES],*line;
	int r;
	CLIENT clie = NULL;
	PRODUCT prod = NULL;
	int month,filial,quant;
	double price;
	char infoP;

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		/* verificar, em caso positivo alocar espaço para a string e copia-la para o array. */
		r = partCheck(line,clients,products,&clie,&prod,&month,&filial,&quant,&price,&infoP);
		if(r){
			sales = updateSales(clie,prod,month,filial,quant,price,infoP);
			insereFact(fact,sales);
			(*validated)++;
		}
		else (*invalidated)++;
	}
	return sales;
}