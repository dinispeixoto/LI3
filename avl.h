#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct avl *Avl;
typedef char* STRING;

Avl initAvl();
int heightAvl(Avl);
Avl insert(Avl,char*);
int existAvl(Avl, char*); /*  se calhar aqui é melhor meter o tipo PRODUTO/CLIENT */
void removeAvl(Avl);
void printAVL(Avl);
int totalElements(Avl);

#endif