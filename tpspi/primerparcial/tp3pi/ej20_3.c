#include <stdio.h>
#include <math.h>
#define DELTA 0.00001

unsigned int factorial(int a){
    if(a == 0)
        return 1;
    int i = a - 1;
    while(i > 0){
        a *= i--;
    }
    return a;
}

int main(){
    int i = 0;
    double answer = 0, last = -1;
    printf("N\te\n");
    while(answer - last > DELTA){
        last = answer;
        answer += 1/(double)factorial(i);
        printf("%d\t%g\n", i + 1, answer);
        ++i;
    }
    return 0;
}

