#include "headers/queries.h"

#define index(i) i-'A'

static DADOS updatePriceQuantity(INFO f,DADOS d,int promo,int mes);
static int checkInfo(INFO i, int filial);
static GROUP_PRODUCTS found(Avl a,GROUP_PRODUCTS list,int* x,int filial);
static DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial);

/* ######################################### QUERIE 2 #################################### */

GROUP_PRODUCTS querie2(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	GROUP_PRODUCTS group = initGroupProducts(totalElements(getP(Catalog,index)));
	MY_AVL a = getP(Catalog,index);
	Avl tree = getAvl(a);
	travessia(tree,0,group);
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

GROUP_PRODUCTS querie4(FACTURACAO f,int* c,int filial){
	GROUP_PRODUCTS group = initGroupProducts(1);
	int i,j;
		
	for(i=0;i<26;i++){
		setJ(group,i+1);
		group = found(getAvl(getProductIndex(f,i)),group,c,filial);
	}
	return group;
}

static int checkInfo(INFO i, int filial){
	int j;
	for(j=0;j<12;j++)
		if(getTotalQuantPQ(getNormalPQ(i,j,filial))>0 || (getTotalQuantPQ(getPromoPQ(i,j,filial)))>0) return 1;
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
static GROUP_CLIENTS removeList(Avl a,GROUP_CLIENTS list );
static GROUP_CLIENTS insereList(Avl a,GROUP_CLIENTS list );
static GROUP_CLIENTS checkClientsValeN (FILIAL* f,GROUP_CLIENTS list);

GROUP_CLIENTS querie7 (FILIAL* f){
	int i;
	GROUP_CLIENTS list = initGroupClients(1);
	checkClientsValeN(f,list);
	return list;
}

static GROUP_CLIENTS removeList(Avl a,GROUP_CLIENTS list ){
	int sp;
	if(a){
		removeList(getAvlLeft(a),list);
		void* x = (INFO_CLIENT)findInfo(a,getAvlCode(a),NULL);
		if(!getComp(x)){
			sp=getGroupClieSp(list);
			removeGROUP_CLIENTS(getGroupClie(list),&sp,getAvlCode(a));
			setGroupClieSp(list,sp);
		}
		removeList(getAvlRight(a),list);
	}
	return list;
}

static GROUP_CLIENTS insereList(Avl a,GROUP_CLIENTS list ){
	int sp;
	if(a){
		insereList(getAvlLeft(a),list);
		void* x = (INFO_CLIENT)findInfo(a,getAvlCode(a),NULL);
		if(getComp(x)){
			sp=getGroupClieSp(list);
			insertGROUP_CLIENTS(getGroupClie(list),&sp,getJC(list),getAvlCode(a));
			setGroupClieSp(list,sp);
			list=reallocGROUP_CLIENTS(list);
		}
		insereList(getAvlRight(a),list);
	}
	return list;
}

static GROUP_CLIENTS checkClientsValeN (FILIAL* f,GROUP_CLIENTS list){
	int i,j;

	for(j=0;j<26;j++){
		setJC(list,j+1);
		insereList(getAvl(getClientIndexF(f[0],j)),list);
		}

	for(i=1;i<3;i++){
		for(j=0;j<26;j++){
			setJC(list,j+1);
			removeList(getAvl(getClientIndexF(f[i],j)),list);
			}
		}
	
	return list;
}

/*#################################QUERIE 8#####################################*/
static GROUP_CLIENTS checkProd(INFO_PRODUCT,GROUP_CLIENTS,GROUP_CLIENTS,char*);
static GROUP_CLIENTS find2(INFO_CLIENT,char*,GROUP_CLIENTS,GROUP_CLIENTS,char*);
static GROUP_CLIENTS find(Avl,char*,GROUP_CLIENTS,GROUP_CLIENTS);

GROUP_CLIENTS querie8(FILIAL f,char* product,GROUP_CLIENTS* P){
	int i;
	GROUP_CLIENTS gcN=initGroupClients(1);
	GROUP_CLIENTS gcP=initGroupClients(1);
	for(i=0;i<26;i++){
		find(getAvl(getClientIndexF(f,i)),product,gcN,gcP);
	}
	(*P)=gcP;
	return gcN;
}

static GROUP_CLIENTS checkProd(INFO_PRODUCT ip,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP,char* client){
	int i,posicao;

	if(getInfoProductQuantity(ip,0)){
		posicao=getGroupClieSp(gcN);
		insertGROUP(getGroupClie(gcN),posicao,client);
		setGroupClieSp(gcN,posicao+1);
		gcN=reallocGROUP_CLIENTS(gcN);
	}
	if(getInfoProductQuantity(ip,1)){
		posicao=getGroupClieSp(gcP);
		insertGROUP(getGroupClie(gcP),posicao,client);
		setGroupClieSp(gcP,posicao+1);
		gcP=reallocGROUP_CLIENTS(gcP);
	}
	return gcN;
}

static GROUP_CLIENTS find2(INFO_CLIENT ic,char* product,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP,char* client){
	int i;
	int index=product[0]-'A';

	for(i=0;i<12;i++){
		if(getAvl(getInfoMesProduct(getInfoMes(ic,i),index))){
			void* x=(INFO_PRODUCT)findInfo(getAvl(getInfoMesProduct(getInfoMes(ic,i),index)),product,NULL);
			if(x) checkProd(x,gcN,gcP,client);
		}
	}
	return gcN;
}

static GROUP_CLIENTS find(Avl a, char* product,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP){
	
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
static GROUP_PRODUCTS converte(Heap,GROUP_PRODUCTS);
static Heap findProd2(Avl,Heap);
static Heap findProd(INFO_CLIENT,int,Heap);

GROUP_PRODUCTS querie9(FILIAL* f, char* client,int month){
	int i;
	Heap heap=initHeap(1);
	int index=index(client[0]);
	for(i=0;i<3;i++){
		void* x=(INFO_CLIENT)findInfo(getAvl(getClientIndexF(f[i],index)),client,NULL);
		findProd(x,month,heap);
	}

	GROUP_PRODUCTS group= initGroupProducts(1);
	
	converte(heap,group);
	return group;
}

static int quant(INFO_PRODUCT ip){
	return (getInfoProductQuantity(ip,0)+getInfoProductQuantity(ip,1));
}

static GROUP_PRODUCTS converte (Heap heap, GROUP_PRODUCTS group){
	int i,posicao;
	while(0<getHeapUsed(heap)){
		posicao=getGroupProdSp(group);
		insertGROUP_P(getGroupProd(group),posicao,extractMax(heap));
		setGroupProdSp(group,posicao+1);
		group=reallocGROUP_PRODUCTS(group);
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
		findProd2(getAvl(getInfoMesProduct(getInfoMes(ic,month-1),i)),heap);
	}
	return heap;
}

/*#################################QUERIE 12#####################################*/

int querie12Clients(FILIAL* f){
	int i,j,sum=0,r;
	for(i=0;i<3;i++)
		for(j=0;j<26;j++){
			r=infoNULL(getAvl(getClientIndexF(f[i],j)));
			sum+=r;
		}
	return sum;
}

int querie12Products(FACTURACAO f){
	int i,sum=0,r;

	for(i=0;i<26;i++){
		r=infoNULL(getAvl(getProductIndex(f,i)));			
		sum+=r;
	}
	return sum;
}

