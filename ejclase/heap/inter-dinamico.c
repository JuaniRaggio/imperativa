#include <stdlib.h>

#define BLOCK 5

int * interseccion(const int * s1, int d1, const int * s2, int d2, int * dim) {
    int * ret = NULL;
    int i = 0, j = 0, w = 0;
    while (i < d1 && j < d2) {
        if (s1[i] < s2[j]) {
            ++i;
        } else if (s1[i] > s2[j]){
            ++j;
        } else {
            if (w % BLOCK == 0) {
                ret = realloc(ret, sizeof(*ret) * (w + BLOCK));
            }
            ret[w++] = s1[i++]; 
            j++;
        }
    }
    ret = realloc(ret, sizeof(*ret) * w);
    ret[w] = '\0';
    /* dim = &w; */ // Esto esta MAL
    *dim = w;
    return ret;
}

