#include <stdio.h>
#include "../fcatedra/getnum.h"
#include <math.h>


int lugar (int num, int pos);


int
main( void )
{
	int boleto, esCapicua=1;
	int  j;
    
    do{
    	boleto = getint("Ingrese un número de 5 dígitos:");
    }while(boleto > 99999);

	for (j=1; j<=2; j++)
		if ( lugar(boleto, j) != lugar(boleto,5-j+1))
		{	
 			esCapicua=0;
			break;
		}
	printf("El boleto %ses capicúa",(esCapicua)? "":"no ");
	return 0;
}


int 
lugar( int num, int pos )
{	
return (num / (int)pow(10, pos-1)) % 10;
}
