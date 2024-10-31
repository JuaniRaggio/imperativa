#ifndef __QUEUEADT_H__
#define __QUEUEADT_H__

typedef int elementType;
 
typedef struct queueCDT * queueADT;
 
queueADT newQueue(void);
 
// Agrega un elemento al final de la cola
void queue(queueADT q, elementType n);
 
// Remueve un elemento del principio de la cola y lo deja en out
void dequeue(queueADT q, elementType * out);
 
int isEmpty(queueADT q);
 
void freeQueue(queueADT q);

// Esto es parte del taller 12
void toBegin(queueADT q);

int hasNext(queueADT q);

elementType next(queueADT q);

#endif

