#include "valida.h"

// Conta quantas linhas do ficheiro com os clientes são válidas, e aloca num array.
int valClients(FILE *file, char** array){
	
	int validated=0; 
	char buffer[SIZE_BUFFER],*line;


	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

	 	//strtoken 
	 	line=strtok(buffer,"\r\n");

	 	//alocar espaço para a string e copia-la para o array
	 	array[validated] = (char*)malloc(SIZE_CLIENTS * sizeof(char));
	 	strcpy(array[validated],line);
	 	validated++;
	 }
	 	
	return validated;
}

// Conta quantas linhas do ficheiro com os produtos são válidas, e aloca num array.
int valProducts(FILE *file, char** array){
	
	int validated=0; 
	char buffer[SIZE_BUFFER],*line;


	while(fgets(buffer,SIZE_BUFFER,file)!=NULL){

	 	//strtoken 
	 	line=strtok(buffer,"\r\n");

	 	//alocar espaço para a string e copia-la para o array
	 	array[validated] = (char*)malloc(SIZE_PRODUCTS * sizeof(char));
	 	strcpy(array[validated],line);
	 	validated++;
	 }
	 	
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
		
		//if(testSales(prod,price,quantity,infoPromo,client,month,filial)) 
			validated++;
    }
	return validated;
}

// 1. APAGAR OS DEFINES QUE NÃO SÃO UTILIZADOS
// 2. A valSales não está feita, faz um bocado da estrutura dela ou assim que eu depois faço o resto se quiseres.
// 3. As funções valProducts e valClients são praticamente iguais, só muda o espaço que usamos para alocar strings, se quiseres junta numa só.
