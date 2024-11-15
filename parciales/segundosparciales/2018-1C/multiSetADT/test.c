#include "multisetADT.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int comp(int a, int b) { return a-b; }

int main(void) {
    multiSetADT set = newMultiSet(comp);
    assert(add(set, 10) == 1);
    assert(add(set, 10) == 2);
    assert(add(set, 20) == 1);
    assert(add(set, 10) == 3);
    assert(add(set, 30) == 1);
    assert(add(set, 40) == 1);
    assert(add(set, 40) == 2);
    assert(size(set) == 4);
    removeAll(set, 60);
    removeAll(set, 30);
    assert(removePrime(set, 10) == 2);
    assert(removePrime(set, 50) == 0);
    assert(removePrime(set, 40) == 1);
    int n;
    elemType * min = minElements(set, &n);
    assert(n == 2);
    puts("Imprime (20, 40) en ningun orden especifico");
    for(int i = 0; i < n; i++) {
        printf("%d\n", min[i]);
    }
    free(min);
}
