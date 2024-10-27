#include <stdlib.h>
#include <stdio.h>

int
main(void) {

        char * p = malloc(11);// Aca habia un error porque luego usabamos i € [0; 10] -> 11 lugares
        for(int i=0; i <= 10; i++)
                p[i] = i * 10;
        for(int i=0; i <= 10; i++)
                printf("%i\n", p[i]);
        free(p);
        return 0;
}

