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
  double totalMP;
  int totalMQ;
};


DADOS initDADOS(){
	int i;
	DADOS d = malloc(sizeof(struct dados));
	for(i=0;i<3;i++){
		d->totalpriceF[i]=0;
  		d->totalquantF[i]=0;
  		
  	}
  	d->totalMP=0;
  	d->totalMQ=0;
  	return d;
}
FACTURACAO initF (){
	FACTURACAO f = malloc(sizeof(struct fact));
	return f;
}

FACTURACAO initFact (FACTURACAO f,CATALOG_PRODUCTS p){
	int i,j;
	for(i=0;i<12;i++)	
		for(j=0;j<26;j++)
			f->prod[i][j] = cloneMyAvl(getP(p,j));
	
	return f;
}

PQ initPQ(){
	PQ x = malloc (sizeof (struct pq));
	x->totalprice=0;
	x->totalquant=0;
	return x;
}

INFO initINFO(){
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

INFO copia (SALES s, INFO i){
	int p,f;
	if(getSalesInfoPromo(s)== 'P') p=1;
	else p=0;

	f=getSalesFilial(s)-1;
	double total=(getSalesPrice(s))*(getSalesQuantity(s));

	i->F[p][f]->totalprice+=total;
	i->F[p][f]->totalquant+=getSalesQuantity(s);
	i->totalMesP+=total;
	i->totalMesQ+=getSalesQuantity(s);
	
	return i;
}
/*###########################Querie3##############################*/

double getnumFilialP(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalprice;
}

int getnumFilialQ(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalquant;
}

DADOS passa(INFO f,DADOS d,int promo){
	int i;
	for(i=0;i<3;i++){
		d->totalpriceF[i]=getnumFilialP(f,i,promo);
		d->totalquantF[i]=getnumFilialQ(f,i,promo);
		d->totalMP+=getnumFilialP(f,i,promo);
		d->totalMQ+=getnumFilialQ(f,i,promo);
	}
	return d;
}

DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	DADOS d = initDADOS();

	int index=product[0]-'A';
	void* x=(INFO)gs(getAvl(f->prod[mes-1][index]),product);
	
	if(x) d=passa(x,d,promo);

	return d;
}
/*###########################Querie3##############################*/

/*###########################Querie4##############################*/
GROUP_PRODUCTS found(Avl a,GROUP_PRODUCTS list){
	int n;
	if(getInfo(a)==NULL){
		setGroupProd(list,insereP(getGroupProd(list),getGroupProdSize(list),getAvlCode(a)));
		setGroupProdSize(list,getGroupProdSize(list)+1);
	}
	else{ 
		list=found(getAvlLeft(a),list);
		list=found(getAvlRight(a),list);
	}
	return list;

}
/*
GROUP_PRODUCTS querie4 (FACTURACAO f){
	GROUP_PRODUCTS gp = initGroupProducts();
	int i;

	for(i=0;i<12;i++){
		verif(f->[i],gp);
	}

}
*/
/*############################Querie4#############################*/

/*###########################Querie6##############################*/

double getnumTotalP(INFO c){
	return c->totalMesP;
}

int getnumTotalQ(INFO c){
	return c->totalMesQ;
}

DADOS ps(Avl a,DADOS d){
	if(a!=NULL && getInfo(a)!=NULL){
		void* x= (INFO)getInfo(a);
		d->totalMP+=getnumTotalP(x);
		d->totalMQ+=getnumTotalQ(x);
		}
	if(a!=NULL){
		d=ps(getAvlLeft(a),d);
		d=ps(getAvlRight(a),d);
	}
	return d;
}

DADOS querie6(FACTURACAO f, int inicio, int fim){
	int i,j;
	DADOS d= initDADOS();
	for(i=(inicio-1);i<fim;i++){
		for(j=0;j<26;j++){
			d=ps(getAvl(f->prod[i][j]),d);
		}
	}
	return d;
}
/*###########################Querie6##############################*/

FACTURACAO insereFact(FACTURACAO f,SALES s){

	void* y;
	int month=getSalesMonth(s)-1;
	int index = getProduct(getSalesProduct(s))[0]-'A';
	
	void* x= (INFO)gs(getAvl(f->prod[month][index]),getProduct(getSalesProduct(s)));

	if(x){
		y=copia(s,x);
	}
	else {
		INFO i=initINFO();
		i=copia(s,i);
		y=i;
	}
	//f->arr[index]=insertMyAvl(f->arr[index],getProduct(getSalesProduct(s)),NULL);
	f->prod[month][index]=insertMyAvl(f->prod[month][index],getProduct(getSalesProduct(s)),y);
	
	return f;
}


/*GET & SET*/
double* getDadosP(DADOS d){
	return d->totalpriceF;
}

int* getDadosQ(DADOS d){
	return d->totalquantF;
}

double getDadosTP(DADOS d){
	return d->totalMP;
}

int getDadosTQ(DADOS d){
	return d->totalMQ;
}