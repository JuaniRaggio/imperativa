#include <stdio.h>
#include <getnum.h>

int factorial(int n) {
    if (n > 0)
        return n * factorial(n - 1);
    return 1;
}

int main(void) {
    int n = getint("Ingrese el factorial que desee calcular");
    printf("%d\n", factorial(n));
    return 0;
}

