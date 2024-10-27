#include <stdio.h>
#include <math.h>
#include "../fcatedra/getnum.h"

int main(){
    int binary = getint("Type a binary number to convert: "), aux = binary, answer = 0;
    // A better way would be to ask until the number is binary
    if(aux < 0){
        printf("The number isn't binary");
        return -1;
    }
    for(int i = 0; aux != 0; ++i, aux /= 10){
        if(aux%10 <= 1){
            answer += pow(2, i) * (aux%10);
        } else {
            printf("The number isn't binary");
            return -1;
        }
    }
    printf("%d -> %d", binary, answer);
    return 0;
}

