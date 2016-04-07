#include "readFiles.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"			


void getFile(CATALOG_CLIENTS clients, CATALOG_PRODUCTS products,SALES* sales){

			
	FILE *fileClients,*fileProducts,*fileSales;	
	int validatedClients = 0;
	int validatedProducts = 0;
	int validatedSales = 0;
	
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
		validatedSales = valSales(fileSales,clients,products,sales);
		printf("VENDAS: Foram validadas %d linhas.\n",validatedSales);
	}


	fclose(fileClients);
	fclose(fileProducts);
	fclose(fileSales);	
}


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

/* Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array. */
int valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,SALES* sales){

	char buffer[SIZE_BUF_SALES],*line;
	int validated=0,r;
	CLIENT clie;
	PRODUCT prod;
	int month,filial,quant;
	double price;
	char infoP;

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		/* verificar, em caso positivo alocar espaço para a string e copia-la para o array. */
		r = partCheck(line,clients,products,clie,prod,&month,&filial,&quant,&price,&infoP);
		if(r){
			sales[validated] = malloc(sizeof(SALES));
			setSalesClient(clie,sales[validated]);
			setSalesProduct(prod,sales[validated]);
			setSalesPrice(price,sales[validated]);
			setSalesQuantity(quant,sales[validated]);
			setSalesInfoPromo(infoP,sales[validated]);
			setSalesFilial(filial,sales[validated]);
			setSalesMonth(month,sales[validated]);	
			validated++;
		}
	}
	return validated;
}
