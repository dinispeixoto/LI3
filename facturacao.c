#include "facturacao.h"
#include "Sales.h"
#include "avl.h"
#include "CatProducts.h"

struct fact{
    MY_AVL prod[SIZE_MONTH][SIZE_ABC];
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

static DADOS initDADOS();
static PQ initPQ();
static INFO initINFO();
static INFO copyInfo(SALES, INFO);
static DADOS updatePriceQuantity(INFO,DADOS,int);
static INFO updateInfo(INFO,INFO);
static Avl compare (Avl,Avl);
static int checkInfo (INFO,int);
static GROUP_PRODUCTS found(Avl,GROUP_PRODUCTS,int*,int);
static DADOS avlToDados(Avl,DADOS);


FACTURACAO initFact(){
	FACTURACAO f = malloc(sizeof(struct fact));
	return f;
}

void freeFact(FACTURACAO f){
	int i,j;
	if(f){
		for(i=0;i<12;i++)
			for(j=0;j<26;j++)
				removeMyAvl(f->prod[i][j]);
		free(f);
	}
}

FACTURACAO copyProducts(FACTURACAO f,CATALOG_PRODUCTS p){
	int i,j;
	for(i=0;i<12;i++)	
		for(j=0;j<26;j++)
			f->prod[i][j] = cloneMyAvl(getP(p,j));
	
	return f;
}

FACTURACAO insereFact(FACTURACAO f,SALES s){

	void* y;
	int month = getSalesMonth(s)-1;
	int index = getProduct(getSalesProduct(s))[0]-'A';
	
	void* x = (INFO)findInfo(getAvl(f->prod[month][index]),getProduct(getSalesProduct(s)));

	if(x)
		y = copyInfo(s,x);
	else {
		INFO i = initINFO();
		i = copyInfo(s,i);
		y = i;
		f->prod[month][index] = insertMyAvl(f->prod[month][index],getProduct(getSalesProduct(s)),y);
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

double getnumFilialP(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalprice;
}

int getnumFilialQ(INFO c,int filial, int promo){
	return c->F[promo][filial]->totalquant;
}

double getDadosTP(DADOS d){
	return d->totalMP;
}

int getDadosTQ(DADOS d){
	return d->totalMQ;
}

double getnumTotalP(INFO c){
	return c->totalMesP;
}

int getnumTotalQ(INFO c){
	return c->totalMesQ;
}

/* STATICS */

static DADOS initDADOS(){
	int i;
	DADOS d = malloc(sizeof(struct dados));
	for(i=0;i<3;i++){
		d->totalpriceF[i] = 0;
  		d->totalquantF[i] = 0;
  	}
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
	for(j=0;j<2;j++){
		for(k=0;k<3;k++)
			i->F[j][k] = initPQ();
	}
	i->totalMesP = 0;
	i->totalMesQ = 0;
	return i;
}


static INFO copyInfo(SALES s, INFO i){
	int p,f;
	double total;

	if(getSalesInfoPromo(s)== 'P') p=1;
	else p=0;

	f=getSalesFilial(s)-1;
	total=(getSalesPrice(s))*(getSalesQuantity(s));

	i->F[p][f]->totalprice += total;
	i->F[p][f]->totalquant += getSalesQuantity(s);
	i->totalMesP += total;
	i->totalMesQ += getSalesQuantity(s);	
	return i;
}


/* ######################################### QUERIE 3 #################################### */


DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	DADOS d = initDADOS();

	int index = product[0]-'A';
	void* x = (INFO)findInfo(getAvl(f->prod[mes-1][index]),product);
	
	if(x) d = updatePriceQuantity(x,d,promo);

	return d;

}

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo){
	int i;
	for(i=0;i<3;i++){
		d->totalpriceF[i]=getnumFilialP(f,i,promo);
		d->totalquantF[i]=getnumFilialQ(f,i,promo);
	}
	return d;
}

/* ######################################### QUERIE 4 ####################################### */

GROUP_PRODUCTS querie4(FACTURACAO f,int* c,int filial){
	GROUP_PRODUCTS group = initGroupProducts(1);
	int i,j;
	MY_AVL clone[26];
	
	for(i=0;i<26;i++)
				clone[i] = cloneMyAvl(f->prod[0][i]);	

	for(i=1;i<12;i++){
			for(j=0;j<26;j++){	
				setAvl(clone[j],compare(getAvl(clone[j]),getAvl(f->prod[i][j])));
			}
		}
	for(i=0;i<26;i++){
		setJ(group,i+1);
		group = found(getAvl(clone[i]),group,c,filial);	
	}
	removeFromMY_AVL(clone,26);
	return group;
}

static INFO updateInfo(INFO a, INFO b){
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<3;j++){
			a->F[i][j]->totalprice += b->F[i][j]->totalprice;
			a->F[i][j]->totalquant += b->F[i][j]->totalquant;

		}
	a->totalMesQ += b->totalMesQ;
	a->totalMesP += b->totalMesQ;
	return a;
}

/*static Avl compare(Avl a, Avl b){

	if(a){
		if(getInfo(b)){
			if(getInfo(a)){
				void* x = (INFO)getInfo(a);
				void* y = (INFO)getInfo(b);
				setInfo(a,updateInfo(x,y));
			}
			else setInfo(a,getInfo(b));
		}
		setAv(getAvlLeft(a),compare(getAvlLeft(a),getAvlLeft(b)));
		setAv(getAvlRight(a),compare(getAvlRight(a),getAvlRight(b)));

	}
	return a;
}*/

static Avl compare(Avl a, Avl b){

	if(a){
		if(getInfo(b)){
			if(getInfo(a)){
				INFO n = initINFO();
				void* y = (INFO)getInfo(b);
				n=updateInfo(n,y);
				INFO m = initINFO();
				void* x = (INFO)getInfo(a);
				m=updateInfo(m,x);
				setInfo(a,updateInfo(m,n));
			}
			else {
				INFO p = initINFO();
				void* r = (INFO)getInfo(b);
				p=updateInfo(p,r);
				setInfo(a,p);
			}
		}
		setAv(getAvlLeft(a),compare(getAvlLeft(a),getAvlLeft(b)));
		setAv(getAvlRight(a),compare(getAvlRight(a),getAvlRight(b)));
	}
	return a;
}

static int checkInfo(INFO i, int filial){
	int r=0,j;
	for(j=0;j<2;j++)
		r += i->F[j][filial-1]->totalquant;
	return r;
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
		for(j=0;j<26;j++){
			d=avlToDados(getAvl(f->prod[i][j]),d);
		}
	}
	return d;
}

static DADOS avlToDados(Avl a,DADOS d){
	if(a!=NULL && getInfo(a)!=NULL){
		void* x= (INFO)getInfo(a);
		d->totalMP+=getnumTotalP(x);
		d->totalMQ++;
		}
	if(a!=NULL){
		d=avlToDados(getAvlLeft(a),d);
		d=avlToDados(getAvlRight(a),d);
	}
	return d;
}
