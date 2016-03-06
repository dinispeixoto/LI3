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

int exist (char * prod, char * client, char** clients, char** products){
    int i,vc=0,vp=0;

    for(i=0;i<171008;i++){
         if(i<16384 && !vc){
         	if(strcmp(client,clients[i])==0) vc=1;

         }
         if(strcmp(prod,products[i])==0) vp=1;


         if(vc && vp) break;
    }

    return (vc && vp);
}

int repartirVerificar (char* line, char** clients,char** products){
    int r=0;
    char *clie,*prod,*token;
    int mes,filial,quant;
    float preco;
    char infoP;
   
    token = strtok(line, " ");
   
   for(int i=0;token != NULL;i++) 
   {
   	  switch(i){
        case 0: prod=token;
        case 1: preco=atof(token);
        case 2: quant=atoi(token); 
        case 3: infoP=token[0];
        case 4: clie=token;
        case 5: mes = atoi(token);
        case 6: filial = atoi (token);
   	  }
      token = strtok(NULL, " ");
   }
    //testSales(preco, quant, infoP, mes, filial) && 
    if(exist(prod,clie,clients,products) ) r=1;
    return r;
}

// Conta quantas linhas do ficheiro com as vendas são válidas.
int valSales(FILE *file,char** clients,char** products){

	char buffer[SIZE_BUF_SALES],*line;
	int validated,r;

	 
	while(fgets(buffer,SIZE_BUF_SALES,file)!=NULL){
		
		line=strtok(buffer,"\r\n");
		r=repartirVerificar(line,clients,products);
		validated+=r;
		printf("%d\n",validated);
    }

	return validated;
}

// 1. APAGAR OS DEFINES QUE NÃO SÃO UTILIZADOS
// 2. A valSales não está feita, faz um bocado da estrutura dela ou assim que eu depois faço o resto se quiseres.
// 3. As funções valProducts e valClients são praticamente iguais, só muda o espaço que usamos para alocar strings, se quiseres junta numa só.
