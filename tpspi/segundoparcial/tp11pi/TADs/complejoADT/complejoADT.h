#ifndef __COMPLEJOADT_H__
#define __COMPLEJOADT_H__

typedef struct complejoCDT * complejoADT;

complejoADT nuevoComp(double real, double compleja);

double parteRealComp(complejoADT complejo);

double parteImagComp(complejoADT complejo);

complejoADT sumaComp(complejoADT complejo1, complejoADT complejo2);

complejoADT restaComp(complejoADT complejo1, complejoADT complejo2);

complejoADT multiplicaComp(complejoADT complejo1, complejoADT complejo2);

complejoADT divideComp(complejoADT complejo1, complejoADT complejo2);

complejoADT conjugadoComp(complejoADT complejo);

void liberaComp(complejoADT complejo);

#endif

