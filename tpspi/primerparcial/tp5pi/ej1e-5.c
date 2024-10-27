#include <stdio.h>

static int cubo(int x);

int main(){
    int x;
    for(x = 1; x <= 5; ++x){
        printf("El cubo de %d es %4d\n", x, cubo(x));
    }
    return 0;
}

static int cubo(int x){
    return x * x * x;
}

