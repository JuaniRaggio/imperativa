#include <stdlib.h>
#include <stdio.h>
#include "queueADT.h"

struct node {
    elementType value;
    struct node * tail;
};

typedef struct node * qList;

struct queueCDT {
    qList first_in_list;
    qList last_in_list;
    qList iterator;
};

queueADT newQueue(void) {
    return calloc(1, sizeof(struct node));
}

void queue(queueADT q, elementType n) {
    qList new_in_queue = malloc(sizeof(struct node));
    new_in_queue->value = n;
    new_in_queue->tail = NULL;
    if (q->last_in_list == NULL) {
        q->last_in_list = new_in_queue;
        q->first_in_list = q->last_in_list;
    }
    q->last_in_list->tail = new_in_queue;
    q->last_in_list = new_in_queue;
}

void dequeue(queueADT q, elementType * out) {
    if (q->first_in_list == NULL)
        return;
    *out = q->first_in_list->value;
    qList aux = q->first_in_list;
    
    // OJO CON ESTO QUE NO LO HABIA PUESTO
    if (q->last_in_list == q->first_in_list) q->last_in_list = NULL;

    q->first_in_list = q->first_in_list->tail;
    free(aux);
}

int isEmpty(queueADT q) {
    return q->first_in_list == NULL;
}

static void freeQueueRec(qList first_in_list) {
    if (first_in_list == NULL)
        return;
    freeQueueRec(first_in_list->tail);
    free(first_in_list);
}

void freeQueue(queueADT q) {
    freeQueueRec(q->first_in_list);
    free(q);
}

void toBegin(queueADT q) {
    q->iterator = q->first_in_list;
}

int hasNext(queueADT q) {
    return q->iterator != NULL;
}

elementType next(queueADT q) {
    if (!hasNext(q)) {
        printf("Error en linea %d en %s, se llama a next sin llamar previamente a hasNext", __LINE__, __FILE__);
        exit(1);
    }
    elementType retValue = q->iterator->value;
    q->iterator = q->iterator->tail;
    return retValue;
}

