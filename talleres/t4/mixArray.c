#include "../../fcatedra/rand.h"
void mixArray(unsigned a[], unsigned dim){
    unsigned aux, mixer;
    for(int i = 0; i < dim; ++i){
        mixer = randInt(0, dim - 1);
        aux = a[mixer];
        a[mixer] = a[i];
        a[i] = aux;
    }
}

void mixnodim(unsigned a[]){
/* The thing here is that we would have to insted of making i < dim the exit condition, make it so that its a[i] != -1 and */
/* also we would have to make the a[] array as an int's array, not an unsigned. */
}


