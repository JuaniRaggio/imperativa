#include <math.h>
#include <stdio.h>
#include "../fcatedra/getnum.h"
#define DELTA 0.001

long double myFunction(unsigned x);
unsigned long factorial(unsigned x);

int main(){
    int x = getint("Introduce x: ");
    printf("%Lg -> %g", myFunction(x), exp(x));
}

unsigned long factorial(unsigned x){
    if(x == 0)
        return 1;
    unsigned long ans = 1;
    while(x > 1){
        ans *= x;
        --x;
    }
    return ans;
}

long double myFunction(unsigned x){
    unsigned divider = 1;
    long double answer = 1.0, last;
    do{
        last = (long double)pow((double)x, (double)divider)/factorial(divider);
        answer += last;
    }while(last > DELTA);
    return answer;
}


