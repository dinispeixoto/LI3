#ifndef __AVL_H__
#define __AVL_H__

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct avl *Avl;
typedef struct myAvl *MY_AVL;
typedef char* STRING;

typedef int BOOL;

typedef void (*Func)(void*);

Avl initAvl();
MY_AVL initMyAvl();
MY_AVL insertMyAvl(MY_AVL,STRING,void*,int);
int heightAvl(Avl);
Avl insert(Avl,STRING,void*);
void removeAvl(Avl,Func);
void removeMyAvl(MY_AVL,Func);
BOOL existMyAvl(MY_AVL,STRING);
BOOL existAvl(Avl, STRING);
int totalElements(MY_AVL);
void* findInfo (Avl ,STRING,int*);
Avl cloneAvl (Avl);
MY_AVL cloneMyAvl (MY_AVL);
void removeFromMY_AVL (MY_AVL*,int);


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

/* APAGAR 
void printAVL(Avl);
void printMyAvl(MY_AVL);
*/

#endif