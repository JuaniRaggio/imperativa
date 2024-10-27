#include <assert.h>
#include <stdio.h>
 
 
int incrementoFCMinMax(int Angulos[], int Distancias[], int dim, int *fMin, int *cMin, int *fMax, int *cMax);
 
int main()
{
    int angulos[] = {0, 45, 90, 135, 180, 225, 270, 315};
    int distancias[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int fMin, cMin, fMax, cMax;
    assert(incrementoFCMinMax(angulos, distancias, sizeof(angulos) / sizeof(angulos[0]), &fMin, &cMin, &fMax, &cMax) == 1);
    assert(fMin == 0 && cMin == 1 && fMax == 1 && cMax == 1);
 
 
    int angulos2[] = {0, 45, 90, 135, 180, 225, 270, 315};
    int distancias2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    assert(incrementoFCMinMax(angulos2, distancias2, sizeof(angulos2) / sizeof(angulos2[0]), &fMin, &cMin, &fMax, &cMax) == 1);
    assert(fMin == 1 && cMin == 1 && fMax == 0 && cMax == 1);
 
 
    int angulos3[] = {45, 90, 135, 225, 180, 0};
    int distancias3[] = {12, 1, 4, 20, 7, 9};
    assert(incrementoFCMinMax(angulos3, distancias3, sizeof(angulos3) / sizeof(angulos3[0]), &fMin, &cMin, &fMax, &cMax) == 1);
    assert(fMin == -1 && cMin == 0 && fMax == 1 && cMax == -1);
 
 
    int angulos4[] = {90};
    int distancias4[] = {1};
    assert(incrementoFCMinMax(angulos4, distancias4, sizeof(angulos4) / sizeof(angulos4[0]), &fMin, &cMin, &fMax, &cMax) == 1);
    assert(fMin == -1 && cMin == 0 && fMax == -1 && cMax == 0);
 
 
    assert(incrementoFCMinMax(NULL, NULL, 0, &fMin, &cMin, &fMax, &cMax) == 0);
    assert(fMin == -1 && cMin == 0 && fMax == -1 && cMax == 0); // no debería modificar los valores
 
 
    puts("OK");
    return 0;
}

#define ANGULOS 8

int find_integer(int integer, const int array[], int dim){
    for(int i = 0; i < dim; ++i){
        if(array[i] == integer)
            return i;
    }
    return -1;
}

int incrementoFCMinMax(int Angulos[], int Distancias[], int dim, int *fMin, int *cMin, int *fMax, int *cMax){
    if(dim == 0)
        return 0;
    static const int angulos_local[ANGULOS] = {0, 45, 90, 135, 180, 225, 270, 315};
    static const int versores[ANGULOS][2] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 1}};
    int i, d_max = 0, d_min = 0;
    for(i = 0; i < dim; ++i){
        if(Distancias[d_max] < Distancias[i])
            d_max = i;
        if(Distancias[d_min] > Distancias[i])
            d_min = i;
    }
    i = find_integer(Angulos[d_min], angulos_local, ANGULOS);
    *fMin = versores[i][0];
    *cMin = versores[i][1];
    i = find_integer(Angulos[d_max], angulos_local, ANGULOS);
    *fMax = versores[i][0];
    *cMax = versores[i][1];
    return 1;
}

