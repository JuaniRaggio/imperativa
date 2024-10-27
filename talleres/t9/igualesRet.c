int igualesRet(const int v1[], const int v2[]) {
    if (*v1 != *v2)
        return 0;
    return *v1 == -1 ? 1:igualesRet(v1 + 1, v2 + 1);
}

void igualesVoid(const int v1[], const int v2[], int * rta) {
    if (*v1 != *v2) {
        *rta = 0;
        return;
    }
    if (*v1 != -1)
        igualesVoid(v1 + 1, v2 + 1, rta);
    *rta = 1;
}

#include <stdio.h>
#include <assert.h>
 
int igualesRet(const int[], const int[]);
void igualesVoid(const int[], const int[], int * rta);
 
int
main(void) {
    int resultado;
    int a[] = {9, 4, 3, 2, 3, 7,-1};
    int b[] = {9, 4, 3, 2, 3, 7,-1};
    int c[] = {7, 3, 2, 3, 4, 9,-1};
    int d[] = {9, 4, 3, -1};
    int e[] = {-1};
 
    assert(igualesRet(a, b) == 1);
    assert(igualesRet(b, c) == 0);
    assert(igualesRet(c, d) == 0);
    assert(igualesRet(d, e) == 0);
 
    igualesVoid(a, b, &resultado);
    assert(resultado == 1);
    igualesVoid(b, c, &resultado);
    assert(resultado == 0);
    igualesVoid(c, d, &resultado);
    assert(resultado == 0);
    igualesVoid(d, e, &resultado);
    assert(resultado == 0);
 
    printf("OK!\n");
    return 0;
}

