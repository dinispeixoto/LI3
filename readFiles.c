#include "readFiles.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"			

/* Faz o cálculo do número de validações em cada um dos ficheiros, em simultâneo guarda o que é
validado em memória, na respectiva estrutura. */
void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,SALES* sales){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	int invalidatedSales = 0;
	
	/*
	fileClients = openFile();	
	fileProducts = openFile();	
	fileSales = openFile();	
	*/
	
	fileClients = fopen(CLIENTS_FILE,"r");	
	fileProducts = fopen(PRODUCTS_FILE,"r");
	fileSales = fopen(SALES_FILE,"r");
	
	

	if(fileClients!=NULL){
		clients = valCli(fileClients,clients,&validatedClients);
		printf("CLIENTES: Foram validadas %d linhas.\n",validatedClients);
	}

	if(fileProducts!=NULL){
		products = valProd(fileProducts,products,&validatedProducts);
		printf("PRODUTOS: Foram validadas %d linhas.\n",validatedProducts);
	}
	
	if(fileSales!=NULL){
		sales = valSales(fileSales,clients,products,sales,&validatedSales,&invalidatedSales);
		printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
	}

	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}


FILE* openFile(){ 
	FILE* file;                             /* Isto é o base, tem de ser melhorado conforme necessitarmos quando tivermos o intrepertador. */
	char fileName[SIZE_FILE_NAME];
	scanf("%s", fileName);
	file = fopen(fileName,"r");
	if(!file){ printf("Não consegui ler o ficheiro.\n"); file = openFile();}
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
SALES* valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,SALES* sales,int *validated, int *invalidated){

	char buffer[SIZE_BUF_SALES],*line;
	int r;
	CLIENT clie = NULL; /* METI ESTA PORCARIA ASSIM PARA NÃO DAR WARNINGS */
	PRODUCT prod = NULL;
	int month,filial,quant;
	double price;
	char infoP;

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		/* verificar, em caso positivo alocar espaço para a string e copia-la para o array. */
		r = partCheck(line,clients,products,&clie,&prod,&month,&filial,&quant,&price,&infoP);
		if(r){
			sales[*validated] = updateSales(clie,prod,month,filial,quant,price,infoP);
			(*validated)++;
		}
		else (*invalidated)++;
	}
	return sales;
}
 