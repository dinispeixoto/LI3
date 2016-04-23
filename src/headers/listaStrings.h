/** @file listaStrings.h
 *  @brief Protótipos das funções que trabalham com a Lista de Strings.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam a Lista de Strings, assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __LISTASTRINGS_H__
#define __LISTASTRINGS_H__

#include <string.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo LISTA_STRINGS, um tipo abstrato. 
 */
typedef struct lista *LISTA_STRINGS;

/**
 * @brief Declaração do tipo PAGE, um tipo abstrato. 
 */
typedef struct page *PAGE;

/**
 * @brief Declaração do tipo STRING, um tipo abstrato. 
 */
typedef struct string *STRING;


void freeListaStr(LISTA_STRINGS ls);

/** @brief Inicia a estrutura Lista de Strings, alocando espaço para a mesma.
 *
 *  @param size Tamanho da Lista.
 *  @param sizeElement Tamanho dos elementos da Lista(Clientes ou Produtos).
 *  @return Lista de Strings.
 */

LISTA_STRINGS initListaStrings(int size,int sizeElement);

/** @brief Inicia a estrutura Página, alocando espaço para a mesma.
 *
 *  @param page_size Tamanho da Página.
 *  @param sizeElement Tamanho dos elementos da Página(Clientes ou Produtos).
 *  @return Página.
 */

PAGE initPage(int page_size,int sizeElement);

/** @brief Cria uma página a partir de uma Lista de Strings, começando num determinado índice.
 *
 *  @param lista Lista de Strings.
 *  @param begin Índice da String inicial.
 *  @param sizeElement Tamanho dos elementos da Página(Clientes ou Produtos).
 *  @param page_size Tamanho da Página.
 *  @return Página.
 */

PAGE updatePage(LISTA_STRINGS lista,int begin,int sizeElement,int page_size);

/** @brief Realoca espaço na Lista de Strings caso esta tenha uma ocupação superior a 75%.
 *
 *  @param lista Lista de Strings.
 *  @return Lista de Strings.
 */

LISTA_STRINGS reallocListaStrings(LISTA_STRINGS lista);

/** @brief Adiciona uma String á Lista de Strings numa determinada posição.
 *
 *  @param ls Lista de Strings.
 *  @param posicao Posição.
 *  @param elem String.
 *  @return Lista de Strings.
 */

LISTA_STRINGS addListaStrings(LISTA_STRINGS ls,int posicao,char* elem);

/** @brief Remove uma String da Lista de Strings.
 *
 *  @param ls Lista de Strings.
 *  @param elem String.
 *  @return Lista de Strings.
 */

LISTA_STRINGS removeListaStrings(LISTA_STRINGS ls,char* elem);


LISTA_STRINGS mergeList(LISTA_STRINGS ls1, LISTA_STRINGS ls2);

/** @brief Retorna o tamanho de uma Lista de Strings.
 *
 *  @param lista Lista de Strings.
 *  @return Tamanho da Lista de Strings.
 */

int getListaSize(LISTA_STRINGS lista);

/** @brief Retorna o número de posições ocupadas na Lista de Strings.
 *
 *  @param lista Lista de Strings.
 *  @return Posições ocupadas da Lista de Strings.
 */

int getListaSp(LISTA_STRINGS lista);

/** @brief Retorna a String presente numa dada posição da Lista de Strings.
 *
 *  @param lista Lista de Strings.
 *  @param index Posição.
 *  @return String que se encontra na posição.
 */

char* getListaString(LISTA_STRINGS lista,int index);

/** @brief Altera o tamanho da Lista de Strings.
 *
 *  @param lista Lista de Strings.
 *  @param size Tamanho.
 *  @return Void.
 */

void setListaSize(LISTA_STRINGS lista,int size);

/** @brief Retorna o apontador para os elementos da Lista de Strings.
 *
 *  @param lista Lista de Strings.
 *  @return Apontador para a Lista.
 */

STRING* getListaElements(LISTA_STRINGS lista);

/** @brief Retorna o tamanho de uma Página.
 *
 *  @param page Página.
 *  @return Tamanho da Página.
 */

int getPageSize(PAGE page);

/** @brief Retorna a String numa determinada posição da Página.
 *
 *  @param page Página.
 *  @return String.
 */

char* getPageElement(PAGE page,int index);

#endif