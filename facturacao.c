#include "facturacao.h"
#include "Sales.h"
#include "avl.h"
#include "CatProducts.h"

struct fact{
	TOTAL_MES tm[12];
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
  double totalpriceF[3];
  int totalquantF[3];
  double totalMP;
  int totalMQ;
};

static DADOS initDADOS();
static PQ initPQ();
static INFO initINFO();
static INFO copyInfoFact(SALES,INFO,FACTURACAO);
static DADOS updatePriceQuantity(INFO,DADOS,int,int);
static INFO updateInfo(INFO,INFO);
static Avl compare (Avl,Avl);
static int checkInfo (INFO,int);
static GROUP_PRODUCTS found(Avl,GROUP_PRODUCTS,int*,int);
static DADOS factToDados(Avl,DADOS);

TOTAL_MES initTotalMes(){
	int i;
	TOTAL_MES tm = malloc(sizeof(struct totalMes));
	tm->totalFacturado=0; 
	tm->totalQuant=0;
	tm->RegistoV=0;
	return tm;
}

FACTURACAO initFact(){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<12;i++)
		f->tm[i]=initTotalMes();
	return f;
}

FACTURACAO copyProducts(FACTURACAO f,CATALOG_PRODUCTS p){
	int i;	
	for(i=0;i<26;i++)
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

/* STATICS */

static DADOS initDADOS(){
	int i;
	DADOS d = malloc(sizeof(struct dados));
	for(i=0;i<3;i++){
		d->totalpriceF[i] = 0;
  		d->totalquantF[i] = 0;
  	}
  	d->totalMP=0;
    d->totalMQ=0;
  	return d;
}

static PQ initPQ(){
	PQ x = malloc (sizeof (struct pq));
	x->totalprice = 0;
	x->totalquant = 0;
	return x;
}

static INFO initINFO(){
	int j,k;
	INFO i=malloc(sizeof(struct info));
	for(j=0;j<12;j++){
		for(k=0;k<3;k++){
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

/* ######################################### QUERIE 3 #################################### */


DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	DADOS d = initDADOS();

	int index = product[0]-'A';
	void* x = (INFO)findInfo(getAvl(f->prod[index]),product,NULL);
	
	if(x) d = updatePriceQuantity(x,d,promo,mes);

	return d;

}

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes){
	int i;
	for(i=0;i<3;i++){
		d->totalpriceF[i]=getnumFilialP(f,i,promo,mes);
		d->totalquantF[i]=getnumFilialQ(f,i,promo,mes);
	}
	return d;
}

/* ######################################### QUERIE 4 ####################################### */

GROUP_PRODUCTS querie4(FACTURACAO f,int* c,int filial){
	GROUP_PRODUCTS group = initGroupProducts(1);
	int i,j;
		
	for(i=0;i<26;i++){
		setJ(group,i+1);
		group = found(getAvl(f->prod[i]),group,c,filial);	
	}
	return group;
}

static int checkInfo(INFO i, int filial){
	int j;
	for(j=0;j<12;j++)
		if((i->N[j][filial-1]->totalquant)>0 || (i->P[j][filial-1]->totalquant)>0 ) return 1;
	return 0;
}


static GROUP_PRODUCTS found(Avl a,GROUP_PRODUCTS list,int* x,int filial){
	int sp;
	if(a){
	void* w = (INFO)getInfo(a);

		list=found(getAvlLeft(a),list,x,filial);
		if(w == NULL || (filial!=-1 && !checkInfo(w,filial))){
			(*x)++;
			sp=getGroupProdSp(list);
			setGroupProd(list,insertGROUP_PRODUCTS(getGroupProd(list),&sp,getJ(list),getAvlCode(a)));
			setGroupProdSp(list,sp);
			list=reallocGROUP_PRODUCTS(list);
		}
		list=found(getAvlRight(a),list,x,filial);
	}

	return list;
}
/* ######################################### QUERIE 6 ####################################### */

DADOS querie6(FACTURACAO f, int inicio, int fim){
	int i,j;
	DADOS d= initDADOS();
	for(i=(inicio-1);i<fim;i++){
		d->totalMP+=f->tm[i]->totalFacturado;
		d->totalMQ+=f->tm[i]->totalQuant;
	}
	return d;
}

/*#################################QUERIE 12#####################################*/
int querie12Products(FACTURACAO f){
	int i,sum=0,r;

	for(i=0;i<26;i++){
		r=infoNULL(getAvl(f->prod[i]));			
		sum+=r;
	}
	return sum;
}



