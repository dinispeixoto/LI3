#include "facturacao.h"
#include "Sales.h"
#include "avl.h"
#include "CatProducts.h"

struct fact{
    MY_AVL prod[SIZE_MONTH][26];
};

struct pq {
	double totalprice;
	int totalquant;
};

struct info{
  PQ F[2][3];
  double totalMesP;
  int totalMesQ;
};

struct dados{
  double totalpriceF[3];
  int totalquantF[3];
};

static DADOS initDADOS();
static PQ initPQ();
static INFO initINFO();
static INFO copia (SALES, INFO);
static DADOS passa(INFO,DADOS,int);


FACTURACAO initFact (){
	int i,j;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<12;i++)	
		for(j=0;j<26;j++)
			f->prod[i][j] = initMyAvl();
	return f;
}

FACTURACAO insereFact(FACTURACAO f,SALES s){

	void* y;
	int month=getSalesMonth(s)-1;
	int index = getProduct(getSalesProduct(s))[0]-'A';
	
	void* x= (INFO)findInfo(getAvl(f->prod[month][index]),getProduct(getSalesProduct(s)));

	if(x){
		y=copia(s,x);
	}
	else {
		INFO i=initINFO();
		i=copia(s,i);
		y=i;
	}

	f->prod[month][index]=insertMyAvl(f->prod[month][index],getProduct(getSalesProduct(s)),y);
	
	return f;
}

DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	DADOS d = initDADOS();

	int index=product[0]-'A';
	void* x=(INFO)findInfo(getAvl(f->prod[mes-1][index]),product);
	
	if(x) d=passa(x,d,promo);

	return d;

}


/*GET & SET*/
double* getDadosP(DADOS d){
	return d->totalpriceF;
}

int* getDadosQ(DADOS d){
	return d->totalquantF;
}

double getnumFilialP(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalprice;
}

int getnumFilialQ(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalquant;
}

/* STATICS */


static DADOS initDADOS(){
	int i;
	DADOS d = malloc(sizeof(struct dados));
	for(i=0;i<3;i++){
		d->totalpriceF[i]=0;
  		d->totalquantF[i]=0;
  	}
  	return d;
}

static PQ initPQ(){
	PQ x = malloc (sizeof (struct pq));
	x->totalprice=0;
	x->totalquant=0;
	return x;
}

static INFO initINFO(){
	int j,k;
	INFO i=malloc(sizeof(struct info));
	for(j=0;j<2;j++){
		for(k=0;k<3;k++)
			i->F[j][k]=initPQ();
	}
	i->totalMesP=0;
	i->totalMesQ=0;
	return i;
}


static INFO copia (SALES s, INFO i){
	int p,f;
	double total;
	if(getSalesInfoPromo(s)== 'P') p=1;
	else p=0;

	f=getSalesFilial(s)-1;
	total=(getSalesPrice(s))*(getSalesQuantity(s));

	i->F[p][f]->totalprice+=total;
	i->F[p][f]->totalquant+=getSalesQuantity(s);
	i->totalMesP+=total;
	i->totalMesQ+=getSalesQuantity(s);
	
	return i;
}


static DADOS passa(INFO f,DADOS d,int promo){
	int i;
	for(i=0;i<3;i++){
		d->totalpriceF[i]=getnumFilialP(f,i,promo);
		d->totalquantF[i]=getnumFilialQ(f,i,promo);
	}
	return d;
}