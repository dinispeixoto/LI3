#include "headers/queries.h"


#define index(i) i-'A'

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes);
static int checkInfo(INFO i, int filial);
static LISTA_STRINGS found(Avl a,LISTA_STRINGS list,int filial);
static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic);

/* ######################################### QUERIE 2 #################################### */
static LISTA_STRINGS travessia (Avl a,LISTA_STRINGS ls){
	char* prod;
	if(a){
		travessia(getAvlLeft(a),ls);
		prod=getAvlCode(a);
		addListaStrings(ls,getListaSp(ls),prod);
		ls=reallocListaStrings(ls);
		travessia(getAvlRight(a),ls);
		free(prod);
		freeNodo(a);
	}
	return ls;
}


LISTA_STRINGS querie2(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	LISTA_STRINGS group = initListaStrings(totalElements(getP(Catalog,index)),SIZE_PRODUCT);
	MY_AVL a = getP(Catalog,index);
	Avl tree = getAvl(a);
	travessia(tree,group);
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
	if(nodo)freeNodo(nodo);
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
	
	for(i=0;i<SIZE_ABC;i++){
		group = found(getProductIndex(f,i),group,filial);
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
	char* prod;
	if(a){
		w = (INFO)getInfo(a);	
		list=found(getAvlLeft(a),list,filial);
		if(w == NULL || (filial!=-1 && !checkInfo(w,filial))){
			prod=getAvlCode(a);
			addListaStrings(list,getListaSp(list),prod);
			list=reallocListaStrings(list);
			free(prod);
		}
		list=found(getAvlRight(a),list,filial);

		freeNodo(a);
	}
	
	return list;
}

/*#################################QUERIE 5##################################### FUNCIONA*/

DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df,char* client){
	void* x;
	int index = client[0]-'A';
	Avl nodo=getClientIndexF(f,index);
	x = (INFO_CLIENT)findInfo(nodo,client,NULL);

	df=addQ(df,x);
	freeNodo(nodo);
	return df;
}

static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic){
	int i;
	for(i=0;i<SIZE_MONTH;i++)
		df = updateQuant_DadosFilial(df,i,getInfoMesQuantity(getInfoMes(ic,i)));
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
	if(a){
		removeList(getAvlLeft(a),list);
		client=getAvlCode(a);
		x = (INFO_CLIENT)findInfo(a,client,NULL);
		if(!getComp(x)){
			removeListaStrings(list,client);
		}
		removeList(getAvlRight(a),list);
		free(client);
		freeNodo(a);
	}
	return list;
}

static LISTA_STRINGS insereList(Avl a,LISTA_STRINGS list){
	void* x;
	char* client;
	if(a){
		insereList(getAvlLeft(a),list);
		client=getAvlCode(a);
		x = (INFO_CLIENT)findInfo(a,client,NULL);
		if(getComp(x)){
			addListaStrings(list,getListaSp(list),client);
			list=reallocListaStrings(list);
		}
		insereList(getAvlRight(a),list);
		free(client);
		freeNodo(a);
	}
	return list;
}

static LISTA_STRINGS checkClientsValeN (FILIAL* f,LISTA_STRINGS list){
	int i,j;
	for(j=0;j<SIZE_ABC;j++){
		insereList(getClientIndexF(f[0],j),list);
		}

	for(i=1;i<SIZE_FILIAIS;i++){
		for(j=0;j<SIZE_ABC;j++){
			removeList(getClientIndexF(f[i],j),list);
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
	for(i=0;i<SIZE_ABC;i++){
		find(getClientIndexF(f,i),product,gcN,gcP);
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
	Avl nodo;
	for(i=0;i<SIZE_MONTH;i++){
		nodo=getInfoMesProduct(getInfoMes(ic,i),index);
		if(getInfoMesProduct(getInfoMes(ic,i),index)){
				void* x=(INFO_PRODUCT)findInfo(getInfoMesProduct(getInfoMes(ic,i),index),product,NULL);
				if(x) checkProd(x,gcN,gcP,client);
				freeNodo(nodo);
		}
	}	
	return gcN;
}

static LISTA_STRINGS find(Avl a, char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP){
	void* x;
	char* prod;
	if(a){
		find(getAvlLeft(a),product,gcN,gcP);
		x = (INFO_CLIENT)getInfo(a);
		prod=getAvlCode(a);
		find2(x,product,gcN,gcP,prod);
		find(getAvlRight(a),product,gcN,gcP);
		free(prod);
		freeNodo(a);
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
		freeNodo(nodo);
	}
	group = initListaStrings(1,SIZE_PRODUCT);
	converte(heap,group,getHeapUsed(heap));
	return group;
}

static int quant(INFO_PRODUCT ip){
	return (getInfoProductQuantity(ip,0)+getInfoProductQuantity(ip,1));
}

static LISTA_STRINGS converte (Heap heap, LISTA_STRINGS group,int total){
	char* prod;
	while(0<total){
		prod=extractMax(heap);
		addListaStrings(group,getListaSp(group),prod);
		group=reallocListaStrings(group);
		total--;
		free(prod);
	}
	return group;
}


static Heap findProd2(Avl a,Heap heap){
	int r; 
	void* x;
	char* prod;
	if(a){
		findProd2(getAvlLeft(a),heap);
		x = (INFO_PRODUCT)getInfo(a);
		r=quant(x);
		prod=getAvlCode(a);
		insertHeap(heap,r,0,prod);
		findProd2(getAvlRight(a),heap);
		free(prod);
		freeNodo(a);
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
	return heap;
}

/*#################################QUERIE 10#####################################*/
static int converteTransfer(Heap heap,LISTA_STRINGS group,int total,int** dados){
	int a=0,limite=getHeapUsed(heap);
	double quant;
	int resg;
	char* prod;
	while(0<total && 0<limite){
			prod=extractMaxQuantity(heap,&quant,&resg);
			addListaStrings(group,getListaSp(group),prod);
			dados[1][a]=(int)quant;
			dados[0][a]=resg;
			group=reallocListaStrings(group);
			total--;
			limite--;
			a++;
			free(prod);
	}
	return 1 ;
}

static int qua (PRODUCT_INFO info,int* registo){
	*registo=getResg(info);
	return getPiQuant(info);
}

static int pesq (Avl a, Heap hp){
	int r,resg; 
	void* x;
	char* aux;

	if(a){
	pesq(getAvlLeft(a),hp);
	x = (PRODUCT_INFO)getInfo(a);
	if(x){
		aux=getAvlCode(a);
		r=qua(x,&resg);
		insertHeap(hp,r,resg,aux);
		free(aux);
	}
	pesq(getAvlRight(a),hp);
	freeNodo(a);
	}
	return 1;
}

static LISTA_STRINGS querie10Fil(FILIAL f,Heap hp,int N,int** dados){
	int i;
	LISTA_STRINGS gp;

	for(i=0;i<SIZE_ABC;i++){
		pesq(getProdInfo(f,i),hp);
	}
	gp = initListaStrings(1,SIZE_PRODUCT);
	converteTransfer(hp,gp,N,dados);
	return gp;
}

LISTA_STRINGS querie10(FILIAL f, int N,int** dados){
	LISTA_STRINGS ls;
	Heap hp=initHeap(1);
	ls=querie10Fil(f,hp,N,dados);
	return ls;
}

/*#################################QUERIE 11#####################################*/

static double quant2(INFO_PRODUCT ip){
	return (getInfoProductPrice(ip,0)+getInfoProductPrice(ip,1));
}

static Heap highCost2 (Avl a,Heap hp){
	double r;
	void* x;
	char* prod;
	if(a){
		highCost2(getAvlLeft(a),hp);
		x= (INFO_PRODUCT)getInfo(a);
		r=quant2(x);
		prod=getAvlCode(a);
		insertHeap(hp,r,0,prod);
		free(prod);
		highCost2(getAvlRight(a),hp);
		freeNodo(a);
	}
	return hp;
}

static Heap highCost (INFO_CLIENT ic,Heap hp){
	int i,j;
	Avl nodo;
	for(i=0;i<SIZE_MONTH;i++){
		for(j=0;j<SIZE_ABC;j++){
			nodo=getInfoMesProduct(getInfoMes(ic,i),j);
			if(nodo)	
				highCost2(nodo,hp);
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
	char* string;
	for(i=0;i<SIZE_FILIAIS;i++){
		nodo=getClientIndexF(f[i],in);
		void* x=findInfo(nodo,client,NULL);
		highCost(x,hp);
		freeNodo(nodo);
	}
	string=getString(hp,0);
	gp = initListaStrings(1, (strlen(string)+1)*sizeof(char));
	free(string);
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
			if(nodo)freeNodo(nodo);
			sum+=r;
		}
	return sum;
}

static int querie12Products(FACTURACAO f){
	int i,sum=0,r;
	Avl nodo;
	for(i=0;i<SIZE_ABC;i++){
		nodo=getProductIndex(f,i);
		r=infoNULL(nodo);	
		if(nodo)freeNodo(nodo);		
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
