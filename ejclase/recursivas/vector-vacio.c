#include <assert.h>

int isNull(int v[], int dim) {
    if (dim == 0)
        return 1;
    return v[0] == 0 && isNull(v+1, dim-1) == 0;
    // Otra forma:
    /* return v[0] != 0 ? 0:isNull(v + 1, dim - 1); */
}

int main(void) {
    int v[] = {9, 3, 2, 3};
    assert(!isNull(v, 4) && !isNull(v, 1));
    assert(isNull(v, 0));
    int v2[100] = {0};
    assert(isNull(v2, 100));
}

