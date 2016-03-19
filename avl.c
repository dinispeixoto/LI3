#include "avl.h"
#include "valida.h"
#include "testes.h"

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

//Inserir numa Avl
Avl insert(Avl estrutura, char* line) {
	int ls,rs,bal,HL,HR;

	if(estrutura == NULL){
		estrutura= (Avl)malloc(sizeof(struct avl));
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

    
    	//OPCAO 1
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

		return estrutura;

	}

}







