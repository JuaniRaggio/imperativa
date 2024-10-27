#define MAXIMO2(x, y, rta) (rta) = (x)>(y) ? (x):(y);
#define MAXIMO3(x, y, z, rta3) (x) > (y) ? MAXIMO2(x, z, rta3):MAXIMO2(y, z, rta3);
#include <stdio.h>

int main(){
    int a = 3, b = 4, rta1, rta2;
    MAXIMO2(a, b, rta1);
    MAXIMO2(a, b, rta2);
    printf("El maximo entre %d y %d es %d o %d", a, b, rta1, rta2);
    return 0;
}

