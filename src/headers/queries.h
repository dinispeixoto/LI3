/** @file queries.h
 *  @brief Protótipos das funções que trabalham com as Queries.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam as Queries, assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "facturacao.h"
#include "filial.h"
#include "heap.h"
#include "listaStrings.h"

/**
 * @brief Tamanho do Abecedário.
 */
#define SIZE_ABC 26

/**
 * @brief Número de mêses.
 */
#define SIZE_MONTH 12

/**
 * @brief Número de Filiais.
 */
#define SIZE_FILIAIS 3

/**
 * @brief Tamanho do Produto.
 */
#define SIZE_PRODUCT 6

/**
 * @brief Tamanho do Cliente.
 */
#define SIZE_CLIENT 5


/** @brief Implementa a Querie 2. Retorna todos os produtos que se iniciam com uma dada letra.
 *
 *  @param Catalog Catálogo de Produtos.
 *  @param letter Letra.
 *  @return Lista de Strings com os Produtos.
 */

LISTA_STRINGS querie2(CATALOG_PRODUCTS Catalog,char letter);

/** @brief Implementa a Querie 3. Retorna a informação relativa a um determinado produto num determinado mês, em modo normal e promoção.
 *
 *  @param f Facturação.
 *  @param mes Mês.
 *  @param product Produto.
 *  @param promo Informação relativa á compra(normal ou promoção).
 *  @return Estrutura de dados sobre um Produto.
 */

DADOS querie3(FACTURACAO f,int mes,char* product,int promo);

/** @brief Implementa a Querie 4. Retorna os Produtos que ninguem comprou nas várias Filiais.
 *
 *  @param f Facturação.
 *  @param filial Filial.
 *  @return Lista de Strings com os Produtos.
 */

LISTA_STRINGS querie4(FACTURACAO f,int filial);

/** @brief Implementa a Querie 5. Retorna a informação relativa à quantidade total comprada nos vários meses, dado um Cliente.
 *
 *  @param f Filial.
 *  @param df Dados relativos ás Filiais.
 *  @param client Cliente.
 *  @param filial Filial.
 *  @return Dados relativos ás Filiais.
 */

DADOS_FILIAL querie5(FILIAL f,DADOS_FILIAL df,char* client);

/** @brief Implementa a Querie 6. Retorna a informação relativa ao total de vendas registadas e o total facturado durante um intervalo de meses.
 *
 *  @param f Facturação.
 *  @param inicio Mês inicial.
 *  @param fim Mês final.
 *  @return Dados relativos aos vários meses.
 */

DADOS querie6(FACTURACAO f,int inicio,int fim);

/** @brief Implementa a Querie 7. Retorna todos os Clientes que realizaram compras em todas as Filiais.
 *
 *  @param f Facturação.
 *  @return Lista de Strings com os vários Clientes.
 */

LISTA_STRINGS querie7(FILIAL* f);

/** @brief Implementa a Querie 8. Retorna todos os Clientes(e o seu número total) que compraram um determinado produto num determinada Filial, em promoção e em venda normal.
 *
 *  @param f Filial.
 *  @param product Produto.
 *  @param P Lista de Strings.
 *  @return Lista de Strings com os vários Clientes.
 */

LISTA_STRINGS querie8(FILIAL f,char* product,LISTA_STRINGS* P);

/** @brief Implementa a Querie 9. Retorna os Produtos mais comprados por ordem decrescente dado um determinado Cliente e um Mês.
 *
 *  @param f Filial.
 *  @param client Cliente.
 *  @param month Mês.
 *  @return Lista de Strings com os vários Produtos.
 */

LISTA_STRINGS querie9(FILIAL* f,char* client,int month);


LISTA_STRINGS querie10(FILIAL f, int N,int** dados);

/** @brief Implementa a Querie 11. Retorna os 3 Produtos em que um dado Cliente mais dinheiro gastou durante todo o ano.
 *
 *  @param f Filial.
 *  @param client Cliente.
 *  @return Lista de Strings com os Produtos.
 */

LISTA_STRINGS querie11(FILIAL* f,char* client);

/** @brief Implementa a Querie 12. Retorna o número de Clientes que não realizaram compras bem como o número de
 *         Produtos que ninguém comprou.
 *
 *  @param f Filial.
 *  @param fact Facturação.
 *  @param sumClient Somatório dos Clientes.
 *  @return Somatório dos Produtos.
 */

int querie12(FILIAL* f,FACTURACAO fact,int* sumClient);

#endif