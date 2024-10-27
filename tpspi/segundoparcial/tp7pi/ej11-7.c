#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void resize(char * p, unsigned int bytes) {
    // El problema con esta funcion es que p es una copia de la variable que me vayan a pasar
    // => p = ... no va a cambiar a la p que me esten pasando por lo que no se va a tener acceso a esa direccion
    // desde el programa
    p = realloc(p, bytes);
}

char * aMayusculas(char * s) {
    char * t;
    for(t = s; (*t = toupper(*t)); t++);
    return s;
}

int main(void) {
    int v[] = {1, 2, 3, 0};
    /* printf("%s\n", aMayusculas(v + 1)); */
    /* printf("%s\n", v); */
    /* char * p = "Hola mundo!"; */
    /* printf("%s\n", aMayusculas(p + 1)); */
    /* printf("%s\n", p); */
    char * p = NULL;
    resize(p, 100); 
    strcpy(p, "Hello world");
    aMayusculas(p);
    printf("%s\n", p);
    return 0;
}

