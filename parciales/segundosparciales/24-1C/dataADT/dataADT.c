#include "dataADT.h"
#include <stdio.h>

struct dataNode {
    elemType element;
    struct dataNode * next;
};

typedef struct dataNode * tData;

struct dataCDT {
    tData localData;
    size_t savedElements;
    cmp fx;
};

dataADT newData(cmp fx) {
    dataADT new = calloc(1, sizeof(struct dataCDT));
    new->fx = fx;
    return new;
}

tData addElementRec(tData list, cmp fx, elemType element, int * added) {
    int comparison;
    if (list == NULL || (comparison = fx(list->element, element)) > 0) {
        tData newNode = malloc(sizeof(struct dataNode));
        newNode->element = element;
        newNode->next = list;
        *added = 1;
        return newNode;
    } else if (comparison < 0) {
        list->next = addElementRec(list->next, fx, element, added);
    }
    *added = 0;
    return list;
}

int addElement(dataADT data, elemType elem) {
    int added = 0;
    data->localData = addElementRec(data->localData, data->fx, elem, &added);
    return added;
}

tData deleteElementRec(tData list, cmp fx, elemType element, int * deleted) {
    int comparison;
    if (list == NULL || (comparison = fx(list->element, element)) > 0) {
        *deleted = 0;
        return list;
    } else if (comparison == 0) {
        tData toReturn = list->next;
        free(list);
        *deleted = 1;
        return toReturn;
    }
    list->next = deleteElementRec(list->next, fx, element, deleted);
    return list;
}

int deleteElement(dataADT data, elemType elem) {
    int deleted = 0;
    data->localData = deleteElementRec(data->localData, data->fx, elem, &deleted);
    return deleted;
}

#define BLOCK 15

elemType * elems(const dataADT data, int (*filter)(elemType), size_t * dim) {
    elemType * vector = NULL;
    *dim = 0;
    size_t i = 0;
    for (tData iterator = data->localData; iterator != NULL; iterator = iterator->next) {
        if (filter(iterator->element)) {
            if (i % BLOCK == 0) {
                vector = realloc(vector, sizeof(elemType) * (i + BLOCK));
            }
            vector[i++] = iterator->element;
        }
    }
    *dim = i;
    if (*dim != 0) vector = realloc(vector, sizeof(elemType) * (*dim));
    return vector;
}
