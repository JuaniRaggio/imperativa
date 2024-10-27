#include <stdlib.h>

#define BLOCK 5

int * pares(const int * conj, size_t dim, size_t * nuevaDim) {
    int * newConj = NULL;
    int i, j;
    for (i = 0, j = 0; i < dim; ++i) {
        if (conj[i] % 2 == 0) {
            if (j % BLOCK == 0) {
                newConj = realloc(newConj, sizeof(*newConj) * (j + BLOCK));
            }
            newConj[j++] = conj[i];
        }
    }
    newConj = realloc(newConj, sizeof(*newConj) * j);
    *nuevaDim = j;
    return newConj;
}

