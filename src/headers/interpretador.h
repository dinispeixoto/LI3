/** @file interpretador.h
 *  @brief Protótipos das funções que trabalham com o Interpretador.
 *
 *  O ficheiro contém os protótipos das funçoes
 *  que implemetam o Interpretador, assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 33
 */

#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "filial.h"
#include "facturacao.h"		
#include "readFiles.h"
#include "queries.h"
#include "listaStrings.h"

/**
 * @brief Ficheiro dos Clientes.
 */
#define CLIENTS_FILE "files/Clientes.txt"

/**
 * @brief Ficheiro dos Produtos.
 */
#define	PRODUCTS_FILE "files/Produtos.txt"

/**
 * @brief Ficheiro das Vendas.
 */
#define SALES_FILE "files/Vendas_1M.txt"

/**
 * @brief Tamanho de uma Página.
 */
#define PAGE_SIZE 20

/**
 * @brief Tamanho do Código de um Produto.
 */
#define SIZE_PRODUCT 7



/** @brief Resposável por implementar o interpretador.
 *
 *  @param clients Catálogo de Clientes.
 *  @param products Catálogo de Produtos.
 *  @param f Filial.
 *  @param fact Facturação.
 *  @return Inteiro de informação para a main.
 */

int interpretador(CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact);


#endif
