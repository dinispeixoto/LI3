#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>

typedef struct heap *Heap;

Heap initHeap (int );
Heap** initHeapMatriz(int ,int ,int);
int insertHeap (Heap , int ,char*);
char*  extractMax (Heap );

int getHeapUsed(Heap);
int getMax(Heap );
char* getString(Heap hp,int i);

#endif