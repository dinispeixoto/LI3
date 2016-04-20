#ifndef __AVL_H__
#define __AVL_H__

#include <string.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

typedef struct avl *Avl;
typedef struct myAvl *MY_AVL;
typedef char* STR;
typedef int BOOL;

typedef void(*Func)(void*);

Avl initAvl();
MY_AVL initMyAvl();
MY_AVL insertMyAvl(MY_AVL,STR,void*,int);
int heightAvl(Avl);
Avl insert(Avl,STR,void*);
void removeAvl(Avl,Func);
void removeMyAvl(MY_AVL,Func);
BOOL existMyAvl(MY_AVL,STR);
BOOL existAvl(Avl, STR);
int totalElements(MY_AVL);
void* findInfo (Avl ,STR,int*);
Avl cloneAvl (Avl);
MY_AVL cloneMyAvl (MY_AVL);
void removeFromMY_AVL (MY_AVL*,int);
int infoNULL(Avl);


/* GETS E SETS */
Avl getAvl(MY_AVL);
Avl getAvlLeft(Avl);
Avl getAvlRight(Avl);
char* getAvlCode(Avl);
void* getInfo(Avl a);
int getSize(MY_AVL a);
void setInfo(Avl a,void* i);
Avl setAv(Avl,Avl);
void setAvl(MY_AVL,Avl);

#endif