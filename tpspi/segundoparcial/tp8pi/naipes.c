#include <stdlib.h>
#include <stdio.h>
#include "./include/rand.h"
#include "./include/getnum.h"

#define CARTASXPALO 13
#define PALOS 4
#define CARTAS 52
#define PAR (14*4)
#define PIERNA PAR+1
#define POKER PIERNA+1
#define PICK 5
#define NCL -1
#define CL 1

// La simulacion de cartas va a ser de la siguiente forma:
typedef struct {
    unsigned char n;
    char * palo;
} carta;

typedef carta * mazo;

typedef struct {
    carta mano[PICK];
    unsigned char pts;
} estado;

mazo mazoMkr(char * palos[PALOS]);
// La hago void para que no tenga que manejar una copia de mazoMix y realmente modifique el mazo del usr
void mazoMix(mazo miMazo, unsigned int cantCartas);
// Retorna PAR, PIERNA o POKER
char picker(mazo miMazo, unsigned char toPick, carta mesa[toPick], unsigned char * pos);
char jugarMazo(mazo naipes, estado * jugador);
unsigned int calcPts(unsigned char pickeadas, const carta mesa[pickeadas]);
void cmpManos(unsigned char pickeadas, estado * jugador, estado * comp);
void mostrarEstado(estado * jugador);
void finJuego(estado jugador, estado comp);

int main(void) {
    randomize();
    char * palos[PALOS] = {"corazones", "diamantes", "treboles", "picas"};
    mazo miMazo = mazoMkr(palos);
    mazoMix(miMazo, CARTAS);
    estado j1;
    j1.pts = 0;
    while(jugarMazo(miMazo, &j1) != NCL && getint("\nPresione 1 para finalizar el juego, otro numero para seguir jugando: ") != 1);
    free(miMazo);
}

char jugarMazo(mazo naipes, estado * jugador) {
    static estado comp;
    static unsigned char i;
    if(picker(naipes, PICK, jugador->mano, &i) <= 2 || picker(naipes, PICK, comp.mano, &i) <= 2) {
        finJuego(*jugador, comp);
        return NCL;
    }
    cmpManos(PICK, jugador, &comp);
    mostrarEstado(jugador);
    return CL;
}

void mostrarPts(int ptsJ, int ptsC){
    printf("Tu puntuacion final fue de: %d pts.\n", ptsJ);
    printf("La computadora obtuvo: %d pts.\n", ptsC);
    return;
}

void finJuego(estado jugador, estado comp) {
    if(jugador.pts > comp.pts) {
        printf("Felicitaciones, ganaste!\n");
    } else if (jugador.pts == comp.pts) {
        printf("Fue un empate!\n");
    } else {
        printf("Perdiste");
    }
    mostrarPts(jugador.pts, comp.pts);
    return;
}

void mostrarEstado(estado * jugador) {
    printf("Tu puntuacion actual es de %d pts.\n", jugador->pts);
    printf("Tu mano actual es:\n");
    for(int i = 0; i < PICK; ++i){
        printf("%d de %s\n", jugador->mano[i].n, jugador->mano[i].palo);
    }
    return;
}

void cmpManos(unsigned char pickeadas, estado * jugador, estado * comp) {
    unsigned int localJ = calcPts(pickeadas, jugador->mano);
    unsigned int localC = calcPts(pickeadas, comp->mano);
    /* localJ > localC ? ++(jugador->pts):(localC > localJ ? ++(comp->pts):++(comp->pts), ++(jugador->pts)); */
    if(localJ > localC) {
        ++(jugador->pts);
    } else if(localC > localJ) {
        ++(comp->pts);
    } else {
        ++(comp->pts);
        ++(jugador->pts);
    }
    return;
}

unsigned int calcPts(unsigned char pickeadas, const carta mesa[pickeadas]) {
    unsigned int localPts = 0;
    unsigned char config = 0, muestra[CARTASXPALO] = {0};
    for(int i = 0; i < pickeadas; ++i) {
        localPts += mesa[i].n;
        config = config > ++muestra[mesa[i].n - 1] ? config:muestra[mesa[i].n - 1];
    }
    unsigned int aSumar = 0;
    switch(config){
        case 2:
            aSumar = PAR;
            break;
        case 3:
            aSumar = PIERNA;
            break;
        case 4:
            aSumar = POKER;
            break;
        default: break;
    }
    localPts += aSumar;
    return localPts;
}

mazo mazoMkr(char * palos[PALOS]) {
    mazo nuevoMazo = malloc(sizeof(carta) * CARTAS);
    for(int i = 0; i < CARTAS; ++i) {
        nuevoMazo[i].palo = palos[i / CARTASXPALO];
        nuevoMazo[i].n = (i % CARTASXPALO) + 1;
    }
    return nuevoMazo;
}

void mazoMix(mazo miMazo, unsigned int cantCartas) {
    int aux;
    carta swaper;
    for(int i = 0; i < cantCartas; ++i) {
        aux = randInt(0, cantCartas - 1);
        swaper = miMazo[i];
        miMazo[i] = miMazo[aux];
        miMazo[aux] = swaper;
    }
    return;
}

char picker(mazo miMazo, unsigned char toPick, carta mesa[toPick], unsigned char * pos) {
    if (*pos + 5 > CARTAS)
        return 2;
    for(int i = 0; i < toPick; ++i) {
        mesa[i] = miMazo[*pos];
        ++*pos;
    }
    return CARTAS - *pos;
}

