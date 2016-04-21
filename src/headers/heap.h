/** @file heap.h
 *  @brief Protótipos das funções que trabalham com Heaps.
 *
 *  O ficheiro contem os prototipos das funçoes
 *  Heap e assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>

/**
 * @brief Declaração do tipo Heap, um tipo abstrato. 
 */
typedef struct heap *Heap;

/** @brief Inicia a estrutura Heap com um dado tamanho, alocando espaço para a mesma.
 *
 *  @param size Tamanho.
 *  @return Heap.
 */

Heap initHeap (int size);

/** @brief Insere numa Heap um determinado valor e uma string.
 *
 *  @param h Heap.
 *  @param x Valor.
 *  @param ct String.
 *  @return Heap.
 */

int insertHeap (Heap h, double x,char* ct);

/** @brief Retorna a String associada ao maior valor da Heap.
 *
 *  @param h Heap.
 *  @return String.
 */

char*  extractMax (Heap h);

/** @brief Retorna a String associada ao maior valor da Heap e coloca esse valor no segundo argumento.
 *
 *  @param h Heap.
 *  @return String.
 */

char* extractMaxQuantity(Heap h,double* res);

/** @brief Retorna o tamanho da Heap utilizado até ao momento.
 *
 *  @param h Heap.
 *  @return Tamanho usado.
 */

int getHeapUsed(Heap h);

/** @brief Retorna o maior valor da Heap.
 *
 *  @param h Heap.
 *  @return Valor.
 */

int getMax(Heap h);

/** @brief Retorna a String presente num determinado índice de uma Heap.
 *
 *  @param hp Heap.
 *  @param i Índice.
 *  @return String.
 */

char* getString(Heap hp,int i);

/** @brief Retorna as Strings presentes até um determinado índice de uma Heap.
 *
 *  @param hp Heap.
 *  @param i Índice.
 *  @return String.
 */

char** getListString(Heap hp,int i);

#endif