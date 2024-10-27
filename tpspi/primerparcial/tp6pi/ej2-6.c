#include "../../fcatedra/getnum.h"
#include <math.h>
#include <stdio.h>
#define IMPRIMEVALORES(a,b) printf("El resultado es: %d/%d", a, b);

unsigned MCD(int x, int y){
    int aux;
    while(y){
        aux = y;
        y = x % y;
        x = aux;
    }
    return aux;
}

void simplifica(int f[]){
    int divisor = MCD(f[0], f[1]);
    f[0] /= divisor;
    f[1] /= divisor;
}

void suma(int f1[], int f2[]){
    int divisor = MCD(f1[1], f2[1]);
    f1[0] = f1[0] * divisor/f1[1] + f2[0] * divisor/f2[1];
    f1[1] = divisor;
}

void solicitaValores(int f[]){
    f[0] = getint("Introduzca el numerador: ");
    f[1] = getint("Introduzca su respectivo denominador");
}

int menu(void) {
    int opcion = getint("Introduzca la opcion que desea:\n"
               "1 - Si desea simplificar una fraccion.\n"
               "2 - Si desea sumar dos fracciones.\n"
               "3 - Si desea finalizar la ejecucion");
    return opcion;
}

int main(void){
    int f1[2], f2[2], aux, opcion;
    do{
    opcion = menu();
    switch(opcion){
        case 1:
        solicitaValores(f1);
        simplifica(f1);
            IMPRIMEVALORES(f1[0], f1[1]);
        break;
        case 2:
        solicitaValores(f1);
        solicitaValores(f2);
        suma(f1, f2);
            IMPRIMEVALORES(f1[0], f1[1]);
        break;
    }
    }while(opcion != 3);
        return 0;
}

