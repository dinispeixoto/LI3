#include "headers/facturacao.h"

struct fact{
	TOTAL_MES total_mes[SIZE_MONTH];  
	MY_AVL prod[SIZE_ABC];
};

struct priceQuantity {
	double totalprice;
	int totalquant;
};

struct totalMes{
	double totalFacturado; 
	int totalQuant;
	int totalVendas;
};

struct info{
	PRICE_QUANTITY N[SIZE_MONTH][SIZE_FILIAIS];
	PRICE_QUANTITY P[SIZE_MONTH][SIZE_FILIAIS];
};

struct dados{
	double totalpriceF[SIZE_FILIAIS];
	int totalquantF[SIZE_FILIAIS];
	double totalMP;
	int totalVendas;
};

static PRICE_QUANTITY initPQ();
static INFO initINFO();
static INFO copyInfoFact(SALES,INFO,FACTURACAO);
static void freeTotalMes(TOTAL_MES m);
static void freePQ(PRICE_QUANTITY x);

TOTAL_MES initTotalMes(){
	TOTAL_MES total_mes = malloc(sizeof(struct totalMes));
	total_mes->totalFacturado=0; 
	total_mes->totalQuant=0;
	total_mes->totalVendas=0;
	return total_mes;
}

FACTURACAO initFact(){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<SIZE_MONTH;i++)
		f->total_mes[i]=initTotalMes();
	return f;
}

void freeFact(FACTURACAO f){
	int i;
	for(i=0;i<SIZE_MONTH;i++) freeTotalMes(f->total_mes[i]);
	for(i=0;i<SIZE_ABC;i++) removeMyAvl(f->prod[i],freeInfo);
	free(f);
	f=NULL;
}

void freeInfo(void* info){
	INFO x = (INFO) info;
	int i,j;
	if(x){
		for(i=0;i<SIZE_MONTH;i++)
			for(j=0;j<SIZE_FILIAIS;j++){
				freePQ(x->N[i][j]);
				freePQ(x->P[i][j]);
			}
		free(x);
	}
}

static void freePQ(PRICE_QUANTITY x){
	free(x);
}

static void freeTotalMes(TOTAL_MES m){
	free(m);
}


DADOS initDADOS(){
	int i;
	DADOS d = malloc(sizeof(struct dados));
	for(i=0;i<SIZE_FILIAIS;i++){
		d->totalpriceF[i] = 0;
		d->totalquantF[i] = 0;
	}
	d->totalMP=0;
	d->totalVendas=0;
	return d;
}

FACTURACAO copyProducts(FACTURACAO f,CATALOG_PRODUCTS p){
	int i;	
	for(i=0;i<SIZE_ABC;i++)
		f->prod[i] = cloneMyAvl(getP(p,i));
	return f;
}

FACTURACAO insereFact(FACTURACAO f,SALES s){

	void* y;
	char* prod = getProduct(getSalesProduct(s));
	int index = prod[0]-'A';
	Avl nodo=getAvl(f->prod[index]);
	void* x = (INFO)findInfo(nodo,prod,NULL);
	
	if(x)
		x = copyInfoFact(s,x,f);
	else {
		INFO i = initINFO();
		i = copyInfoFact(s,i,f);
		y = i;
		f->prod[index] = insertMyAvl(f->prod[index],prod,y,1);
	}
	freeNodo(nodo);
	free(prod);
	return f;
}

/*GET & SET*/

double* getDadosP(DADOS d){
	return d->totalpriceF;
}

int* getDadosQ(DADOS d){
	return d->totalquantF;
}

double getnumFilialP(INFO i,int filial, int promo,int mes){
	if(promo)
		return i->P[mes-1][filial]->totalprice;
	else 
		return i->N[mes-1][filial]->totalprice;
	
}

int getnumFilialQ(INFO i,int filial, int promo,int mes){
	if(promo)
		return i->P[mes-1][filial]->totalquant;
	else 
		return i->N[mes-1][filial]->totalquant;
}

double getDadosTP(DADOS d){
	return d->totalMP;
}

int getDadosTV(DADOS d){
	return d->totalVendas;
}

DADOS setTotalPrice(DADOS d,int index,double total){
	d->totalpriceF[index] = total;
	return d;
}

DADOS setTotalQuantity(DADOS d,int index,int total){
	d->totalquantF[index] = total;
	return d;
}

Avl getProductIndex(FACTURACAO f,int index){
	return getAvl(f->prod[index]);
}

PRICE_QUANTITY getNormalPQ(INFO i,int month,int filial){
	return i->N[month][filial-1];
}

PRICE_QUANTITY getPromoPQ(INFO i,int month,int filial){
	return i->P[month][filial-1];
}

int getTotalQuantPQ(PRICE_QUANTITY a){
	return a->totalquant;
}

double getTotalMP(DADOS d){
	return d->totalMP; 
}

DADOS setTotalMP(DADOS d, double total){
	d->totalMP = total;
	return d;
}

DADOS updateTotalMP(DADOS d, double total){
	d->totalMP += total;
	return d;
}

int getTotalVendas(DADOS d){
	return d->totalVendas;
}

DADOS setTotalVendas(DADOS d, int total){
	d->totalVendas = total;
	return d;
}

DADOS updateTotalVendas(DADOS d, int total){
	d->totalVendas += total;
	return d;
}

TOTAL_MES getTotalMes(FACTURACAO i,int month){
	return i->total_mes[month];
}

double getTotalFacturadoMES(TOTAL_MES m){
	return m->totalFacturado;
}

int getTotalQuantMES(TOTAL_MES m){
	return m->totalQuant;
}

int getTotalRegisto(TOTAL_MES m){
	return m->totalVendas;
}

/* STATICS */

static PRICE_QUANTITY initPQ(){
	PRICE_QUANTITY x = malloc (sizeof (struct priceQuantity));
	x->totalprice = 0;
	x->totalquant = 0;
	return x;
}

static INFO initINFO(){
	int j,k;
	INFO i=malloc(sizeof(struct info));
	for(j=0;j<SIZE_MONTH;j++){
		for(k=0;k<SIZE_FILIAIS;k++){
			i->N[j][k] = initPQ();
			i->P[j][k] = initPQ();
		}
	}
	return i;
}

static INFO copyInfoFact(SALES s, INFO i,FACTURACAO f){
	double price=getSalesPrice(s);
	int quantity=getSalesQuantity(s);
	int filial=getSalesFilial(s)-1;
	int month=getSalesMonth(s)-1;
	char infoP=getSalesInfoPromo(s);
	double total=price*quantity;

	switch(infoP){
		case 'P':	i->P[month][filial]->totalprice += total;
					i->P[month][filial]->totalquant ++;	
					break;
		case 'N':	i->N[month][filial]->totalprice += total;
					i->N[month][filial]->totalquant ++;		
					break;
	}

	f->total_mes[month]->totalFacturado+=total;
	f->total_mes[month]->totalQuant+=quantity;
	f->total_mes[month]->totalVendas++; 
	return i;
}
