
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EPSILON 0.01

double raizNR(double anterior, int iterador, double discriminante);

int main(void){

    assert(fabs(raizNR(4, 3, 8)-2.833) <= EPSILON);
    assert(raizNR(0, 0, 0) <= EPSILON);
    assert(raizNR(0, 0, 4) <= EPSILON);
    
    printf("OK!\n");
}

double raizNR(double anterior, int iterador, double discriminante) {
    if (iterador == 0)
        return anterior;
    return raizNR((anterior + discriminante/anterior)/2, iterador - 1, discriminante);
}

