#include <math.h>

int esPrimo(int x){
    int aux = 2;
    int max = (int)sqrt(x);
    while(aux <= max){
        if(x % aux == 0)
            return 0;
        ++aux;
    }
    return 1;
}

