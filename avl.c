#include "avl.h"

#define SIZE_CODE 7
#define LEFT -2
#define RIGHT 2

struct avl {
	STRING code;
	int height;
	struct avl *left, *right;
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

/*static void insertArray (char** array,Avl estrutura,int *a){
	
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
*/

Avl initAvl(){
	return NULL;
}

int heightAvl(Avl a){

	if(a==NULL) return 0;
	else return a->height;
}

/* Inserir numa Avl */
Avl insert(Avl estrutura, char* line) {
	int ls,rs,bal,HL,HR;

	if(estrutura == NULL){
		estrutura= (Avl)malloc(sizeof(struct avl));
		estrutura->code = malloc(SIZE_CODE);
		strcpy((estrutura)->code,line);
		estrutura->left=NULL;
		estrutura->right=NULL;
		estrutura->height=0;
	}
	else {
		if(strcmp(estrutura->code,line) >= 0) estrutura->left=insert(estrutura->left,line);
		else estrutura->right=insert(estrutura->right,line);

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
	return estrutura;

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

