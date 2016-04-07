#include "avl.h"


struct avl {
	char code[SIZE_CODE];
	int height;
	void *info;
	struct avl *left, *right;
};

int maior (int a, int b);
Avl actualizarAltura(Avl,Avl);
Avl rotateRight(Avl);
Avl rotateLeft(Avl);
void insertArray(char**,Avl,int*);

Avl initAvl(){
	return NULL;
}

int maior(int a, int b){
	if(a>b)return a;
	else return b;
}

int heightAvl(Avl a){

	if(a==NULL) return 0;
	else return a->height;
}

Avl actualizarAltura(Avl a, Avl b){

	a->height = maior(heightAvl(a->left), heightAvl(a->right))+1;
	b->height = maior(heightAvl(b->left), heightAvl(b->right))+1;

	return b;
}


Avl rotateRight(Avl a) {
	Avl aux;
    
	aux = a->left;
	a->left=aux->right;
	aux->right=a;

	aux=actualizarAltura(a,aux);
    
	return aux;
}


Avl rotateLeft(Avl a) {
	Avl aux;
    
	aux = a->right;
	a->right=aux->left;
	aux->left=a;

	aux=actualizarAltura(a,aux);
    
	return aux;
}


Avl insert(Avl estrutura, char* line, void *info) {
	int ls,rs,bal,HL,HR,cp;

	if(estrutura == NULL){
		estrutura= (Avl)malloc(sizeof(struct avl));
		strcpy((estrutura)->code,line);
		estrutura->left=NULL;
		estrutura->right=NULL;
		estrutura->height=0;
		estrutura->info=NULL;
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

void insertArray (char** array,Avl estrutura,int *a){
	
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
}

void printAVL(Avl estrutura) {

	if (!estrutura) printf("*\n");
	else {
		printAVL(estrutura->left);
		printf("%s\n", estrutura->code);
		printAVL(estrutura->right);
	}
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

int totalElements(Avl estrutura){

	int total = 0;
	if(estrutura!=NULL){
	total++;
	total+=totalElements(estrutura->right);
	total+=totalElements(estrutura->left);
}
	return total;
}

void removeAvl(Avl estrutura){

	if(estrutura != NULL){
		removeAvl(estrutura->right);
		removeAvl(estrutura->left);
		free(estrutura);
	}
}

Avl cloneAvl (Avl estrutura){
	Avl aux = malloc (sizeof(struct avl));
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

void* getInfo(Avl c){
	return c->info;
}

char* getCode(Avl c){
	return c->code;
}

