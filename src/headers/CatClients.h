/** @file CatClients.h
 *  @brief Protótipos do Catálogo dos Clientes.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam o Catálogo dos Clientes, assim como a implementação das estruturas necessárias e macros.  
 *
 *  @author Grupo 33
 */

#ifndef __CATCLIENTS_H__
#define __CATCLIENTS_H__

/**
 * @brief Tamanho do Código de um Cliente.
 */
#define SIZE_CLIENTS 6

/**
 * @brief Número de letras de um Cliente.
 */
#define LETRAS_C 1

/**
 * @brief Tamanho do Abecedário.
 */
#define SIZE_ABC 26

#include <ctype.h>
#include "avl.h"

/**
 * @brief Declaração do tipo CLIENT, um tipo abstrato. 
 */
typedef struct client *CLIENT;

/**
 * @brief Declaração do tipo CATALOG_CLIENT, um tipo abstrato. 
 */
typedef struct catc *CATALOG_CLIENTS;


/** @brief Inicia o Catálogo dos Clientes, alocando espaço para o mesmo.
 *
 *  @return Catálogo de Clientes.
 */

CATALOG_CLIENTS initClients();

/** @brief Inicia a estrutura do Cliente, alocando espaço para a mesmo.
 *
 *  @return Cliente.
 */

CLIENT initClie();

/** @brief Insere um Cliente no respetivo Catálogo.
 *
 *  @param Catalog Catalogo de Clientes.
 *  @param clie Cliente a inserir.
 *  @return Catálogo de Clientes que já contém o Cliente.
 */

CATALOG_CLIENTS insertClient(CATALOG_CLIENTS Catalog, CLIENT clie);

/** @brief Testa se um Cliente tem uma estrutura correta.
 *
 *  @param client Cliente.
 *  @return BOOL.
 */

BOOL testClient(CLIENT client);

/** @brief Verifica se um determinado Cliente existe num Catálogo de Clientes.
 *
 *  @param Catalog Catalogo de Clientes.
 *  @param clie Cliente.
 *  @return BOOL.
 */

BOOL existClient(CATALOG_CLIENTS Catalog, CLIENT clie);

/** @brief Remove um Cliente, libertando o espaço ocupado por este.
 *
 *  @param clie Cliente a ser removido.
 *
 *  @return Void.
 */

void freeClient(CLIENT clie);

/** @brief Limpa o Catálogo de Clientes, removendo as várias MY_AVL's.
 *
 *  @param Catalog Catalogo de Clientes a limpar.
 *
 *  @return Void.
 */

void removeCatClients(CATALOG_CLIENTS Catalog);

/** @brief Calcula quantos Clientes, começados por uma determinada letra, existem num Catálogo de Clientes.
 *
 *  @param Catalog Catalogo de Clientes.
 *  @param letter Letra.
 *  @return Total de Clientes começados pela Letra.
 */

int totalClientsLetter(CATALOG_CLIENTS Catalog,char letter);

/** @brief Calcula quantos Clientes existem num Catálogo de Clientes.
 *
 *  @param Catalog Catálogo de Clientes.
 *  @return Total de Clientes no Catálogo.
 */

int totalClients(CATALOG_CLIENTS Catalog);

/* GETS & SETS */

/** @brief Retorna o código de um Cliente.
 *
 *  @param clie Cliente.
 *  @return String do Cliente.
 */

char* getClient(CLIENT clie);

/** @brief Cria um Cliente a partir de uma String.
 *
 *  @param c Cliente.
 *  @param string String.
 *  @return Cliente.
 */

CLIENT setClient(CLIENT c,char* string);

/** @brief Retorna a MY_AVL presente num determinado índice do Catálogo de Clientes.
 *
 *  @param c Catálogo de Clientes.
 *  @param i Índice.
 *  @return MY_AVL presente no Índice.
 */

MY_AVL getC(CATALOG_CLIENTS c,int i);

#endif