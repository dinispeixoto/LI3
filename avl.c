#include "avl.h"
#include <stdio.h>

#define SIZE_CODE 7
#define LEFT -2
#define RIGHT 2

struct avl {
	STRING code;
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

MY_AVL insertMyAvl(MY_AVL a,char* line,void* info){

	if(a == NULL) a = initMyAvl();
	(a->avl) = insert(a->avl,line,info);
	if(!info)(a->total)++;
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
	return estrutura->total;
}

void removeMyAvl(MY_AVL estrutura){
	removeAvl(estrutura->avl);
}

void removeAvl(Avl estrutura){
	if(estrutura != NULL){
		removeAvl(estrutura->right);
		removeAvl(estrutura->left);
		free(estrutura);
	}
}

void* gs (Avl a,STRING line){
	int cp=0;
	Avl aux=a;
	while(a){
		if((cp=strcmp(a->code,line)) > 0) a=a->left;
		else if(cp<0) a=a->right;
			else break;
	}
	if(a) return a->info;
	a=aux;
	return NULL;
}

Avl cloneAvl (Avl estrutura){
	Avl aux = malloc (sizeof(struct avl));
	aux->code = malloc(SIZE_CODE);
	if(estrutura){
		strcpy(aux->code,estrutura->code);
		aux->height=estrutura->height;
		aux->info=estrutura->info;
		aux->left=cloneAvl(estrutura->left);
		aux->right=cloneAvl(estrutura->right);
	}
	else aux=NULL;
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

void elimAux (Avl a){
	if(a){
		elimAux(a->left);
		elimAux(a->right);
		free(a);
	}
	else free (a);
}

void eliminar (MY_AVL* a, int x){
	int i;
	for(i=0;i<x;i++){
		elimAux(a[i]->avl);
	}
}


/* GETS E SETS */ 

Avl getAvl(MY_AVL estrutura){
	return estrutura->avl;
}

Avl getAvlLeft(Avl a){
	return a->left;
}

Avl getAvlRight(Avl a){
	return a->right;
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
	return a->code;
}

void setAv(Avl a, Avl b){
	a=b;
}

void setAvl(MY_AVL a, Avl b){
	a->avl=b;
}

/* ############################################################## APAGAR ##########################################################################

void printMyAvl(MY_AVL a){
	printAVL(a->avl);
}

void printAVL(Avl estrutura) {	
	if (!estrutura);
	else {
		printAVL(estrutura->left);
		printf("%s\n", estrutura->code);
		printAVL(estrutura->right);
	}
}

static void insertArray (char** array,Avl estrutura,int *a){
	
	if(estrutura->left==NULL && estrutura->right==NULL){
		array[*a]=estrutura->code;
		(*a)++;
	}

	else if(estrutura->left==NULL){ 
		insertArray(array,estrutura->right,a);
		array[*a]=estrutura->code;
		(*a)++;
	}

	else { 
		insertArray(array,estrutura->left,a);
		array[*a]=estrutura->code;
		(*a)++;
		if(estrutura->right!=NULL)insertArray(array,estrutura->right,a);
	}
}*/