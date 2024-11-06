#include <assert.h>
#include "piersADT.h"

int main(void) {
    piersADT piersAdt = newPiers();

    // Agrega puertos y muelles
    assert(addPier(piersAdt, 5) == 1);           // Agrega el puerto 5
    assert(addPierDock(piersAdt, 5, 4) == 1);     // Agrega el muelle 4 del puerto 5
    assert(addPierDock(piersAdt, 5, 7) == 1);     // Agrega el muelle 7 del puerto 5
    assert(addPier(piersAdt, 10) == 1);           // Agrega el puerto 10
    assert(addPierDock(piersAdt, 10, 1) == 1);    // Agrega el muelle 1 del puerto 10
    assert(addPierDock(piersAdt, 10, 7) == 1);    // Agrega el muelle 7 del puerto 10

    // Verifica que no haya embarcaciones amarradas inicialmente
    assert(shipInDock(piersAdt, 5, 4) == 0);      // Muelle 4 del puerto 5 está libre
    assert(shipInDock(piersAdt, 5, 7) == 0);      // Muelle 7 del puerto 5 está libre
    assert(pierShips(piersAdt, 5) == 0);          // Ninguna embarcación en el puerto 5
    assert(shipInDock(piersAdt, 10, 1) == 0);     // Muelle 1 del puerto 10 está libre
    assert(shipInDock(piersAdt, 10, 7) == 0);     // Muelle 7 del puerto 10 está libre
    assert(pierShips(piersAdt, 10) == 0);         // Ninguna embarcación en el puerto 10

    // Amarra embarcaciones en el puerto 5
    assert(dockShip(piersAdt, 5, 4) == 1);        // Amarra en el muelle 4 del puerto 5
    assert(shipInDock(piersAdt, 5, 4) == 1);      // Muelle 4 del puerto 5 está ocupado
    assert(shipInDock(piersAdt, 5, 7) == 0);      // Muelle 7 del puerto 5 sigue libre
    assert(pierShips(piersAdt, 5) == 1);          // Una embarcación en el puerto 5

    assert(dockShip(piersAdt, 5, 7) == 1);        // Amarra en el muelle 7 del puerto 5
    assert(shipInDock(piersAdt, 5, 4) == 1);      // Muelle 4 del puerto 5 sigue ocupado
    assert(shipInDock(piersAdt, 5, 7) == 1);      // Muelle 7 del puerto 5 está ocupado
    assert(pierShips(piersAdt, 5) == 2);          // Dos embarcaciones en el puerto 5

    // Desamarra la embarcación del muelle 7 del puerto 5
    assert(undockShip(piersAdt, 5, 7) == 1);      // Desamarra en el muelle 7 del puerto 5
    assert(shipInDock(piersAdt, 5, 4) == 1);      // Muelle 4 del puerto 5 sigue ocupado
    assert(shipInDock(piersAdt, 5, 7) == 0);      // Muelle 7 del puerto 5 está libre
    assert(pierShips(piersAdt, 5) == 1);          // Una embarcación en el puerto 5

    // Libera los recursos utilizados
    freePiers(piersAdt);

    return 0;
}
