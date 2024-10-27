#include <stdio.h>
#include "../fcatedra/getnum.h"
#define DIM 50

int readArray(float v[DIM], int dim);

int main(){
    float v[DIM];
    int leidos;
    leidos = readArray(v, DIM);
    printf("Se leyeron %d numero%s", leidos, leidos > 1 ? "s":"");
    return 0;
}

int readArray(float v[DIM], int dim){
    float c;
    int i = 0;
    while(i < dim && (c = getfloat("")) >= 0){
        v[i++] = c;
    }
    return i;
}

