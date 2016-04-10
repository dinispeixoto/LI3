#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "avl.h"
#include "Sales.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "readFiles.h"
#include "facturacao.h"

/* Main -> Gerar estruturas que vão armazenar os dados em memória */
int main(){	
	
	CATALOG_CLIENTS CatClients = initClients();
	CATALOG_PRODUCTS CatProducts = initProducts();
	FACTURACAO fact = initF();
	SALES Sales = initSales();

	getFile(CatClients,CatProducts,Sales,fact);	

	/*##########################TESTES(Querie3)###################################### FUNCIONA
	getchar();
	int i;
	double cont=0;
	int cont2=0;

	DADOS d=querie3(fact,5,"AF1184",1);

	for(i=0;i<3;i++){
		printf("Filial %d: Price-> %f | Quant -> %d\n",i,getDadosP(d)[i],getDadosQ(d)[i]);
		cont+=getDadosP(d)[i];
		cont2+=getDadosQ(d)[i];
	}
	printf("TotalpriceMes -> %f\n",cont );
	printf("TotalquantMes -> %d\n",cont2);
	*/

	/*##########################TESTES(Querie4(TOTAIS e Filiais))###################################### FUNCIONA*/
	//SOU UM GENIO CRL
	getchar();
	int a,i;
	GROUP_PRODUCTS f1;
	//for(i=1;i<4;i++){
	//a=0;
	for(i=1;i<4;i++){
	a=0;	
	f1 = querie4(fact,&a,i);

	//printGP(f1,a);
	printf("%d\n",a);
	}
	//}
	/*##########################TESTES(Querie6)###################################### FUNCIONA
	getchar();
	int i;
	double cont=0;
	int cont2=0;

	DADOS d=querie6(fact,1,12);

	printf("TotalpriceMes -> %f\n",getDadosTP(d));
	printf("TotalquantMes -> %d\n",getDadosTQ(d));
	*/

	return 0;
}