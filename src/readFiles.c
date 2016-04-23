#include "headers/readFiles.h"

static int valCli(FILE *,CATALOG_CLIENTS,int*);
static int valProd(FILE *,CATALOG_PRODUCTS,int*);
static int valSales(FILE *,CATALOG_CLIENTS,CATALOG_PRODUCTS,FILIAL*,FACTURACAO,int*);


/* Faz o cálculo do número de validações em cada um dos ficheiros, em simultâneo guarda o que é
validado em memória, na respectiva estrutura. */
int getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact,char* clientsFile,char* productsFile,char* salesFile){

	int r=1;

	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	int invalidatedSales = 0;
	int invalidatedClients = 0;
	int invalidatedProducts = 0;
	int i;
	
	/* TEMPOS */
	time_t begin_clients;
	time_t begin_products;
	time_t begin_sales;
	time_t end_clients;
	time_t end_products;
	time_t end_sales;
	double time_elapsed_clients = 0;
	double time_elapsed_products = 0;
	double time_elapsed_sales = 0;

	
	fileClients = fopen(clientsFile,"r");	
	fileProducts = fopen(productsFile,"r");
	fileSales = fopen(salesFile,"r");
	
	
	if(fileClients!=NULL){
		time(&begin_clients);
		invalidatedClients = valCli(fileClients,clients,&validatedClients);
		for(i=0;i<3;i++)
			f[i] = copyCPO(f[i],clients);
		time(&end_clients);
		time_elapsed_clients = difftime(end_clients,begin_clients);
		
		printf("	 _______________________________________\n");
		printf("	| 		CLIENTES 		|\n");
		printf("	| Nome do ficheiro: %18s	|\n",clientsFile);
		printf("	| Foram lidas %7d linhas.		|\n",validatedClients+invalidatedClients);
		printf("	| Foram validadas %7d linhas.	|\n",validatedClients);
		printf("	| Não foram validadas %7d linhas.	|\n",invalidatedClients);
		printf("	| Tempo de leitura: %9f s.	|\n",time_elapsed_clients);
		printf("	|_______________________________________|\n");
	}
	else return 0;



	if(fileProducts!=NULL){
		time(&begin_products);
		invalidatedProducts = valProd(fileProducts,products,&validatedProducts);
		fact = copyProducts(fact,products);
		for(i=0;i<3;i++)
			f[i] = copyP(f[i],products);
		time(&end_products);
		time_elapsed_products = difftime(end_products,begin_products);
		
		printf("	 _______________________________________\n");
		printf("	| 		PRODUTOS 		|\n");
		printf("	| Nome do ficheiro: %18s	|\n",productsFile);
		printf("	| Foram lidas %7d linhas.		|\n",validatedProducts+invalidatedProducts);
		printf("	| Foram validadas %7d linhas.	|\n",validatedProducts);
		printf("	| Não foram validadas %7d linhas.	|\n",invalidatedProducts);
		printf("	| Tempo de leitura: %9f s.	|\n",time_elapsed_products);
		printf("	|_______________________________________|\n");
	}
	else return 0;

	
	if(fileSales!=NULL){
		time(&begin_sales);
		invalidatedSales = valSales(fileSales,clients,products,f,fact,&validatedSales);
		time(&end_sales); 
		time_elapsed_sales = difftime(end_sales,begin_sales);


		printf("	 _______________________________________\n");
		printf("	| 		VENDAS 			|\n");
		printf("	| Nome do ficheiro: %18s	|\n",salesFile);
		printf("	| Foram lidas %7d linhas.		|\n",validatedSales+invalidatedSales);
		printf("	| Foram validadas %7d linhas.	|\n",validatedSales);
		printf("	| Não foram validadas %7d linhas.	|\n",invalidatedSales);
		printf("	| Tempo de leitura: %9f s.	|\n",time_elapsed_sales);
		printf("	|_______________________________________|\n");
	}
	else return 0;

	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	

	return r;
}

/* Faz a validação dos clientes. */
static int valCli(FILE *file, CATALOG_CLIENTS Catalog ,int *validated){

	int invalidated = 0;
	char buffer[SIZE_BUFFER];
	CLIENT line = initClie();

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setClient(line,strtok(buffer,"\r\n"));
		if(testClient(line)){
			Catalog = insertClient(Catalog,line);
			(*validated)++;
		}
		else invalidated++;
	}
		
	return invalidated;
}

/* Faz a validação dos produtos. */
static int valProd(FILE *file, CATALOG_PRODUCTS Catalog ,int *validated){

	int invalidated = 0;
	char buffer[SIZE_BUFFER];
	PRODUCT line =initProd();

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setProduct(line,strtok(buffer,"\r\n"));
		if(testProduct(line)){
			Catalog = insertProduct(Catalog,line);
			(*validated)++;
		}
		else invalidated++;
	}
		
	return invalidated;
}

/* Conta quantas linhas do ficheiro com as vendas são válidas. */
static int valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact,int *validated){

	char buffer[SIZE_BUF_SALES],*line;
	int r,invalidated=0;
	int month,filial,quant;
	double price;
	char infoP;
	CLIENT clie=initClie(); 
	PRODUCT prod=initProd();
	SALES sales = initSales();

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		/* verificar, em caso positivo alocar espaço para a string e copia-la para o array. */
		r = partCheck(line,clients,products,&clie,&prod,&month,&filial,&quant,&price,&infoP);
		if(r){

			sales = updateSales(sales,clie,prod,month,filial,quant,price,infoP);
			insereFact(fact,sales);

			switch(filial){
				case(1): f[0] = insertFilial(f[0],sales); break;
				case(2): f[1] = insertFilial(f[1],sales); break;
				case(3): f[2] = insertFilial(f[2],sales); break;
			}

			(*validated)++;
		}
		else invalidated++;

	}
	free(sales);
	freeProduct(prod);
	freeClient(clie);
	return invalidated;
}

void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	int i;
	removeCatClients(CatClients);
	removeCatProds(CatProducts);
	freeFact(fact);
	for(i=0;i<3;i++)
		freeFilial(arrayFiliais[i]);	
} 