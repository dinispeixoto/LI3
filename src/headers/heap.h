#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>

typedef struct heap *Heap;

Heap initHeap (int );
int insertHeap (Heap , double ,char*);
char*  extractMax (Heap );
char* extractMaxQuantity(Heap h,double* res);

int getHeapUsed(Heap);
int getMax(Heap );
char* getString(Heap hp,int i);
char** getListString(Heap hp,int i);

#endif