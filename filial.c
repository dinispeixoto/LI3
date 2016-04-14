#include "filial.h"
#include "Sales.h"
#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"

FILIAIS initFilial(){
	int i;
	FILIAL f = malloc(sizeof(struct filial));
		f->filial = initClientsProducts();
	return f;
}

CLIENTS_PRODUCTS initClientsProducts(){
	int i;
	CLIENTS_PRODUCTS cp = malloc(sizeof(struct clients_products));
	for(i=0;i<26;i++){
		cp->Clients[i] = initMyAvl();
		cp->Products[i] = initMyAvl();
	}
	return cp;
}

INFO_CLIENTS initFiliaisClients(){
	int i,j;
	INFO_CLIENTS info=malloc(sizeof(struct totalClient));
	for(i=0;i<12;i++)
		for(j=0;j<2;j++)
			info->clientsMatriz[i][j] = initFiliaisTotal();
	return info;
}

INFO_PRODUCTS initFiliaisProducts(){
	INFO_PRODUCTS info=malloc(sizeof(struct totalClient));
	int i,j;
	for(i=0;i<12;i++)
		for(j=0;j<2;j++)
			info->productsMatriz[i][j] = initFiliaisTotal();
	return info;
}

TOTAL initFiliaisTotal(){
	TOTAL t = malloc(sizeof(struct totalClient));
	t->totalQ=0;
	t->totalP=0;
	//for(i=0;i<26;i++){
	//t->prods[i]=initMyAvl();
    //}
	return t;
}

VALORES initValores(){
	VALORES v = malloc(sizeof(struct valores ));
	v->quant=0;
	v->pago=0;
	return v;
}


FILIAIS copyP(FILIAIS f,CATALOG_PRODUCTS p){
	int i,j;
	for(i=0;i<3;i++)	
		for(j=0;j<26;j++)
			f->filiais[i]->Products[j] = cloneMyAvl(getP(p,j));
	return f;
}

FILIAIS copyC(FILIAIS f,CATALOG_CLIENTS c){
	int i,j;
	for(i=0;i<3;i++)	
		for(j=0;j<26;j++)
			f->filiais[i]->Clients[j] = cloneMyAvl(getC(c,j));
	return f;
}


static INFO_CLIENTS copyInfoClient(SALES s, INFO_CLIENTS info,int index){
	MY_AVL a;
	MONTH month = getSalesMonth(s);
	PRICE price = getSalesPrice(s);
	QUANTITY quantity = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	PRODUCT product = getSalesProduct(s);
	
	/*Fazer funcao auxiliar*/
	switch(infoPromo){ 
		case 'P': info->clientsMatriz[month-1][1]->totalP+=(price*quantity);
					//printf("%f\n",info->clientsMatriz[month-1][1]->totalP);
				  info->clientsMatriz[month-1][1]->totalQ+=quantity;
				  //printf("%d\n",info->clientsMatriz[month-1][1]->totalQ );
				  /*a=info->clientsMatriz[month-1][1]->prods[index];
				  VALORES v1 = initValores();
				  v1->quant=quantity;
				  v1->pago=(price*quantity);
				  void* x=v1;
				  a=insertMyAvl(a,getProduct(product),x);*/
				  break;
		case 'N': info->clientsMatriz[month-1][0]->totalP+=(price*quantity);
					//printf("%d\n",info->clientsMatriz[month-1][0]->totalQ);
				  info->clientsMatriz[month-1][0]->totalQ+=quantity;
				    //printf("%f\n",info->clientsMatriz[month-1][0]->totalP);
				  /*a=info->clientsMatriz[month-1][0]->prods[index];
				  VALORES v2 = initValores();
				  v2->quant=quantity;
				  v2->pago=(price*quantity);
				  void* y=v2;
				  a=insertMyAvl(a,getProduct(product),y);*/
				  break;
	}
	return info;
}

static INFO_PRODUCTS copyInfoProduct(SALES s, INFO_PRODUCTS info, int index){
	MY_AVL a;
	MONTH month = getSalesMonth(s);	
	PRICE price = getSalesPrice(s);
	QUANTITY quantity = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	CLIENT client = getSalesClient(s);

	switch(infoPromo){ 
		case 'P': info->productsMatriz[month-1][1]->totalP+=(price*quantity);
				  info->productsMatriz[month-1][1]->totalQ+=quantity;
				  /*a=info->productsMatriz[month-1][1]->prods[index];
				  VALORES v1 = initValores();
				  v1->quant=quantity;
				  v1->pago=(price*quantity);
				  void* x=v1;
				  a=insertMyAvl(a,getClient(client),x);*/
				  break;
		case 'N': info->productsMatriz[month-1][0]->totalP+=(price*quantity);
				  info->productsMatriz[month-1][0]->totalQ+=quantity;
				  /*a=info->productsMatriz[month-1][0]->prods[index];
				  VALORES v2 = initValores();
				  v2->quant=quantity;
				  v2->pago=(price*quantity);
				  void* y=v2;
				  a=insertMyAvl(a,getClient(client),y);*/
				  break;
	}
	return info;
}


FILIAIS insertFiliais(FILIAIS f,SALES s){
	
	CLIENT client = getSalesClient(s);
	PRODUCT product = getSalesProduct(s);
	FILIAL filial = getSalesFilial(s);
	void* x;
	void* y;
	CLIENTS_PRODUCTS a = f->filiais[filial-1];

	int index_product = getProduct(product)[0]-'A';
	int index_client = getClient(client)[0]-'A';

	void* infoProducts = (INFO_PRODUCTS) findInfo(getAvl(a->Products[index_product]),getProduct(product));
	void* infoClients = (INFO_CLIENTS) findInfo(getAvl(a->Clients[index_client]),getClient(client));

	if(infoProducts){
		infoProducts = copyInfoProduct(s,infoProducts,index_product);
	}
	else {
		INFO_PRODUCTS ip = initFiliaisProducts();
		ip=copyInfoProduct(s,ip,index_product);
		y = ip;
		f->filiais[filial-1]->Products[index_product] = insertMyAvl(a->Products[index_product],getProduct(product),y);	
	}

	if(infoClients){
		infoClients = copyInfoClient(s,infoClients,index_client);
	}
	else {
		INFO_CLIENTS ic = initFiliaisClients();
		ic=copyInfoClient(s,ic,index_client);
		x = ic;
		a->Clients[index_client] = insertMyAvl(a->Clients[index_client],getClient(client),x);
	}
	return f;
}


