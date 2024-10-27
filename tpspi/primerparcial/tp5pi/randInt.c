#include <stdlib.h>

int randInt(int min, int max){
    return (rand()/RAND_MAX + min) % (max + 1);
}

