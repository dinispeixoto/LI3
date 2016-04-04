#include "testes.h"
#include "avl.h"
#include "valida.h"
#include "CatClients.h"
#include "CatProducts.h"

// Conta quantas linhas dos ficheiros (Clientes e Produtos) são válidas, e aloca num array.
// Vamos reservar um array em que as strings têm diferente tamanho:
// Array de Clientes : tamanho = SIZE_CLIENTS
// Array de Produtos : tamanho = SIZE_PRODUCTS
Avl* valCliProd(FILE *file, Avl* estrutura,int *validated){
 
	char buffer[SIZE_BUFFER],*line;
	
	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

		line=strtok(buffer,"\r\n");

		// muda isto para processar um array 
		//*estrutura=insert(*estrutura,line);
		//(*validated)++;
	}

	return estrutura;
}

// Conta quantas linhas do ficheiro com as vendas são válidas, e aloca num array.
int valSales(FILE *file,CATOLOG_CLIENTS clients,CATOLOG_PRODUCTS  products,Vendas* sales){

	char buffer[SIZE_BUF_SALES],*line;
	int validated=0,r;
	char *clie[SIZE_CLIENTS],*prod[SIZE_PRODUCTS];
	int month,filial,quant;
	double price;
	char infoP;

	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line = strtok(buffer,"\r\n");

		// verificar, em caso positivo alocar espaço para a string e copia-la para o array.
		r = partCheck(line,clients,products,clie,prod,&month,&filial,&quant,&price,&infoP);
		if(r){
			sales[validated] = malloc(sizeof(struct vendas));
			strcpy(sales[validated]->client,*clie);
			strcpy(sales[validated]->product,*prod);
			sales[validated]->price=price;
			sales[validated]->quantity=quant;
			sales[validated]->infoPromo=infoP;
			sales[validated]->filial=filial;
			sales[validated]->month=month;
			validated+=r;
		}
	}
	return validated;
}

// ############################################## FUNÇÕES AUXILIARES ################################################################################################################


//Função auxiliar que verifica se um dado produto e cliente existem.
int exist(char* line, Avl estrutura){

	int r=0;

    int s=strcmp(estrutura->code,line);
    
    if(s==0) return 1;
	else if(s>0 && estrutura->left!=NULL)
		r=exist(line,estrutura->left);

	else if (estrutura->right!=NULL)
		r=exist(line,estrutura->right);

    return r;
}

//Função que reparte um linha de venda, e verifica se a linha é válida,ou seja, se o produto e cliente exitem, 
//e se os outros parametros estao corretos. 
int partCheck(char* line, CATOLOG_CLIENTS clients,CATOLOG_PRODUCTS  products,char** clie,char** prod,int *month,int *filial,int *quant,double *price,char *infoP){
	char *token;
	int r=0, i;


			
	token = strtok(line, " ");
   
	for(i=0;token != NULL;i++){
		switch(i){
			case 0: *prod = token; break;
			case 1: *price = atof(token); break;
			case 2: *quant = atoi(token); break;
			case 3: *infoP = token[0]; break;
			case 4: *clie = token; break;
			case 5: *month = atoi(token); break;
			case 6: *filial = atoi(token); break;
		}
			token = strtok(NULL, " ");
	}

	int indexClient =  *clie[0]-'A';
	int indexProduct = *prod[0]-'A';
    Avl auxClient = getC(clients,indexClient);
	Avl auxProduct = getP(products,indexProduct);


	if(exist(*prod,auxProduct) && exist(*clie, auxClient) && testSales(*price, *quant, *infoP, *month, *filial)) r=1;
	return r;
}

// Calcula o comprimentos dos Arrays de Clientes de Produtos.
