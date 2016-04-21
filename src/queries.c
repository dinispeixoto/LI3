#include "headers/queries.h"

#define index(i) i-'A'

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes);
static int checkInfo(INFO i, int filial);
static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial);
static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial);

/* ######################################### QUERIE 2 #################################### */
static LISTA_STRINGS travessia (Avl a,LISTA_STRINGS ls){
	Avl nodo;
	char* prod;
	if(a){
		nodo=getAvlLeft(a);
		travessia(nodo,ls);
		prod=getAvlCode(a);

		addListaStrings(ls,getListaSp(ls),prod);
		ls=reallocListaStrings(ls);
		free(prod);
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
		nodo=getAvlRight(a);
		travessia(nodo,ls);
		if(nodo)freeNodo(nodo);
	}
	return ls;
}


LISTA_STRINGS querie2(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	LISTA_STRINGS group = initListaStrings(totalElements(getP(Catalog,index)),SIZE_PRODUCT);
	MY_AVL a = getP(Catalog,index);
	Avl nodo = getAvl(a);
	travessia(nodo,group);
	
	if(nodo)freeNodo(nodo);
	
	return group;
}

/* ######################################### QUERIE 3 #################################### */


DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	
	void* x;
	DADOS d = initDADOS();
	int index = product[0]-'A';
	Avl nodo=getProductIndex(f,index);
	x = (INFO)findInfo(nodo,product,NULL);
	
	if(x) d = updatePriceQuantity(x,d,promo,mes);
	if(nodo)free(nodo);
	return d;

}

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes){
	int i;
	for(i=0;i<SIZE_FILIAIS;i++){
		d = setTotalPrice(d,i,getnumFilialP(f,i,promo,mes));
		d = setTotalQuantity(d,i,getnumFilialQ(f,i,promo,mes));
	}
	return d;
}

/* ######################################### QUERIE 4 ####################################### */

LISTA_STRINGS querie4(FACTURACAO f,int filial){
	LISTA_STRINGS group = initListaStrings(1,SIZE_PRODUCT);
	int i;
	Avl nodo;

	for(i=0;i<SIZE_ABC;i++){
		nodo=getProductIndex(f,i);
		group = found(getProductIndex(f,i),group,filial);
		if(nodo)freeNodo(nodo);
	}
	return group;
}

static int checkInfo(INFO i, int filial){
	int j;
	for(j=0;j<SIZE_MONTH;j++)
		if(getTotalQuantPQ(getNormalPQ(i,j,filial))>0 || (getTotalQuantPQ(getPromoPQ(i,j,filial)))>0) return 1;
	return 0;
}

static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial){
	void* w;
	char* prod=NULL;
	if(a){
		prod=getAvlCode(a);
		Avl nodo=getAvlLeft(a);
		w = (INFO)getInfo(a);	
		list=found(nodo,list,filial);
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
		if(w == NULL || (filial!=-1 && !checkInfo(w,filial))){
			addListaStrings(list,getListaSp(list),prod);
			list=reallocListaStrings(list);
		}
		nodo=getAvlRight(a);
		list=found(getAvlRight(a),list,filial);
		if(nodo)freeNodo(nodo);
	}
	if(prod)free(prod);
	return list;
}

/*#################################QUERIE 5##################################### FUNCIONA*/

DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df,char* client,int filial){
	void* x;
	int index = client[0]-'A';
	Avl nodo=getClientIndexF(f,index);
	x = (INFO_CLIENT)findInfo(getClientIndexF(f,index),client,NULL);

	df=addQ(df,x,filial);
	freeNodo(nodo);
	return df;
}

static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial){
	int i;
	for(i=0;i<SIZE_MONTH;i++)
		df = updateQuant_DadosFilial(df,filial,i,getInfoMesQuantity(getInfoMes(ic,i)));
	return df;
}


/* ######################################### QUERIE 6 ####################################### */

DADOS querie6(FACTURACAO f, int inicio, int fim){
	int i;
	DADOS d= initDADOS();
	for(i=(inicio-1);i<fim;i++){
		d = updateTotalMP(d,getTotalFacturadoMES(getTotalMes(f,i)));
		d = updateTotalVendas(d,getTotalRegisto(getTotalMes(f,i)));
	}
	return d;
}

/*#################################QUERIE 7###################################### FUNCIONA(VERIFICAR REMOVE)*/
static LISTA_STRINGS removeList(Avl a,LISTA_STRINGS list );
static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS list );
static LISTA_STRINGS checkClientsValeN (FILIAL* f,LISTA_STRINGS list);

LISTA_STRINGS querie7 (FILIAL* f){
	LISTA_STRINGS list = initListaStrings(1,SIZE_CLIENT);
	checkClientsValeN(f,list);
	return list;
}

static LISTA_STRINGS removeList(Avl a,LISTA_STRINGS list ){
	void* x;
	char* client;
	Avl nodo;
	if(a){
		nodo=getAvlLeft(a);
		removeList(nodo,list);
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
		client=getAvlCode(a);
		x = (INFO_CLIENT)findInfo(a,client,NULL);
		if(!getComp(x)){
			removeListaStrings(list,client);
		}
		free(client);
		nodo=getAvlRight(a);
		removeList(nodo,list);
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
	}
	return list;
}

static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS list){
	void* x;
	Avl aux;
	char* client;
	if(a){
		aux=getAvlLeft(a);
		insereList(aux,list);
		if(aux){freeNodo(aux);
				aux=NULL;}
		client=getAvlCode(a);
		x = (INFO_CLIENT)findInfo(a,client,NULL);
		
		if(getComp(x)){

			addListaStrings(list,getListaSp(list),client);
			list=reallocListaStrings(list);
		}
		free(client);
		aux=getAvlRight(a);
		insereList(aux,list);
		if(aux){freeNodo(aux);
				aux=NULL;}
	}
	return list;
}

static LISTA_STRINGS checkClientsValeN (FILIAL* f,LISTA_STRINGS list){
	int i,j;
	Avl aux;
	for(j=0;j<SIZE_ABC;j++){
		aux=getClientIndexF(f[0],j);
		insereList(getClientIndexF(f[0],j),list);
		freeNodo(aux);
		aux=NULL;
		}

	for(i=1;i<SIZE_FILIAIS;i++){
		for(j=0;j<SIZE_ABC;j++){
			aux=getClientIndexF(f[i],j);
			removeList(aux,list);
			freeNodo(aux);
			aux=NULL;
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
	Avl nodo=NULL;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getClientIndexF(f,i);
		find(nodo,product,gcN,gcP);
		freeNodo(nodo);
	}
	(*P)=gcP;
	return gcN;
}

static LISTA_STRINGS checkProd(INFO_PRODUCT ip,LISTA_STRINGS gcN,LISTA_STRINGS gcP,char* client){

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
	Avl nodo=NULL;
	for(i=0;i<SIZE_MONTH;i++){
		Avl nodo=getInfoMesProduct(getInfoMes(ic,i),index);
			if(nodo){
				void* x=(INFO_PRODUCT)findInfo(nodo,product,NULL);
				if(x) checkProd(x,gcN,gcP,client);
			}
	}
	if(nodo)freeNodo(nodo);	
	return gcN;
}

static LISTA_STRINGS find(Avl a, char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP){
	
	void* x;

	if(a){
		Avl nodo=getAvlLeft(a);
		find(nodo,product,gcN,gcP);
		x = (INFO_CLIENT)getInfo(a);
		find2(x,product,gcN,gcP,getAvlCode(a));
		if(nodo)freeNodo(nodo);
		nodo=NULL;
		nodo=getAvlRight(a);
		find(nodo,product,gcN,gcP);
		if(nodo)freeNodo(nodo);
	}
	return gcN;
}

/*#################################QUERIE 9#####################################*/

static int quant(INFO_PRODUCT);
static LISTA_STRINGS converte (Heap,LISTA_STRINGS,int);
static Heap findProd2(Avl,Heap);
static Heap findProd(INFO_CLIENT,int,Heap);

LISTA_STRINGS querie9(FILIAL* f, char* client,int month){
	int i; void* x;
	LISTA_STRINGS group;
	Heap heap=initHeap(1);
	int index=index(client[0]);
	Avl nodo;
	for(i=0;i<SIZE_FILIAIS;i++){
		nodo=getClientIndexF(f[i],index);
		x =(INFO_CLIENT)findInfo(nodo,client,NULL);
		findProd(x,month,heap);
		if(nodo)freeNodo(nodo);
	}

	group = initListaStrings(1,SIZE_PRODUCT);
	converte(heap,group,getHeapUsed(heap));
	return group;
}

static int quant(INFO_PRODUCT ip){
	return (getInfoProductQuantity(ip,0)+getInfoProductQuantity(ip,1));
}

static LISTA_STRINGS converte (Heap heap, LISTA_STRINGS group,int total){
	int limite = getHeapUsed(heap);
	while(0<total && 0<limite){
		addListaStrings(group,getListaSp(group),extractMax(heap));
		group=reallocListaStrings(group);
		total--;
		limite--;
	}
	return group;
}


static Heap findProd2(Avl a,Heap heap){
	int r; 
	void* x;
	Avl nodo;
	char* prod;
	if(a){
		nodo = getAvlLeft(a);
		findProd2(nodo,heap);
		x = (INFO_PRODUCT)getInfo(a);
		r=quant(x);
		freeNodo(nodo);
		nodo=NULL;
		prod=getAvlCode(a);
		insertHeap(heap,r,0,prod);
		free(prod);
		nodo=getAvlRight(a);
		findProd2(nodo,heap);
		freeNodo(nodo);
	}
	return heap;
}

static Heap findProd(INFO_CLIENT ic, int month,Heap heap){
	int i;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getInfoMesProduct(getInfoMes(ic,month-1),i);
		if(nodo)
			findProd2(nodo,heap);
	}
	freeNodo(nodo);
	return heap;
}

/*#################################QUERIE 10#####################################*/
static int converteTransfer(Heap heap,LISTA_STRINGS group,int total,int** dados){
	int a=0,limite=getHeapUsed(heap);
	double quant;
	int resg;
	while(0<total && 0<limite){
			addListaStrings(group,getListaSp(group),extractMaxQuantity(heap,&quant,&resg));
			dados[1][a]=(int)quant;
			dados[0][a]=resg;
			group=reallocListaStrings(group);
			total--;
			limite--;
			a++;
	}
	return 1 ;
}

static int qua (CENA info,int* registo){
	int i,sum=0;
	*registo=getResg(info);
	return getCenaQuant(info);
}

static int pesq (Avl a, Heap hp){
	int r,ww; 
	void* x;
	char* aux;

	if(a){
		pesq(getAvlLeft(a),hp);
		x = (CENA)getInfo(a);
		if(x){
			aux=getAvlCode(a);
			r=qua(x,&ww);
			insertHeap(hp,r,ww,aux);
			free(aux);
		}
		pesq(getAvlRight(a),hp);
	}
	return 1;
}



static LISTA_STRINGS  querie10Fact (FILIAL f,Heap hp,int N,int** dados){
	int i;
	LISTA_STRINGS gp;
	for(i=0;i<SIZE_ABC;i++){
		pesq(getProd10(f,i),hp);
	}
	gp = initListaStrings(1,SIZE_PRODUCT);
	converteTransfer(hp,gp,N,dados);
	return gp;
}

LISTA_STRINGS querie10(FILIAL f,FACTURACAO fact, int N,int filial,int** dados){
	LISTA_STRINGS ls;
	Heap hp=initHeap(1);
	ls=querie10Fact(f,hp,N,dados);
	return ls;
}

/*#################################QUERIE 11#####################################*/

static double quant2(INFO_PRODUCT ip){
	return (getInfoProductPrice(ip,0)+getInfoProductPrice(ip,1));
}

static Heap highCost2 (Avl a,Heap hp){
	double r;
	void* x;
	char* copy;
	Avl nodo;
	if(a){
		nodo =getAvlLeft(a);
		highCost2(nodo,hp);
		x= (INFO_PRODUCT)getInfo(a);
		r=quant2(x);
		copy=getAvlCode(a);
		insertHeap(hp,r,0,copy);
		free(copy);
		
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
		nodo=getAvlRight(a);
		highCost2(nodo,hp);
		if(nodo)freeNodo(nodo);
	}
	return hp;
}

static Heap highCost (INFO_CLIENT ic,Heap hp){
	int i,j;
	Avl nodo;
	for(i=0;i<SIZE_MONTH;i++){
		for(j=0;j<SIZE_ABC;j++){
			nodo=getInfoMesProduct(getInfoMes(ic,i),j);
			if(nodo){	
				highCost2(nodo,hp);
				freeNodo(nodo);
				nodo=NULL;
			}
		}
	}
	return hp;
}

LISTA_STRINGS querie11(FILIAL* f,char* client){
	int i;
	LISTA_STRINGS gp;
	int in = index(client[0]);
	Heap hp=initHeap(1);
	Avl nodo;
	for(i=0;i<SIZE_FILIAIS;i++){
		nodo=getClientIndexF(f[i],in);
		void* x=findInfo(nodo,client,NULL);
		highCost(x,hp);
		if(nodo){
			freeNodo(nodo);
			nodo=NULL;
		}
	}
	gp = initListaStrings(1,SIZE_PRODUCT);
	
	converte(hp,gp,3);
	return gp;
}

/*#################################QUERIE 12#####################################*/

static int querie12Clients(FILIAL* f){
	int i,j,sum=0,r;
	Avl nodo;
	for(i=0;i<SIZE_FILIAIS;i++)
		for(j=0;j<SIZE_ABC;j++){
			nodo=getClientIndexF(f[i],j);
			r=infoNULL(nodo);
			sum+=r;
			free(nodo);
			nodo=NULL;
		}
	return sum;
}

static int querie12Products(FACTURACAO f){
	int i,sum=0,r;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getProductIndex(f,i);
		r=infoNULL(nodo);			
		sum+=r;
		free(nodo);
		nodo=NULL;
	}
	return sum;
}

int querie12(FILIAL* f, FACTURACAO fact, int* sumClient){
	int sumProduct;
	*sumClient=querie12Clients(f);
	sumProduct=querie12Products(fact);
	return sumProduct;
}
