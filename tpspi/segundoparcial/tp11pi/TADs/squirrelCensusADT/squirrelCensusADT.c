#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "squirrelCensusADT.h"

struct block {
    size_t squirrels;
};

struct horizontal {
    struct block * squares;
    size_t xSize;
};

struct squirrelCensusCDT {
    struct horizontal * park;
    size_t blockSize;
    size_t ySize;
};

squirrelCensusADT newSquirrelCensus(size_t blockSizeMeters) {
    squirrelCensusADT newPark = malloc(sizeof(*newPark));
    newPark->park = NULL;
    newPark->blockSize = blockSizeMeters;
    newPark->ySize = 0;
    return newPark;
}


void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize) {
    if (oldSize >= newSize) return;
    *ptr = realloc(*ptr, sizePtr * newSize);
    memset((char *)*ptr + oldSize * sizePtr, 0, (newSize - oldSize) * sizePtr);
}


size_t countSquirrel(squirrelCensusADT squirrelAdt, size_t yDistance, size_t xDistance) {
    if (yDistance < 0 || xDistance < 0) 
        return 0;
    if (squirrelAdt->ySize <= yDistance/squirrelAdt->blockSize) {
        reCalloc((void **)&(squirrelAdt->park), sizeof(struct horizontal), squirrelAdt->ySize, yDistance/squirrelAdt->blockSize + 1);
        squirrelAdt->ySize = yDistance/squirrelAdt->blockSize + 1;
    }
    if (squirrelAdt->park[yDistance/squirrelAdt->blockSize].xSize <= xDistance/squirrelAdt->blockSize) {
        reCalloc((void **)&(squirrelAdt->park[yDistance/squirrelAdt->blockSize].squares), sizeof(struct block),
                 squirrelAdt->park[yDistance/squirrelAdt->blockSize].xSize, xDistance/squirrelAdt->blockSize + 1);
        squirrelAdt->park[yDistance/squirrelAdt->blockSize].xSize = xDistance/squirrelAdt->blockSize + 1;
    }
    return ++squirrelAdt->park[yDistance/squirrelAdt->blockSize].squares[xDistance/squirrelAdt->blockSize].squirrels;
}


size_t squirrelsInBlock(const squirrelCensusADT squirrelAdt, size_t yDist, size_t xDist) {
    size_t yAxe = yDist/squirrelAdt->blockSize, xAxe = xDist/squirrelAdt->blockSize;
    return yAxe < squirrelAdt->ySize && xAxe < squirrelAdt->park[yAxe].xSize ? squirrelAdt->park[yAxe].squares[xAxe].squirrels:0;
}


void freeSquirrelCensus(squirrelCensusADT squirrelAdt) {
    for (int i = 0; i < squirrelAdt->ySize; ++i) {
        free(squirrelAdt->park[i].squares);
    }
    free(squirrelAdt->park);
    free(squirrelAdt);
}


/* size_t countSquirrel(squirrelCensusADT squirrelAdt, size_t yDistance, size_t xDistance) { */
/*     size_t xAxe = xDistance/squirrelAdt->blockSize, yAxe = yDistance/squirrelAdt->blockSize; */
/*     if (squirrelAdt->ySize <= yAxe) { */
/*         squirrelAdt->park = realloc(squirrelAdt->park, sizeof(struct horizontal) * (yAxe + 1)); */
/*         while (squirrelAdt->ySize <= yAxe) { */
/*             squirrelAdt->park[squirrelAdt->ySize].squares = NULL; */
/*             squirrelAdt->park[squirrelAdt->ySize++].xSize = 0; */
/*         } */
/*     } */
/*     if (squirrelAdt->park[yAxe].xSize <= xAxe) { */
/*         squirrelAdt->park[yAxe].squares = realloc(squirrelAdt->park[yAxe].squares, sizeof(struct block) * (xAxe + 1)); */
/*         while (squirrelAdt->park[yAxe].xSize <= xAxe) { */
/*             squirrelAdt->park[yAxe].squares[squirrelAdt->park[yAxe].xSize++].squirrels = 0; */
/*         } */
/*     } */
/*     return ++squirrelAdt->park[yAxe].squares[xAxe].squirrels; */
/* } */

