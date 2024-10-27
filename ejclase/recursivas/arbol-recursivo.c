#include <stdio.h>
#include <getnum.h>

float arbolRecursivo(float altura, float aGraficar) {
    if (aGraficar > altura)
        return 0;
    return 1 + 2 * arbolRecursivo(altura/2, aGraficar);
}

int main(void) {
    int altura = getfloat("Ingrese la altura: "), aGraficar = getfloat("Ingrese la altura minima a graficar: ");
    printf("La cantidad de ramas posibles a dibujar es: %f", arbolRecursivo(altura, aGraficar));
    return 0;
}

