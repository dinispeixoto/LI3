#include "valida.h"

// Conta quantas linhas do ficheiro com os clientes são válidas.
int valClients(FILE *file){
	
	int validated=0; 
	char letter;
	int number;

	while(fscanf(file,"%c%d\n",&letter,&number)!=EOF)
		if(isupper(letter) && (number>=1000) && (number<=5000)) 
			validated++; 

	return validated;
}

// Conta quantas linhas do ficheiro com os produtos são válidas.
int valProducts(FILE *file){

	int validated=0;
	char firstLetter,secondLetter;
	int number;
	char letters[2]; // Futuramente temos de juntar os dois caracteres numa string, provavelmente.


	while(fscanf(file,"%c%c%d\n",&firstLetter,&secondLetter,&number)!=EOF)
		if(isupper(firstLetter) && isupper(secondLetter) && (number>=1000) && (number<=1999)) 
			validated++;

	return validated;
}

// Conta quantas linhas do ficheiro com as vendas são válidas.
int valSales(FILE *file){

	int validated=0,quantity, month;
	int filial; // Filial ou Branch????? 
	char prod[6], client[5];
	float price;
	char infoPromo;

	// Código do Produto | Preço | Quantidade | Normal ou Promoção | Código do Cliente | Mês da Compra | Filial // 
	while(fscanf(file,"%s %f %d %c %s %d %d", prod, &price, &quantity, &infoPromo, client, &month, &filial)!=EOF){
		
		if(testSales(prod,price,quantity,infoPromo,client,month,filial)) 
			validated++;
    }
	return validated;
}

/*************************************************/
// A cena do Atoi nao sei se da, mas penso que sim
int testProduct (char* prod){
   int num = atoi(prod+LetrasP),i,r=0;

   for(i=0;i<2;i++)
       if(!(isupper(prod[i]))) return 0;

   /* OU o for ou esta merda xD
   if(!(isupper(prod[0]) && isupper(prod[1] && (num>=1000) && (num<=1999))) return 0;
   */
   	
   if(!((num>=1000) && (num<=1999))) return 0;
	
   return 1;
}

 int testClient(char* client){
    int num = atoi(client+LetrasC),r=0;
    
    if(isupper(client[0]) && (num>=1000) && (num<=5000))r++;

    return r;
 }
/**************************************************/

// Testa as diferentes cenas das Vendas.
// Código do produto bem estruturado;
// Preço de 0 a 999.99;
// Quantidade de 0 a 200;
// Caracter a informar se o preço é normal(N) ou em promoção(P);
// Código do cliente bem estruturado;
// Mês (1 a 12);
// Filial (1 a 3);
int testSales(char* product, float price, int quantity, char infoPromo, char *client, int month, int filial){

	// falta testar o código do produto e o código do cliente.
	if(!(testProduct(product))) return 0;
	else if(price < 0 || price > 999.99) return 0;
	else if(quantity < 1 || quantity > 200) return 0;
	else if(infoPromo != 'P' && infoPromo != 'N') return 0;
	else if(!(testClient(client))) return 0;
	else if(month < 1 || month > 12) return 0;
	else if(filial < 1 || filial > 3) return 0;
	else return 1;
}

