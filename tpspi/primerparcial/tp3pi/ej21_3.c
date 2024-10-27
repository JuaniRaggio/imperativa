#include "../fcatedra/getnum.h"
#include <math.h>
#include <stdio.h>
#define DELTA 0.1

int main(){
    int number = getint("Introduce an integer number: "), reversed = 0, aux = number, i = 0;
    while(aux > DELTA){
        reversed += (aux%10)*pow(10, i);
        aux /= 10;
        ++i;
    }
    printf("%d is%s capicua\n", number, (reversed == number) ? "":"n't");
    return 0;
}

