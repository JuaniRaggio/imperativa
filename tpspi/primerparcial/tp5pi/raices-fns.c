#include <math.h>
#include <stdio.h>
#include "../fcatedra/getnum.h"
#define INC 0.001

typedef double(*fn)(double x);

void fraices(fn f, double izq, double der);

int main(){
    int opcion = getint("Ingrese:\n"
                        "1 - Si desea hayar las raices del seno(x)\n"
                        "2 - Si desea hayar las raices del coseno(x)\n"
                        "3 - Si desea hayar las raices de 2^x * x^3\n"
                        "4 - Si desea hayar las raices de seno(x) + log(x)\n"
                        "5 - Si desea hayar las raices de e^x + x^(1/2)");
    /* Este programa tendria mucho mejor estilo si pudiese usar punteros a funcion */
    /* Despues de hacerlo como me piden, lo voy a hacer con punteros a funcion separando bien el front del back */
    printf("Tenga en cuenta que si ingresa los limites de los intervalos invertidos, el programa los invertira automaticamente\n");
    double izq = getdouble("Ingrese el limite izquierdo del intervalo: ");
    double der = getdouble("Ingrese el limite derecho del intervalo: ");
    /* Aca no nos queda otra mas que usar punteros a funcion o hacer una funcion para cada funcion */
    switch(opcion){
        case 1:
            fraices(sin, izq, der);
        break;
        case 2:
            fraices(cos, izq, der);
        break;
        case 3:
            fraices(); // Preguntar como puedo hacer, se me ocurre definir la funcion que haga eso como una funcion aux
        break;
        case 4:
            fraices(); // Idem anterior
        break;
        case 5:
            fraices();
        break;
    }
}

        
