#include "testes.h"

// Testa os produtos 
int testProduct (char* prod){
   int num = atoi(prod+LETRAS_P),i,r=0;

   for(i=0;i<LETRAS_P;i++)
       if(!(isupper(prod[i]))) return 0;

   if(!((num>=1000) && (num<=1999))) return 0;
  
   return 1;
}

// Testa os Clientes
 int testClient(char* client){
    int num = atoi(client+LETRAS_C),r=0;

    if(isupper(client[0]) && (num>=1000) && (num<=5000))r++;

    return r;
 }

<<<<<<< HEAD
/ Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array.
int valSales(FILE *file,char** clients,char** products,Vendas* sales){

  char buffer[SIZE_BUF_SALES],*line;
  int validated=0,r;/ Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array.
int valSales(FILE *file,char** clients,char** products,Vendas* sales){

  char buffer[SIZE_BUF_SALES],*line;
  int validated=0,r;/ Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array.
int valSales(FILE *file,char** clients,char** products,Vendas* sales){

  char buffer[SIZE_BUF_SALES],*line;
  int validated=0,r;
=======

>>>>>>> 7c9efc798723f643ba551f22a4817e8d9fe420f4
// Testa as diferentes cenas das Vendas.
// Preço de 0 a 999.99;
// Quantidade de 0 a 200;
// Caracter a informar se o preço é normal(N) ou em promoção(P);
// Mês (1 a 12);
// Filial (1 a 3);
int testSales(float price, int quantity, char infoPromo, int month, int filial){

  if(price < 0 || price > 999.99) return 0;
  else if(quantity < 1 || quantity > 200) return 0;
  else if(infoPromo != 'P' && infoPromo != 'N') return 0;
  else if(month < 1 || month > 12) return 0;
  else if(filial < 1 || filial > 3) return 0;
  else return 1;
}