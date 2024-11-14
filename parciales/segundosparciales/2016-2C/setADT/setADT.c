#include <string.h>
#include <stdlib.h>
#include "setADT.h"

typedef int (*cmp)(void *, void *);

typedef struct node * TList;

typedef struct node {
    void * element;
    TList tail;
} TNode;

struct setCDT {
    TList set;
    TList max;
    TList min;
    TList last;
    size_t pSize;
    size_t listSize;
    cmp fx;
};

setADT newSet(cmp fx, size_t size) {
    setADT new = calloc(1, sizeof(struct setCDT));
    new->pSize = size;
    new->fx = fx;
    return new;
}

int size(const setADT set) {
    return set->listSize;
}

void * mkcpy(const void * element, size_t size) {
    void * cpy = malloc(size);
    memcpy(cpy, element, size);
    return cpy;
}

TList addSetRec(TList set, cmp fx, size_t pSize, size_t * size, TList * max, TList * min, TList * last, void * elem) {
    int cmp;
    if (set == NULL || (cmp = fx(set->element, elem)) > 0) {
        TList new = malloc(sizeof(TNode));
        new->element = malloc(pSize);
        memcpy(new->element, elem, pSize);
        new->tail = set->tail;
        ++*size;
        *last = new;
        if ((fx(new->element, (*max)->element)) > 0) *max = new;
        else if ((fx(new->element, (*min)->element)) < 0) *min = new;
        return new;
    } else if (cmp < 0) {
        set->tail = addSetRec(set->tail, fx, pSize, size, max, min, last, elem);
        return set;
    }
    return set;
}

int add(setADT set, void * elem) {
    set->set = addSetRec(set->set, set->fx, set->pSize, &set->listSize, &set->min, &set->max, &set->last, elem);
    return set->listSize;
}

void * max(const setADT set) {
    return mkcpy(set->max, set->pSize);
}

void * min(const setADT set) {
    return mkcpy(set->min, set->pSize);
}

void * last(const setADT set) {
    return mkcpy(set->last, set->pSize);
}

void ** setToArray(const setADT set, size_t * dim, size_t * pSize) {
    *pSize = set->pSize;
    void ** array = malloc(sizeof(void *) * set->listSize);
    int i = 0;
    for (TList aux = set->set; i < set->listSize; ++i, aux = aux->tail) {
        /* memcpy((char *)*array + i, mkcpy(aux->element, set->pSize), sizeof(void *)); */
        array[i] = mkcpy(aux->element, set->pSize);
    }
    return array;
}

