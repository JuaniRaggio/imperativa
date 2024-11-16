// Multiset es un conjunto de elementos sin orden pero donde cada elemento puede aparecer mas de una vez
#ifndef MULTISET_ADT_H
#define MULTISET_ADT_H

typedef struct multiSetCDT * multiSetADT;

typedef int elemType;  // Tipo de elemento a insertar

/**
 ** Retorna 0 si los elementos son iguales, negativo si el es "menor" que e2 y positivo
 ** si el es "mayor" que e2
 */
static int compare (elemType el, elemType e2) {
    return el - e2;
}

typedef int (*cmp)(elemType, elemType);

/* Retorna un nuevo multiSet de elementos genéricos. Al inicio está vacío */
multiSetADT newMultiSet(cmp fx);

/* Inserta un elemento. Retorna cuántas veces está elem en el conjunto
 ** luego de haberlo insertado (p.e. si es la primera inserción retorna 1).
 */
unsigned int add(multiSetADT multiSet, elemType elem);

/* Retorna cuántas veces aparece el elemento en el multiSet */
unsigned int count(const multiSetADT multiSet, elemType elem);

/* Retorna la cantidad de elementos distintos que hay en el multiSet */
unsigned int size(const multiSetADT multiSet);

/* Elimina una repetición del elemento. Retorna cuántas veces está elem en el conjunto
 ** luego de haberlo borrado (si el elemento no estaba, retorna cero)
 */
int remove(multiSetADT multiSet, elemType elem);

/* Elimina todas las apariciones de un elemento. */
void removeAll(multiSetADT multiSet, elemType elem);

/* Retorna un vector con los elementos que menos aparecen en el conjunto
 ** Si el conjunto está vacío retorna NULL
 ** En el parámetro se salda dim almacena la cantidad de elementos del vector
 */
elemType * minElements(const multiSetADT multiSet, int * dim);

#endif // MULTISET_ADT_H

