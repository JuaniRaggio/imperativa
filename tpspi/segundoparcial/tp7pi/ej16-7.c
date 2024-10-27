#include <stdio.h>

int main(void) {
    char * color[6] = {"rojo", "verde", "azul", "blanco", "negro", "amarillo"};
    printf("%s\n", *(color + 2));
    printf("%p\n", *(color));
    printf("%p\n", *(color + 1));
    printf("%p\n", *(color  + 2));
    printf("%p\n", *(color  + 3));
    printf("%p\n", *(color  + 4));
    printf("%p\n", *(color  + 5));
}

