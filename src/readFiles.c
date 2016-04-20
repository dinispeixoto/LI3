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
		begin_clients = clock();
		invalidatedClients = valCli(fileClients,clients,&validatedClients);
		for(i=0;i<3;i++)
			f[i] = copyCPO(f[i],clients);
		end_clients = clock();
		time_elapsed_clients = (double) (end_clients - begin_clients) / CLOCKS_PER_SEC;
		
		printf("	 _______________________________________\n");
		printf("	| 		CLIENTES 		|\n");
		printf("	| Nome do ficheiro: %15s.	|\n",clientsFile);
		printf("	| Foram lidas %7d linhas.		|\n",validatedClients+invalidatedClients);
		printf("	| Foram validadas %7d linhas.	|\n",validatedClients);
		printf("	| Não foram validadas %7d linhas.	|\n",invalidatedClients);
		printf("	| Tempo de leitura: %9f s.	|\n",time_elapsed_clients);
		printf("	|_______________________________________|\n");
	}
	else return 0;



	if(fileProducts!=NULL){
		begin_products = clock();
		invalidatedProducts = valProd(fileProducts,products,&validatedProducts);
		fact = copyProducts(fact,products);
		end_products = clock();
		time_elapsed_products = (double) (end_products - begin_products) / CLOCKS_PER_SEC;
		
		printf("	 _______________________________________\n");
		printf("	| 		PRODUTOS 		|\n");
		printf("	| Nome do ficheiro: %15s.	|\n",productsFile);
		printf("	| Foram lidas %7d linhas.		|\n",validatedProducts+invalidatedProducts);
		printf("	| Foram validadas %7d linhas.	|\n",validatedProducts);
		printf("	| Não foram validadas %7d linhas.	|\n",invalidatedProducts);
		printf("	| Tempo de leitura: %9f s.	|\n",time_elapsed_products);
		printf("	|_______________________________________|\n");
	}
	else return 0;

	
	if(fileSales!=NULL){
		begin_sales = clock();
		invalidatedSales = valSales(fileSales,clients,products,f,fact,&validatedSales);
		end_sales = clock();
		time_elapsed_sales = (double) (end_sales - begin_sales) / CLOCKS_PER_SEC;


		printf("	 _______________________________________\n");
		printf("	| 		VENDAS 			|\n");
		printf("	| Nome do ficheiro: %15s.	|\n",salesFile);
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
	CLIENT line = malloc(sizeof(CLIENT));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setClient(strtok(buffer,"\r\n"));
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
	PRODUCT line = malloc(sizeof(PRODUCT));

	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){
		line = setProduct(strtok(buffer,"\r\n"));
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
	CLIENT clie = NULL;
	PRODUCT prod = NULL;
	int month,filial,quant;
	double price;
	char infoP;
	SALES sales = initSales();

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		/* verificar, em caso positivo alocar espaço para a string e copia-la para o array. */
		r = partCheck(line,clients,products,&clie,&prod,&month,&filial,&quant,&price,&infoP);
		if(r){
			sales = updateSales(clie,prod,month,filial,quant,price,infoP);
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

	return invalidated;
}

void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact){
	/* LIMPAR MEMÓRIA */
	int i;
	if(CatClients && CatProducts /*&& arrayFiliais && fact*/){
		removeCatClients(CatClients);
		removeCatProds(CatProducts);
		freeFact(fact);
		for(i=0;i<3;i++)
			freeFilial(arrayFiliais[i]);
	}
	else{
		printf("A MEMÓRIA JÁ ESTÁ VAZIA\n");
	}
		
} 