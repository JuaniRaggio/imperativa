#include <stdio.h>
#include "../fcatedra/getnum.h"
#include <math.h>


int lugar (int num, int pos);

int cuentaDigitos(int numero);

int
main( void )
{
	int boleto, esCapicua=1;
	int  j, digitos;
	
	boleto = getint("Ingrese un número de 5 dígitos:");

    digitos = cuentaDigitos(boleto);

	for (j = 1; j<= digitos; j++)
		if ( lugar(boleto, j) != lugar(boleto, digitos-j+1))
		{	
 			esCapicua=0;
			break;
		}
	printf("El boleto %ses capicúa",(esCapicua)? "":"no ");
	return esCapicua;
}

int cuentaDigitos(int numero){
    int i;
    for(i = 0; numero > 0; ++i){
        numero /= 10;
    }
    return i;
}

int 
lugar( int num, int pos )
{	
return (num / (int)pow(10, pos-1)) % 10;
}
