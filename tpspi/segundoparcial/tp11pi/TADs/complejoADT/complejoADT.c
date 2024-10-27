#include <stdlib.h>
#include "complejoADT.h"

struct complejoCDT{
    double x;
    double y;
};

complejoADT nuevoComp(double real, double compleja) {
    complejoADT nuevo = malloc(sizeof(*nuevo));
    nuevo->x = real;
    nuevo->y = compleja;
    return nuevo;
}

double parteRealComp(complejoADT complejo) {
    return complejo->x;
}

double parteImagComp(complejoADT complejo) {
    return complejo->y;
}

complejoADT sumaComp(complejoADT complejo1, complejoADT complejo2) {
    complejoADT ans = malloc(sizeof(*ans));
    ans->x = complejo1->x + complejo2->y;
    ans->y = complejo1->y + complejo2->y;
    return ans;
}

complejoADT restaComp(complejoADT complejo1, complejoADT complejo2) {
    complejoADT ans = malloc(sizeof(*ans));
    ans->x = complejo1->x - complejo2->x;
    ans->y = complejo1->y - complejo2->y;
    return ans;
}

complejoADT multiplicaComp(complejoADT complejo1, complejoADT complejo2) {
    complejoADT ans = malloc(sizeof(*ans));
    ans->x = complejo1->x * complejo2->x - complejo1->y * complejo2->y;
    ans->y = complejo1->x * complejo2->y + complejo1->y * complejo2->x;
    return ans;
}

/* complejoADT divideComp(complejoADT complejo1, complejoADT complejo2) { */
/* } */

complejoADT conjugadoComp(complejoADT complejo) {
    complejoADT conjugado = malloc(sizeof(*conjugado));
    conjugado->x = complejo->x;
    conjugado->y = -1 * complejo->y;
    return conjugado;
}

void liberaComp(complejoADT complejo) {
    free(complejo);
}


