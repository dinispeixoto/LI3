#include "headers/heap.h"

#define PARENT(i) (i-1)/2               /* Determina o índice do Pai de um determinado Nodo. */
#define LEFT(i) 2*i + 1                 /* Determina o Nodo à esquerda de um determinado Nodo. */   
#define RIGHT(i) 2*i + 2                /* Determina o Nodo à direita de um determinado Nodo. */

/* Estrutura de um elemento. */
struct elem{
    double valor;                       /* Valor associado a um elemento. */
    int registo;                        /* Registo associado a um elemento. */
    char* c;                            /* String associada a um elemento. */
};

/* Estrutura da Heap. */
struct heap{    
    int   size;                         /* Tamanho alocado para a Heap.*/
    int   used;                         /* Número de elementos da Heap. */
    struct elem *values;                /* Array de elementos que formam a Heap. */
};

/* Funções privadas ao módulo. */
static void swap(Heap,int,int);
static void bubbleUp(Heap,int);
static void bubbleDown(Heap,int);

/* Inicializa uma Heap. */
Heap initHeap(int size){
    Heap h = malloc(sizeof(struct heap));
    h->size = size;
    h->used = 0;
    h->values=malloc(size*sizeof(struct elem));
    return h;
}

/* Insere numa Heap. */
int insertHeap(Heap h, double x,int y,char* ct){
    
    if (h->used == h->size) {
        h->values = realloc(h->values, 2*(h->size)*sizeof(struct elem)); 
        h->size *= 2;
    }
    h->values[h->used].valor= x;
    h->values[h->used].registo = y;
    h->values[h->used].c=malloc((strlen(ct)+1)*sizeof(char));
    strcpy(h->values[h->used].c,ct);
    (h->used)++;
    bubbleUp(h, h->used-1);
    return 1;
}

/* Extrai o máximo da Heap, actualizando o resto da mesma. */
char* extractMax(Heap h){
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

/* Extrai o máximo da Heap, actualizando o resto da mesma, retorna informação pelos argumentos. */
char* extractMaxQuantity(Heap h,double* quant,int* resg){
if (h->used > 0) {
        char* r=malloc((strlen(h->values[0].c)+1)*sizeof(char));
        strcpy(r,h->values[0].c);
        *quant=h->values[0].valor;
        *resg=h->values[0].registo;    
        h->values[0] = h->values[h->used-1]; 
        (h->used)--;
        bubbleDown(h, h->used);
        return r;
    }
    else return NULL;
}

/* Função responsável por fazer clone de uma Heap. */
Heap cloneHeap(Heap hp){
    int i;
    Heap h=initHeap(hp->size);
    for(i=0;i<hp->used;i++)
        insertHeap(h,hp->values[i].valor,hp->values[i].registo,hp->values[i].c);

    return h;
}


/* GETS E SETS */
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

/* Funções privadas ao módulo. */

/* Função responsável por fazer swap numa Heap. */
static void swap(Heap h, int a, int b){
    struct elem t = h->values[a];
    h->values[a] = h->values[b];
    h->values[b] = t;
}

/* Função que faz Bubble-Up na Heap, questões de algoritmo. */
static void bubbleUp(Heap h, int i){
    while (i!=0 && h->values[i].valor > h->values[PARENT(i)].valor) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }    
}

/* Função que faz Bubble-Down na Heap, questões de algoritmo. */
static void bubbleDown(Heap h, int N){
    int i = 0, max ;    
    while (RIGHT(i) < N && h->values[max = h->values[LEFT(i)].valor > h->values[RIGHT(i)].valor ? LEFT(i) : RIGHT(i)].valor > h->values[i].valor) {
        swap(h, i, max); 
        i = max;
    }
    if (LEFT(i) < N && h->values[LEFT(i)].valor > h->values[i].valor) 
        swap(h, i, LEFT(i)); 
}