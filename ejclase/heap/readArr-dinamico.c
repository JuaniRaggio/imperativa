#include <stdlib.h>
#include "../../pi/fcatedra/getnum.h"

float * readArray(size_t * dim){
    int n;
    do {
        n = getint("Ingrese la cantidad de numeros que va a ingresar");
    } while(n <= 0);
    *dim = n;
    float * vec = malloc(n * sizeof(*vec));
    for(int i = 0; i < n; ++i)
        vec[i] = getint("Ingrese un numero: ");
    // Si o si, si voy a retornar un vector tiene que estar en el heap
    return vec;
}

