#include "filiais.h"

typedef struct filiais *FILIAIS;
typedef struct clients_products *CLIENTS_PRODUCTS;
typedef struct infoClients *INFO_CLIENTS;
typedef struct infoProducts *INFO_PRODUCTS;


struct filiais{
	CLIENTS_PRODUCTS filiais[3];
};

struct clients_products{
	MY_AVL Clients[26];
	MY_AVL Products[26];
};

struct infoClients{
	MY_AVL clientsMatriz[12][2];
	MY_AVL products_diferentes;
};

struct infoProducts{
	MY_AVL productsMatriz;
	MY_AVL clients_diferentes;
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

	info->products_diferentes = initMyAvl();
	return info;
}

INFO_PRODUCTS initFiliaisProducts(){
	INFO_PRODUCTS info;
	info->productsMatriz = initMyAvl();
	info->clients_diferentes = initMyAvl();
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

	return f;
}