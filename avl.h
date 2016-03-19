#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE_BUFFER 64
#define SIZE_BUF_SALES 128

#define SIZE_CLIENTS 6 //CONTAR COM O /0
#define SIZE_PRODUCTS 7 // CONTAR COM O /0
#define SIZE_SALES 29 // 

#define LEFT -2
#define RIGHT 2


struct avl {
	char code[SIZE_CLIENTS];
	int height;
	struct avl *left, *right;
};

typedef struct avl *Avl;

int maior (int a, int b);
int heightAvl(Avl);
Avl actualizarAltura(Avl,Avl);
Avl rotateRight(Avl);
Avl rotateLeft(Avl);
Avl insert(Avl,char*);

#endif