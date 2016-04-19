#include "headers/queries.h"

#define index(i) i-'A'

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes);
static int checkInfo(INFO i, int filial);
static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial);
static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial);

/* ######################################### QUERIE 2 #################################### */

 LISTA_STRINGS querie2(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	LISTA_STRINGS group = initListaStrings(totalElements(getP(Catalog,index)),SIZE_PRODUCT);
	MY_AVL a = getP(Catalog,index);
	Avl tree = getAvl(a);
	/*travessia(tree,0,group);*/
	return group;
}

/* ######################################### QUERIE 3 #################################### */


DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	DADOS d = initDADOS();

	int index = product[0]-'A';
	void* x = (INFO)findInfo(getAvl(getProductIndex(f,index)),product,NULL);
	
	if(x) d = updatePriceQuantity(x,d,promo,mes);

	return d;

}

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes){
	int i;
	for(i=0;i<3;i++){
		d = setTotalPrice(d,i,getnumFilialP(f,i,promo,mes));
		d = setTotalQuantity(d,i,getnumFilialQ(f,i,promo,mes));
	}
	return d;
}

/* ######################################### QUERIE 4 ####################################### */

LISTA_STRINGS querie4(FACTURACAO f,int filial){
	LISTA_STRINGS group = initListaStrings(1,SIZE_PRODUCT);
	int i,j;
		
	for(i=0;i<26;i++){
		group = found(getAvl(getProductIndex(f,i)),group,filial);
	}
	return group;
}

static int checkInfo(INFO i, int filial){
	int j;
	for(j=0;j<12;j++)
		if(getTotalQuantPQ(getNormalPQ(i,j,filial))>0 || (getTotalQuantPQ(getPromoPQ(i,j,filial)))>0) return 1;
	return 0;
}

static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial){
	int sp;
	if(a){
	void* w = (INFO)getInfo(a);

		list=found(getAvlLeft(a),list,filial);
		if(w == NULL || (filial!=-1 && !checkInfo(w,filial))){
			addListaStrings(list,getListaSp(list),getAvlCode(a));
			list=reallocListaStrings(list);
		}
		list=found(getAvlRight(a),list,filial);
	}

	return list;
}

/*#################################QUERIE 5##################################### FUNCIONA*/

DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df,char* client,int filial){
	int i,j;
	int index = client[0]-'A';
	void* x = (INFO_CLIENT)findInfo(getAvl(getClientIndexF(f,index)),client,NULL);

	df=addQ(df,x,filial);
	
	return df;
}

static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial){
	int i;
	for(i=0;i<12;i++)
		df = updateQuant_DadosFilial(df,filial,i,getInfoMesQuantity(getInfoMes(ic,i)));
	return df;
}


/* ######################################### QUERIE 6 ####################################### */

DADOS querie6(FACTURACAO f, int inicio, int fim){
	int i,j;
	DADOS d= initDADOS();
	for(i=(inicio-1);i<fim;i++){
		d = updateTotalMP(d,getTotalFacturadoMES(getTotalMes(f,i)));
		d = updateTotalMQ(d,getTotalQuantMES(getTotalMes(f,i)));
	}
	return d;
}

/*#################################QUERIE 7###################################### FUNCIONA(VERIFICAR REMOVE)*/
static LISTA_STRINGS removeList(Avl a,LISTA_STRINGS list );
static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS list );
static LISTA_STRINGS checkClientsValeN (FILIAL* f,LISTA_STRINGS list);

LISTA_STRINGS querie7 (FILIAL* f){
	int i;
	LISTA_STRINGS list = initListaStrings(1,SIZE_CLIENT);
	checkClientsValeN(f,list);
	return list;
}

static LISTA_STRINGS removeList(Avl a,LISTA_STRINGS list ){
	int sp;
	if(a){
		removeList(getAvlLeft(a),list);
		void* x = (INFO_CLIENT)findInfo(a,getAvlCode(a),NULL);
		if(!getComp(x)){
			removeListaStrings(list,getAvlCode(a));
		}
		removeList(getAvlRight(a),list);
	}
	return list;
}

static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS list){
	int sp;
	if(a){
		insereList(getAvlLeft(a),list);
		void* x = (INFO_CLIENT)findInfo(a,getAvlCode(a),NULL);
		if(getComp(x)){
			addListaStrings(list,getListaSp(list),getAvlCode(a));
			list=reallocListaStrings(list);
		}
		insereList(getAvlRight(a),list);
	}
	return list;
}

static LISTA_STRINGS checkClientsValeN (FILIAL* f,LISTA_STRINGS list){
	int i,j;

	for(j=0;j<26;j++){
		insereList(getAvl(getClientIndexF(f[0],j)),list);
		}

	for(i=1;i<3;i++){
		for(j=0;j<26;j++){
			removeList(getAvl(getClientIndexF(f[i],j)),list);
			}
		}
	return list;
}

/*#################################QUERIE 8#####################################*/
static LISTA_STRINGS checkProd(INFO_PRODUCT,LISTA_STRINGS,LISTA_STRINGS,char*);
static LISTA_STRINGS find2(INFO_CLIENT,char*,LISTA_STRINGS,LISTA_STRINGS,char*);
static LISTA_STRINGS find(Avl,char*,LISTA_STRINGS,LISTA_STRINGS);

LISTA_STRINGS querie8(FILIAL f,char* product,LISTA_STRINGS* P){
	int i;
	LISTA_STRINGS gcN = initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS gcP = initListaStrings(1,SIZE_CLIENT);
	for(i=0;i<26;i++){
		find(getAvl(getClientIndexF(f,i)),product,gcN,gcP);
	}
	(*P)=gcP;
	return gcN;
}

static LISTA_STRINGS checkProd(INFO_PRODUCT ip,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client){
	int i,posicao;

	if(getInfoProductQuantity(ip,0)){
		addListaStrings(gcN,getListaSp(gcN),client);
		gcN=reallocListaStrings(gcN);
	}
	if(getInfoProductQuantity(ip,1)){
		addListaStrings(gcP,getListaSp(gcP),client);
		gcP=reallocListaStrings(gcP);
	}
	return gcN;
}

static LISTA_STRINGS find2(INFO_CLIENT ic,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client){
	int i;
	int index=product[0]-'A';

	for(i=0;i<12;i++){
		if(getInfoMesProduct(getInfoMes(ic,i),index)){
			if(getAvl(getInfoMesProduct(getInfoMes(ic,i),index))){
				void* x=(INFO_PRODUCT)findInfo(getAvl(getInfoMesProduct(getInfoMes(ic,i),index)),product,NULL);
				if(x) checkProd(x,gcN,gcP,client);
			}
		}
	}	
	return gcN;
}

static LISTA_STRINGS find(Avl a, char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP){
	
	if(a){
		find(getAvlLeft(a),product,gcN,gcP);
		void* x=(INFO_CLIENT)getInfo(a);
		find2(x,product,gcN,gcP,getAvlCode(a));
		find(getAvlRight(a),product,gcN,gcP);
	}
	return gcN;
}


/*#################################QUERIE 9#####################################*/

static int quant(INFO_PRODUCT);
static LISTA_STRINGS converte (Heap,LISTA_STRINGS,int);
static Heap findProd2(Avl,Heap);
static Heap findProd(INFO_CLIENT,int,Heap);

LISTA_STRINGS querie9(FILIAL* f, char* client,int month){
	int i;
	Heap heap=initHeap(1);
	int index=index(client[0]);
	for(i=0;i<3;i++){
		void* x=(INFO_CLIENT)findInfo(getAvl(getClientIndexF(f[i],index)),client,NULL);
		findProd(x,month,heap);
	}

	LISTA_STRINGS group = initListaStrings(1,SIZE_PRODUCT);
	converte(heap,group,getHeapUsed(heap));
	return group;
}

static int quant(INFO_PRODUCT ip){
	return (getInfoProductQuantity(ip,0)+getInfoProductQuantity(ip,1));
}

static LISTA_STRINGS converte (Heap heap, LISTA_STRINGS group,int total){
	int i,posicao;
	while(0<total){
		addListaStrings(group,getListaSp(group),extractMax(heap));
		group=reallocListaStrings(group);
		total--;
	}
	return group;
}


static Heap findProd2(Avl a,Heap heap){
	int r;
	if(a){
		findProd2(getAvlLeft(a),heap);
		void* x= (INFO_PRODUCT)getInfo(a);
		r=quant(x);
		insertHeap(heap,r,getAvlCode(a));
		findProd2(getAvlRight(a),heap);
	}
	return heap;
}

static Heap findProd(INFO_CLIENT ic, int month,Heap heap){
	int i;
	for(i=0;i<26;i++){
		if(getInfoMesProduct(getInfoMes(ic,month-1),i))
			findProd2(getAvl(getInfoMesProduct(getInfoMes(ic,month-1),i)),heap);
	}
	return heap;
}

/*#################################QUERIE 10#####################################*/
static int qua (INFO info,int filial){
	int i,sum=0;
	for(i=0;i<12;i++){
		sum+=(getTotalQuantPQ(getNormalPQ(info,i,filial))+getTotalQuantPQ(getPromoPQ(info,i,filial)));
	}
	return sum;
}

static int pesq (Avl a, Heap hp,int filial){
	int r;
	if(a){
	pesq(getAvlLeft(a),hp,filial);
	void* x= (INFO)getInfo(a);
	if(x){
		r=qua(x,filial);
		insertHeap(hp,r,getAvlCode(a));
	}
	pesq(getAvlRight(a),hp,filial);
	}
	return 1;
}

static int pesquisa2 (INFO_CLIENT ic, Heap hp,int N,int* num,char** prod){
	int i,j;
	int ind;
	for(j=0;j<N;j++){
		ind= index(prod[j][0]);
		for(i=0;i<12;i++){
			if(getInfoMesProduct(getInfoMes(ic,i),ind)){
				void* x=findInfo(getAvl(getInfoMesProduct(getInfoMes(ic,i),ind)),prod[j],NULL);
				if(x){num[j]++;return 1;}
			}	
		}
	}
	return 1;
}

static int pesquisa (Avl a, Heap hp,int N,int* num,char** prod){
	if(a){
	pesquisa(getAvlLeft(a),hp,N,num,prod);
	
	void* x= (INFO_CLIENT)getInfo(a);
	pesquisa2(x,hp,N,num,prod);

	pesquisa(getAvlRight(a),hp,N,num,prod);
	}
	return 1;
}

static int querie10Fact (FACTURACAO f,Heap hp,int filial){
	int i;
	for(i=0;i<26;i++){
		pesq(getAvl(getProductIndex(f,i)),hp,filial);
	}
	return 1;
}

static LISTA_STRINGS querie10Fil(FILIAL f,Heap hp,int N){
	int i;
	int num[N];
	char* prod[N];
	for(i=0;i<N;i++){
		num[i]= 0;
		prod[i]=getString(hp,i);
	}
	for(i=0;i<26;i++){
		pesquisa(getAvl(getClientIndexF(f,i)),hp,N,num,prod);
	} 
	LISTA_STRINGS gp = initListaStrings(1,SIZE_PRODUCT);
	
	/*for(i=0;i<N;i++){
		printf("%d-%s\n",num[i],*prod[i]);
	}*/
	converte(hp,gp,N);
	return gp;
}

LISTA_STRINGS querie10 (FILIAL f,FACTURACAO fact, int N,int filial){
	Heap hp=initHeap(1);
	querie10Fact(fact,hp,filial);
	LISTA_STRINGS ls;
	ls=querie10Fil(f,hp,N);
	return ls;
}

/*#################################QUERIE 11#####################################*/

static int quant2(INFO_PRODUCT ip){
	return (getInfoProductPrice(ip,0)+getInfoProductPrice(ip,1));
}

static Heap highCost2 (Avl a,Heap hp){
	int r;
	if(a){
	highCost2(getAvlLeft(a),hp);
	void* x= (INFO_PRODUCT)getInfo(a);
	r=quant2(x);
	insertHeap(hp,r,getAvlCode(a));
	highCost2(getAvlRight(a),hp);
	}
	return hp;
}

static Heap highCost (INFO_CLIENT ic,Heap hp){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<26;j++){
			if(getInfoMesProduct(getInfoMes(ic,i),j))	
				highCost2(getAvl(getInfoMesProduct(getInfoMes(ic,i),j)),hp);
		}
	}
	return hp;
}

LISTA_STRINGS querie11(FILIAL* f,char* client){
	int i;
	int in = index(client[0]);
	Heap hp=initHeap(1);
	for(i=0;i<3;i++){
		void* x=findInfo(getAvl(getClientIndexF(f[i],in)),client,NULL);
		highCost(x,hp);
	}
	LISTA_STRINGS gp= initListaStrings(1,SIZE_PRODUCT);
	
	converte(hp,gp,3);
	return gp;
}

/*#################################QUERIE 12#####################################*/

static int querie12Clients(FILIAL* f){
	int i,j,sum=0,r;
	for(i=0;i<3;i++)
		for(j=0;j<26;j++){
			r=infoNULL(getAvl(getClientIndexF(f[i],j)));
			sum+=r;
		}
	return sum;
}

static int querie12Products(FACTURACAO f){
	int i,sum=0,r;

	for(i=0;i<26;i++){
		r=infoNULL(getAvl(getProductIndex(f,i)));			
		sum+=r;
	}
	return sum;
}

int querie12(FILIAL* f, FACTURACAO fact, int* sumClient){
	int sumProduct;
	*sumClient=querie12Clients(f);
	sumProduct=querie12Products(fact);
	return sumProduct;
}
