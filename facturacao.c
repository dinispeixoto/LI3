#include "facturacao.h"
#include "Sales.h"
#include "avl.h"

FACTURACAO initFact (){
	int i;
	FACTURACAO f = malloc(sizeof(struct fact));
	for(i=0;i<12;i++)	f->prod[i] = initMyAvl();
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
	i->totalMes=0;
	return i;
}


INFO copia (SALES s, INFO i){
	int p,f;
	if(getSalesInfoPromo(s)== 'P') p=1;
	else p=0;

	f=getSalesFilial(s)-1;
	int total=(getSalesPrice(s))*(getSalesQuantity(s));

	i->F[p][f]->totalprice+=total;
	i->F[p][f]->totalquant+=getSalesQuantity(s);
	i->totalMes+=total;
	
	return i;
}

FACTURACAO insereFact(FACTURACAO f,SALES s){

	INFO i=initINFO();
	
	i=copia(s,i);
	void* y=&i;
	int month=getSalesMonth(s);

	f->prod[month]=insertMyAvl(f->prod[month],getProduct(getSalesProduct(s)),y);

	return f;
}


