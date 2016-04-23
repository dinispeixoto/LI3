#include "headers/facturacao.h"

/* Estrutura com os valores de um determinado mês. */
struct totalMes{
	double totalFacturado; 					/* Total facturado num determinado mês. */
	int totalQuant;							/* Quantidade total vendida num determinado mês. */
	int totalVendas;						/* Total de vendas num determinado mês. */
};

typedef struct totalMes *TOTAL_MES;

/* Estrutura com informações sobre o preço e a quantidade. */
struct priceQuantity {
	double totalprice;						/* Preço. */
	int totalquant;							/* Quantidade. */
};

typedef struct priceQuantity *PRICE_QUANTITY;

/* Informação em cada nodo das MY_AVL do Catalógo de Produtos. */
struct info{
	PRICE_QUANTITY N[SIZE_MONTH][SIZE_FILIAIS];	/* Matriz de estruturas PRICE_QUANTITY referentes às vendas sem promoção.*/
	PRICE_QUANTITY P[SIZE_MONTH][SIZE_FILIAIS]; /* Matriz de estruturas PRICE_QUANTITY referentes às vendas com promoção.*/
};

typedef struct info *INFO;

/* Estrutura principal da facturação. */
struct fact{
	TOTAL_MES total_mes[SIZE_MONTH];		/* Array de 12 de estruturas TOTAL_MES. */
	MY_AVL prod[SIZE_ABC];					/* Catálogo de Produtos. */
};

/* Estrutura auxiliar à resolução de algumas queries. */
struct dados{
	double totalpriceF[SIZE_FILIAIS];			/* Array com o total facturado em cada filial. */			
	int totalquantF[SIZE_FILIAIS];				/* Array com o total vendido em cada filial. */
	double totalMP;								/* Total facturado. */
	int totalVendas;
	int totalMQ;							/* Total vendido. */
};

/* Funções privadas ao módulo. */
static PRICE_QUANTITY initPQ();
static INFO initINFO();
static INFO copyInfoFact(SALES,INFO,FACTURACAO);
static void freeTotalMes(TOTAL_MES m);
static void freePQ(PRICE_QUANTITY x);
static TOTAL_MES initTotalMes();
static int checkInfo(INFO i, int filial);
static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial);
static DADOS updatePQ(INFO inf,DADOS d,int promo,int mes);


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

/* Inicializa uma estrutura FACTURACAO. */
FACTURACAO initFact(){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<SIZE_MONTH;i++)
		f->total_mes[i]=initTotalMes();
	return f;
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
	d->totalMQ=0;
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

double getDadosTP(DADOS d){
	return d->totalMP;
}

int getDadosTV(DADOS d){
	return d->totalVendas;
}

Avl getProductIndex(FACTURACAO f,int index){
	return getAvl(f->prod[index]);
}

double getTotalMP(DADOS d){
	return d->totalMP; 
}

DADOS updateTotalMP(DADOS d, double total){
	d->totalMP += total;
	return d;
}

int getTotalVendas(DADOS d){
	return d->totalVendas;
}

DADOS updateTotalVendas(DADOS d, int total){
	d->totalVendas += total;
	return d;
}



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
					i->P[month][filial]->totalquant += quantity;	
					break;
		case 'N':	i->N[month][filial]->totalprice += total;
					i->N[month][filial]->totalquant += quantity;	
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

/* ######################################### QUERIE 3 #################################### */

DADOS updatePriceQuantity(FACTURACAO f,DADOS d,int promo,int mes,char* product){
	void* x;
	int index = product[0]-'A';
	x = (INFO)findInfo(getAvl(f->prod[index]),product,NULL);
	if(x) d=updatePQ(x,d,promo,mes);
	return d;
}

/*Função que calcula os valores provenientes de um porduto, dado um mês e uma Promoção.*/
static DADOS updatePQ(INFO inf,DADOS d,int promo,int mes){
	int i;
	for(i=0;i<SIZE_FILIAIS;i++){
		if(promo){
			d->totalpriceF[i] = inf->P[mes-1][i]->totalprice;
			d->totalquantF[i] = inf->P[mes-1][i]->totalquant;
		}
		else {
			d->totalpriceF[i] = inf->N[mes-1][i]->totalprice;
			d->totalquantF[i] = inf->N[mes-1][i]->totalquant;
		}
	}
	return d;
}

/* ######################################### QUERIE 4 #################################### */

LISTA_STRINGS listaProducts (FACTURACAO f,LISTA_STRINGS group, int filial){
	int i;
	for(i=0;i<SIZE_ABC;i++){
		group = found(getAvl(f->prod[i]),group,filial);
	}
	return group;
}

/*Função que verifica se um produto comprou numa dada filial. */
static int checkInfo(INFO i, int filial){
	int j;
	for(j=0;j<SIZE_MONTH;j++)
		if((i->N[j][filial-1]->totalquant)>0 || (i->P[j][filial-1]->totalquant)>0 ) return 1;
	return 0;
}

/*Função que procura e insere numa Lista de Strings os produtos que nunca foram comprados numa dada filial ou em geral. */
static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial){
	void* w;
	if(a){
		w = (INFO)getInfo(a);	
		list=found(getAvlLeft(a),list,filial);
		if(w == NULL || (filial!=-1 && !checkInfo(w,filial))){
			addListaStrings(list,getListaSp(list),getAvlCode(a));
			list=reallocListaStrings(list);
		}
		list=found(getAvlRight(a),list,filial);
		freeNodo(a);
	}
	return list;
}

/* ######################################### QUERIE 6 #################################### */

DADOS totalM(FACTURACAO f,DADOS d,int inicio, int fim){
	int i;
	for(i=(inicio-1);i<fim;i++){
		d->totalMP += f->total_mes[i]->totalFacturado;
		d->totalVendas += f->total_mes[i]->totalVendas;
		d->totalMQ += f->total_mes[i]->totalQuant;
	}
	return d;
}



/* ######################################### QUERIE 12 #################################### */
int querie12Products(FACTURACAO f){
	int i,sum=0,r;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getAvl(f->prod[i]);
		r=infoNULL(nodo);			
		sum+=r;
		freeNodo(nodo);
	}
	return sum;
}






