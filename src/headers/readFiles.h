/** @file readFiles.h
 *  @brief Protótipos das Funções resposáveis por tratar dos ficheiros.
 *
 *  O ficheiro contem os protótipos das funçoes
 *  que trabalham com os ficheiros de entrada, assim como a implementação das estruturas necessárias e macros.  
 *
 *  @author Grupo 33
 */

#ifndef __READFILES_H__
#define __READFILES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "CatClients.h"
#include "CatProducts.h"
#include "facturacao.h"		
#include "filial.h"

/** @brief Faz o cálculo do número de validações em cada um dos ficheiros, em simultâneo guarda o que é
 *         validado em memória, na respectiva estrutura.
 *
 *  @param clients Catálogo de Clientes.
 *  @param products Catálogo de Produtos.
 *  @param f Filiais.
 *  @param fact Facturação.
 *  @param clientsFile Ficheiro dos Clientes.
 *  @param productsFile Ficheiro dos Produtos.
 *  @param salesFile Ficheiro das Vendas.
 *  @return 1 caso consiga abrir todos os ficheiros, 0 caso contrário.
 */

int getFile(CATALOG_CLIENTS clients,CATALOG_PRODUCTS products,FILIAL* f,FACTURACAO fact,char* clientsFile,char* productsFile,char* salesFile);

/** @brief Remove todas as estruturas, libertando a memória ocupada por todas ela.
 *
 *  @param CatClients Catálogo de Clients.
 *  @param CatProducts Catálogo de Produtos.
 *  @param arrayFiliais Filiais.
 *  @param fact Facturação.
 *  @return Void.
 */

void freeMemory(CATALOG_CLIENTS CatClients,CATALOG_PRODUCTS CatProducts,FILIAL* arrayFiliais,FACTURACAO fact);

#endif