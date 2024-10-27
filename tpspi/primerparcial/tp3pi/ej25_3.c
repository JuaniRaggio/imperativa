#include <stdio.h>
#include "../fcatedra/getnum.h"

int main(){
    int number = getint("Introduce an integer number: "), aux = number, counter = 0;
    while(aux > 0){
        if(aux & 1)
            ++counter;
        aux = aux >> 1;
    }
    printf("%d has %d ones", number, counter);
    return 0;
}

