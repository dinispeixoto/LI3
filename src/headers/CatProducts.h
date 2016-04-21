/** @file CatProducts.h
 *  @brief Protótipos do Catálogo dos Produtos.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam o Catálogo dos Produtos, assim como a implementação das estruturas necessárias e macros.  
 *
 *  @author Grupo 33
 */

#ifndef __CATPRODUCTS_H__
#define __CATPRODUCTS_H__

/**
 * @brief Tamanho do Código de um Produto.
 */
#define SIZE_PRODUCTS 7

/**
 * @brief Número de letras de um Produto.
 */
#define LETRAS_P 2

/**
 * @brief Tamanho do Abecedário.
 */
#define SIZE_ABC 26

/**
 * @brief Tamanho do Buffer.
 */
#define SIZE_BUFFER 64

#include <ctype.h>
#include "avl.h"

/**
 * @brief Declaração do tipo PRODUCT, um tipo abstrato. 
 */
typedef struct product *PRODUCT;

/**
 * @brief Declaração do tipo CATALOG_PRODUCTS, um tipo abstrato. 
 */
typedef struct catp *CATALOG_PRODUCTS;

/** @brief Inicia o Catálogo dos Produtos, alocando espaço para o mesmo.
 *
 *  @return Catálogo de Produtos.
 */

CATALOG_PRODUCTS initProducts();

/** @brief Inicia a estrutura do Produto, alocando espaço para a mesma.
 *
 *  @return Produto.
 */

PRODUCT initProd();

/** @brief Insere um Produto no respetivo Catálogo.
 *
 *  @param Catalog Catalogo de Clientes.
 *  @param prod Cliente a inserir.
 *  @return Catálogo de Produtos que já contém o Produto.
 */

CATALOG_PRODUCTS insertProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod);

/** @brief Testa se um Produto tem uma estrutura correta.
 *
 *  @param prod Produto.
 *  @return BOOL.
 */

BOOL testProduct (PRODUCT prod);

/** @brief Verifica se um determinado Produto existe num Catálogo de Produtos.
 *
 *  @param Catalog Catalogo de Produtos.
 *  @param prod Produto.
 *  @return BOOL.
 */

BOOL existProduct(CATALOG_PRODUCTS Catalog, PRODUCT prod);

/** @brief Remove um Produto, libertando o espaço ocupado por este.
 *
 *  @param prod Produto a ser removido.
 *
 *  @return Void.
 */

void freeProduct(PRODUCT prod);

/** @brief Limpa o Catálogo de Produtos, removendo as várias MY_AVL's.
 *
 *  @param Catalog Catalogo de Produtos a limpar.
 *
 *  @return Void.
 */

void removeCatProds(CATALOG_PRODUCTS Catalog);

/** @brief Calcula quantos Produtos, começados por uma determinada letra, existem num Catálogo de Produtos.
 *
 *  @param Catalog Catalogo de Produtos.
 *  @param letter Letra.
 *  @return Total de Produtos começados pela Letra.
 */

int totalProductsLetter(CATALOG_PRODUCTS Catalog,char Letra);

/** @brief Calcula quantos Produtos existem num Catálogo de Produtos.
 *
 *  @param Catalog Catálogo de Produtos.
 *  @return Total de Produtos no Catálogo.
 */

int totalProducts(CATALOG_PRODUCTS Catalog);

/* GETS & SETS */

/** @brief Retorna a String de um Produto.
 *
 *  @param prod Produto.
 *  @return String do Produto.
 */

char* getProduct(PRODUCT prod);

/** @brief Cria um Produto a partir de uma String.
 *
 *  @param prod Produto.
 *  @param string String.
 *  @return Produto.
 */

PRODUCT setProduct(PRODUCT prod,char* string);

/** @brief Retorna a MY_AVL presente num determinado índice do Catálogo de Produtos.
 *
 *  @param c Catálogo de Produtos.
 *  @param i Índice.
 *  @return MY_AVL presente no Índice.
 */

MY_AVL getP(CATALOG_PRODUCTS c, int i);

#endif