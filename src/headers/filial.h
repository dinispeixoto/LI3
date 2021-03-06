/** @file filial.h
 *  @brief Protótipos das funções que trabalham com a Filial.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam a Filial, assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __FILIAIS_H__
#define __FILIAIS_H__

#include "avl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Sales.h"

/**
 * @brief Número de meses.
 */
#define SIZE_MONTH 12

/**
 * @brief Número de Filiais.
 */
#define SIZE_FILIAIS 3

/**
 * @brief Tipos de Venda(normal ou promoção).
 */
#define SIZE_INFOP 2

/**
 * @brief Declaração do tipo FILIAL, um tipo abstrato. 
 */
typedef struct filial *FILIAL;

/**
 * @brief Declaração do tipo INFO_MES, um tipo abstrato. 
 */
typedef struct infoMes *INFO_MES;

/**
 * @brief Declaração do tipo INFO_CLIENT, um tipo abstrato. 
 */
typedef struct infoClient *INFO_CLIENT;

/**
 * @brief Declaração do tipo INFO_PRODUCT, um tipo abstrato. 
 */
typedef struct infoProduct *INFO_PRODUCT;

/**
 * @brief Declaração do tipo DADOS_FILIAL, um tipo abstrato. 
 */
typedef struct dadosFilial *DADOS_FILIAL;

/* FALTA ESTA */
typedef struct productInfo *PRODUCT_INFO;


/** @brief Inicia a estrutura da Filial, alocando espaço para a mesma.
 *
 *  @return Filial.
 */

FILIAL initFilial();

/** @brief Insere uma Venda na estrutura Filial.
 *
 *  @param f Filial.
 *  @param s Venda.
 *  @return Filial.
 */

FILIAL insertFilial(FILIAL f,SALES s);

/** @brief Inicia a estrutura DADOS_FILIAL, alocando espaço para a mesma.
 *
 *  @return Estrutura com informação sobre uma Filial.
 */

DADOS_FILIAL initDadosFilial();

/** @brief Remove a estrutura Filial, libertando o espaço ocupado por esta.
 *
 *  @param f Filial.
 *
 *  @return Void.
 */

void freeFilial(FILIAL f);


FILIAL copyP(FILIAL f,CATALOG_PRODUCTS cp); /* FALTA ESTA */


/** @brief Copia os Clientes do Catálogo para a Filial.
 *
 *  @param f Filial.
 *  @param c Catálogo de Clientes.
 *
 *  @return Filial.
 */

FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c);


/** @brief Verifica se um Cliente comprou algum produto.
 *
 *  @param x Estrutura com informação sobre um Cliente.
 *
 *  @return Retorna 1 caso tenha comprado algum produto.
 */

int getComp(INFO_CLIENT x);

/** @brief Retorna a Avl presente num determinado indice da estrutura Filial.
 *
 *  @param f Filial.
 *  @param index Índice.
 *
 *  @return Avl que se encontra no índice.
 */

Avl getClientIndexF(FILIAL f,int index);

/** @brief Actualiza os dados relativos a uma dada Filial num dado mês.
 *
 *  @param df Estrutura com a informação relativa á Filial.
 *  @param filial Filial.
 *  @param month Mês.
 *  @param total Quantidade de produtos comprados
 *
 *  @return Estrutura com a informação relativa á Filial.
 */

DADOS_FILIAL updateQuant_DadosFilial(DADOS_FILIAL df,int month,int total);

/** @brief Retorna a informação das compras realizadas por um determinado Cliente, num determinado Mês.
 *
 *  @param info Estrutura com a informação sobre um Cliente.
 *  @param month Mês.
 *
 *  @return Estrutura com a informação relativa ao Mês.
 */

INFO_MES getInfoMes(INFO_CLIENT info,int month);

/** @brief Retorna a quantidade de produtos comprados num determinado Mês.
 *
 *  @param info Estrutura com a informação sobre um determinado Mês.
 *
 *  @return Quantidade de Produtos comprados.
 */

int getInfoMesQuantity(INFO_MES info);

/** @brief Retorna a quantidade comprada de um determinado produto em preço normal ou em promoção.
 *
 *  @param info Estrutura com a informação sobre um determinado Produto.
 *  @param index Tipo de compra (normal ou promoção).
 *
 *  @return Quantidade do produto comprada.
 */

int getInfoProductQuantity(INFO_PRODUCT info,int index);

/** @brief Retorna o dinheiro total gasto num determinado produto em preço normal ou em promoção.
 *
 *  @param info Estrutura com a informação sobre um determinado Produto.
 *  @param index Tipo de compra (normal ou promoção).
 *
 *  @return Dinheiro total gasto.
 */

double getInfoProductPrice(INFO_PRODUCT info,int index);

/** @brief Retorna a MY_AVL presente na estrutura INFO_MES, num determinado índice.
 *
 *  @param info Estrutura com a informação sobre um determinado Mês.
 *  @param index Índice.
 *
 *  @return MY_AVL presente no índice.
 */

MY_AVL getInfoMesProduct(INFO_MES info,int index);

/** @brief Retorna a quantidade de produtos comprados numa dada Filial, num dado Mês.
 *
 *  @param df Estrutura com a informação sobre a Filial.
 *  @param filial Filial.
 *  @param month Mês.
 *
 *  @return Quantidade de Produtos comprados.
 */

int getDadosFilialQuantity(DADOS_FILIAL df,int month);

Avl getProdInfo(FILIAL f,int index);

int getResg(PRODUCT_INFO info);

int	getPiQuant(PRODUCT_INFO info);

#endif