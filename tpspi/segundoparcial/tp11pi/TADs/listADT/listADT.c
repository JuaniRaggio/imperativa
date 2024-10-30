#include "listADT.h"
#include <stdlib.h>
#include <assert.h>

// Si bien puede parecer mas complicado, al tener una sola lista, basta con
// borrar el nodo una sola vez, no es necesario tener que primero buscar si
// esta el elemento en la lista ascendente y luego volver a buscarlo en la
// lista de insercion => Va a ser mas corto el problema que tenemos que
// resolver, basta con borrar el nodo que encontremos y mantener los punteros
// anteriores
struct node {
  elemType value;
  struct node * prevInsert;
  struct node * nextInsert;
  struct node * prevIncreasing;
  struct node * nextIncreasing;
};

typedef struct node * header;

typedef int (*fCompare)(elemType, elemType);

struct listCDT {
  header firstInc; // Es el primero de la lista ascendente
  header firstAdded;
  header lastAdded; // Es el ultimo agregado
  header iteratorAdded;
  header iteratorInc;
  fCompare cmp;
};

listADT newList(int (*compare) (elemType e1, elemType e2)) {
  listADT new = malloc(sizeof(*new));
  new->firstInc = NULL;
  new->firstAdded = NULL;
  new->lastAdded = NULL;
  new->iteratorAdded = NULL;
  new->iteratorInc = NULL;
  new->cmp = compare;
  return new;
}

header addListRec(header list, header * lastAdded, fCompare cmp, elemType toAdd) {
  int comparison, isNull = list == NULL;
  if (isNull || (comparison = cmp(list->value, toAdd)) > 0) {
      header new = malloc(sizeof(*new));
      new->value = toAdd;
      new->nextIncreasing = list;
      new->prevInsert = *lastAdded;
      if (*lastAdded != NULL) (*lastAdded)->nextInsert = new;
      *lastAdded = new;
      // Como no hay mas despues, el siguiente va a ser NULL
      new->nextInsert = NULL;
      new->prevIncreasing = isNull ? NULL:list->prevIncreasing;
      if (!isNull) list->prevIncreasing = new;
      return new;
   } else if (comparison < 0) {
      list->nextIncreasing = addListRec(list->nextIncreasing, lastAdded, cmp, toAdd);
   }
   return list; 
}

void add(listADT list, elemType elem) {
  int modifyFirst = list->firstAdded == NULL;
  list->firstInc = addListRec(list->firstInc, &list->lastAdded, list->cmp, elem);
  if (modifyFirst) list->firstAdded = list->firstInc;
}

void toBegin(listADT list) {
  list->iteratorAdded = list->firstAdded;
}

int hasNext(listADT list) {
  return list->iteratorAdded != NULL;
}

elemType next(listADT list) {
  assert(list->iteratorAdded != NULL);
  elemType retValue = list->iteratorAdded->value;
  list->iteratorAdded = list->iteratorAdded->nextInsert;
  return retValue;
}

void toBeginAsc(listADT list) {
  list->iteratorInc = list->firstInc;
}

int hasNextAsc(listADT list) {
  return list->iteratorInc != NULL;
}

elemType nextAsc(listADT list) {
  assert(list->iteratorInc != NULL);
  elemType retValue = list->iteratorInc->value;
  list->iteratorInc = list->iteratorInc->nextIncreasing;
  return retValue;
}

void freeListRec(header list) {
  if (list == NULL)
    return;
  freeListRec(list->nextIncreasing);
  free(list);
}

void freeListPrime(listADT list) {
  freeListRec(list->firstInc);
  free(list);
}

