/** @file facturacao.h
 *  @brief Protótipos das funções que trabalham com a facturacao.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam a Facturacao, assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __FACTURACAO_H__
#define __FACTURACAO_H__

/**
 * @brief Número de meses.
 */
#define SIZE_MONTH 12

/**
 * @brief Tamanho do Código de um Produto.
 */
#define SIZE_PRODUCT 7

/**
 * @brief Numero de Filiais.
 */
#define SIZE_FILIAIS 3

#include "avl.h"
#include "Sales.h"
#include "listaStrings.h"


/*Estruturas para organizar a facturacao em um array de 12, com cada indice um apontador para um array de 26 
apontadores para uma avl*/
/**
 * @brief Declaração do tipo FACTURACAO, um tipo abstrato. 
 */
typedef struct fact *FACTURACAO;

/**
 * @brief Declaração do tipo DADOS, um tipo abstrato. 
 */
typedef struct dados *DADOS;

/** @brief Inicia a estrutura da Facturação, alocando espaço para a mesma.
 *
 *  @return Facturação.
 */

FACTURACAO initFact();

/** @brief Inicia a estrutura dos dados, alocando espaço para a mesma.
 *
 *  @return Estrutura de dados.
 */

DADOS initDADOS();

/** @brief Copia os produtos do Catálogo de Produtos para a Facturação.
 *
 *  @param f Facturação.
 *  @param p Catálogo de Produtos.
 *  @return Facturação.
 */

FACTURACAO copyProducts(FACTURACAO f,CATALOG_PRODUCTS p);

/** @brief Insere uma Venda na estrutura Facturação.
 *
 *  @param f Facturação.
 *  @param s Venda.
 *  @return Facturação.
 */

FACTURACAO insereFact(FACTURACAO f,SALES s);

/** @brief Remove a estrutura da Facturação, libertando o espaço ocupado por esta.
 *
 *  @param f Facturação.
 *
 *  @return Void.
 */

void freeFact(FACTURACAO f);

/** @brief Remove a estrutura Info, libertando o espaço ocupado por esta.
 *
 *  @param info Info.
 *
 *  @return Void.
 */

void freeInfo(void* info);


/* GETS E SETS */

/** @brief Retorna um apontador para um array com a quantidade total facturada nas várias filiais.
 *
 *  @param d Dados.
 *
 *  @return Total facturado.
 */

double* getDadosP(DADOS d);

/** @brief Retorna um apontador para um array com a quantidade total de produtos comprados nas várias filiais.
 *
 *  @param d Dados.
 *
 *  @return Quantidade de produtos comprados.
 */

int* getDadosQ(DADOS d);

/** @brief Retorna o total facturado num Mês.
 *
 *  @param d Dados.
 *
 *  @return Quantidade total facturada.
 */

double getDadosTP(DADOS d);

/** @brief Retorna a quantidade total de produtos comprados num Mês.
 *
 *  @param d Dados.
 *
 *  @return Quantidade total de Produtos.
 */

int getDadosTV(DADOS d);


/** @brief Retorna a quantidade total facturada.
 *
 *  @param d Estrutura com informação geral.
 *
 *  @return Facturação total.
 */

double getTotalMP(DADOS d);

/** @brief Retorna a quantidade total .
 *
 *  @param d Estrutura com informação geral.
 *
 *  @return Qunatidade total.
 */

int getDadosTQ(DADOS d);

/** @brief Retorna a quantidade total de produtos vendidos.
 *
 *  @param d Estrutura com informação geral.
 *
 *  @return Quantidade total.
 */

int getTotalVendas(DADOS d);

/** @brief Retorna a quantidade total de produtos vendidos.
 *
 *  @param f Facturação.
 *  @param d Estrutura de dados.
 *  @param inicio Mês inicial.
 *	@param fim Mês final.
 *
 *  @return Quantidade total.
 */

DADOS totalM(FACTURACAO f,DADOS d,int inicio, int fim);

/** @brief Constrói uma lista dos produtos, nunca comprados, de forma Total ou por Filial.
 *
 *  @param f Facturação.
 *  @param ls Lista de Strings.
 *  @param filial Nº da Filial.
 *
 *  @return Quantidade total.
 */

LISTA_STRINGS listaProducts (FACTURACAO f,LISTA_STRINGS group,int filial);

/** @brief Recolhe os dados sobre um produto, num dado mês e promoção.
 *
 *  @param f Filial.
 *  @param d Estrutura de dados.
 *  @param promo Tipo de promoção.
 *  @param mes Mês. 
 *  @param product Produto.
 *
 *  @return Estrutura de dados.
 */

DADOS updatePriceQuantity(FACTURACAO f,DADOS d,int promo,int mes,char* product);

/** @brief Calcula o número de produtos nunca comprados.
 *
 *  @param f Facturação.
 *
 *  @return Quantidade total.
 */

int querie12Products(FACTURACAO f);

#endif