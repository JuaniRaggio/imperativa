#include "vectorADT.h"
#include <stdlib.h>
#include <stdbool.h>

// Necesitamos un vector que nos diga si una posicion esta ocupada o no
// ==> Nos va a serivir para la funcion put
// A la vez necesitamos el vector con los valores

// Necesitamos que el usuario nos pase una funcion de comparacion para getIdx
// sino no podemos saber si encontramos o no el elemento por ser elementos genericos

typedef int (*fcompare)(elemType, elemType);

struct vectorCDT {
    elemType * vector_valores;
    char * vector_ocupados;
    unsigned int espacio_guardado;
    unsigned int cantidad_insertada;
    fcompare cmp;
};

vectorADT newVector(int (*compare)(elemType source, elemType target)) {
    vectorADT new = calloc(1, sizeof(*new));
    new->cmp = compare;
    return new;
}

size_t put(vectorADT v, elemType * elems, size_t dim, size_t index) {
    size_t guardados = 0;
    for (int i = 0; i < dim; ++i) {
        if (i + index + dim > v->espacio_guardado) {
            unsigned int espacio_anterior = v->espacio_guardado;
            v->espacio_guardado = i + index + dim;
            v->vector_valores = realloc(v->vector_valores, sizeof(elemType) * v->espacio_guardado);
            v->vector_ocupados = realloc(v->vector_ocupados, v->espacio_guardado);
            while (espacio_anterior < v->espacio_guardado) {
                v->vector_ocupados[espacio_anterior++] = false;
            }
        }
        if (v->vector_ocupados[i + index] == 0) {
            v->vector_valores[i + index] = elems[i];
            v->vector_ocupados[i + index] = true;
            ++v->cantidad_insertada;
            ++guardados;
        }
    }
    return guardados;
}

int getIdx(vectorADT v, elemType elem) {
    for (int i = 0; i < v->espacio_guardado; ++i) {
        if (v->vector_ocupados[i] == true && v->cmp(v->vector_valores[i], elem) == 0) {
            return i;
        }
    }
    return -1;
}

void freeVector(vectorADT v) {
    free(v->vector_ocupados);
    free(v->vector_valores);
    free(v);
}

void deleteElement(vectorADT v, size_t index) {
    if (index >= v->espacio_guardado)
        return;
    v->cantidad_insertada -= v->vector_ocupados[index];
    v->vector_ocupados[index] = false;
    return;
}

int elementCount(vectorADT v) {
    return v->cantidad_insertada;
}

