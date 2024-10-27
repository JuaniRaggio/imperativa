#include <stdio.h>

int main(){
    do{
        int num = getint("Introduce a positive integer: ");
    }while(num < 0);
    int answer = 1;
    while(num > 0){
        answer *= num;
        --num;
    }
    printf("The factorial is: %d", answer);
    return 0;
}

