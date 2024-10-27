#include <stdlib.h>
#include "bagADT.h"

struct elemento {
    elemType valor;
    size_t apariciones;
};

struct node {
    struct elemento info;
    struct node * siguiente;
};

typedef struct node * bList;

struct bagCDT {
    bList primer;
    bList mostPopular;
    compare cmp;
    unsigned int cantidadDistintos;
};

bagADT newBag(compare cmp) {
    bagADT new = calloc(1, sizeof(*new));
    new->cmp = cmp;
    return new;
}

elemType mostPopular(bagADT bag) {
    if (bag == NULL || bag->cantidadDistintos == 0)
        exit(1);
    return bag->mostPopular->info.valor;
}

unsigned int size(const bagADT bag) {
    return bag->cantidadDistintos;
}

void freeBagRec(bList primer) {
    if (primer == NULL)
        return;
    freeBagRec(primer->siguiente);
    free(primer);
}

void freeBag(bagADT bag) {
    freeBagRec(bag->primer);
    bag->primer = NULL;
    bag->mostPopular = NULL;
    free(bag);
}

// Estoy suponiendo que la funcion que me pasan hace la resta entre el primero contra el segundo
unsigned int count(const bagADT bag, elemType elem) {
    bList iterador;
    for (iterador = bag->primer; iterador != NULL; iterador = iterador->siguiente) {
        int comparacion = bag->cmp(iterador->info.valor, elem);
        if (comparacion > 0) {
            return 0;
        } else if (comparacion == 0) {
            return iterador->info.apariciones;
        }
    }
    return 0;
}

bList newMostPopular(bList primer, unsigned int oldPopularity) {
    bList new = primer;
    while (primer != NULL) {
        if (new->info.apariciones < primer->info.apariciones) {
            new = primer;
        }
        if (new->info.apariciones == oldPopularity) return new;
        primer = primer->siguiente;
    }
    return new;
}

bList deleteRec(bList primer, compare cmp, elemType elemento, unsigned int * apariciones, int * reducirBag) {
    int comparacion;
    if (primer == NULL || (comparacion = cmp(primer->info.valor, elemento)) > 0) {
        *apariciones = 0;
        *reducirBag = 0;
    } else if (comparacion < 0) {
        primer->siguiente = deleteRec(primer->siguiente, cmp, elemento, apariciones, reducirBag);
    } else {
        *apariciones = --(primer->info.apariciones);
        if (*apariciones == 0) {
            bList aux = primer->siguiente;
            free(primer);
            *reducirBag = 1;
            return aux;
        }
        *reducirBag = 0;
    }
    return primer;
}

unsigned int delete(bagADT bag, elemType elem) {
    if (bag->mostPopular == NULL || bag->mostPopular->info.apariciones == 0)
        return 0;
    int reducirBag = 0;
    unsigned int apariciones, oldPopularity = bag->mostPopular->info.apariciones;
    bag->primer = deleteRec(bag->primer, bag->cmp, elem, &apariciones, &reducirBag);
    bag->cantidadDistintos -= reducirBag;
    // En este caso si despues de liberar no le asigno NULL a bag->mostPopular, podria estar desref
    // algo que esta liberado
    if (oldPopularity > bag->mostPopular->info.apariciones) {
        bag->mostPopular = newMostPopular(bag->primer, oldPopularity);
    }
    return apariciones;
}

bList addRec(bList primer, compare cmp, elemType aAgregar, bList * agregado) {
    int comparacion;
    if (primer == NULL || (comparacion = cmp(primer->info.valor, aAgregar)) > 0) {
        bList aux = malloc(sizeof(*aux));
        aux->info.apariciones = 1;
        aux->info.valor = aAgregar;
        aux->siguiente = primer;
        *agregado = aux;
        primer = aux;
    } else if (comparacion == 0) {
        ++primer->info.apariciones;
        *agregado = primer;
    } else if (comparacion < 0) {
        primer->siguiente = addRec(primer->siguiente, cmp, aAgregar, agregado);
    }
    return primer;
}

unsigned int add(bagADT bag, elemType elem) {
    bList agregado;
    bag->primer = addRec(bag->primer, bag->cmp, elem, &agregado);
    if (bag->mostPopular == NULL || agregado->info.apariciones > bag->mostPopular->info.apariciones) {
        bag->mostPopular = agregado;
    }
    if (agregado->info.apariciones == 1) {
        bag->cantidadDistintos++;
    }
    return agregado->info.apariciones;
}

