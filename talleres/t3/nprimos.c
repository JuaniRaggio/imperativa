#include "../../fcatedra/getnum.h"
#include <stdio.h>
#include "esprimo.c"

int main(){
    int primes = 1, howmany = getint("Introduce how many prime you would like me to print");
    while(howmany > 0){
        if(esPrimo(primes) == 1){
            printf("%d\n", primes);
            --howmany;
        }
        ++primes;
    }
    return 0;
}

