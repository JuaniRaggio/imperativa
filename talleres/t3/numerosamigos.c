#include "../../fcatedra/getnum.h"
#include <stdio.h>

int esAmigo(int a, int b){
    int suma = 0, divisores = a - 1;
    while(divisores >= 1){
        if(a % divisores == 0)
            suma += divisores;
        --divisores;
    }
    return suma == b;
}

int numerosAmigos(int a, int b){
    return esAmigo(a, b) && esAmigo(b, a);
}

int main(){
    int n1 = getint("Ingrese el primer numero: ");
    int n2 = getint("Ingrese el segundo numero: ");
    printf("%s amigos!",numerosAmigos(n1, n2) ? "Son":"No son");
    return 0;
}

