#include "readFiles.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"
#include "facturacao.h"		
#include "filial.h"	

/* Faz o cálculo do número de validações em cada um dos ficheiros, em simultâneo guarda o que é
validado em memória, na respectiva estrutura. */
void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	int invalidated = 0;
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

	/*
	fileClients = openFile();	
	fileProducts = openFile();	
	fileSales = openFile();	
	*/
	
	fileClients = fopen(CLIENTS_FILE,"r");	
	fileProducts = fopen(PRODUCTS_FILE,"r");
	fileSales = fopen(SALES_FILE,"r");
	
	
	if(fileClients!=NULL){
		begin_clients = clock();
		clients = valCli(fileClients,clients,&validatedClients);
		for(i=0;i<3;i++)
			f[i] = copyCPO(f[i],clients);
		printf("	CLIENTES: Foram validadas %d linhas.\n",validatedClients);
		end_clients = clock();
	}



	if(fileProducts!=NULL){
		begin_products = clock();
		products = valProd(fileProducts,products,&validatedProducts);
		printf("	PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
		fact = copyProducts(fact,products);
		/*filiais = copyP(filiais,products);*/
		end_products = clock();
	}

	
	if(fileSales!=NULL){
		begin_sales = clock();
		invalidated = valSales(fileSales,clients,products,f,fact,&validatedSales);
		end_sales = clock();
		printf("	VENDAS: Foram validadas %d linhas.\n",validatedSales);
		printf("	VENDAS: Não foram validadas %d linhas.\n",invalidated);
	}


	time_elapsed_clients = (double) (end_clients - begin_clients) / CLOCKS_PER_SEC;
	time_elapsed_products = (double) (end_products - begin_products) / CLOCKS_PER_SEC;
	time_elapsed_sales = (double) (end_sales - begin_sales) / CLOCKS_PER_SEC;

	putchar('\n');
	printf("	Tempo de leitura dos CLIENTES: %f s.\n",time_elapsed_clients);
	printf("	Tempo de leitura dos PRODUTOS: %f s.\n",time_elapsed_products);
	printf("	Tempo de leitura das VENDAS: %f s.\n",time_elapsed_sales);



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
int valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact,int *validated){

	char buffer[SIZE_BUF_SALES],*line;
	int r,invalidated=0;
	CLIENT clie = NULL;
	PRODUCT prod = NULL;
	int month,filial,quant;
	double price;
	char infoP;
	SALES sales = initSales();

	/* TESTES */

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
