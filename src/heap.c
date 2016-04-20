#include "headers/heap.h"

#define PARENT(i) (i-1)/2  /* os indices do array começam em 0 */
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2
#define SIZE_PRODUCTS 7

struct elem{
    int valor;
    char c[SIZE_PRODUCTS];
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

Heap** initHeapMatriz(int size,int x,int y){
    int i,j;
    Heap** hp=malloc(26*sizeof(struct heap***));

    for(i=0;i<x;i++){
        hp[i]=malloc(26*sizeof(struct heap*));
        for(j=0;j<y;j++)
            hp[i][j]=initHeap(1);
    }
    return hp;
}

void bubbleUp (Heap h, int i) {

    while (i!=0 && h->values[i].valor > h->values[PARENT(i)].valor) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }    
    
}

int  insertHeap (Heap h, int x,char* ct) {
    int i;
    if (h->used == h->size) {
        h->values = realloc(h->values, 2*(h->size)*sizeof(struct elem)); 
        h->size *= 2;
    }
    /*if(r){
        for(i=0;i<h->used;i++){
          if(strcmp(h->values[i].c,ct)==0){  
                h->values[i].valor+= x;
                h->values[i].registo++;
                r=0;
                bubbleUp(h, i);
                break;
            }
        }
    } 
    if(r){*/
        h->values[h->used].valor= x;
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
        char* r=malloc(SIZE_PRODUCTS);
        strcpy(r,h->values[0].c);   
        h->values[0] = h->values[h->used-1]; 
        (h->used)--;
        bubbleDown(h, h->used);
        return r;
    }
    else return NULL;
}

int getMax(Heap h){
    return (h->values[0].valor);
}

int getHeapUsed(Heap h){
    return h->used;
}

char* getString(Heap hp,int i){
    return hp->values[i].c;
}
