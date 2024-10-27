#include <math.h>
#include <stdio.h>
#include "../fcatedra/getnum.h"

double redondeo(double nro, int multiplicador){
    double sum = (nro > 0 ? 0.5:-0.5);
    return floor(nro * multiplicador + sum)/multiplicador;
}

double menu(){
    double rta = getdouble("Ingrese el numero que desea modificar"); 
    int opcion = getint("Ingrese:\n1 - Si desea redondear al entero mas cercano\n"
                        "2 - Si desea redondear a la decima mas cercana\n"
                        "3 - Si desea redondear a la centesima mas cercana\n"
                        "4 - Si desea redondear a la milesima mas cercana\n");
    return redondeo(rta, pow(10, opcion - 1));
}

int main(){
    double rta = menu();
    printf("El numero modificado quedaria en: %g", rta);
    return 0;
}

