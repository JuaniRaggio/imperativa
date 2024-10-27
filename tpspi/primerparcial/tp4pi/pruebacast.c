#include <stdio.h>

int main(){
    double a = 1;
    printf("%g\n", a/3);
    printf("%g\n", 10/3);
    printf("%d");
    /*
     * Notemos que aunque no le pase nada alk ultimo printf como variable para
     * que printee, me va a mostrar en pantalla el 3, que es el resultado de
     * la ultima operacion con resultado entero, entonces por defecto el printf
     * si le paso un %"algo", va a ir al registro con el tipo de dato "algo" y
     * me va a printear lo que haya ahi
     */
}

