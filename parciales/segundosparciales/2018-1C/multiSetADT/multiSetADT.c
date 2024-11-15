#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "multiSetADT.h"

typedef struct node * TList;

struct node {
    elemType element;
    size_t views;
    struct node * next;
};

struct multiSetCDT {
    TList set;
    size_t diferent;
    cmp fx;
};

multiSetADT newMultiSet(cmp fx) {
    multiSetADT new = calloc(1, sizeof(struct multiSetCDT));
    new->fx = fx;
    return new;
}

unsigned int size(const multiSetADT multiSet) {
    return multiSet->diferent;
}

static TList lookelem(TList list, cmp fx, elemType element, size_t * views) {
    int comparison;
    if (list == NULL || (comparison = fx(list->element, element)) > 0) {
        *views = 0;
        return NULL;
    } else if (comparison == 0) {
        *views = list->views;
        return list;
    }
    return lookelem(list->next, fx, element, views);
}

unsigned int count(const multiSetADT multiSet, elemType elem) {
    size_t count;
    lookelem(multiSet->set, multiSet->fx, elem, &count);
    return count;
}

TList removeNode(TList list) {
    TList aux = list->next;
    free(list);
    return aux;
}

TList removeRec(TList set, cmp fx, elemType element, int * count, bool removeAll) {
    int comparison;
    if (set == NULL || (comparison = fx(set->element, element)) > 0) {
        *count = 0;
        return set;
    } else if (comparison == 0) {
        *count = --set->views;
        if (*count == 0 || removeAll) set = removeNode(set);
        return set;
    }
    set->next = removeRec(set->next, fx, element, count, removeAll);
    return set;
}

int removePrime(multiSetADT multiSet, elemType elem) {
    int count;
    multiSet->set = removeRec(multiSet->set, multiSet->fx, elem, &count, false);
    if (count == 0)
        multiSet->diferent--;
    return count;
}

void removeAll(multiSetADT multiSet, elemType elem) {
    int removed = 2;
    multiSet->set = removeRec(multiSet->set, multiSet->fx, elem, &removed, true);
    if (removed == 1) multiSet->diferent--;
}

elemType * minElements(const multiSetADT multiSet, int * dim) {
    *dim = 0;
    if (multiSet->diferent == 0) return NULL;
    elemType * vector = malloc(sizeof(elemType) * multiSet->diferent);
    int i = 0, min = multiSet->set->views;
    for (TList iterator = multiSet->set; iterator != NULL; iterator = iterator->next) {
        if (min > iterator->views) {
            i = 0;
            min = iterator->views;
        }
        if (min == iterator->views) {
            vector[i] = iterator->element;        
            ++i;
        }
    }
    *dim = i;
    vector = realloc(vector, sizeof(elemType) * i);
    return vector;
}

TList addRec(TList list, cmp fx, elemType element, size_t * count) {
    int comparison;
    if (list == NULL || (comparison = fx(list->element, element)) > 0) {
        TList new = malloc(sizeof(struct node));
        new->element = element;
        new->views = 1;
        new->next = list;
        *count = new->views;
        return new;
    } else if (comparison == 0) {
        *count = ++list->views;
        return list;
    }
    list->next = addRec(list->next, fx, element, count);
    return list;
}

unsigned int add(multiSetADT multiSet, elemType elem) {
    size_t count;
    multiSet->set = addRec(multiSet->set, multiSet->fx, elem, &count);
    if (count == 1) ++multiSet->diferent;
    return count;
}

