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
#include "heap.h"
#include "listaStrings.h"

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

#define SIZE_PRODUCT 6

#define SIZE_ABC 26

/**
 * @brief Declaração do tipo FILIAL, um tipo abstrato. 
 */
typedef struct filial *FILIAL;

/**
 * @brief Declaração do tipo DADOS_FILIAL, um tipo abstrato. 
 */
typedef struct dadosFilial *DADOS_FILIAL;


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


LISTA_STRINGS dontBuyClient(FILIAL f, LISTA_STRINGS ls);

Heap highCostProd(FILIAL f,Heap hp, char* client);

Heap querie10Fil(FILIAL f,Heap hp);

Heap moreBuy(FILIAL f, Heap hp, char* client,int month);

LISTA_STRINGS productNeP(FILIAL f,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP);

LISTA_STRINGS checkClientsValeN (FILIAL f,LISTA_STRINGS ls);

DADOS_FILIAL valoresFilial(FILIAL f,DADOS_FILIAL df,char* client);


FILIAL copyP(FILIAL f,CATALOG_PRODUCTS cp); /* FALTA ESTA */


/** @brief Copia os Clientes do Catálogo para a Filial.
 *
 *  @param f Filial.
 *  @param c Catálogo de Clientes.
 *
 *  @return Filial.
 */

FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c);



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


#endif