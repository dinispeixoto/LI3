#include "headers/avl.h"

#define SIZE_CODE 7
#define LEFT -2
#define RIGHT 2

struct avl {
	STR code;
	int height;
	void* info;
	struct avl *left, *right;
};

struct myAvl {
	int total;
	Avl avl;
};


/* Estes prototypes não são para estar no .h porque são auxiliares */
static Avl rotateRight(Avl);
static Avl rotateLeft(Avl);
static int maior (int a, int b);
static Avl actualizarAltura(Avl,Avl);
static void removeFromMY_AVL_AUX(Avl);
static Avl insertINFO(Avl,STR,void*);
/*static void insertArray(char**,Avl,int*);*/


static int maior(int a, int b){
	if(a>b)return a;
	else return b;
}

static Avl actualizarAltura(Avl a, Avl b){
	a->height = maior(heightAvl(a->left), heightAvl(a->right))+1;
	b->height = maior(heightAvl(b->left), heightAvl(b->right))+1;
	return b;
}

static Avl rotateRight(Avl a) {
	Avl aux;
	aux = a->left;
	a->left=aux->right;
	aux->right=a;
	aux=actualizarAltura(a,aux);
	return aux;
}

static Avl rotateLeft(Avl a) {
	
	Avl aux;
	aux = a->right;
	a->right=aux->left;
	aux->left=a;
	aux=actualizarAltura(a,aux);
	return aux;
}

MY_AVL initMyAvl(){
	MY_AVL a = malloc(sizeof(struct myAvl));
	a-> avl = initAvl();
	a->total = 0;
	return a;
}

Avl initAvl(){
	return NULL;
}

int heightAvl(Avl a){	
	if(a==NULL) return 0;
	else return a->height;
}

/* Inserir numa Avl */
Avl insert(Avl estrutura, char* line,void* info) {
	
	int ls,rs,bal,HL,HR,cp;

	if(estrutura == NULL){
		estrutura= (Avl)malloc(sizeof(struct avl));
		estrutura->code = malloc(SIZE_CODE);
		strcpy((estrutura)->code,line);
		estrutura->left=NULL;
		estrutura->right=NULL;
		estrutura->height=0;
		estrutura->info=info;
	}
	else {
		if((cp=strcmp(estrutura->code,line)) > 0) estrutura->left=insert(estrutura->left,line,info);
		else if(cp<0)estrutura->right=insert(estrutura->right,line,info);
		else estrutura->info=info;
		

		if(cp){
		HL = heightAvl(estrutura->left);
		HR = heightAvl(estrutura->right);

		estrutura->height = maior(HL,HR)+1;

		bal = HL - HR;

		if(bal>1) bal=RIGHT;
		if(bal<-1) bal=LEFT;

		switch (bal){

			case 2: if((ls=strcmp(line,estrutura->left->code)) < 0)
						return rotateRight(estrutura);
					else if (ls>0){
						estrutura->left =  rotateLeft(estrutura->left);
						return rotateRight(estrutura);
					}
					break;

			case -2: if((rs=strcmp(line,estrutura->right->code)) > 0)
						return rotateLeft(estrutura);
					else if (rs<0){
						estrutura->right = rotateRight(estrutura->right);
						return rotateLeft(estrutura);
					}	
					break;
		}
	}

	}
	return estrutura;

}

MY_AVL insertMyAvl(MY_AVL a,char* line,void* info,int aux){

	if(a == NULL) a = initMyAvl();
	if(!info || aux)(a->avl) = insert(a->avl,line,info);
	else (a->avl)=insertINFO(a->avl,line,info);
	(a->total)++;
	return a;
}

static Avl insertINFO(Avl a,STR line,void* i){
	Avl aux=a;
	int cp;
	while(a){
		if((cp=strcmp(a->code,line)) > 0) a=a->left;
		else if(cp<0) a=a->right;
			else {a->info=i;break;}
	}

	a=aux;
	return a;
}

int existMyAvl(MY_AVL estrutura,char* line){
	int r = existAvl(estrutura->avl,line);
	return r;
}

int existAvl(Avl estrutura, char* line){
	int r=0;
	int s=strcmp(estrutura->code,line);
	if(s==0) return 1;
	else if(s>0 && estrutura->left!=NULL)
		r=existAvl(estrutura->left,line);
	else if (estrutura->right!=NULL)
		r=existAvl(estrutura->right,line);
	return r;
}

int totalElements(MY_AVL estrutura){
	if(estrutura) return estrutura->total;
	else return 0;
}

void removeMyAvl(MY_AVL estrutura,Func f){
	if(estrutura)
		removeAvl(estrutura->avl,f);
		free(estrutura);
}

void removeAvl(Avl estrutura,Func freeInfo){
	if(estrutura != NULL){
		removeAvl(estrutura->right,freeInfo);
		removeAvl(estrutura->left,freeInfo);
		free(estrutura->code);
		if(freeInfo!=NULL)
			freeInfo(estrutura->info);
		free(estrutura);
	}
}

void* findInfo (Avl a,STR line,int *x){
	int cp=0;
	while(a){
		if((cp=strcmp(a->code,line)) > 0) a=a->left;
		else if(cp<0) a=a->right;
		else break;
	}
	if(a) return a->info;
	else if(x){(*x)++;return NULL;}
		else return NULL;
}

Avl cloneAvl (Avl estrutura){
	Avl aux;
	if(estrutura){
		aux = malloc (sizeof(struct avl));
		aux->code = malloc(SIZE_CODE);
		strcpy(aux->code,estrutura->code);
		aux->height=estrutura->height;
		aux->info=estrutura->info;
		aux->left=cloneAvl(estrutura->left);
		aux->right=cloneAvl(estrutura->right);
	}
	else return NULL;

	return aux;
}

MY_AVL cloneMyAvl (MY_AVL estrutura){
	MY_AVL aux = malloc (sizeof(struct myAvl));
	if(estrutura){
		aux->avl=cloneAvl(estrutura->avl);
		aux->total=estrutura->total;
	}
	else aux=NULL;
	return aux;
}
/*
void removeFromMY_AVL (MY_AVL* a, int x){
	int i;
	for(i=0;i<x;i++){
		removeFromMY_AVL_AUX(a[i]->avl);
		free(a[i]);
	}
	free(a);
	a=NULL;
}

static void removeFromMY_AVL_AUX (Avl a){
	if(a){
		removeFromMY_AVL_AUX(a->left);
		removeFromMY_AVL_AUX(a->right);
		free(a->code);
		free(a);
	}
	else free (a);
	a=NULL;
}
*/

void freeNodo(Avl a){
	free(a->code);
	free(a);
}

int infoNULL(Avl a){
	int r=0;
	if(a){
		r+=infoNULL(a->left);
		r+=infoNULL(a->right);
		if(!a->info)r++;
	}
	return r;
}


/* GETS E SETS */ 

Avl getAvl(MY_AVL estrutura){
	Avl aux;
	if(estrutura->avl){
		aux = malloc (sizeof(struct avl));
		aux->code = malloc((strlen(estrutura->avl->code)+1)*sizeof(char));
		strcpy(aux->code,estrutura->avl->code);
		aux->height=estrutura->avl->height;
		aux->info=estrutura->avl->info;
		aux->left=estrutura->avl->left;
		aux->right=estrutura->avl->right;
	}
	else return NULL;
	return aux;
}

Avl getAvlLeft(Avl a){
	Avl aux;
	if(a->left){
		aux = malloc (sizeof(struct avl));
		aux->code = malloc((strlen(a->left->code)+1)*sizeof(char));
		strcpy(aux->code,a->left->code);
		aux->height=a->left->height;
		aux->info=a->left->info;
		aux->left=a->left->left;
		aux->right=a->left->right;
	}
	else return NULL;
	return aux;
}

Avl getAvlRight(Avl a){
	Avl aux;
	if(a->right){
		aux = malloc (sizeof(struct avl));
		aux->code = malloc((strlen(a->right->code)+1)*sizeof(char));
		strcpy(aux->code,a->right->code);
		aux->height=a->right->height;
		aux->info=a->right->info;
		aux->left=a->right->left;
		aux->right=a->right->right;
	}
	else return NULL;
	return aux;
}


int getSize(MY_AVL a){
	return a->total;
}

void* getInfo(Avl a){
	return a->info;
}

void setInfo(Avl a,void* i){
	a->info=i;
}

char* getAvlCode(Avl a){
	char* new = malloc((strlen(a->code)+1)*sizeof(char));
	strcpy(new,a->code);
	return new;
}

void setAvl(MY_AVL a, Avl b){
	a->avl=b;
}