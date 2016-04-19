#define MAX_SALES 1000000

#include "headers/Sales.h"


struct sales{
	CLIENT client;
	PRODUCT product;
	PRICE price;
	QUANTITY quantity;
	INFO_PROMO infoPromo;
	FILIAIS filial;
	MONTH month;
};

static int testSales(CLIENT,PRODUCT,double,int,char,int,int);

/* Inicializa uma estrutura SALES. */
SALES initSales(){
	SALES a = malloc(sizeof(struct sales));
	a->client=NULL;
	a->product=NULL; 
	return a;
}

void freeSale(SALES a){
	if(a){
		freeClient(a->client);
		freeProduct(a->product);
		free(a);
	}	
}

/* GETS E SETS */

CLIENT getSalesClient(SALES a){
	return a->client;
}

SALES setSalesClient(CLIENT c,SALES a){
	a->client = setClient(getClient(c));
	return a;
}

PRODUCT getSalesProduct(SALES a){
	return a->product;
}

SALES setSalesProduct(PRODUCT c,SALES a){
	a->product = setProduct(getProduct(c));
	return a;
}

PRICE getSalesPrice(SALES a){
	return a->price;
}

SALES setSalesPrice(PRICE c,SALES a){
	a->price = c;
	return a;
}

QUANTITY getSalesQuantity(SALES a){
	return a->quantity;
}

SALES setSalesQuantity(QUANTITY c,SALES a){
	a->quantity = c;
	return a;
}

INFO_PROMO getSalesInfoPromo(SALES a){
	return a->infoPromo;
}

SALES setSalesInfoPromo(INFO_PROMO c,SALES a){
	a->infoPromo = c;
	return a;
}

FILIAIS getSalesFilial(SALES a){
	return a->filial;
}

SALES setSalesFilial(FILIAIS c,SALES a){
	a->filial = c;
	return a;
}

MONTH getSalesMonth(SALES a){
	return a->month;
}

SALES setSalesMonth(MONTH c,SALES a){
	a->month = c;
	return a;
}

/*Função que reparte um linha de venda, e verifica se a linha é válida,ou seja, se o produto e cliente exitem, 
e se os outros parametros estao corretos. */
int partCheck(char* line, CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,CLIENT* clie,PRODUCT* prod,int *month,int *filial,int *quant,double *price,char *infoP){
	char *token;
	int r=0, i;

		
	token = strtok(line, " ");

	for(i=0;token != NULL;i++){
		switch(i){
			case 0: *prod = setProduct(token); break;
			case 1: *price = atof(token); break;
			case 2: *quant = atoi(token); break;
			case 3: *infoP = token[0]; break;
			case 4: *clie = setClient(token); break;
			case 5: *month = atoi(token); break;
			case 6: *filial = atoi(token); break;
		}
			token = strtok(NULL, " ");
	}

	if(testSales(*clie,*prod,*price,*quant,*infoP,*month,*filial) && existClient(clients,*clie) && existProduct(products,*prod)) r=1;
	return r;
}

/* Testa as diferentes cenas das Vendas.
	 Preço de 0 a 999.99;
	 Quantidade de 0 a 200;
	 Caracter a informar se o preço é normal(N) ou em promoção(P);
	 Mês (1 a 12);
	 Filial (1 a 3);
*/

static int testSales(CLIENT clie, PRODUCT prod,double price, int quantity, char infoPromo, int month, int filial){

  if(price < 0 || price > 999.99) return 0;
  else if(!testClient(clie)) return 0;
  else if(!testProduct(prod)) return 0;
  else if(quantity < 1 || quantity > 200) return 0;
  else if(infoPromo != 'P' && infoPromo != 'N') return 0;
  else if(month < 1 || month > 12) return 0;
  else if(filial < 1 || filial > 3) return 0;
  else return 1;
}

SALES updateSales(CLIENT clie,PRODUCT prod,MONTH month,FILIAIS filial,QUANTITY quant,PRICE price,INFO_PROMO infoP){
	SALES sale = initSales();
	sale->client = clie;
	sale->product = prod;
	sale->month = month;
	sale->filial = filial;
	sale->quantity = quant;
	sale->price = price;
	sale->infoPromo = infoP;
	return sale;	
}
