#include <getnum.h>
#include <rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OPCIONES 4
#define COORDENADAS 2
#define XCOORD 0
#define YCOORD 1
#define BLOQUE 20

typedef struct {
    int x;
    int y;
    double distanciaOrigen;
} particula;

typedef struct {
    particula * posiciones;
    unsigned int iteraciones;
    double radio;
    unsigned int tam;
} circulo;

circulo * nuevoCirculo(double radio) {
    circulo * nuevo = malloc(sizeof(* nuevo));
    nuevo->radio = radio;
    nuevo->tam = BLOQUE;
    nuevo->posiciones = malloc(sizeof(particula) * nuevo->tam);
    nuevo->iteraciones = 0;
    return nuevo;
}

double calcOrigen(double x, double y) {
    return sqrt(pow((double)x, 2.0) + pow((double)y, 2));
}

void calcPaso(circulo * circulo) {
    static int movimiento[OPCIONES][COORDENADAS] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    if(circulo->tam % circulo->iteraciones == 0) {
        circulo->tam += BLOQUE;
        circulo->posiciones = realloc(circulo->posiciones, sizeof(particula) * circulo->tam);
    }
    unsigned int opcion = randInt(0, OPCIONES - 1);
    circulo->iteraciones++;
    circulo->posiciones[circulo->iteraciones].x = circulo->posiciones[circulo->iteraciones - 1].x + movimiento[opcion][XCOORD];
    circulo->posiciones[circulo->iteraciones].y = circulo->posiciones[circulo->iteraciones - 1].y + movimiento[opcion][YCOORD];
    circulo->posiciones[circulo->iteraciones].distanciaOrigen = 
        calcOrigen((double)circulo->posiciones[circulo->iteraciones].x, (double)circulo->posiciones[circulo->iteraciones].y);
    return;
}

void mostrarEstado(circulo * circulo) {
    particula actual = circulo->posiciones[circulo->iteraciones];
    printf("x: %d - y: %d - radio/tiempo: %g\n", actual.x, actual.y, actual.distanciaOrigen/circulo->iteraciones);
}

int main(void) {
    randomize();
    double radio;
    do {
        radio = getint("Ingrese el radio del circulo que desea tener:");
    } while(radio < 0);
    circulo * miCirculo = nuevoCirculo(radio);
    do {
        calcPaso(miCirculo);
        mostrarEstado(miCirculo);
    } while(miCirculo->posiciones[miCirculo->iteraciones - 1].distanciaOrigen <= radio);
    return 0;
}

