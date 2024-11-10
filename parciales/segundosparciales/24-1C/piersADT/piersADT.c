#include <stdlib.h>
#include <stdbool.h>
#include "piersADT.h"

// Como se asume una baja cantidad de muelles libres dentro de un puerto,
// podemos hacer que sea un vector
struct pier {
    // Representa los muelles dentro de este puerto
    // 1 quiere decir ocupado, 0 libre, -1 no existe
    char * docks;
    // Cantidad de barcos amarrados
    size_t shiped;
    // Cantidad de muelles en el puerto
    size_t dim;
    // Porque puede que hayamos alocado espacio pero que el usuario todavia no
    // haya creado el puerto
    bool exists;
};

typedef struct pier * pPiers;

struct piersCDT {
    // Representa los puertos en una ciudad
    pPiers piers;
    // Cantidad de puertos
    size_t dim;
};

piersADT newPiers(void) {
    return calloc(1, sizeof(struct piersCDT));
}

bool existsPier(piersADT piers, size_t pierNumber) {
    return piers->dim > pierNumber && piers->piers[pierNumber].exists == true;
}

int dockState(piersADT piers, size_t pierNumber, size_t dockNumber) {
    if (!existsPier(piers, pierNumber)) return -1;
    return piers->piers[pierNumber].docks[dockNumber];
}

size_t addPierDock(piersADT piers, size_t pierNumber, size_t dockNumber) {
    int dState = dockState(piers, pierNumber, dockNumber);
    // No existe el puerto o ya existe el muelle en el puerto
    if (!existsPier(piers, pierNumber) || dState != -1) return 0;
    if (piers->piers[pierNumber].dim > dockNumber) {
        piers->piers[pierNumber].docks[dockNumber] = 0;
        return 1;
    }
    piers->piers[pierNumber].docks = realloc(piers->piers[pierNumber].docks, dockNumber + 1);
    for (size_t i = piers->piers[pierNumber].dim; i <= dockNumber; ++i) {
        piers->piers[pierNumber].docks[i] = -1;
    }
    piers->piers[pierNumber].dim = dockNumber + 1;
    return 1;
}

size_t dockShip(piersADT piers, size_t pierNumber, size_t dockNumber) {
    if (!existsPier(piers, pierNumber) || dockState(piers, pierNumber, dockNumber) != 0) return 0;
    piers->piers[pierNumber].docks[dockNumber] = 1;
    piers->piers[pierNumber].shiped++;
    return 1;
}

int shipInDock(const piersADT piers, size_t pierNumber, size_t dockNumber) {
    int dockState;
    if (!existsPier(piers, pierNumber)) return -1;
    return piers->piers[pierNumber].docks[dockNumber];
}

