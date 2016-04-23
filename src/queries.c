#include "headers/queries.h"

/* Funções privadas ao módulo. */
static LISTA_STRINGS travessia (Avl a,LISTA_STRINGS ls);
static LISTA_STRINGS converte(Heap heap, LISTA_STRINGS group,int total);
static int converteTransfer(Heap heap,LISTA_STRINGS group,int total,int** dados);
static int querie12Clients(FILIAL* f);

/* ######################################### QUERIE 2 #################################### */

LISTA_STRINGS querie2(CATALOG_PRODUCTS Catalog,char letter){
	
	int index = letter - 'A';
	LISTA_STRINGS group = initListaStrings(totalElements(getP(Catalog,index)),SIZE_PRODUCT);
	MY_AVL a = getP(Catalog,index);
	Avl tree = getAvl(a);
	travessia(tree,group);
	return group;
}

/*Função faz uma travessia in-order as AVL's, do catalogo de produtos, contruindo uma LISTA_STRINGS ordenada. */
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

/* ######################################### QUERIE 3 #################################### */


DADOS querie3(FACTURACAO f,int mes, char* product,int promo){
	DADOS d = initDADOS();
	d = updatePriceQuantity(f,d,promo,mes,product);
	return d;
}

/* ######################################### QUERIE 4 #################################### */

LISTA_STRINGS querie4(FACTURACAO f,int filial){
	LISTA_STRINGS group = initListaStrings(1,SIZE_PRODUCT);
	group = listaProducts(f,group,filial);
	return group;
}
	

/* ######################################### QUERIE 5 #################################### */

DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df, char* client){
	
	valoresFilial(f,df,client);
	return df;
}

/* ######################################### QUERIE 6 #################################### */

DADOS querie6(FACTURACAO f, int inicio, int fim){
	DADOS d= initDADOS();
	d=totalM(f,d, inicio, fim);
	return d;
}

/* ######################################### QUERIE 7 #################################### */

LISTA_STRINGS querie7 (FILIAL* f){
	int i;

	LISTA_STRINGS ls1=initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS ls2=initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS ls3=initListaStrings(1,SIZE_CLIENT);
	
	for(i=0;i<SIZE_FILIAIS;i++){
		switch(i){
				case 0: ls1=checkClientsValeN(f[0],ls1);
						break;
				case 1: ls2=checkClientsValeN(f[1],ls2);
						break;
				case 2: ls3=checkClientsValeN(f[2],ls3);
						break;
			}
		}	

	LISTA_STRINGS aux1,aux2;
	aux1=mergeList(ls1,ls2);
	freeListaStr(ls1);
	freeListaStr(ls2);	
	aux2=mergeList(aux1,ls3);
	freeListaStr(aux1);
	freeListaStr(ls3);
	return aux2;
}

/* ######################################### QUERIE 8 #################################### */

LISTA_STRINGS querie8(FILIAL f,char* product,LISTA_STRINGS* P){
	LISTA_STRINGS gcN = initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS gcP = initListaStrings(1,SIZE_CLIENT);
	gcN=productNeP(f,product,gcN,gcP);
	(*P)=gcP;
	return gcN;
}

/* ######################################### QUERIE 9 #################################### */


LISTA_STRINGS querie9(FILIAL* f, char* client,int month){
	int i;
	LISTA_STRINGS group;
	Heap heap=initHeap(1);
	for(i=0;i<SIZE_FILIAIS;i++){
		moreBuy(f[i],heap,client,month);
	}
	group = initListaStrings(1,SIZE_PRODUCT);
	converte(heap,group,getHeapUsed(heap));
	return group;
}

/*Função que converte uma Heap em uma LISTA_STRINGS ordenanda pelo valor facturado com o produto. */
static LISTA_STRINGS converte(Heap heap, LISTA_STRINGS group,int total){
	while(0<total){
		addListaStrings(group,getListaSp(group),extractMax(heap));
		group=reallocListaStrings(group);
		total--;
	}
	return group;
}

/* ######################################### QUERIE 10 #################################### */

LISTA_STRINGS querie10(FILIAL f, int N,int** dados){
	LISTA_STRINGS gp;
	Heap hp=initHeap(1);
	hp=querie10Fil(f,hp);
	gp = initListaStrings(1,SIZE_PRODUCT);
	converteTransfer(hp,gp,N,dados);
	return gp;
}

/*Função que converte uma Heap em uma LISTA_STRINGS, no entanto, também preenche uma matriz de dados, ou seja, para cada 
produto que provém da heap, é passado para a matriz os valores (Quantidade e Nº Clientes) respondentes.*/
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

/* ######################################### QUERIE 10 #################################### */

LISTA_STRINGS querie11(FILIAL* f,char* client){
	int i;
	LISTA_STRINGS gp;
	Heap hp=initHeap(1);
	for(i=0;i<SIZE_FILIAIS;i++){
		highCostProd(f[i],hp,client);
	}
	gp = initListaStrings(1,SIZE_PRODUCT);
	converte(hp,gp,3);
	return gp;
}

/* ######################################### QUERIE 12 #################################### */

int querie12(FILIAL* f, FACTURACAO fact, int* sumClient){
	int sumProduct;
	*sumClient=querie12Clients(f);
	sumProduct=querie12Products(fact);
	return sumProduct;
}

/*Função que cria 3 LISTA_STRINGS, uma para cada filial, controi listas com os clients que nunca compraram em cada filial, e no fim, 
faz a junção das listas, removendo os clients iguais.*/
static int querie12Clients(FILIAL* f){
	int i,sum=0;

	LISTA_STRINGS ls1=initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS ls2=initListaStrings(1,SIZE_CLIENT);
	LISTA_STRINGS ls3=initListaStrings(1,SIZE_CLIENT);

	for(i=0;i<SIZE_FILIAIS;i++){
			
			switch(i){
				case 0: dontBuyClient(f[0],ls1);
						break;
				case 1: dontBuyClient(f[1],ls2);
						break;
				case 2: dontBuyClient(f[2],ls3);
						break;
			}
		}	
	LISTA_STRINGS aux1,aux2;
	aux1=mergeList(ls1,ls2);
	freeListaStr(ls1);
	freeListaStr(ls2);	
	aux2=mergeList(aux1,ls3);
	freeListaStr(aux1);
	freeListaStr(ls3);
	sum=getListaSp(aux2);
	freeListaStr(aux2);
	return sum;
}
