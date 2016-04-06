#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"					

#define MAX_SALES 1000000

struct sales{
	CLIENT client;
	PRODUCT product;
	double price;
	int quantity;
	char infoPromo;
	int filial;
	int month;
};

static int partCheck(char*,CATALOG_CLIENTS,CATALOG_PRODUCTS,CLIENT,PRODUCT,int*,int*,int*,double*,char*);
static int testSales(CLIENT,PRODUCT,float,int,char,int,int);

SALES* initSales(){
	SALES* sales = malloc (MAX_SALES*sizeof(SALES));
	return sales;
}

/* Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array. */
int valSales(FILE *file,CATALOG_CLIENTS clients,CATALOG_PRODUCTS  products,SALES* sales){

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
			sales[validated] = malloc(sizeof(struct sales));
			sales[validated]->client = clie;
			sales[validated]->product = prod;
			sales[validated]->price = price;
			sales[validated]->quantity = quant;
			sales[validated]->infoPromo = infoP;
			sales[validated]->filial = filial;
			sales[validated]->month = month;
			validated+=r;
		}
	}
	return validated;
}

/*Função que reparte um linha de venda, e verifica se a linha é válida,ou seja, se o produto e cliente exitem, 
e se os outros parametros estao corretos. */
static int partCheck(char* line, CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,CLIENT clie,PRODUCT prod,int *month,int *filial,int *quant,double *price,char *infoP){
	char *token;
	int r=0, i;

		
	token = strtok(line, " ");

	for(i=0;token != NULL;i++){
		switch(i){
			case 0: prod = setProductString(token); break;
			case 1: *price = atof(token); break;
			case 2: *quant = atoi(token); break;
			case 3: *infoP = token[0]; break;
			case 4: clie = setClientString(token); break;
			case 5: *month = atoi(token); break;
			case 6: *filial = atoi(token); break;
		}
			token = strtok(NULL, " ");
	}

	/*int indexClient =  *clie[0]-'A';
	int indexProduct = *prod[0]-'A';

	Avl auxClient = getC(clients,indexClient);
	Avl auxProduct = getP(products,indexProduct);*/


	if(/*testSales(clie,prod,*price,*quant,*infoP,*month,*filial) &&*/ existClient(clients,clie) && existProduct(products,prod)) r=1;
	return r;
}

/* Testa as diferentes cenas das Vendas.
	 Preço de 0 a 999.99;
	 Quantidade de 0 a 200;
	 Caracter a informar se o preço é normal(N) ou em promoção(P);
	 Mês (1 a 12);
	 Filial (1 a 3);
*/

static int testSales(CLIENT clie, PRODUCT prod,float price, int quantity, char infoPromo, int month, int filial){

  if(price < 0 || price > 999.99) return 0;
  else if(!testClient(clie)) return 0;
  else if(!testProduct(prod)) return 0;
  else if(quantity < 1 || quantity > 200) return 0;
  else if(infoPromo != 'P' && infoPromo != 'N') return 0;
  else if(month < 1 || month > 12) return 0;
  else if(filial < 1 || filial > 3) return 0;
  else return 1;
}