#include <stdio.h>

int main(){
    printf("Ingrese dos caracteres: ");
    char c1 = getchar(), c2 = getchar();
    if(c1 > c2)
        printf("El primero es mayor\n");
    else if (c1 < c2)
        printf("El primero es menor\n");
    else
        printf("Son iguales\n");
    return 0;
}

