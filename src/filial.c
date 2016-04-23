#include "headers/filial.h"


/* Estrutura com a informação de um determinado mês. */
struct infoMes{
	MY_AVL Products[SIZE_ABC];				/* Catálogo de Produtos comprados pelo Cliente num determinado mês. */
	int quantity;							/* Quantidade de produtos comprados pelo Clientes num determinado mês. */
};
typedef struct infoMes *INFO_MES;

/* Estrutura com a informação de um Cliente. */
struct infoClient{
	INFO_MES info_mes[SIZE_MONTH];			/* Array em que cada mês tem associado uma estrutura INFO_MES. */
	int Comprou;                     		/* Inteiro responsável por dizer se um Cliente fez compras ou não, questões de desempenho. */
};

typedef struct infoClient *INFO_CLIENT;

/* Estrutura com a informação de um Produto. */
struct infoProduct{
	int quantity[SIZE_INFOP];				/* Array em que cada tipo de promoção tem associado uma quantidade. */
	double price[SIZE_INFOP];				/* Array em que cada tipo de promoção tem associado um preço. */
};

typedef struct infoProduct *INFO_PRODUCT;


/* Estrutura com a informação relativa ao produto comprado. */
struct productInfo{
	int quant;								/* Quantidade do produto comprada. */
	int registo;							/* Número de vendas do produto. */
};

typedef struct productInfo *PRODUCT_INFO;

/* Estrutura de um filial. */
struct filial{
	MY_AVL Clients[SIZE_ABC];				/* Catálogo de Clientes. */
	MY_AVL Products[SIZE_ABC];				/* Catálogo de Produtos. */
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
static LISTA_STRINGS dontBuy(Avl,LISTA_STRINGS);
static double price(INFO_PRODUCT);
static Heap highCost(INFO_CLIENT ic,Heap hp);
static Heap highCost2(Avl a,Heap hp);
static int quantityNclients(PRODUCT_INFO info,int* registo);
static int pesquisa(Avl a, Heap hp);
static int quantity(INFO_PRODUCT ip);
static Heap addProdQuant(Avl a,Heap heap);
static Heap findProd(INFO_CLIENT ic, int month,Heap heap);
static DADOS_FILIAL addQ(DADOS_FILIAL df,INFO_CLIENT ic);
static LISTA_STRINGS checkProd(INFO_PRODUCT ip,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client);
static LISTA_STRINGS findInfoProduct(INFO_CLIENT ic,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client);
static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS ls);
static LISTA_STRINGS findProduct(Avl a, char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP);


/* Liberta a estrutura de um filial. */
void freeFilial(FILIAL f){
	int i;
	if(f){
		for(i=0;i<SIZE_ABC;i++)
			removeMyAvl(f->Clients[i],freeInfoClient);
	}
	free(f);
}

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


Avl getProdInfo(FILIAL f,int index){
	return getAvl(f->Products[index]);
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

/*Função que percorre a AVL de clients, e verifica se o campo info, é NULL ou não, indicado se comprou ou não. Caso tenha comprado, é adicionado a lista.*/
static LISTA_STRINGS dontBuy(Avl a,LISTA_STRINGS ls){
	void* x;
	char* clie;
	if(a){
		dontBuy(getAvlLeft(a),ls);
		x = (INFO_CLIENT)getInfo(a);
		clie=getAvlCode(a);
		if(!x){
			addListaStrings(ls,getListaSp(ls),clie);
			ls=reallocListaStrings(ls);
		}	
		dontBuy(getAvlRight(a),ls);
		free(clie);
		freeNodo(a);
	}
	return ls;
}

LISTA_STRINGS dontBuyClient(FILIAL f, LISTA_STRINGS ls){
	Avl nodo;
	int i;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getAvl(f->Clients[i]);
		ls=dontBuy(nodo,ls);
	}
	return ls;
}

/***********/

static double price(INFO_PRODUCT ip){
	return (ip->price[0]+ip->price[1]);
}

static Heap highCost2(Avl a,Heap hp){
	double r;
	void* x;
	char* prod;
	if(a){
		highCost2(getAvlLeft(a),hp);
		x= (INFO_PRODUCT)getInfo(a);
		r=price(x);
		prod=getAvlCode(a);
		insertHeap(hp,r,0,prod);
		highCost2(getAvlRight(a),hp);
		free(prod);
		freeNodo(a);
	}
	return hp;
}

static Heap highCost(INFO_CLIENT ic,Heap hp){
	int i,j;
	Avl nodo;
	for(i=0;i<SIZE_MONTH;i++){
		for(j=0;j<SIZE_ABC;j++){
			nodo=getAvl(ic->info_mes[i]->Products[j]);
			if(nodo)	
				highCost2(nodo,hp);
		}
	}
	return hp;
}

/* ######################################### QUERIE 11 #################################### */

Heap highCostProd(FILIAL f,Heap hp, char* client){
	int index = client[0]-'A';
	Avl nodo=getAvl(f->Clients[index]);
	void* x=findInfo(nodo,client,NULL);
	hp=highCost(x,hp);
	freeNodo(nodo);
	return hp;
}

/*************/

static int  quantityNclients(PRODUCT_INFO info,int* registo){
	*registo=info->registo;
	return info->quant;
}

static int pesquisa(Avl a, Heap hp){
	int r,resg; 
	void* x;
	char* aux;

	if(a){
		pesquisa(getAvlLeft(a),hp);
		x = (PRODUCT_INFO)getInfo(a);
		if(x){
			aux=getAvlCode(a);
			r=quantityNclients(x,&resg);
			insertHeap(hp,r,resg,aux);
			free(aux);
		}
		pesquisa(getAvlRight(a),hp);
		freeNodo(a);
	}
	return 1;
}

/* ######################################### QUERIE 10 #################################### */

Heap querie10Fil(FILIAL f,Heap hp){
	int i;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getAvl(f->Products[i]);
		pesquisa(nodo,hp);
	}
	return hp;
}

/*************/

static int quantity(INFO_PRODUCT ip){
	return (ip->quantity[0]+ip->quantity[1]);
}

static Heap addProdQuant(Avl a,Heap heap){
	int r; 
	void* x;
	char* prod;
	if(a){
		addProdQuant(getAvlLeft(a),heap);
		x = (INFO_PRODUCT)getInfo(a);
		r=quantity(x);
		prod=getAvlCode(a);
		insertHeap(heap,r,0,prod);
		addProdQuant(getAvlRight(a),heap);
		free(prod);
		freeNodo(a);
	}
	return heap;
}

static Heap findProd(INFO_CLIENT ic, int month,Heap heap){
	int i;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getAvl(ic->info_mes[month-1]->Products[i]);
		if(nodo)
			addProdQuant(nodo,heap);
	}
	return heap;
}

/* ######################################### QUERIE 9 #################################### */

Heap moreBuy(FILIAL f, Heap hp, char* client,int month){
	void* x;
	int index=client[0]-'A';
	x =(INFO_CLIENT)findInfo(getAvl(f->Clients[index]),client,NULL);
	findProd(x,month,hp);		
	return hp;
}

/*************/
static LISTA_STRINGS checkProd(INFO_PRODUCT ip,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client){

	if(ip->quantity[0]){
		addListaStrings(gcN,getListaSp(gcN),client);
		gcN=reallocListaStrings(gcN);
	}
	if(ip->quantity[1]){
		addListaStrings(gcP,getListaSp(gcP),client);
		gcP=reallocListaStrings(gcP);
	}
	return gcN;
}

static LISTA_STRINGS findInfoProduct(INFO_CLIENT ic,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client){
	int i;
	int index=product[0]-'A';
	Avl nodo;
	for(i=0;i<SIZE_MONTH;i++){
		nodo=getAvl(ic->info_mes[i]->Products[index]);
		if(nodo){
			void* x=(INFO_PRODUCT)findInfo(nodo,product,NULL);
			if(x) checkProd(x,gcN,gcP,client);
			freeNodo(nodo);
		}
	}	
	return gcN;
}

static LISTA_STRINGS findProduct(Avl a, char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP){
	void* x;
	char* prod;
	if(a){
		findProduct(getAvlLeft(a),product,gcN,gcP);
		x = (INFO_CLIENT)getInfo(a);
		prod=getAvlCode(a);
		findInfoProduct(x,product,gcN,gcP,prod);
		findProduct(getAvlRight(a),product,gcN,gcP);
		free(prod);
		freeNodo(a);
	}
	return gcN;
}

/* ######################################### QUERIE 8 #################################### */

LISTA_STRINGS productNeP(FILIAL f,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP){
	int i;
	for(i=0;i<SIZE_ABC;i++){
		findProduct(getAvl(f->Clients[i]),product,gcN,gcP);
	}
	return gcN;
}

/*************/
static LISTA_STRINGS insereList (Avl a,LISTA_STRINGS ls){
	void* x;
	char* clie;
	if(a){
		insereList(getAvlLeft(a),ls);
		x = (INFO_CLIENT)getInfo(a);
		clie=getAvlCode(a);
		if(x){
			addListaStrings(ls,getListaSp(ls),clie);
			ls=reallocListaStrings(ls);
		}	
		insereList(getAvlRight(a),ls);
		free(clie);
		freeNodo(a);
	}
	return ls;
}

/* ######################################### QUERIE 7 #################################### */

LISTA_STRINGS checkClientsValeN(FILIAL f,LISTA_STRINGS ls){
	int j;
	Avl nodo;
	for(j=0;j<SIZE_ABC;j++){
		nodo=getAvl(f->Clients[j]);
		insereList(nodo,ls);
	}
	return ls;
}

static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic){
	int i;
	for(i=0;i<SIZE_MONTH;i++)
		df->quant[i] +=ic->info_mes[i]->quantity;
	return df;
}

/* ######################################### QUERIE 5 #################################### */

DADOS_FILIAL valoresFilial(FILIAL f,DADOS_FILIAL df,char* client){
	void* x;
	int index = client[0]-'A';
	Avl nodo=getAvl(f->Clients[index]);
	x = (INFO_CLIENT)findInfo(nodo,client,NULL);
	df=addQ(df,x);
	freeNodo(nodo);
	return df;
}

