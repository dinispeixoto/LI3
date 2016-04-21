#include "headers/heap.h"

#define PARENT(i) (i-1)/2  /* os indices do array começam em 0 */
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

struct elem{
    double valor;
    char* c;
};

struct heap{
    int   size;
    int   used;
    struct elem *values;
};


void swap (Heap h, int a, int b) {
    struct elem t = h->values[a];
    h->values[a] = h->values[b];
    h->values[b] = t;
}

Heap initHeap (int size) {
    Heap h = malloc(sizeof(struct heap));
    h->size = size;
    h->used = 0;
    h->values=malloc(size*sizeof(struct elem));
    return h;
}

void bubbleUp (Heap h, int i) {

    while (i!=0 && h->values[i].valor > h->values[PARENT(i)].valor) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }    
}

int  insertHeap (Heap h, double x,char* ct) {
    
    if (h->used == h->size) {
        h->values = realloc(h->values, 2*(h->size)*sizeof(struct elem)); 
        h->size *= 2;
    }

    h->values[h->used].valor= x;
    h->values[h->used].c=malloc((strlen(ct)+1)*sizeof(char));
    strcpy(h->values[h->used].c,ct);
    (h->used)++;
    bubbleUp(h, h->used-1);
    return 1;
}

void bubbleDown (Heap h, int N) {
    int i = 0, max ;    

    while (RIGHT(i) < N && h->values[max = h->values[LEFT(i)].valor > h->values[RIGHT(i)].valor ? LEFT(i) : RIGHT(i)].valor > h->values[i].valor) {
        swap(h, i, max); 
        i = max;
    }
    if (LEFT(i) < N && h->values[LEFT(i)].valor > h->values[i].valor) 
        swap(h, i, LEFT(i)); 
}

char*  extractMax(Heap h){
   
    if (h->used > 0) {
        char* r=malloc((strlen(h->values[0].c)+1)*sizeof(char));
        strcpy(r,h->values[0].c);   
        h->values[0] = h->values[h->used-1]; 
        (h->used)--;
        bubbleDown(h, h->used);
        return r;
    }
    else return NULL;
}


char* extractMaxQuantity(Heap h,double* res){
if (h->used > 0) {
        char* r=malloc((strlen(h->values[0].c)+1)*sizeof(char));
        strcpy(r,h->values[0].c);
        *res=h->values[0].valor;   
        h->values[0] = h->values[h->used-1]; 
        (h->used)--;
        bubbleDown(h, h->used);
        return r;
    }
    else return NULL;
}

Heap cloneHeap (Heap hp){
    int i;
    Heap h=initHeap(hp->size);
    for(i=0;i<hp->used;i++)
        insertHeap(h,hp->values[i].valor,hp->values[i].c);

    return h;
}

int getMax(Heap h){
    return (h->values[0].valor);
}

int getHeapUsed(Heap h){
    return h->used;
}

char* getString(Heap hp,int i){
    char* aux=malloc((strlen(hp->values[i].c)+1)*sizeof(char));
    strcpy(aux,hp->values[i].c);
    return aux;
}

char** getListString(Heap hp,int i){
    Heap h;
    int j;
    char** aux=malloc(i*sizeof(char**));
    h=cloneHeap(hp);
    for(j=0;j<i;j++){
        aux[j]=extractMax(h);
    }
    return aux;
}

