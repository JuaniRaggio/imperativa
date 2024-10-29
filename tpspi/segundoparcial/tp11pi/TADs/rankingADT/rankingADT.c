#include <stdlib.h>
#include "rankingADT.h"

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

typedef int (*cmp)(elemType, elemType);

struct rankingCDT {
    elementList rankList;
    pElement * renkVector;
    size_t last;
    size_t size;
};

rankingADT newRanking(elemType elems[], size_t dim, compare cmp) {
}


