#include "../fcatedra/getnum.c"
#include <stdio.h>
#define BASE 300

int main(){
    do
    int ventas = getint("Introduzca la suma vendida esta semana: $");
    while(ventas < 0);
    int acobrar;
    if(ventas <= 1000)
        acobrar = BASE;
    else if(ventas <= 2000)
        acobrar = BASE + ventas * 0.05;
    else if(ventas <= 4000)
        acobrar = BASE + ventas * 0.07;
    else
        acobrar = BASE + ventas * 0.09;

    return 0;
}

