#include "headers/filial.h"

struct filial{
	MY_AVL Clients[SIZE_ABC];
	MY_AVL Products[SIZE_ABC];
};

struct infoMes{
	MY_AVL Products[SIZE_ABC];
	int quantity;
};

struct infoClient{
	INFO_MES info_mes[SIZE_MONTH];
	int Comprou;                           
};

struct infoProduct{
	int quantity[SIZE_INFOP];
	double price[SIZE_INFOP];
};

struct dadosFilial{
	int quant[SIZE_FILIAIS][SIZE_MONTH];
};

struct cena{
	int quant;
	int registo;
};

CENA initCena(){
	CENA c = malloc(sizeof(struct cena));
	c->quant=0;
	c->registo=0;
	return c;
}

FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c){
	int j;	
	for(j=0;j<SIZE_ABC;j++)
		f->Clients[j] = cloneMyAvl(getC(c,j));	
	return f;
}

FILIAL copyP(FILIAL f,CATALOG_PRODUCTS p){
	int j;	
	for(j=0;j<SIZE_ABC;j++)
		f->Products[j] = cloneMyAvl(getP(p,j));	
	return f;
}

void freeFilial(FILIAL f){
	int i;
	if(f){
		for(i=0;i<SIZE_ABC;i++)
			removeMyAvl(f->Clients[i],freeInfoClient);
	}
	free(f);
}

void freeInfoClient(void* infoClient){
	int i;
	INFO_CLIENT x = (INFO_CLIENT) infoClient;
	if(x){
		for(i=0;i<SIZE_MONTH;i++)
			freeInfoMes(x->info_mes[i]);
	}
	free(x);
}

void freeInfoMes(INFO_MES info){
	int i;
	if(info){
		for(i=0;i<SIZE_ABC;i++)
			removeMyAvl(info->Products[i],freeInfoProduct);
	}
	free(info);
}

void freeInfoProduct(void* infoProduct){

	INFO_PRODUCT x = (INFO_PRODUCT) infoProduct;
	if(x){
		free(x);
	}
}

FILIAL initFilial(){
	int i;
	FILIAL filial = malloc(sizeof(struct filial));
	for(i=0;i<SIZE_ABC;i++){
		filial->Clients[i] = NULL;
		filial->Products[i] = NULL;
	}
	return filial;
}

INFO_MES initInfoMes(){
	int i;
	INFO_MES info_mes = malloc(sizeof(struct infoMes));
	for(i=0;i<SIZE_ABC;i++){
		info_mes->Products[i]=NULL;
	}
	info_mes->quantity=0;
	return info_mes;
}

INFO_CLIENT initInfoClient(){
	int i;
	INFO_CLIENT info = malloc(sizeof(struct infoClient));
	
	for(i=0;i<SIZE_MONTH;i++)
		info->info_mes[i] = initInfoMes();
	info->Comprou=0;
	return info;
}

INFO_PRODUCT initInfoProduct(){
	int i;
	INFO_PRODUCT info = malloc(sizeof(struct infoProduct));
	for(i=0;i<SIZE_INFOP;i++){
		info->quantity[i] = 0;
		info->price[i] = 0;
	}
	return info;
}

DADOS_FILIAL initDadosFilial(){
	int i,j;
	DADOS_FILIAL df = malloc(sizeof(struct dadosFilial));
	for(i=0;i<SIZE_FILIAIS;i++)
		for(j=0;j<SIZE_MONTH;j++)
			df->quant[i][j]=0;

	return df;
}

CENA updateCena (CENA c,SALES s){
	c->quant+=getSalesQuantity(s);
	c->registo++;
	return c;
}

FILIAL insertFilial(FILIAL f,SALES s){
	int exist=0,aux=0;

	CLIENT client = getSalesClient(s);
	char* cli = getClient(client);
	PRODUCT product= getSalesProduct(s);
	char* prod= getProduct(product);

	int index_client = cli[0]-'A';
	int index_product = prod[0]-'A';

	Avl nodoC=getAvl(f->Clients[index_client]);
	Avl nodoP=NULL;

	INFO_CLIENT infoC = (INFO_CLIENT) findInfo(nodoC,cli,NULL);
	
	if(!infoC){
		infoC = initInfoClient();
		infoC = updateInfoC(infoC,s,&exist);
		f->Clients[index_client] = insertMyAvl(f->Clients[index_client],cli,infoC,1);
	}
	else infoC = updateInfoC(infoC,s,&exist);
	
	nodoP=getAvl(f->Products[index_product]);
	CENA infoCena;

	if(!exist){
			infoCena= (CENA) findInfo(nodoP,prod,NULL);
			if(!infoCena){
				infoCena = initCena();
				infoCena = updateCena(infoCena,s);
				f->Products[index_product] = insertMyAvl(f->Products[index_product],prod,infoCena,1);
			}
			else infoCena = updateCena(infoCena,s);
		}
	else {
		if(nodoP){
			infoCena = (CENA) findInfo(nodoP,prod,&aux);
			infoCena = updateCena(infoCena,s);	
		}
	}

	infoC->Comprou=1;

	if(nodoC)freeNodo(nodoC);
	if(nodoP)freeNodo(nodoP);
	free(cli);
	free(prod);
	return f;
}

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s,int* exist){

	PRODUCT product = getSalesProduct(s);
	MONTH month = getSalesMonth(s);
	char* prod=getProduct(product);
	int index_product = prod[0]-'A';
	int aux=0;
	INFO_PRODUCT infoP;

 	MY_AVL a = infoC->info_mes[month-1]->Products[index_product];
 	Avl nodo=NULL;
 	if(a){
 		nodo=getAvl(a);
 		infoP = (INFO_PRODUCT) findInfo(nodo,prod,&aux);

 		if(!infoP) {
 			infoP = initInfoProduct(); 
			infoP = updateInfoP(infoP,s);
			a = insertMyAvl(a,prod,infoP,aux);
		}
		else {
			infoP = updateInfoP(infoP,s);
			*exist=1;
		}
	}
	else{ 
		infoC->info_mes[month-1]->Products[index_product]=initMyAvl();
		infoP = initInfoProduct(); 
		infoP = updateInfoP(infoP,s);
		infoC->info_mes[month-1]->Products[index_product]= insertMyAvl(infoC->info_mes[month-1]->Products[index_product],prod,infoP,1);
	}
	

	infoC->info_mes[month-1]->quantity+=getSalesQuantity(s);
	if(nodo)freeNodo(nodo);
	free(prod);
 	return infoC;
}

INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s){

	PRICE price = getSalesPrice(s);
	QUANTITY qt = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	int info_int;

	if(infoPromo == 'P') info_int = 1;
	else info_int = 0; 

	info->quantity[info_int] += qt;
	info->price[info_int] += price*qt;
	return info;
}



/*GET E SET*/
int getDadosI(DADOS_FILIAL df,int i,int j){
	return df->quant[i][j];
}

int getComp( INFO_CLIENT x){
	return x->Comprou;
}

Avl getClientIndexF(FILIAL f,int index){
	Avl nodo = getAvl(f->Clients[index]);
	return nodo;
}

int getDadosFilialQuantity(DADOS_FILIAL df,int filial,int month){
	return df->quant[filial-1][month-1];
}

DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL df,int filial,int month,int total){
	df->quant[filial][month] += total;
	return df;
}

INFO_MES getInfoMes(INFO_CLIENT info,int month){
	return info->info_mes[month];
}

int getInfoMesQuantity(INFO_MES info){
	return info->quantity;
}

Avl getInfoMesProduct(INFO_MES info,int index){
	return getAvl(info->Products[index]);
}

int getInfoProductQuantity(INFO_PRODUCT info,int index){
	return info->quantity[index];
}

double getInfoProductPrice(INFO_PRODUCT info,int index){
	return info->price[index];
}

Avl getProd10(FILIAL f,int index){
	return getAvl(f->Products[index]);
}

int getResg(CENA info){
	return info->registo;
} 

int	getCenaQuant(CENA info){
	return info->quant;
}