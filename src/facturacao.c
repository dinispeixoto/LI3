#include "headers/facturacao.h"

/* Estrutura principal da facturação. */
struct fact{
	TOTAL_MES total_mes[SIZE_MONTH];		/* Array de 12 de estruturas TOTAL_MES. */
	MY_AVL prod[SIZE_ABC];					/* Catálogo de Produtos. */
};

/* Estrutura com informações sobre o preço e a quantidade. */
struct priceQuantity {
	double totalprice;						/* Preço. */
	int totalquant;							/* Quantidade. */
};

/* Estrutura com os valores de um determinado mês. */
struct totalMes{
	double totalFacturado; 					/* Total facturado num determinado mês. */
	int totalQuant;							/* Quantidade total vendida num determinado mês. */
	int totalVendas;						/* Total de vendas num determinado mês. */
};

/* Informação em cada nodo das MY_AVL do Catalógo de Produtos. */
struct info{
	PRICE_QUANTITY N[SIZE_MONTH][SIZE_FILIAIS];	/* Matriz de estruturas PRICE_QUANTITY referentes às vendas sem promoção.*/
	PRICE_QUANTITY P[SIZE_MONTH][SIZE_FILIAIS]; /* Matriz de estruturas PRICE_QUANTITY referentes às vendas com promoção.*/
};

/* Estrutura auxiliar à resolução de algumas queries. */
struct dados{
	double totalpriceF[SIZE_FILIAIS];			/* Array com o total facturado em cada filial. */			
	int totalquantF[SIZE_FILIAIS];				/* Array com o total vendido em cada filial. */
	double totalMP;								/* Total facturado. */
	int totalVendas;							/* Total vendido. */
};

/* Funções privadas ao módulo. */
static PRICE_QUANTITY initPQ();
static INFO initINFO();
static INFO copyInfoFact(SALES,INFO,FACTURACAO);
static void freeTotalMes(TOTAL_MES m);
static void freePQ(PRICE_QUANTITY x);
static TOTAL_MES initTotalMes();

/* Inicializa uma estrutura FACTURACAO. */
FACTURACAO initFact(){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<SIZE_MONTH;i++)
		f->total_mes[i]=initTotalMes();
	return f;
}

/* Liberta uma estrutura FACTURACAO. */
void freeFact(FACTURACAO f){
	int i;
	for(i=0;i<SIZE_MONTH;i++) freeTotalMes(f->total_mes[i]);
	for(i=0;i<SIZE_ABC;i++) removeMyAvl(f->prod[i],freeInfo);
	free(f);
	f=NULL;
}

/* Liberta uma estrutura com informação (da Avl). */
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

/* Inicializa uma estrutura DADOS. */
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

/* Função que copia o Catálogo de Produtos para a estrutura FACTURACAO. */
FACTURACAO copyProducts(FACTURACAO f,CATALOG_PRODUCTS p){
	int i;	
	for(i=0;i<SIZE_ABC;i++)
		f->prod[i] = cloneMyAvl(getP(p,i));
	return f;
}

/* Função que insere uma Venda na estrutura FACTURACAO. */
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


/*GETS & SETS*/
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

MY_AVL getProductIndex(FACTURACAO f,int index){
	return f->prod[index];
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

/* Inicializa uma estrutura PRICE_QUANTITY. */
static PRICE_QUANTITY initPQ(){
	PRICE_QUANTITY x = malloc (sizeof (struct priceQuantity));
	x->totalprice = 0;
	x->totalquant = 0;
	return x;
}

/* Inicializa uma estrutura INFO. */
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

/* Inicializa uma estrutura TOTAL_MES. */
static TOTAL_MES initTotalMes(){
	TOTAL_MES total_mes = malloc(sizeof(struct totalMes));
	total_mes->totalFacturado=0; 
	total_mes->totalQuant=0;
	total_mes->totalVendas=0;
	return total_mes;
}

/* Função que copia a informação da Venda. */
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

/* Liberta memória da estrutura PRICE_QUANTITY. */
static void freePQ(PRICE_QUANTITY x){
	free(x);
}

/* Liberta memória da estrutura TOTAL_MES. */
static void freeTotalMes(TOTAL_MES m){
	free(m);
}