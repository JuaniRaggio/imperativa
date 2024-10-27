#include <math.h>
#include <stdio.h>
#define PI 3.14
#define VOL(answer, r) (answer) = ((double)4/3) * PI * pow((r), 3)

int main(){
    double ans;
    for(int i = 1; i <= 10; ++i)
        printf("r = %d -> Volume = %g\n", i, VOL(ans, i));
}

