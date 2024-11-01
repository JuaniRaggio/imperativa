#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rankingADT.h"

#define BLOCK 10
#define ADDED -1

// Quizas tiene mas sentido que reciba solo el puntero que tiene que modificar y no el rankingADT entero
// pero como es una macro y no hace una copia, no cambia en terminos de eficiencia
#define newrank(toChange, oldRank) {\
    pElement aux = toChange->rankVector[oldRank - 1];\
    toChange->rankVector[oldRank - 1] = toChange->rankVector[oldRank];\
    toChange->rankVector[oldRank] = aux;\
    toChange->rankVector[oldRank]->rank = (oldRank - 1);\
    toChange->rankVector[oldRank - 1]->rank = oldRank;\
}

struct elementInfo {
    elemType value;
    size_t rank;
};

typedef struct elementInfo * pElement;

struct node {
    pElement element;
    struct node * next;
};

typedef struct node * elementList;

struct rankingCDT {
    elementList rankList;
    pElement * rankVector;
    compare cmp;
    size_t last;
    size_t size;
};

elementList addToRanking(elementList rankList, pElement ** rankVector, compare cmp, elemType elem, long int * add, size_t * lastAdded, size_t * size) {
    int compare;
    if (rankList == NULL || (compare = cmp(rankList->element->value, elem)) > 0) {
        elementList newElement = malloc(sizeof(*newElement));
        newElement->element = malloc(sizeof(struct elementInfo));
        memcpy(&newElement->element->value, &elem, sizeof(elem));
        newElement->element->rank = *lastAdded;
        if (*size <= *lastAdded) {
            *size += BLOCK;
            *rankVector = realloc(*rankVector, sizeof(**rankVector) * *size);
        }
        (*rankVector)[*lastAdded++] = newElement->element;
        *add = ADDED;
        return newElement;
    } else if (compare < 0) {
        rankList->next = addToRanking(rankList->next, rankVector, cmp, elem, add, lastAdded, size);
        return rankList;
    }
    *add = rankList->element->rank;
    return rankList;
}

int addOnly(rankingADT ranking, elemType elem) 
// Esta funcion tiene que simplemente agregar un elemento al ranking y
// tocar sus paramentros como size, last added, etc.
// Si el elemento ya estaba, retorna su rank.
// Si no estaba, retorna -1 => Lo agrego.
{
    long int add = ADDED;
    ranking->rankList = addToRanking(ranking->rankList, &ranking->rankVector, ranking->cmp, elem, &add, &ranking->last, &ranking->size);
    return add;
}

rankingADT newRanking(elemType elems[], size_t dim, compare cmp) {
    rankingADT new = malloc(sizeof(struct rankingCDT));
    new->cmp = cmp;
    new->size = dim;
    new->last = 0;
    new->rankVector = dim > 0 ? malloc(sizeof(pElement) * new->size):NULL;
    int i, newElem;
    for (i = 0; i < dim; ++i) {
        if ((newElem = addOnly(new, elems[i])) != ADDED) {
            newrank(new, newElem);
        }
    }
    return new;
}

void addRanking(rankingADT ranking, elemType elem) {
    addOnly(ranking, elem);
}

size_t size(const rankingADT ranking) {
    return ranking->last;
}

int getByRanking(rankingADT ranking, size_t n, elemType * elem) {
    --n;
    if (n >= ranking->last) {
        return -1;
    }
    memcpy(ranking->rankVector[n], elem, sizeof(elemType));
    newrank(ranking, n);
    return 1;
}


elemType * getTopRanking(const rankingADT ranking, size_t * top) {
    if (ranking->last == 0) {
        *top = 0;
        return NULL;
    }
    elemType * topRanking = malloc(sizeof(*topRanking) * (ranking->last + 1));
    int i;
    for (i = 0; i < *top && i < ranking->last; ++i) {
        memcpy(&topRanking[i], &ranking->rankVector[i]->value, sizeof(elemType));
    }
    *top -= i;
    return topRanking;
}

int containsRec(elementList rankList, pElement * rankVector, compare cmp, elemType toFind) {
    int comparison;
    if (rankList == NULL || (comparison = cmp(rankList->element->value, toFind)) > 0) {
        return 0;
    } else if (comparison < 0) {
        return containsRec(rankList->next, rankVector, cmp, toFind);
    }
    return rankList->element->rank;
}

int contains(rankingADT ranking, elemType elem) {
    int rank = containsRec(ranking->rankList, ranking->rankVector, ranking->cmp, elem);
    if (rank < ranking->last) {
        newrank(ranking, rank);
        return rank;
    }
    return 0;
}

void downByRanking(rankingADT ranking, size_t n) {
    n = n - 1;
    if (n >= ranking->last)
        return;
    // Que suba el anterior al que me piden que baje, es equivalente
    newrank(ranking, n + 1);
}

void freeRankList(elementList rankList) {
    if (rankList == NULL)
        return;
    freeRankList(rankList->next);
    free(rankList);
}

void freeRanking(rankingADT r) {
    free(r->rankVector);
    freeRankList(r->rankList);
    free(r);
}

int positionRec(elementList rankList, compare cmp, elemType toFind) {
    int comparison;
    if (rankList == NULL || (comparison = cmp(rankList->element->value, toFind)) > 0) {
        return -1;
    } else if (comparison < 0) {
        return positionRec(rankList->next, cmp, toFind);
    }
    return rankList->element->rank;
}

int position(const rankingADT r, elemType elem) {
    int rank = positionRec(r->rankList, r->cmp, elem);
    newrank(r, rank);
    // Pues rank empieza en 0
    return rank + 1;
}

