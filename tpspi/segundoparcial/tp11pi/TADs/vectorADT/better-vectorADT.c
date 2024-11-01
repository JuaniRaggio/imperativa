#include "vectorADT.h"
#include <stdio.h>
#include <stdlib.h>

typedef int (*fCompare)(elemType, elemType);

typedef struct {
    elemType valor;
    char ocupado;
} infoElemento;

struct vectorCDT {
    infoElemento *elemento;
    fCompare cmp;
    size_t espacio;
    size_t dim;
    size_t guardados;
};

vectorADT newVector(int (*compare)(elemType source, elemType target)) {
    vectorADT new = calloc(1, sizeof(*new));
    new->cmp = compare;
    return new;
}

void freeVector(vectorADT v) {
    free(v->elemento);
    free(v);
}

int getIdx(vectorADT v, elemType elem) {
    int i;
    for (i = 0; i < v->dim; ++i)
        if (v->elemento[i].ocupado == 1 && v->cmp(v->elemento[i].valor, elem) == 0)
            return i;
    return -1;
}

void deleteElement(vectorADT v, size_t index) {
    if (index >= v->dim || v->elemento[index].ocupado == 0)
        return;
    v->elemento[v->dim].ocupado = 0;
    v->guardados--;
}

int elementCount(vectorADT v) { return v->guardados; }

// Rehacer
/* size_t put(vectorADT v, elemType *elems, size_t dim, size_t index) { */
/*     for (int i = index, j = 0; j < dim && i < v->espacio; ++i, ++j) { */
/*         if (v->espacio <= i) { */
/*             size_t vacios = v->espacio; */
/*             v->espacio += dim; */
/*             v->elemento = realloc(v->elemento, sizeof(infoElemento) * v->espacio); */
/*             while (vacios < v->espacio) { */
/*                 v->elemento[vacios++].ocupado = 0; */
/*             } */
/*         } */
/*         if (v->elemento[i].ocupado == 0) { */
/*             v->elemento[i].valor = elems[i]; */
/*             v->elemento[i].ocupado = 1; */
/*             v->dim += i >= dim ? 1:0; */
/*             v->guardados++; */
/*         } */
/*     } */
/*     return v->guardados; */
/* } */
