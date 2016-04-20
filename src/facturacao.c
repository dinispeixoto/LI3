#include "headers/facturacao.h"

struct fact{
	TOTAL_MES tm[SIZE_MONTH]; 
	MY_AVL prod[SIZE_ABC];
};

struct pq {
	double totalprice;
	int totalquant;
};

struct totalMes{
	double totalFacturado; 
	int totalQuant;
	int RegistoV;
};

struct info{
	PQ N[SIZE_MONTH][SIZE_FILIAIS];
	PQ P[SIZE_MONTH][SIZE_FILIAIS];
};

struct dados{
	double totalpriceF[SIZE_FILIAIS];
	int totalquantF[SIZE_FILIAIS];
	double totalMP;
	int totalMQ;
};

static PQ initPQ();
static INFO initINFO();
static INFO copyInfoFact(SALES,INFO,FACTURACAO);
static void freeTotalMes(TOTAL_MES m);
static void freePQ(PQ x);

TOTAL_MES initTotalMes(){
	TOTAL_MES tm = malloc(sizeof(struct totalMes));
	tm->totalFacturado=0; 
	tm->totalQuant=0;
	tm->RegistoV=0;
	return tm;
}

FACTURACAO initFact(){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<SIZE_MONTH;i++)
		f->tm[i]=initTotalMes();
	return f;
}

void freeFact(FACTURACAO f){
	int i;
	for(i=0;i<SIZE_MONTH;i++) freeTotalMes(f->tm[i]);
	for(i=0;i<SIZE_ABC;i++) removeMyAvl(f->prod[i],freeInfo);
	free(f);
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

static void freePQ(PQ x){
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
	d->totalMQ=0;
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
	int index = getProduct(getSalesProduct(s))[0]-'A';
	
	void* x = (INFO)findInfo(getAvl(f->prod[index]),getProduct(getSalesProduct(s)),NULL);

	if(x)
		x = copyInfoFact(s,x,f);
	else {
		INFO i = initINFO();
		i = copyInfoFact(s,i,f);
		y = i;
		f->prod[index] = insertMyAvl(f->prod[index],getProduct(getSalesProduct(s)),y,1);
	}
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

int getDadosTQ(DADOS d){
	return d->totalMQ;
}

DADOS setTotalPrice(DADOS d,int index,double total){
	d->totalpriceF[index] = total;
	return d;
}

DADOS setTotalQuantity(DADOS d,int index,int total){
	d->totalquantF[index] = total;
	return d;
}

MY_AVL getProductIndex(FACTURACAO f,int index){
	return f->prod[index];
}

PQ getNormalPQ(INFO i,int month,int filial){
	return i->N[month][filial-1];
}

PQ getPromoPQ(INFO i,int month,int filial){
	return i->P[month][filial-1];
}

int getTotalQuantPQ(PQ a){
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

int getTotalMQ(DADOS d){
	return d->totalMQ;
}

DADOS setTotalMQ(DADOS d, int total){
	d->totalMQ = total;
	return d;
}

DADOS updateTotalMQ(DADOS d, int total){
	d->totalMQ += total;
	return d;
}

TOTAL_MES getTotalMes(FACTURACAO i,int month){
	return i->tm[month];
}

double getTotalFacturadoMES(TOTAL_MES m){
	return m->totalFacturado;
}

int getTotalQuantMES(TOTAL_MES m){
	return m->totalQuant;
}

/* STATICS */

static PQ initPQ(){
	PQ x = malloc (sizeof (struct pq));
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
					i->P[month][filial]->totalquant += quantity;	
					break;
		case 'N':	i->N[month][filial]->totalprice += total;
					i->N[month][filial]->totalquant += quantity;		
					break;
	}

	f->tm[month]->totalFacturado+=total;
	f->tm[month]->totalQuant+=quantity;
	f->tm[month]->RegistoV++; 
	return i;
}
