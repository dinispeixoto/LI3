#include "filiais.h"

struct filiais{
	CLIENTS_PRODUCTS filiais[3];
};

struct clients_products{
	MY_AVL Clients[26];
	MY_AVL Products[26];
};

struct infoClients{
	MY_AVL clientsMatriz[12][2];
	MY_AVL products_diferentes[26];
};

struct infoProducts{
	MY_AVL productsArray[12];
	MY_AVL clients_diferentes[26];
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
}

INFO_CLIENTS initFiliaisClients(){
	int i,j;
	INFO_CLIENTS info;
	for(i=0;i<12;i++)
		for(j=0;j<2;j++)
			info->clientsMatriz[i][j] = initMyAvl();

	for(i=0;i<26;i++)
		info->products_diferentes[i] = initMyAvl();
	return info;
}

INFO_PRODUCTS initFiliaisProducts(){
	INFO_PRODUCTS info;
	int i;
	for(i=0;i<12;i++)
		info->productsArray[i] = initMyAvl();
	for(i=0;i<26;i++)
		info->clients_diferentes[i] = initMyAvl();
	return info;
}

FILIAIS insertFiliais(FILIAIS f,SALES s){
	
	CLIENT client = getSalesClient(s);
	PRODUCT product = getSalesProduct(s);
	PRICE price = getSalesPrice(s);
	QUANTITY quantity = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	FILIAL filial = getSalesFilial(s);
	MONTH month = getSalesMonth(s);

	CLIENTS_PRODUCTS a = f->filiais[filial];

	int index_product = getProduct(product)[0]-'A';
	int index_client = getClient(client)[0]-'A';

	int exist_product = existMyAvl(a->Products[index_product],getProduct(product));
	int exist_client = existMyAvl(a->Clients[index_client],getClient(client));

	if(!exist_client) a->Products[index_product] = insertMyAvl(a->Products[index_product],getProduct(product),NULL);
	else /*update*/

	if(!exist_product) a->Clients[index_client] = insertMyAvl(a->Clients[index_client],getClient(client),NULL);
	else /*update*/

	return f;
}