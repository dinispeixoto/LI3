#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>

typedef struct heap *Heap;

Heap initHeap (int );
int insertHeap (Heap , double ,int,char*);
char*  extractMax (Heap );
char* extractMaxQuantity(Heap ,double* ,int*);

int getHeapUsed(Heap);
int getMax(Heap );
char* getString(Heap hp,int i);
char** getListString(Heap hp,int i);

#endif