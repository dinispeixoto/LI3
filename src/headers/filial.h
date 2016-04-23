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

/**
 * @brief Tamanho do Código de um Produto.
 */
#define SIZE_PRODUCTS 7


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

/** @brief Copia os Produtos do Catálogo para a Filial.
 *
 *  @param f Filial.
 *	@param c Catálogo de Produtos.
 *  @return Void.
 */

FILIAL copyP(FILIAL f,CATALOG_PRODUCTS cp); 


/** @brief Copia os Clientes do Catálogo para a Filial.
 *
 *  @param f Filial.
 *  @param c Catálogo de Clientes.
 *
 *  @return Filial.
 */

FILIAL copyCPO(FILIAL f,CATALOG_CLIENTS c);

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

/** @brief Constrói uma lista de Strings, com os clientes que nunca compraram nada.
 *
 *  @param f Filial.
 *  @param ls Lista de Strings.
 *
 *  @return .
 */

LISTA_STRINGS dontBuyClient(FILIAL f, LISTA_STRINGS ls);

/** @brief Constrói uma Heap, ordenada por os produtos com maior facturação.
 *
 *  @param f Filial.
 *  @param hp Heap.
 *  @param client Cliente.
 *	
 *  @return Heap.
 */

Heap highCostProd(FILIAL f,Heap hp, char* client);

/** @brief Constrói uma Heap, ordenada pelos produtos mais vendidos em quantidade.
 *
 *  @param f Filial.
 *	@param hp Heap.
 *
 *  @return Heap.
 */

Heap querie10Fil(FILIAL f,Heap hp);

/** @brief Constrói uma Heap, ordenada pelos produtos com maior gastos.
 *	
 *  @param f Filial.
 *	@param hp Heap.
 *	@param client Cliente.
 *	@param month Mes.
 *
 *  @return Heap.
 */

Heap moreBuy(FILIAL f, Heap hp, char* client,int month);

/** @brief Constrói duas Listas de Strings, tendo uma os produtos que um cliente comprou sem promoção e outra com promoção.
 *	
 *  @param f Filial.
 *	@param product.
 *	@param gcN Lista de Strings de promoção N.
 *	@@param gcP Lista de Strings de promoção P.
 *	
 *  @return  Lista de Strings.
 */

LISTA_STRINGS productNeP(FILIAL f,char* product,LISTA_STRINGS gcN,LISTA_STRINGS gcP);

/** @brief Constrói uma Lista de Strings, com os Clientes que compraram numa filial.
 *
 *  @param f Filial.
 *	@param ls Lista de Strings.
 *
 *  @return  Lista de Strings.
 */

LISTA_STRINGS checkClientsValeN (FILIAL f,LISTA_STRINGS ls);

/** @brief Recolhe os dados de uma filial, sobre um dado cliente.
 *
 *  @param f Filial.
 *	@param df Dados sobre uma filial.
 *	@param client CLiente.
 *
 *  @return Estrutura com a informação relativa á Filial.
 */

DADOS_FILIAL valoresFilial(FILIAL f,DADOS_FILIAL df,char* client);


#endif