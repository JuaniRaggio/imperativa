#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "countersADT.h"

int main(void) {
    countersADT terminalA = newCounters(10);

    enterCounter(terminalA, 5, "Foo"); // "Foo" ingresa a la cola del mostrador 5
    enterCounter(terminalA, 5, "Bar");
    enterCounter(terminalA, 5, "Bar");
    enterCounter(terminalA, 4, "Abc");
    enterCounter(terminalA, 4, "Xyz");

    // Consultar los pasajeros en el mostrador 5
    toBeginByCounter(terminalA, 5); // "Foo" es el primero en el mostrador 5
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Foo") == 0);
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);

    toBeginByCounter(terminalA, 4);
    assert(hasNextByCounter(terminalA, 4) == 1);
    assert(strcmp(nextByCounter(terminalA, 4), "Abc") == 0);

    // Consultar en simultáneo mostradores distintos
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(hasNextByCounter(terminalA, 4) == 1);
    assert(strcmp(nextByCounter(terminalA, 4), "Xyz") == 0);
    assert(hasNextByCounter(terminalA, 5) == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);

    // Realizar checkIn en cada mostrador
    size_t checkInResultDim;
    struct checkInResult *checkInResultVec;

    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 2); // CheckIn en dos mostradores: 4 y 5

    // Resultado del checkIn en el mostrador 4
    assert(checkInResultVec[0].counterNumber == 4);
    assert(checkInResultVec[0].waitingPassengers == 1);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Abc") == 0);

    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[1].counterNumber == 5);
    assert(checkInResultVec[1].waitingPassengers == 2);
    assert(strcmp(checkInResultVec[1].checkedInPassenger, "Foo") == 0);

    free(checkInResultVec);

    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(strcmp(nextByCounter(terminalA, 4), "Xyz") == 0);

    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 2); // CheckIn en mostradores: 4 y 5

    // Resultado del checkIn en el mostrador 4
    assert(checkInResultVec[0].counterNumber == 4);
    assert(checkInResultVec[0].waitingPassengers == 0);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Xyz") == 0);

    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[1].counterNumber == 5);
    assert(checkInResultVec[1].waitingPassengers == 1);
    assert(strcmp(checkInResultVec[1].checkedInPassenger, "Bar") == 0);

    free(checkInResultVec);

    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);

    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 1);

    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[0].counterNumber == 5);
    assert(checkInResultVec[0].waitingPassengers == 0);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Bar") == 0);

    free(checkInResultVec);

    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(hasNextByCounter(terminalA, 5) == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);

    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 0);
    assert(checkInResultVec == NULL);

    freeCounters(terminalA);

    return 0;
}
