#include <stdio.h>

int main(){
    int counter = 0, number = getint("Introduce an integer number: ");
    while(number > 0)
        counter += (number%10 == 5);
    return 0;
}

