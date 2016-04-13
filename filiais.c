#include "filiais.h"

struct filiais{
	CLIENTS_PRODUCTS filiais[3];
};

struct clients_products{
	MY_AVL Clients[26];
	MY_AVL Products[26];
};

struct total{
	int totalQ;
	double totalP;
	//Heap ou MY_avl
};

//dentro do info da avl de cima
struct valores{
	int quant;
	double pago;
};

struct infoClients{
	TOTAL clientsMatriz[12][2];
};

struct infoProducts{
	TOTAL productsMatriz[12][2];
};

FILIAIS initFiliais(){
	int i;
	FILIAIS f = malloc(sizeof(struct filiais));
	for(i=0;i<3;i++)
		f->filiais[i] = initClientsProducts();
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
	INFO_CLIENTS info;
	for(i=0;i<12;i++)
		for(j=0;j<2;j++)
			info->clientsMatriz[i][j] = initFiliaisTotal();
	return info;
}

INFO_PRODUCTS initFiliaisProducts(){
	INFO_PRODUCTS info;
	int i,j;
	for(i=0;i<12;i++)
		for(j=0;j<2;j++)
			info->productsMatriz[i][j] = initFiliaisTotal();
	return info;
}

TOTAL initFiliaisTotal(){

	TOTAL t = malloc(sizeof(struct total));
	return t;
}

FILIAIS insertFiliais(FILIAIS f,SALES s){
	
	/* REMOVER O QUE NÃO É USADO LOGO DE INICIO */
	CLIENT client = getSalesClient(s);
	PRODUCT product = getSalesProduct(s);
	PRICE price = getSalesPrice(s);
	QUANTITY quantity = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	FILIAL filial = getSalesFilial(s);
	MONTH month = getSalesMonth(s);
	void* new_infoProducts;
	void* new_infoClients;

	CLIENTS_PRODUCTS a = f->filiais[filial];

	int index_product = getProduct(product)[0]-'A';
	int index_client = getClient(client)[0]-'A';

	void* infoProducts = (INFO_PRODUCTS) findInfo(getAvl(a->Products[index_product]),getProduct(product));
	void* infoClients = (INFO_CLIENTS) findInfo(getAvl(a->Clients[index_client]),getClient(client));

	if(!infoProducts){
		INFO_PRODUCTS infoProducts = initFiliaisProducts();
		infoProducts = copyInfoClient(s,infoProducts);
	}

	if(!infoClients){
		INFO_CLIENTS infoClients = initFiliaisClients();
		infoClients = copyInfoClient(s,infoClients);
	}

	return f;
}

static INFO_CLIENTS copyInfoClient(SALES s, INFO_CLIENTS info){

	

}

static INFO_PRODUCTS copyInfoProduct(SALES s, INFO_PRODUCTS info){

}