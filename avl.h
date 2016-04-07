#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct avl *Avl;
typedef struct myAvl *MY_AVL;
typedef char* STRING;

MY_AVL initMyAvl();
MY_AVL insertMyAvl(MY_AVL,STRING);
Avl initAvl();
int heightAvl(Avl);
Avl insert(Avl,STRING);
int existAvl(Avl, STRING); /*  se calhar aqui é melhor meter o tipo PRODUTO/CLIENT */
void removeAvl(Avl);
void removeMyAvl(MY_AVL);
int existMyAvl(MY_AVL,STRING);
void printAVL(Avl);
void printMyAvl(MY_AVL);
int totalElements(MY_AVL);
Avl getAvl(MY_AVL);

#endif