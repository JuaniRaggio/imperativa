#include <stdio.h>
#include <assert.h>
 
int whereisit(const int a[], int dim, int num, int pos[]);
 
int
main(void) {
    int v[] = {3,5,5,5,5,6,7,7,8,9,12,15};
    int dim = sizeof(v)/sizeof(v[0]);
    int positions[dim];
    int positionsDim = whereisit(v, dim, 5, positions);
    for(int i = 0; i < positionsDim; i++) {
        printf("%d ", positions[i]);
    }
 
    assert(positionsDim == 4); // Busco el elemento 5 en v
    assert(positions[0] == 1);
    assert(positions[1] == 2);
    assert(positions[2] == 3);
    assert(positions[3] == 4);
 
    assert(whereisit(v, 2, 5, positions) == 1); // Busco el elemento 5 en v con dim 2
    assert(positions[0] == 1);
 
    assert(whereisit(v, 1, 5, positions) == 0); // Busco el elemento 5 en v con dim 1
 
    assert(whereisit(v, 0, 1, positions) == 0); // Busco el elemento 5 en v con dim 0
 
    assert(whereisit(v, dim, 20, positions) == 0); // Busco el elemento 20 en v
 
    printf("\nOK!");
    return 0;
}

int whereisit(const int a[], int dim, int num, int pos[]){
    int i, j = -1;
    for(i = 0; i < dim && a[i] < num; ++i);
    for(j = 0; i < dim && a[i] == num; ++j, ++i)
        pos[j] = i;
    return j;
}

// This would be if I don't want to save the positions and I only care of the first time it appears
/* int where(int a[], int dim, int num){ */
/*     int i; */
/*     for(i = 0; i < dim && a[i] < num; ++i); */
/*     return a[i] == num ? i:-1; */
/* } */
/*  */
/* void whereisit(const int a[], int dim, int num){ */
/*     printf("The number is in the %d position", where(a, dim, num)); */
/* } */
/*  */

