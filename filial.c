#include "filial.h"
#include <stdio.h> /* retirar dqui esta merda!!! */

struct filial{
	MY_AVL Clients[26];
};

struct infoClient{
	MY_AVL Products[12][26];
	int totalProducts;                           /* soma dos avl->size das 26 letras; dá o total de produtos comprados num ano */
};

struct infoProduct{
	int quantity[2];
	double price[2];
};



FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c){
	int i,j;	
	for(j=0;j<26;j++)
		f->Clients[j] = cloneMyAvl(getC(c,j));
	return f;
}

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
	
	for(i=0;i<12;i++)
		for(j=0;j<26;j++)
				info->Products[i][j] = initMyAvl();

	info->totalProducts = 0;
	return info;
}

INFO_PRODUCT initInfoProduct(){
	int i;
	INFO_PRODUCT info = malloc(sizeof(struct infoProduct));
	for(i=0;i<2;i++){
	info->quantity[i] = 0;
	info->price[i] = 0;
}
	return info;
}

FILIAL insertFilial(FILIAL f,SALES s){
	
	CLIENT client = getSalesClient(s);

	int index_client = getClient(client)[0]-'A';

	/*if(!getSize(f->Clients[index_client]))
		f->Clients[index_client] = firstNode(getClient(client),NULL);*/

	INFO_CLIENT infoC = (INFO_CLIENT) findInfo(getAvl(f->Clients[index_client]),getClient(client),NULL);

	if(!infoC){
		infoC = initInfoClient();
		infoC = updateInfoC(infoC,s);
		f->Clients[index_client] = insertMyAvl(f->Clients[index_client],getClient(client),infoC,1);
	}
	else infoC = updateInfoC(infoC,s);

	return f;

}

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s){

	PRODUCT product = getSalesProduct(s);
	MONTH month = getSalesMonth(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	char* prod=getProduct(product);
	int index_product = prod[0]-'A';
	int aux=0;

	int info_int;
	if(infoPromo == 'P') info_int = 1;
	else info_int = 0; 

 	MY_AVL a = infoC->Products[month-1][index_product];

 	INFO_PRODUCT infoP = (INFO_PRODUCT) findInfo(getAvl(a),prod,&aux);

 	if(!infoP) {
 		infoP = initInfoProduct(); /* TESTAR A FAZER UPDATE E INIT AO MESMO TEMPO A VER SE É MAIS RPD */
		infoP = updateInfoP(infoP,s);
		a = insertMyAvl(a,getProduct(product),infoP,aux);
	}
	else infoP = updateInfoP(infoP,s);

	infoC->totalProducts += getSalesQuantity(s);

 	return infoC;
}

INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s){

	PRICE price = getSalesPrice(s);
	QUANTITY qt = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	int info_int,i;

	if(infoPromo == 'P') info_int = 1;
	else info_int = 0; 

	for(i=0;i<2;i++){
	info->quantity[info_int] += qt;
	info->price[info_int] += price*qt;
	}
	return info;
}