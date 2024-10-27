#include <stdio.h>
#include <getnum.h>

int euclides(int a, int b) {
    if (b == 0)
        return a;
    return euclides(b, a % b);
}

int main(void) {
    int a = getint("Ingrese a: "), b = getint("Ingrese b: ");
    printf("%d", euclides(a, b));
}
