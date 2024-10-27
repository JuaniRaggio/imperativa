//Generar un numero entre 1 y 256
//Generar una letra mayuscula random
//Leer hasta N caracteres y contar las veces que aparece esa letra

#include "../../fcatedra/rand.h"
#include <stdio.h>
#include <ctype.h>
#define MINN 1
#define MAXN 256

int generator(void){
    int letra = randInt('A', 'Z'), aleer = randInt(MINN, MAXN), c, leidos = 0;
    while((c = getchar()) != EOF && aleer){
        leidos += (toupper(c) == letra);
        --aleer;
    }
    return leidos;
}


