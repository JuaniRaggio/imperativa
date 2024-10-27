#include <stdio.h>

void reglaRecursiva(int alturaCentral) {
    if (alturaCentral == 0)
        return;
    reglaRecursiva(alturaCentral / 2);
    printf("%d ", alturaCentral);
    reglaRecursiva(alturaCentral / 2);
}

