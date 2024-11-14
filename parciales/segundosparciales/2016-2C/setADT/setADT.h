typedef struct setCDT * setADT;

#include <stdio.h>

typedef int (*cmp)(void *, void *);

/* Retorna un nuevo conjunto de elementos genéricos. Al inicio está vacío */
setADT newSet(cmp fx, size_t size);
/* Inserta elem siempre y cuando el elemento no esté
** en el conjunto. Retorna la cantidad total de elementos luego de agregar el elemento nuevo
*/
int add(setADT set, void * elem);
/* Retorna cuántos elementos hay en el conjunto */
int size(const setADT set);
/* Retorna una copia del mayor elemento del conjunto, NULL si no hay elementos */
void * max(const setADT set);
/* Retorna una copia del menor elemento del conjunto, NULL si no hay elementos */
void * min(const setADT set);
/* Retorna una copia del último elemento agregado en el conjunto, NULL si está vacío */
void * last(const setADT set);
/* Retorna un vector con todos los elementos del conjunto, ordenados en forma ascendente */
void ** setToArray(const setADT set, size_t * dim, size_t * pSize);

