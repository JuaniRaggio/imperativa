#include <stdio.h>
#include <assert.h>
 
int interseccion(const int a1[], int d1, const int a2[], int d2, int inter[]);

int interord(const int a1[], int d1, const int a2[], int d2, int inter[]);
 
int
main(void) {
    // Prueba para interseccion de desordenados
    int a[] = {7,9,3,5,15};
    int b[] = {5,6,7,9,8};
    int ayb[5];
    int aybDim = interseccion(a, 5, b, 5, ayb);
    assert(aybDim == 3);
    for(int i = 0; i < aybDim; i++) { // Debería obtenerse 5, 7 y 9 en cualquier orden
        printf("%d ", ayb[i]);
    }
 
    // Prueba para interseccion de ordenados (y también desordenados)
    int c[] = {3,5,7,9,15};
    int d[] = {5,6,7,8,9};
    int cyd[5];
    int cybDim = interord(c, 5, d, 5, cyd);
    assert(cybDim == 3);
    assert(cyd[0] == 5);
    assert(cyd[1] == 7);
    assert(cyd[2] == 9);
 
    printf("\nOK!");
    return 0;
}

int interseccion(const int a1[], int d1, const int a2[], int d2, int inter[]){
    int dinter = 0;
    for(int i = 0; i < d1; ++i)
        for(int j = 0, encontrado = 0; j < d2 && !encontrado; ++j)
            if(a1[i] == a2[j]){
                inter[dinter++] = a2[j];
                encontrado = 1;
            }
    return dinter;
}

int interord(const int a1[], int d1, const int a2[], int d2, int inter[]){
    int dinter = 0, i = 0, j = 0;
    while(i < d1 && j < d2){
        if(a1[i] > a2[j])
            ++j;
        else if(a1[i] < a2[j])
            ++i;
        else{
            inter[dinter++] = a1[i++];
            ++j;
        }
    }
    return dinter;
}

