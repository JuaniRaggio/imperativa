#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define BLOCK 20
#define ISVOWEL(a) (tolower(a) == 'a' || tolower(a) == 'e' || tolower(a) == 'i' || tolower(a) == 'o' || tolower(a) == 'u')

int myGetline(char ** s) {
    *s = NULL;
    int i = 0, tam = 0;
    do {
        if (i % BLOCK == 0) {
            tam += BLOCK;
            *s = realloc(*s, tam);
        }
    } while(((*s)[i++] = getchar()) != '\n');
    (*s)[i] = '\0';
    return i;
}

int contarVocales(char * s) {
    if (*s == '\0')
        return 0;
    return ISVOWEL(*s) + contarVocales(s + 1);
}

int main(void) {
    char * s = NULL;
    myGetline(&s);
    printf("La cantidad de vocales es: %i", contarVocales(s));
}

