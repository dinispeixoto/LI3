#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE_CODE 7
#define LEFT -2
#define RIGHT 2

typedef struct avl *Avl;

Avl initAvl();
int heightAvl(Avl);
Avl insert(Avl,char*);
int existAvl(Avl, char*);
void removeAvl(Avl);
void printAVL(Avl);
int totalElements(Avl);

#endif