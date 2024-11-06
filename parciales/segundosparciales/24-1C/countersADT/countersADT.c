#include <stdlib.h>
#include <string.h>
#include "countersADT.h"

struct person {
    char * name;
    size_t nameLen;
    struct person * next;
};

typedef struct person * queue;

struct counters {
    queue firstInQueue;
    queue lastInQueue;
    queue iterator;
    size_t length;
};

typedef struct counters * tCounter;

struct countersCDT {
    tCounter queues;
    size_t totalCounters;
    size_t ocupied;
};

countersADT newCounters( size_t maxCounters) {
    countersADT new = calloc(1, sizeof(struct countersCDT));
    new->totalCounters = maxCounters;
    new->queues = calloc(maxCounters, sizeof(struct counters));
    return new;
}

void enterCounter(countersADT counters, size_t counterNumber, const char *passenger) {
    if (counterNumber > counters->totalCounters) return;
    struct counters * currentCounter = &counters->queues[counterNumber];
    if(currentCounter->lastInQueue == NULL) {
        counters->ocupied++;
        currentCounter->firstInQueue = malloc(sizeof(struct person));
        currentCounter->firstInQueue->nameLen = strlen(passenger);
        currentCounter->firstInQueue->name = malloc(currentCounter->firstInQueue->nameLen + 1);
        strncpy(currentCounter->firstInQueue->name, passenger, currentCounter->firstInQueue->nameLen + 1);
        currentCounter->firstInQueue->next = NULL;
        currentCounter->lastInQueue = currentCounter->firstInQueue;
    } else {
        currentCounter->lastInQueue->next = malloc(sizeof(struct person));
        currentCounter->lastInQueue = currentCounter->lastInQueue->next;
        currentCounter->lastInQueue->nameLen = strlen(passenger);
        strncpy(currentCounter->lastInQueue->name, passenger, currentCounter->lastInQueue->nameLen + 1);
        currentCounter->lastInQueue->next = NULL;
    }
}

void toBeginByCounter(countersADT counters, size_t counterNumber) {
    counters->queues[counterNumber].iterator = counters->queues[counterNumber].firstInQueue;
}

struct checkInResult *checkInCounters( countersADT counters, size_t *checkInResultDim) {
    struct checkInResult * retVector = malloc(sizeof(struct checkInResult) * counters->ocupied);
    *checkInResultDim = 0;
    tCounter aux;
    for (int i = 0; i < counters->totalCounters; ++i) {
        aux = &counters->queues[i];
        if (aux->firstInQueue != NULL) {
            retVector[*checkInResultDim].counterNumber = i;
            retVector[*checkInResultDim].waitingPassengers = --counters->queues[i].length;
            retVector[*checkInResultDim].checkedInPassenger = malloc(aux->firstInQueue->nameLen + 1);
            strncpy(retVector[*checkInResultDim].checkedInPassenger, aux->firstInQueue->name, aux->firstInQueue->nameLen + 1);
            counters->queues[i].firstInQueue = counters->queues[i].firstInQueue->next;
            if (counters->queues[i].firstInQueue == NULL) free(aux->lastInQueue);
            free(aux->firstInQueue);
            ++*checkInResultDim;
        }
    }
    return retVector;
}

