/** @file Sales.h
 *  @brief Protótipos das Vendas.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que implemetam as Vendas, assim como a implementação das estruturas necessárias e macros.  
 *
 *  @author Grupo 33
 */

#ifndef __SALES_H__
#define __SALES_H__

#include <string.h>
#include <stdlib.h>

#include "CatClients.h"
#include "CatProducts.h"

/**
 * @brief Tamanho do Buffer das Vendas.
 */
#define SIZE_BUF_SALES 128

/**
 * @brief Declaração do tipo SALES, um tipo abstrato. 
 */
typedef struct sales *SALES;

/**
 * @brief Declaração do tipo QUANTITY. 
 */
typedef int QUANTITY;

/**
 * @brief Declaração do tipo PRICE. 
 */
typedef double PRICE;

/**
 * @brief Declaração do tipo INFO_PROMO. 
 */
typedef char INFO_PROMO;

/**
 * @brief Declaração do tipo FILIAIS. 
 */
typedef int FILIAIS;

/**
 * @brief Declaração do tipo MONTH. 
 */
typedef int MONTH;


/** @brief Inicia a estrutura de uma Venda, alocando espaço para a mesmo.
 *
 *  @return Venda.
 */

SALES initSales();

/** @brief Actualiza uma estrutura de Venda com os parametros dados.
 *
 *  @param sale Venda.
 *  @param clie Cliente.
 *  @param prod Produto.
 *  @param month Mês.
 *  @param filial Filial.
 *  @param quant Quantidade comprada.
 *  @param price Preço do Produto.
 *  @param infoP Informação sobre o tipo de compra(Promoção ou normal).
 *  @return Venda.
 */

SALES updateSales(SALES sale,CLIENT clie,PRODUCT prod,MONTH month,FILIAIS filial,QUANTITY quant,PRICE price,INFO_PROMO infoP);

/** @brief Função que reparte um linha de venda, e verifica se a linha é válida,ou seja, se o produto e cliente são válidos e exitem
 *         nos Catálogos, e se os outros parametros estao corretos. Coloca todos esses valores em variáveis que recebe como argumento.
 *
 *  @param line Registo de uma Venda.
 *  @param clients Catálogo de Clientes.
 *  @param products Catálogo de Produtos.
 *  @param clie Cliente.
 *  @param prod Produto.
 *  @param month Mês.
 *  @param filial Filial.
 *  @param quant Quantidade comprada.
 *  @param price Preço do Produto.
 *  @param infoP Informação sobre o tipo de compra(Promoção ou normal).
 *  @return BOOL.
 */
int partCheck(char* line,CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,CLIENT* clie,PRODUCT* prod,MONTH* month,FILIAIS* filial,QUANTITY* quant,PRICE* price,INFO_PROMO* infoP);

/** @brief Remove uma Venda, libertando o espaço ocupado por esta.
 *
 *  @param a Venda a ser removida.
 *
 *  @return Void.
 */

void freeSale(SALES a);

/* GETS E SETS */

/** @brief Retorna o Cliente de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Cliente.
 */

CLIENT getSalesClient(SALES a);

/** @brief Retorna o Produto de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Produto.
 */

PRODUCT getSalesProduct(SALES a);

/** @brief Retorna o Preço do produto de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Preço.
 */

PRICE getSalesPrice(SALES a);

/** @brief Retorna a quantidade de produtos de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Quantidade.
 */

QUANTITY getSalesQuantity(SALES a);

/** @brief Retorna a Informação sobre o tipo de compra(Promoção ou normal) de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Informação de compra.
 */

INFO_PROMO getSalesInfoPromo(SALES a);

/** @brief Retorna o mês de uma dada Venda.
 *
 *  @param a Venda.
 *  @return Mês.
 */

MONTH getSalesMonth(SALES a);

/** @brief Retorna a Filial onde ocorreu uma dada Venda.
 *
 *  @param a Venda.
 *  @return Filial.
 */

FILIAIS getSalesFilial(SALES a);

/** @brief Altera o Cliente de uma dada Venda.
 *
 *  @param c Cliente.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesClient(CLIENT c,SALES a);

/** @brief Altera o Produto de uma dada Venda.
 *
 *  @param c Produto.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesProduct(PRODUCT c,SALES a);

/** @brief Altera o Preço do Produto de uma dada Venda.
 *
 *  @param c Preço.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesPrice(PRICE c,SALES a);

/** @brief Altera a quantidade de Produtos de uma dada Venda.
 *
 *  @param c Quantidade.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesQuantity(QUANTITY c,SALES a);

/** @brief Altera a informação de uma dada Venda.
 *
 *  @param c Informação.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesInfoPromo(INFO_PROMO c,SALES a);

/** @brief Altera o mês de uma dada Venda.
 *
 *  @param c Mês.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesMonth(MONTH c,SALES a);

/** @brief Altera a Filial de uma dada Venda.
 *
 *  @param c Filial.
 *  @param a Venda.
 *  @return Venda.
 */

SALES setSalesFilial(FILIAIS c,SALES a);



#endif