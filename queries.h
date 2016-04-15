#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "facturacao.h"
#include "filial.h"

DADOS querie3(FACTURACAO,int,char*,int );
GROUP_PRODUCTS querie4(FACTURACAO,int*,int);
DADOS_FILIAL querie5(FILIAL,DADOS_FILIAL,char*,int);
DADOS querie6(FACTURACAO,int,int);
#endif