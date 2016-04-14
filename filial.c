#include "filial.h"
#include <stdio.h> /* retirar dqui esta merda!!! */

struct filial{
	MY_AVL Clients[26];
};

struct infoClient{
	MY_AVL Products[26][12][2];
	int totalProducts;                           /* soma dos avl->size das 26 letras; dá o total de produtos comprados num ano */
};

struct infoProduct{
	int quantity;
	double price;
};

FILIAL initFilial(){
	int i;
	FILIAL filial = malloc(sizeof(struct filial));
	for(i=0;i<26;i++)
		filial->Clients[i] = initMyAvl();
	return filial;
}

INFO_CLIENT initInfoClient(){

	int i,j,k;
	INFO_CLIENT info = malloc(sizeof(struct infoClient));
	
	for(i=0;i<26;i++)
		for(j=0;j<12;j++)
			for(k=0;k<2;k++)
				info->Products[i][j][k] = initMyAvl();

	info->totalProducts = 0;
	return info;
}

INFO_PRODUCT initInfoProduct(){
	
	INFO_PRODUCT info = malloc(sizeof(struct infoProduct));
	info->quantity = 0;
	info->price = 0;
	return info;

}

FILIAL insertFilial(FILIAL f,SALES s){
	
	CLIENT client = getSalesClient(s);

	int index_client = getClient(client)[0]-'A';

	/*if(!getSize(f->Clients[index_client]))
		f->Clients[index_client] = firstNode(getClient(client),NULL);*/

	INFO_CLIENT infoC = (INFO_CLIENT) findInfo(getAvl(f->Clients[index_client]),getClient(client));

	if(!infoC){
		infoC = initInfoClient();
		infoC = updateInfoC(infoC,s);
		f->Clients[index_client] = insertMyAvl(f->Clients[index_client],getClient(client),infoC);
	}
	else infoC = updateInfoC(infoC,s);

	return f;

}

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s){

	PRODUCT product = getSalesProduct(s);
	MONTH month = getSalesMonth(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	int index_product = getProduct(product)[0]-'A';


	int info_int;
	if(infoPromo = 'P') info_int = 1;
	else info_int = 0; 

 	MY_AVL a = infoC->Products[index_product][month-1][info_int];

 	INFO_PRODUCT infoP = (INFO_PRODUCT) findInfo(getAvl(a),getProduct(product));

 	if(!infoP) {
 		infoP = initInfoProduct(); /* TESTAR A FAZER UPDATE E INIT AO MESMO TEMPO A VER SE É MAIS RPD */
		infoP = updateInfoP(infoP,s);
		a = insertMyAvl(a,getProduct(product),infoP);
	}

	else infoP = updateInfoP(infoP,s);

	infoC->totalProducts += getSalesQuantity(s);

 	return infoC;
}

INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s){

	PRICE price = getSalesPrice(s);
	QUANTITY qt = getSalesQuantity(s);

	info->quantity += qt;
	info->price += price*qt;
	return info;
}