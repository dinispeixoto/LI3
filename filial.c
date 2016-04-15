#include "filial.h"

struct filial{
	MY_AVL Clients[26];
};

struct infoMes{
	MY_AVL Products[26];
	int quantity;
};

struct infoClient{
	INFO_MES im[12];
	int Comprou;                           /* soma dos avl->size das 26 letras; dá o total de produtos comprados num ano */
};

struct infoProduct{
	int quantity[2];
	double price[2];
};

struct dadosFilial{
	int quant[3][12];
	MY_AVL clients[26];
};


FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c){
	int i,j;	
	for(j=0;j<26;j++)
		f->Clients[j] = cloneMyAvl(getC(c,j));
	return f;
}

FILIAL initFilial(){
	int i;
	FILIAL filial = malloc(sizeof(struct filial));
	for(i=0;i<26;i++)
		filial->Clients[i] = initMyAvl();
	return filial;
}

INFO_MES initInfoMes(){
	int i;
	INFO_MES im = malloc(sizeof(struct infoMes));
	for(i=0;i<26;i++){
		im->Products[i]=initMyAvl();
	}
	im->quantity=0;
	return im;
}

INFO_CLIENT initInfoClient(){
	int i,j,k;
	INFO_CLIENT info = malloc(sizeof(struct infoClient));
	
	for(i=0;i<12;i++)
		info->im[i] = initInfoMes();
	info->Comprou=0;
	return info;
}

INFO_PRODUCT initInfoProduct(){
	int i;
	INFO_PRODUCT info = malloc(sizeof(struct infoProduct));
	for(i=0;i<2;i++){
	info->quantity[i] = 0;
	info->price[i] = 0;
}
	return info;
}

DADOS_FILIAL initDadosFilial(){
	int i,j;
	DADOS_FILIAL df = malloc(sizeof(struct dadosFilial));
	for(i=0;i<3;i++)
		for(j=0;j<12;j++)
			df->quant[i][j]=0;

	for(i=0;i<26;i++) df->clients[i]=initMyAvl();	
	return df;
}

FILIAL insertFilial(FILIAL f,SALES s){
	
	CLIENT client = getSalesClient(s);

	int index_client = getClient(client)[0]-'A';

	INFO_CLIENT infoC = (INFO_CLIENT) findInfo(getAvl(f->Clients[index_client]),getClient(client),NULL);

	if(!infoC){
		infoC = initInfoClient();
		infoC = updateInfoC(infoC,s);
		f->Clients[index_client] = insertMyAvl(f->Clients[index_client],getClient(client),infoC,1);
	}
	else infoC = updateInfoC(infoC,s);

	infoC->Comprou=1;
	return f;

}

INFO_CLIENT updateInfoC(INFO_CLIENT infoC, SALES s){

	PRODUCT product = getSalesProduct(s);
	MONTH month = getSalesMonth(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	char* prod=getProduct(product);
	int index_product = prod[0]-'A';
	int aux=0;

	int info_int;
	if(infoPromo == 'P') info_int = 1;
	else info_int = 0; 

 	MY_AVL a = infoC->im[month-1]->Products[index_product];

 	INFO_PRODUCT infoP = (INFO_PRODUCT) findInfo(getAvl(a),prod,&aux);

 	if(!infoP) {
 		infoP = initInfoProduct(); /* TESTAR A FAZER UPDATE E INIT AO MESMO TEMPO A VER SE É MAIS RPD */
		infoP = updateInfoP(infoP,s);
		a = insertMyAvl(a,getProduct(product),infoP,aux);
	}
	else infoP = updateInfoP(infoP,s);

	infoC->im[month-1]->quantity+=getSalesQuantity(s);

 	return infoC;
}

INFO_PRODUCT updateInfoP(INFO_PRODUCT info, SALES s){

	PRICE price = getSalesPrice(s);
	QUANTITY qt = getSalesQuantity(s);
	INFO_PROMO infoPromo = getSalesInfoPromo(s);
	int info_int,i;

	if(infoPromo == 'P') info_int = 1;
	else info_int = 0; 

	for(i=0;i<2;i++){
	info->quantity[info_int] += qt;
	info->price[info_int] += price*qt;
	}
	return info;
}

/*GET E SET*/
int getDadosI(DADOS_FILIAL df,int i,int j){
	return df->quant[i][j];
}

int getComp( INFO_CLIENT x){
	return x->Comprou;
}

MY_AVL getClientIndexF(FILIAL f,int index){
	return f->Clients[index];
}

DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL df,int filial,int month,int total){
	df->quant[filial][month] += total;
	return df;
}

INFO_MES getInfoMes(INFO_CLIENT info,int month){
	return info->im[month];
}

int getInfoMesQuantity(INFO_MES info){
	return info->quantity;
}

/*####################Acede a strcut mais funda ##############################
int c(INFO_PRODUCT ip){
	return (ip->quantity[0]+ip->quantity[1]);
}


int cen(INFO_CLIENT ic){
	void* x = (INFO_CLIENT)findInfo(getAvl(ic->im[0]->Products[4]),"EG1226",NULL);
	return c(x);
}


int getCenas(FILIAL f){
	void* x = (INFO_CLIENT)findInfo(getAvl(f->Clients[0]),getAvlCode(getAvl(f->Clients[0])),NULL);
	int y=cen(x);
	return y;
}
*/
/*#################################QUERIE 5##################################### FUNCIONA

DADOS_FILIAL addQ (DADOS_FILIAL df,INFO_CLIENT ic,int filial){
	int i;
	for(i=0;i<12;i++){
		df->quant[filial][i]+=ic->im[i]->quantity;
	}
	return df;
}


DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df,char* client,int filial){
	int i,j;
	int index = client[0]-'A';
	void* x = (INFO_CLIENT)findInfo(getAvl(f->Clients[index]),client,NULL);

	df=addQ(df,x,filial);
	
	return df;
}
*/
/*#################################QUERIE 7###################################### FUNCIONA(VERIFICAR REMOVE)*/
static GROUP_CLIENTS removeList(Avl a,GROUP_CLIENTS list );
static GROUP_CLIENTS insereList(Avl a,GROUP_CLIENTS list );
static GROUP_CLIENTS checkClientsValeN (FILIAL* f,GROUP_CLIENTS list);

GROUP_CLIENTS removeList(Avl a,GROUP_CLIENTS list ){
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

GROUP_CLIENTS insereList(Avl a,GROUP_CLIENTS list ){
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

GROUP_CLIENTS checkClientsValeN (FILIAL* f,GROUP_CLIENTS list){
	int i,j;

	for(j=0;j<26;j++){
		setJC(list,j+1);
		insereList(getAvl(f[0]->Clients[j]),list);
		}
	
	for(i=1;i<3;i++){
		for(j=0;j<26;j++){
			setJC(list,j+1);
			removeList(getAvl(f[i]->Clients[j]),list);
			}
		}
	
	return list;
}

GROUP_CLIENTS querie7 (FILIAL* f){
	int i;
	GROUP_CLIENTS list = initGroupClients(1);

	checkClientsValeN(f,list);

	return list;
}

/*#################################QUERIE 8#####################################*/
GROUP_CLIENTS checkProd(INFO_PRODUCT ip,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP,char* client){
	int i,posicao;

	if(ip->quantity[0]){
		posicao=getGroupClieSp(gcN);
		insertGROUP(getGroupClie(gcN),posicao,client);
		setGroupClieSp(gcN,posicao+1);
		gcN=reallocGROUP_CLIENTS(gcN);
	}
	if(ip->quantity[1]){
		posicao=getGroupClieSp(gcP);
		insertGROUP(getGroupClie(gcP),posicao,client);
		setGroupClieSp(gcP,posicao+1);
		gcP=reallocGROUP_CLIENTS(gcP);
	}
	return gcN;
}

GROUP_CLIENTS find2 (INFO_CLIENT ic,char* product,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP,char* client){
	int i;
	int index=product[0]-'A';

	for(i=0;i<12;i++){
		if(getAvl(ic->im[i]->Products[index])){
			void* x=(INFO_PRODUCT)findInfo(getAvl(ic->im[i]->Products[index]),product,NULL);
			if(x) checkProd(x,gcN,gcP,client);
		}
	}
	return gcN;
}

GROUP_CLIENTS find (Avl a, char* product,GROUP_CLIENTS gcN,GROUP_CLIENTS gcP){
	
	if(a){
		find(getAvlLeft(a),product,gcN,gcP);
		void* x=(INFO_CLIENT)getInfo(a);
		find2(x,product,gcN,gcP,getAvlCode(a));
		find(getAvlRight(a),product,gcN,gcP);
	}
	return gcN;
}


GROUP_CLIENTS querie8(FILIAL f,char* product,GROUP_CLIENTS* P){
	int i;
	GROUP_CLIENTS gcN=initGroupClients(1);
	GROUP_CLIENTS gcP=initGroupClients(1);
	for(i=0;i<26;i++){
		find(getAvl(f->Clients[i]),product,gcN,gcP);
	}
	(*P)=gcP;
	return gcN;
}

/*#################################QUERIE 9#####################################*/

/*#################################QUERIE 10#####################################*/

/*#################################QUERIE 11#####################################*/

/*#################################QUERIE 12#####################################*/



