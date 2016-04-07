#include "facturacao.h"
#include "avl.h"


FACTURACAO initFact (Avl* a){
	int i;
	FACTURACAO f = malloc (sizeof(struct fact));
	for(i=0;i<26;i++){
		f->prod[i]=cloneAvl(a[i]);
	}
	f->totalElementos=0;
	f->totalFact=0;
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
	for(j=0;j<6;j++){
		for(k=0;k<12;k++)
			i->F[j][k]=initPQ();
	}
	return i;
}

INFO copia (Sales s, INFO i){
	if(s->infoPromo == 'P'){
		i->F[s->filial+2][s->month-1]->totalprice+=(s->price)*(s->quantity);
		i->F[s->filial+2][s->month-1]->totalquant+=s->quantity;
	}
	else {
		i->F[s->filial-1][s->month-1]->totalprice+=(s->price)*(s->quantity);
		i->F[s->filial-1][s->month-1]->totalquant+=s->quantity;
	}
	return i;
}

FACTURACAO insereFact(FACTURACAO f,Sales s){

	void* y=malloc (sizeof(struct info));
	INFO i=initINFO();
	
	i=copia(s,i);
	
	int index = s->product[0]-'A';

	memcpy(y,i,sizeof(*i));

	f->prod[index]=insert(f->prod[index],s->product,y);

	//f->totalFact+=i->price;
	//f->totalElementos++;
	return f;
}


	

