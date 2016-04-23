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
 * @brief Tamanho do Código de um Cliente.
 */
#define SIZE_CLIENTS 6 

/**
 * @brief Numero de Filiais.
 */
#define SIZE_FILIAIS 3

#include "avl.h"
#include "Sales.h"


/*Estruturas para organizar a facturacao em um array de 12, com cada indice um apontador para um array de 26 
apontadores para uma avl*/
/**
 * @brief Declaração do tipo FACTURACAO, um tipo abstrato. 
 */
typedef struct fact *FACTURACAO;

/*Estrutura pertencente a um nodo de uma avl, que contem a informacao de um produto*/

/**
 * @brief Declaração do tipo PRICE_QUANTITY, um tipo abstrato. 
 */
typedef struct priceQuantity *PRICE_QUANTITY;

/**
 * @brief Declaração do tipo INFO, um tipo abstrato. 
 */
typedef struct info *INFO;

/**
 * @brief Declaração do tipo DADOS, um tipo abstrato. 
 */
typedef struct dados *DADOS;

/**
 * @brief Declaração do tipo TOTAL_MES, um tipo abstrato. 
 */
typedef struct totalMes *TOTAL_MES;


/** @brief Inicia a estrutura da Facturação, alocando espaço para a mesma.
 *
 *  @return Facturação.
 */

FACTURACAO initFact();

/** @brief Inicia a estrutura dos dados, alocando espaço para a mesma.
 *
 *  @return Facturação.
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

/** @brief Retorna o numero total facturado de um Produto num determinado mês numa determinada filial.
 *
 *  @param i Info.
 *  @param filial Filial.
 *  @param promo Informação relativa á compra(promoção ou normal).
 *  @param mes Mês.
 *
 *  @return Numero total facturado.
 */

double getnumFilialP(INFO i,int filial,int promo,int mes);

/** @brief Retorna a quantidade comprada de um Produto num determinado mês numa determinada filial.
 *
 *  @param i Info.
 *  @param filial Filial.
 *  @param promo Informação relativa á compra(promoção ou normal).
 *  @param mes Mês.
 *
 *  @return Numero total facturado.
 */

int getnumFilialQ(INFO i,int filial,int promo,int mes);

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

/** @brief Altera a quantidade total facturada numa determinada Filial.
 *
 *  @param d Dados.
 *  @param index Filial.
 *  @param total Total facturado.
 *
 *  @return Dados.
 */

DADOS setTotalPrice(DADOS d,int index,double total);

/** @brief Altera a quantidade total de produtos comprados numa determinada Filial.
 *
 *  @param d Dados.
 *  @param index Filial.
 *  @param total Quantidade total.
 *
 *  @return Dados.
 */

DADOS setTotalQuantity(DADOS d,int index,int total);

/** @brief Retorna a MY_AVL de produtos presente num determinado índice da Facturação.
 *
 *  @param f Facturação.
 *  @param index Índice.
 *
 *  @return Dados.
 */

Avl getProductIndex(FACTURACAO f,int index);

/** @brief Retorna a informação relativa a um produto vendido em modo normal num determinado mês, numa determinada Filial.
 *
 *  @param i Info.
 *  @param month Mês.
 *  @param filial Filial.
 *
 *  @return Estrutura com a informação relativa ao mês e Filial.
 */

PRICE_QUANTITY getNormalPQ(INFO i,int month,int filial);

/** @brief Retorna a informação relativa a um produto vendido em modo promoção num determinado mês, numa determinada Filial.
 *
 *  @param i Info.
 *  @param month Mês.
 *  @param filial Filial.
 *
 *  @return Estrutura com a informação relativa ao mês e Filial.
 */

PRICE_QUANTITY getPromoPQ(INFO i,int month,int filial);

/** @brief Retorna a quantidade total de um produto vendido.
 *
 *  @param a Estrutura relativa a um determinado mês e determinada filial.
 *
 *  @return Quantidade total.
 */

int getTotalQuantPQ(PRICE_QUANTITY a);

/** @brief Retorna a quantidade total facturada.
 *
 *  @param d Estrutura com informação geral.
 *
 *  @return Facturação total.
 */

double getTotalMP(DADOS d);

/** @brief Retorna a quantidade total de produtos vendidos.
 *
 *  @param d Estrutura com informação geral.
 *
 *  @return Quantidade total.
 */

int getTotalVendas(DADOS d);

/** @brief Altera a quantidade total facturada.
 *
 *  @param d Estrutura com informação geral.
 *  @param total Facturação total.
 *
 *  @return Facturação total.
 */

DADOS setTotalMP(DADOS d,double total);

/** @brief Altera a quantidade total de produtos vendidos.
 *
 *  @param d Estrutura com informação geral.
 *  @param total Quantidade total.
 *
 *  @return Quantidade total.
 */

DADOS setTotalVendas(DADOS d,int total);

/** @brief Actualiza a quantidade total facturada.
 *
 *  @param d Estrutura com informação geral.
 *  @param total Facturação total.
 *
 *  @return Estrutura de dados.
 */

DADOS updateTotalMP(DADOS d,double total);

/** @brief Actualiza a quantidade total de produtos vendidos.
 *
 *  @param d Estrutura com informação geral.
 *  @param total Quantidade total.
 *
 *  @return Estrutura de dados.
 */

DADOS updateTotalVendas(DADOS d,int total);

/** @brief Retorna uma estrutura com a informação relativa á facturação num determinado mês.
 *
 *  @param i Facturação.
 *  @param month Mês.
 *
 *  @return Estrutura de dados.
 */

TOTAL_MES getTotalMes(FACTURACAO i,int month);

/** @brief Retorna a quantidade total facturada num determinado mês.
 *
 *  @param m Estrutura com facturação relativa a um determinado mês.
 *
 *  @return Quantidade total facturada num determinado mês.
 */

double getTotalFacturadoMES(TOTAL_MES m);

/** @brief Retorna a quantidade de produtos comprados num determinado mês.
 *
 *  @param m Estrutura com facturação relativa a um determinado mês.
 *
 *  @return Quantidade de produtos comprados.
 */

int getTotalQuantMES(TOTAL_MES m);

/** @brief Retorna a quantidade de vendas num determinado mês.
 *
 *  @param m Estrutura com facturação relativa a um determinado mês.
 *
 *  @return Quantidade de vendas.
 */
int getTotalRegisto(TOTAL_MES m);

#endif