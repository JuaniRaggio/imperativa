#include <stdio.h>
#include <assert.h>
#include "../../fcatedra/getnum.h"

int MCD(int x, int y){
    int aux;
    while(y != 0){
        aux = y;
        y = x%y;
        x = aux;
    }
    // Nos quedamos con el ultimo resto
    return aux;
}

int menu(){
    int opcion = getint("Introduzca:\n"
                        "1 - Si desea simplificar una fraccion\n"
                        "2 - Si desea sumar dos fracciones\n"
                        "3 - Si desea finalizar la ejecucion\n");
    return opcion;
}

int main(){
    int opcion, den, n1, d1, n2, d2;
    do{
        opcion = menu();
        switch(opcion){
            case 1:
                n1 = getint("Ingrese el numerador\n");
                d1 = getint("Ingrese el denominador\n");
                assert(d1 != 0);
                den = MCD(n1, d1);
                n1 /= den;
                d1 /= den;
                printf("%d/%d\n", n1, d1);
            break;
            case 2:
                n1 = getint("Ingrese el numerador del primer numero\n");
                d1 = getint("Ingrese el denominador del primer numero\n");
                assert(d1 != 0);
                n2 = getint("Ingrese el numerador del segundo numero\n");
                d2 = getint("Ingrese el denominador del segundo numero\n");
                assert(d2 != 0);
                den = MCD(d1, d2);
                n1 = n1*(den/d1) + n2*(den/d2);
                d1 = MCD(n1, den);
                n1 /= d1;
                den /= d1;
                printf("%d/%d\n", n1, den);
            break;
        }
    }while(opcion != 3);
    return 0;
}
