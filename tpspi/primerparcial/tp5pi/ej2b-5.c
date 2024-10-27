#include <math.h>
#include <stdio.h>
int main(){
    
for (double x = -1; x < 2; x += 0.5 )
{
	printf("%f  %f   %f   %f\n", x, fabs(x), ceil(x), floor(x));
	printf("%f  %f\n", pow(x,2), pow(x,.5));
}
}
