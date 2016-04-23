#include "headers/Sales.h"

/* Estrutura onde é guardada toda a informação de cada linha do ficheiro Vendas. */
struct sales{
	CLIENT client;							/* Estrutura CLIENT com informação sobre o cliente. */
	PRODUCT product;						/* Estrutura PRODUCT com informação sobre o produto. */
	PRICE price;							/* Tipo PRICE com informação sobre o preço. */
	QUANTITY quantity;						/* Tipo QUANTITY com informação sobre a quantidade. */
	INFO_PROMO infoPromo;					/* Tipo INFO_PROMO com informação sobre a promoção. */
	FILIAIS filial;							/* Tipo FILIAIS com informação sobre o filial. */
	MONTH month;							/* Tipo MONTH com informação sobre o mês. */
};

/* Função privada ao módulo */
static int testSales(CLIENT,PRODUCT,double,int,char,int,int);

/* Inicializa uma estrutura SALES. */
SALES initSales(){
	SALES a = malloc(sizeof(struct sales));
	a->client=NULL;
	a->product=NULL; 
	return a;
}

/* Liberta uma estrutura SALES. */
void freeSale(SALES a){
	if(a){
		freeClient(a->client);
		freeProduct(a->product);
		free(a);
	}	
}

/*Função que reparte um linha de venda, e verifica se a linha é válida,ou seja, se o produto e cliente exitem, 
e se os outros parametros estão corretos. */
int partCheck(char* line, CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,CLIENT* clie,PRODUCT* prod,int *month,int *filial,int *quant,double *price,char *infoP){
	char *token;
	int r=0, i;

		
	token = strtok(line, " ");

	for(i=0;token != NULL;i++){
		switch(i){
			case 0: *prod = setProduct(*prod,token); break;
			case 1: *price = atof(token); break;
			case 2: *quant = atoi(token); break;
			case 3: *infoP = token[0]; break;
			case 4: *clie = setClient(*clie,token); break;
			case 5: *month = atoi(token); break;
			case 6: *filial = atoi(token); break;
		}
			token = strtok(NULL, " ");
	}

	if(testSales(*clie,*prod,*price,*quant,*infoP,*month,*filial) && existClient(clients,*clie) && existProduct(products,*prod)) r=1;
	return r;
}

/* Actualiza uma estrutura SALES com os parâmetros correspondentes. */
SALES updateSales(SALES sale,CLIENT clie,PRODUCT prod,MONTH month,FILIAIS filial,QUANTITY quant,PRICE price,INFO_PROMO infoP){
	sale->client = clie;
	sale->product = prod;
	sale->month = month;
	sale->filial = filial;
	sale->quantity = quant;
	sale->price = price;
	sale->infoPromo = infoP;
	return sale;	
}

/* Testa as diferentes características das Vendas.
	 Preço de 0 a 999.99;
	 Testar se o cliente e produto têm a estrutura correcta.
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

/* GETS E SETS */
CLIENT getSalesClient(SALES a){
	return a->client;
}

PRODUCT getSalesProduct(SALES a){
	return a->product;
}

PRICE getSalesPrice(SALES a){
	return a->price;
}

QUANTITY getSalesQuantity(SALES a){
	return a->quantity;
}

INFO_PROMO getSalesInfoPromo(SALES a){
	return a->infoPromo;
}

FILIAIS getSalesFilial(SALES a){
	return a->filial;
}

MONTH getSalesMonth(SALES a){
	return a->month;
}
