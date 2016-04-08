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

MY_AVL initMyAvl();
MY_AVL insertMyAvl(MY_AVL,STRING);
Avl initAvl();
int heightAvl(Avl);
Avl insert(Avl,STRING);
void removeAvl(Avl);
void removeMyAvl(MY_AVL);
BOOL existMyAvl(MY_AVL,STRING);
BOOL existAvl(Avl, STRING);
int totalElements(MY_AVL);

/* GETS E SETS */
Avl getAvl(MY_AVL);
Avl getAvlLeft(Avl);
Avl getAvlRight(Avl);
char* getAvlCode(Avl);

/* APAGAR 
void printAVL(Avl);
void printMyAvl(MY_AVL);
*/

#endif