#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "avl.h"
#include "valida.h"
#include "testes.h"

int maior (int a, int b){
    if(a>b)return a;
    else return b;
}

int altura (Avl a){

    if(a==NULL) return 0;
    else return (a->height);
}


Avl rightRotate(Avl a) {

    Avl x = a->left;
    Avl T2 = x->right;
 
    x->right = a;
    a->left = T2;
 
    a->height = maior(altura(a->left), altura(a->right))+1;
    x->height = maior(altura(x->left), altura(x->right))+1;
 
    return x;
}


Avl leftRotate(Avl a) {

    Avl x = a->right;
    Avl T2 = x->left;
 
    // Perform rotation
    x->left = a;
    a->right = T2;
 
    //  Update heights
    a->height = maior(altura(a->left), altura(a->right))+1;
    x->height = maior(altura(x->left), altura(x->right))+1;
 
    // Return new root
    return x;
}

int getBalance(Avl a){
   if(a==0)return 0;
   else return(altura(a->left)-altura(a->right));
}


//inserir numa Avl
Avl insert(Avl estrutura, char* line) {

     if(estrutura == NULL){
     	estrutura= (Avl)malloc(sizeof(struct avl));
        strcpy((estrutura)->code,line);
        estrutura->left=NULL;
        estrutura->right=NULL;
        estrutura->height=0;
     }
     else 
     {
     if(strcmp(estrutura->code,line) >= 0)
                estrutura->left=insert(estrutura->left,line);
            else estrutura->right=insert(estrutura->right,line);
    }

    /* Atualiza os pesos */
    estrutura->height = maior(altura(estrutura->left), altura(estrutura->right)) + 1;
 
    /* Varifica o balanceamento */
    int balance = getBalance(estrutura);
 
    // Caso esteja não balanceada, aplica o caso correspondente.
 
    // Left Left Case
    if (balance > 1 && strcmp(line,estrutura->left->code) < 0)
        return rightRotate(estrutura);
 
    // Right Right Case
    if (balance < -1 && strcmp(line,estrutura->right->code) > 0)
        return leftRotate(estrutura);
 
    // Left Right Case
    if (balance > 1 && strcmp(line,estrutura->left->code) > 0)
    {
        estrutura->left =  leftRotate(estrutura->left);
        return rightRotate(estrutura);
    }
     // Right Left Case
    if (balance < -1 && strcmp(line, estrutura->right->code) < 0)
    {
        estrutura->right = rightRotate(estrutura->right);
        return leftRotate(estrutura);
    }
 
    return estrutura;
}






