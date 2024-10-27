#include <getnum.h>
#include <stdio.h>

float potencia(float base, int exponente) {
    if(exponente >= 1)
        return base * potencia(base, exponente - 1);
    return 1.0;
}

int main(void) {
    float nro = getfloat("Ingrese la base: "), exponente = getfloat("Ingrese el exponente: ");
    printf("%f", potencia(nro, exponente));
    return 0;
}

