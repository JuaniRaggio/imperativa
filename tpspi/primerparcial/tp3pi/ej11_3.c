#include <stdio.h>
#define ST 10
#define ND 100
#define RD 1000
#define LIMIT 20

int main(){
    printf("N \t10*N\t100*N\t1000*N\n");
    for(int n = 1; n <= LIMIT; ++n){
            printf("%2d\t%4d\t%5d\t%6d\n", n, n*ST, n*ND, n*RD);
    }     
    return 0;
}

