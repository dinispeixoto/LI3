/** @file avl.h
 *  @brief Protótipos das funções que trabalham com AVL's.
 *
 *  O ficheiro contem os prototipos das funçoes
 *  AVL e assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __AVL_H__
#define __AVL_H__

#include <string.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

/**
 * @brief Declaração do tipo Avl, um tipo abstrato. 
 */
typedef struct avl *Avl;

/**
 * @brief Declaração do tipo MY_AVL, um tipo abstrato. 
 */
typedef struct myAvl *MY_AVL;

/**
 * @brief Declaração do tipo STRING, um tipo abstrato. 
 */
typedef char* STR;

/**
 * @brief Declaração do tipo BOOL. 
 */
typedef int BOOL;

/**
 * @brief Declaração do tipo Func, apontador para uma função. 
 */
typedef void(*Func)(void*);


/** @brief Inicia a Avl, colocando-a a NULL.
 *
 *  @return NULL.
 */

Avl initAvl();

/** @brief Inicia a estrutura MY_AVL, alocando espaço para a mesma.
 *
 *  @return Estrutura MY_AVL.
 */

MY_AVL initMyAvl();

/** @brief Insere uma string e uma info numa MY_AVL.
 *
 *  @param a MY_AVL na qual será inserida a string.
 *  @param line String que será inserida.
 *  @param info Informaçao que será inserida.
 *  @param aux Informação acerca da info do nodo(aux=1 se já existe uma info no nodo).
 *  @return Arvore que já contem a respetiva string.
 */

MY_AVL insertMyAvl(MY_AVL a,char* line,void* info,int aux);

/** @brief Retorna a altura de uma dada Avl.
 *
 *  @param a Arvore com uma dada altura.
 *  @return Altura da Avl.
 */

int heightAvl(Avl a);

/** @brief Insere uma string e uma info num dado nodo de uma Avl.
 *
 *  @param estrutura Arvore na qual será inserida a string.
 *  @param line String que será inserida.
 *  @param info Informaçao que será inserida.
 *  @return Arvore que já contem a respetiva string.
 */

Avl insert(Avl estrutura,STR line,void* info);

/** @brief Remove uma dada Avl, libertando o espaço ocupado pela mesma.
 *
 *  @param estrutura Arvore que se pretende remover.
 *  @param freeInfo Apontador para uma Função que vai libertar o espaço ocupado pela Info.
 *  @return Void.
 */

void removeAvl(Avl estrutura,Func freeInfo);

/** @brief Remove uma estrutura MY_AVL, libertando o espaço ocupado pela mesma.
 *
 *  @param estrutura Estrutura MY_AVL que se pretende remover.
 *  @param f Apontador para uma Função que vai libertar o espaço ocupado pela Info.
 *  @return Void.
 */

void removeMyAvl(MY_AVL estrutura,Func f);

/** @brief Remove um nodo de uma Avl, libertando o espaço ocupado por este.
 *
 *  @param a Árvore.
 *  @return Void.
 */

void freeNodo(Avl a);

/** @brief Verifica se uma dada String existe numa dada estrutura MY_AVL.
 *
 *  @param estrutura Estrutura MY_AVL que contém ou nao a String em questao.
 *  @param line String que será procurada na MY_AVL.
 *  @return BOOL.
 */

BOOL existMyAvl(MY_AVL estrutura,STR line);

/** @brief Verifica se uma dada String existe numa dada Avl.
 *
 *  @param estrutura Arvore que contém ou nao a String em questao.
 *  @param line String que será procurada na Avl.
 *  @return BOOL.
 */

BOOL existAvl(Avl estrutura, STR line);

/** @brief Retorna o numero de elementos de uma dada estrutura MY_AVL.
 *
 *  @param estrutura Estrutura MY_AVL com um dado numero de elementos.
 *  @return Numero de elementos da MY_AVL.
 */

int totalElements(MY_AVL estrutura);

/** @brief Procura uma String que exista num dado nodo de uma Avl e retorna a info que lá se encontra
 *  retorna NULL caso nao exista. 
 *
 *  @param a Arvore que contém ou nao uma dada String.
 *  @param line String que pretendemos encontrar.
 *  @param x Incrementa caso nao encontre.
 *  @return *Void.
 */

void* findInfo (Avl a,STR line,int* x);

/** @brief Faz um clone de uma dada Avl.
 *
 *  @param estrutura Avl a ser clonada. 
 *  @return Arvore clonada.
 */

Avl cloneAvl (Avl estrutura);

/** @brief Faz um clone de uma dada MY_AVL.
 *
 *  @param estrutura MY_AVL a ser clonada. 
 *  @return MY_AVL clonada.
 */

MY_AVL cloneMyAvl (MY_AVL estrutura);

/** @brief Remove x nodos de uma dada MY_AVL.
 *
 *  @param estrutura MY_AVL a ser removida.
 *  @param x Numero de nodos a ser removidos. 
 *  @return Void.
 */

void removeFromMY_AVL (MY_AVL* estrutura,int x);

/** @brief Conta em quantos nodos de uma Avl nao existe Info.
 *
 *  @param a Árvore.
 *  @return Número de nodos sem Info.
 */

int infoNULL(Avl a);


/* GETS E SETS */

/** @brief Retorna a Avl que se encontra numa estrutura MY_AVL.
 *
 *  @param estrutura Estrutura MY_AVL que contem uma Avl.
 *  @return Arvore que se encontra na MY_AVL.
 */

Avl getAvl(MY_AVL estrutura);

/** @brief Retorna a Sub-arvore do lado esquerdo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Sub-arvore esquerda da Avl.
 */

Avl getAvlLeft(Avl a);

/** @brief Retorna a Sub-arvore do lado direito de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Sub-arvore direita da Avl.
 */

Avl getAvlRight(Avl a);

/** @brief Retorna a String presente no nodo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return String do nodo da Avl.
 */

char* getAvlCode(Avl a);

/** @brief Retorna a Info presente no nodo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Info do nodo da Avl.
 */

void* getInfo(Avl a);

/** @brief Retorna o tamanho de uma dada estrutura MY_AVL.
 *
 *  @param a Estrutura MY_AVL com um dado numero de elementos.
 *  @return Numero de elementos da MY_AVL.
 */

int getSize(MY_AVL a);

/** @brief Altera a Info presente no nodo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @param i Info.
 *  @return Void.
 */

void setInfo(Avl a,void* i);

/** @brief Coloca a Avl b numa MY_AVL.
 *
 *  @param a MY_AVL com uma dada Avl.
 *  @param b Avl.
 *  @return Void.
 */

void setAvl(MY_AVL a,Avl b);

#endif