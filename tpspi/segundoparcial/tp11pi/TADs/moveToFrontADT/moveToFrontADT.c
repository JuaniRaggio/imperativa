#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "moveToFrontADT.h"

struct node {
    elemType element;
    struct node * prevIncreasing;
    struct node * nextIncreasing;
    struct node * prevInQueue;
    struct node * nextInQueue;
};

typedef struct node * frontList;

struct moveToFrontCDT {
    frontList firstIncreasing;
    frontList firstQueue;
    frontList lastIncreasing;
    frontList lastQueue;
    frontList iterator;
    compare cmp;
    size_t elementsInList;
};

moveToFrontADT newMoveToFront(compare cmp) {
    moveToFrontADT new = calloc(1, sizeof(*new));
    new->cmp = cmp;
    return new;
}

void freeRec(frontList list) {
    if (list == NULL)
        return;
    freeRec(list->nextIncreasing);
    free(list);
}

void freeMoveToFront(moveToFrontADT moveToFront) {
    freeRec(moveToFront->firstIncreasing);
    free(moveToFront);
}

/* Se ubica al principio del conjunto, para poder iterar sobre el mismo */
void toBegin(moveToFrontADT moveToFront) {
    moveToFront->iterator = moveToFront->firstQueue;
}

/* Retorna 1 si hay un elemento siguiente en el iterador, 0 si no */
int hasNext(moveToFrontADT moveToFront) {
    return moveToFront->iterator != NULL;
}

/* Retorna el siguiente elemento. Si no hay siguiente elemento, aborta */
elemType next(moveToFrontADT moveToFront) {
    if (!hasNext(moveToFront)) {
        printf("Error en la linea %d en el archivo %s en la funcion %s. No se llama a hasNext() antes de iterar", __LINE__, __FILE__, __func__);
        exit(1);
    }
    elemType retValue = moveToFront->iterator->element;
    moveToFront->iterator = moveToFront->iterator->nextInQueue;
    return retValue;
}

unsigned int size(moveToFrontADT moveToFront) {
    return moveToFront->elementsInList;
}

frontList addElementRec(frontList list, compare cmp, elemType element, frontList * lastQueue, frontList * lastIncreasing, int * added) {
    int comparison;
    if (list == NULL || (comparison = cmp(list->element, element)) > 0) {
        frontList newElement = malloc(sizeof(*newElement));
        newElement->element = element;
        // El problema esta aca
        // Si tenemos que agregar el elemento en el ultimo lugar, hace que prevIncreasing
        // del que agreguemos sea NULL y no deberia ser asi
        if (*lastIncreasing != NULL)
            (*lastIncreasing)->nextIncreasing = newElement;
        newElement->prevIncreasing = *lastIncreasing;
        *lastIncreasing = newElement;
        if (list != NULL)
            list->prevIncreasing = newElement;
        newElement->nextIncreasing = list;
        newElement->prevInQueue = *lastQueue;
        newElement->nextInQueue = NULL;
        if (*lastQueue != NULL) 
            (*lastQueue)->nextInQueue = newElement;
        *lastQueue = newElement;
        *added = 1;
        return newElement;
    } else if (comparison < 0) {
        list->nextIncreasing = addElementRec(list->nextIncreasing, cmp, element, lastQueue, lastIncreasing, added);
        return list;
    }
    *added = 0;
    return list;
}

unsigned int add(moveToFrontADT moveToFront, elemType elem) {
    int added = 0;
    moveToFront->firstIncreasing = 
        addElementRec(moveToFront->firstIncreasing, moveToFront->cmp, elem, &moveToFront->lastQueue, &moveToFront->lastIncreasing, &added);
    moveToFront->elementsInList += added;
    if (moveToFront->firstQueue == NULL) {
        moveToFront->firstQueue = moveToFront->firstIncreasing;
        moveToFront->lastQueue = moveToFront->firstIncreasing;
    }
    return added;
}

elemType * get(moveToFrontADT moveToFront, elemType elem) {
    frontList aux;
    for (aux = moveToFront->firstIncreasing; aux != NULL; aux = aux->nextIncreasing) {
        int comparison = moveToFront->cmp(aux->element, elem);
        if (comparison > 0) {
            return NULL;
        } else if (comparison == 0) {
            if (aux->prevInQueue != NULL) {
                aux->prevInQueue->nextInQueue = aux->nextInQueue;
                if (moveToFront->lastQueue == aux) {
                    moveToFront->lastQueue = moveToFront->lastQueue->prevInQueue;
                    moveToFront->lastQueue->nextInQueue = NULL;
                }
            }
            if (aux->nextInQueue != NULL)
                aux->nextInQueue->prevInQueue = aux->prevInQueue;
            aux->nextInQueue = moveToFront->firstQueue;
            if (moveToFront->firstQueue != NULL)
                moveToFront->firstQueue->prevInQueue = aux;
            moveToFront->firstQueue = aux;
            aux->prevInQueue = NULL;
            elemType * retValue = malloc(sizeof(elemType));
            *retValue = aux->element;
            return retValue;
        }
    }
    return NULL;
}


