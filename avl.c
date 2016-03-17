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
    else return a->height;
}

Avl actualizarAltura(Avl a, Avl b){

    a->height = maior(altura(a->left), altura(a->right))+1;
    b->height = maior(altura(b->left), altura(b->right))+1;

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
        if(strcmp(estrutura->code,line) >= 0)
            estrutura->left=insert(estrutura->left,line);
        else 
            estrutura->right=insert(estrutura->right,line);
        }
    
    HL=altura(estrutura->left);
    HR=altura(estrutura->right);

    estrutura->height = maior(HL,HR)+1;
    
    bal = HL - HR;

    
    //OPCAO 1
    if(bal>1) bal=2;
    if(bal<-1) bal=-2;
    
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
   
    /*

    //OPCAO 2
    // Rotacao Simples a esquerda
    if (bal > 1 && (ls=strcmp(line,estrutura->left->code)) < 0)
        return rotateRight(estrutura);
    
    // Rotacao dulpa (diretia->esquerda)
    else {if(bal > 1 && ls>0){
            estrutura->left =  rotateLeft(estrutura->left);
            return rotateRight(estrutura);
            }
          }  
 
    // Rotacao Simples a direita
    if (bal < -1 && (rs=strcmp(line,estrutura->right->code)) > 0)
        return rotateLeft(estrutura);

    // Rotacao dupla (esquerda->direita)
    else {if(bal < -1 && rs<0){
            estrutura->right = rotateRight(estrutura->right);
            return rotateLeft(estrutura);
            }
         }
    */

    // duas opcoes de implementar aquilo em cima... escolhe o que achares mais bonito, bem programado, 
    // e assim, e tb ve os tempos de execucao de cada um.. acho que o switch demora mais... ou vai dar ao mesmo...

    return estrutura;
}







