#include <stdio.h>
#include <assert.h>
#include "utillist.h"

/**
** En esta versiรณn dejamos el primer elemento de una secuencia de repetidos
** Puede ser void porque el head de la lista no cambia
*/
void deleteDupl (TList list);

/*
** Dejamos el ultimo de la secuencia, por lo que la lista puede cambiar
*/ 
TList deleteDupl2 (TList list);


int main(void) {

  // Secuencias sin repetir, cantidad par e impar de repetidos
  // Probar repetidos en el medio, al principio y al final
  // En realidad no hace falta que esten ordenados, deberia funcionar igual
  int v[] = {1, 2, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8};
  int w[] = {1, 2, 3, 4, 5, 6,  7, 8};

  TList l1 = fromArray(v, 16);
  deleteDupl(l1);
  assert(checkElems(l1, w, 8));
  freeList(l1);

  l1 = fromArray(v, 16);
  l1 = deleteDupl2(l1);
  assert(checkElems(l1, w, 8));
  freeList(l1);

  l1 = fromArray(v, 1);
  deleteDupl(l1);
  assert(checkElems(l1, w, 1));
  freeList(l1);

  l1 = fromArray(v, 1);
  l1 = deleteDupl2(l1);
  assert(checkElems(l1, w, 1));
  freeList(l1);

  l1 = fromArray(v, 2);
  deleteDupl(l1);
  assert(checkElems(l1, w, 2));
  freeList(l1);

  l1 = fromArray(v, 2);
  l1 = deleteDupl2(l1);
  assert(checkElems(l1, w, 2));
  freeList(l1);

  l1 = fromArray(v, 4);
  deleteDupl(l1);
  assert(checkElems(l1, w, 3));
  freeList(l1);

  l1 = fromArray(v, 4);
  l1 = deleteDupl2(l1);
  assert(checkElems(l1, w, 3));
  freeList(l1);

  l1 = fromArray(v+2, 5);
  deleteDupl(l1);
  assert(checkElems(l1, w+2, 2));
  freeList(l1);

  l1 = fromArray(v+2, 5);
  l1 = deleteDupl2(l1);
  assert(checkElems(l1, w+2, 2));
  freeList(l1);

  printf ("OK!\n");
  return 0;
}
