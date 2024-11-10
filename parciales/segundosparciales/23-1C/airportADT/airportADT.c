#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "airportADT.h"

struct node {
    char * matricula;
    struct node * siguiente;
    struct node * anterior;
};

typedef struct node * tAviones;

struct pista {
    tAviones primeroAD;
    tAviones ultimoAD;
    // Esto lo guardamos para crear pending flights con un solo malloc
    size_t cantAviones;
};

typedef struct pista * tPista;

struct airportCDT {
    // Si pistas[i] == NULL quiere decir que no existe
    tPista * pistas;
    size_t cantPistas;
};

airportADT newAirport(void) {
    return calloc(1, sizeof(struct airportCDT));
}

static bool existePista(airportADT airportAdt, size_t runwayId) { return airportAdt->cantPistas <= runwayId || airportAdt->pistas[runwayId] == NULL; }

static void deletePlane(tPista runway, size_t * planes) {
    tAviones aux = runway->primeroAD;
    runway->primeroAD = runway->primeroAD->siguiente;
    if (runway->primeroAD == NULL) {
        runway->ultimoAD = runway->primeroAD;
    }
    free(aux);
    --*planes;
}

char * takeOff(airportADT airportAdt, size_t runwayId) {
    runwayId--;
    if (existePista(airportAdt, runwayId) || airportAdt->pistas[runwayId]->cantAviones == 0) return NULL;
    char * retValue = airportAdt->pistas[runwayId]->primeroAD->matricula;
    deletePlane(airportAdt->pistas[runwayId], &airportAdt->pistas[runwayId]->cantAviones);
    return retValue;
}

char ** pendingFlights(airportADT airportAdt, size_t runwayId) {
    runwayId--;
    char ** pending = malloc(sizeof(char *) * (airportAdt->cantPistas + 1));
    size_t i = 0;
    for (tAviones aux = airportAdt->pistas[runwayId]->ultimoAD; i < airportAdt->pistas[runwayId]->cantAviones && aux != NULL; aux = aux->anterior, ++i) {
        pending[i] = malloc(strlen(aux->matricula) + 1);
        strcpy(pending[i], aux->matricula);
    }
    pending[i] = "";
    return pending;
}

