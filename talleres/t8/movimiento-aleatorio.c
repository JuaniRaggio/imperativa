#include <rand.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 10

typedef struct {
    int x;
    int y;
} tPunto2D;

void prt_points(tPunto2D * points, int dim) {
    // Para mostrarlo en forma de matriz y que el 1 este en el centro,
    // 1. sumarle a x dim/2
    // 2. Restringir los valores para que no excedan la matriz
    for(int i = 0; i <= dim; ++i)
        printf("x_%d: %d, y_%d: %d\n",i, points[i].x, i, points[i].y);
}

tPunto2D * append_points(int * i) {
    *i = 0;
    tPunto2D * points = malloc(sizeof(*points) * BLOCK);
    points[0].x = 0;
    points[0].y = 0;
    do {
        ++*i;
        if (*i % BLOCK == 0) {
            points = realloc(points, sizeof(*points) * (*i + BLOCK));
        }
        points[*i].x = points[*i-1].x + randInt(-1, 1);
        points[*i].y = points[*i-1].y + randInt(-1, 1);
    } while(points[*i].x != 0 || points[*i].y != 0);
    points = realloc(points, sizeof(*points) * (++*i));
    return points;
}

int main(void) {
    randomize();
    int dim;
    tPunto2D * points = append_points(&dim);
    prt_points(points, dim);
    free(points);
    return 0;
}

