#include "headers/filial.h"

/* Estrutura de um filial. */
struct filial{
	MY_AVL Clients[SIZE_ABC];				/* Catálogo de Clientes. */
	MY_AVL Products[SIZE_ABC];				/* Catálogo de Produtos. */
};

/* Estrutura com a informação de um Cliente. */
struct infoClient{
	INFO_MES info_mes[SIZE_MONTH];			/* Array em que cada mês tem associado uma estrutura INFO_MES. */
	int Comprou;                     		/* Inteiro responsável por dizer se um Cliente fez compras ou não, questões de desempenho. */
};

/* Estrutura com a informação de um Produto. */
struct infoProduct{
	int quantity[SIZE_INFOP];				/* Array em que cada tipo de promoção tem associado uma quantidade. */
	double price[SIZE_INFOP];				/* Array em que cada tipo de promoção tem associado um preço. */
};

/* Estrutura com a informação de um determinado mês. */
struct infoMes{
	MY_AVL Products[SIZE_ABC];				/* Catálogo de Produtos comprados pelo Cliente num determinado mês. */
	int quantity;							/* Quantidade de produtos comprados pelo Clientes num determinado mês. */
};

/* Estrutura com a informação relativa ao produto comprado. */
struct productInfo{
	int quant;								/* Quantidade do produto comprada. */
	int registo;							/* Número de vendas do produto. */
};

/* Estrutura auxiliar à resolução das queries. */
struct dadosFilial{
	int quant[SIZE_MONTH];					/* Array de quantidades em cada mês. */
};


/* Funções privadas ao módulo. */
static INFO_CLIENT initInfoClient();
static void freeInfoClient(void*);
static INFO_MES initInfoMes();
static void freeInfoMes(INFO_MES);
static INFO_PRODUCT initInfoProduct();
static void freeInfoProduct(void*);
static PRODUCT_INFO initProductInfo();
static INFO_CLIENT updateInfoC(INFO_CLIENT,SALES,int*);
static INFO_PRODUCT updateInfoP(INFO_PRODUCT,SALES);
static PRODUCT_INFO updatePi(PRODUCT_INFO,SALES);
static PRODUCT_INFO updatePiQ(PRODUCT_INFO,SALES);

/* Inicializa a estrutura de um filial. */
FILIAL initFilial(){
	int i;
	FILIAL filial = malloc(sizeof(struct filial));
	for(i=0;i<SIZE_ABC;i++){
		filial->Clients[i] = NULL;
		filial->Products[i] = NULL;
	}
	return filial;
}

/* Liberta a estrutura de um filial. */
void freeFilial(FILIAL f){
	int i;
	if(f){
		for(i=0;i<SIZE_ABC;i++)
			removeMyAvl(f->Clients[i],freeInfoClient);
	}
	free(f);
}

/* Inicializa a estrutura DADOS_FILIAL. */
DADOS_FILIAL initDadosFilial(){
	int j;
	DADOS_FILIAL df = malloc(sizeof(struct dadosFilial));
	for(j=0;j<SIZE_MONTH;j++)
			df->quant[j]=0;

	return df;
}

/* Insere as informações de uma venda na estrutura do corresponde filial. */
FILIAL insertFilial(FILIAL f,SALES s){
	int exist=0;
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
	PRODUCT_INFO pinfo;

	if(!exist){
			pinfo= (PRODUCT_INFO) findInfo(nodoP,prod,NULL);
			if(!pinfo){
				pinfo = initProductInfo();
				pinfo = updatePi(pinfo,s);
				f->Products[index_product] = insertMyAvl(f->Products[index_product],prod,pinfo,1);
			}
			else pinfo = updatePi(pinfo,s);
		}
	else {
		if(nodoP){
			pinfo = (PRODUCT_INFO) findInfo(nodoP,prod,NULL);
			pinfo = updatePiQ(pinfo,s);	
		}
	}

	infoC->Comprou=1;
	
	if(nodoC)freeNodo(nodoC);
	if(nodoP)freeNodo(nodoP);
	free(cli);
	free(prod);
	return f;
}

/* Copia Catálogo de Clientes para a estrutura filial.*/
FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c){
	int j;	
	for(j=0;j<SIZE_ABC;j++)
		f->Clients[j] = cloneMyAvl(getC(c,j));
	return f;
}

/* Copia Catálogo de Produtos para a estrutura filial.*/
FILIAL copyP(FILIAL f,CATALOG_PRODUCTS p){
	int j;	
	for(j=0;j<SIZE_ABC;j++)
		f->Products[j] = cloneMyAvl(getP(p,j));	
	return f;
}


/*GETS E SETS*/
int getComp( INFO_CLIENT x){
	return x->Comprou;
}

Avl getClientIndexF(FILIAL f,int index){
	return getAvl(f->Clients[index]);
}

int getDadosFilialQuantity(DADOS_FILIAL df,int month){
	return df->quant[month-1];
}

DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL df,int month,int total){
	df->quant[month] += total;
	return df;
}

INFO_MES getInfoMes(INFO_CLIENT info,int month){
	return info->info_mes[month];
}

int getInfoMesQuantity(INFO_MES info){
	return info->quantity;
}

MY_AVL getInfoMesProduct(INFO_MES info,int index){
	return info->Products[index];
}

int getInfoProductQuantity(INFO_PRODUCT info,int index){
	return info->quantity[index];
}

double getInfoProductPrice(INFO_PRODUCT info,int index){
	return info->price[index];
}

Avl getProdInfo(FILIAL f,int index){
	return getAvl(f->Products[index]);
}

int getResg(PRODUCT_INFO info){
	return info->registo;
} 

int	getPiQuant(PRODUCT_INFO info){
	return info->quant;
}

/* STATICS */
/* Inicializa a estrutura INFO_CLIENT. */
static INFO_CLIENT initInfoClient(){
	int i;
	INFO_CLIENT info = malloc(sizeof(struct infoClient));
	
	for(i=0;i<SIZE_MONTH;i++)
		info->info_mes[i] = initInfoMes();
	info->Comprou=0;
	return info;
}

/* Liberta a estrutura INFO_CLIENT. */
static void freeInfoClient(void* infoClient){
	int i;
	INFO_CLIENT x = (INFO_CLIENT) infoClient;
	if(x){
		for(i=0;i<SIZE_MONTH;i++)
			freeInfoMes(x->info_mes[i]);
	}
	free(x);
}

/* Inicializa a estrutura INFO_MES. */
static INFO_MES initInfoMes(){
	int i;
	INFO_MES info_mes = malloc(sizeof(struct infoMes));
	for(i=0;i<SIZE_ABC;i++){
		info_mes->Products[i]=NULL;
	}
	info_mes->quantity=0;
	return info_mes;
}

/* Liberta a estrutura INFO_MES. */
static void freeInfoMes(INFO_MES info){
	int i;
	if(info){
		for(i=0;i<SIZE_ABC;i++)
			removeMyAvl(info->Products[i],freeInfoProduct);
	}
	free(info);
}

/* Inicializa a estrutura INFO_PRODUCT. */
static INFO_PRODUCT initInfoProduct(){
	int i;
	INFO_PRODUCT info = malloc(sizeof(struct infoProduct));
	for(i=0;i<SIZE_INFOP;i++){
		info->quantity[i] = 0;
		info->price[i] = 0;
	}
	return info;
}

/* Liberta a estrutura INFO_PRODUCT. */
static void freeInfoProduct(void* infoProduct){
	INFO_PRODUCT x = (INFO_PRODUCT) infoProduct;
	if(x){
		free(x);
	}
}

/* Inicializa a estrutura PRODUCT_INFO. */
static PRODUCT_INFO initProductInfo(){
	PRODUCT_INFO pi = malloc(sizeof(struct productInfo));
	pi->quant=0;
	pi->registo=0;
	return pi;
}

/* Actualiza a estrutura INFO_CLIENT. */
static INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s,int* exist){
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
		else {infoP = updateInfoP(infoP,s);
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

/* Actualiza a estrutura INFO_PRODUCT. */
static INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s){

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

/* Actualiza a estrutura PRODUCT_INFO. */
static PRODUCT_INFO updatePi(PRODUCT_INFO pi,SALES s){
	pi->quant+=getSalesQuantity(s);
	pi->registo++;
	return pi;
}

/* Actualiza a estrutura PRODUCT_INFO. */
static PRODUCT_INFO updatePiQ(PRODUCT_INFO pi,SALES s){
	pi->quant+=getSalesQuantity(s);
	return pi;
}