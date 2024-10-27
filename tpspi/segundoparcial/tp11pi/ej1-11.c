#include <stdio.h>
#include <assert.h>
#include <utillist.h>
#include <stdlib.h>


TList removeIf (TList list, int (*criteria)(int));

int esPar(int n) {
  return n % 2 == 0;
}

int esImpar(int n) {
  return n % 2;
}

int true(int n) {
  return 1;
}


int main(void) {

  int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int v_i[] = {1, 3, 5, 7, 9};
  int v_p[] = {2, 4, 6, 8};
  int p[] = {2, 4, 6, 8, 4, 2, 0, -10};

  TList l1 = fromArray(v, 9);
  l1 = removeIf(l1, esPar);
  assert(checkElems(l1,v_i, 5));
    freeList(l1);

  l1 = fromArray(v, 9);
  l1 = removeIf(l1, esImpar);
  assert(checkElems(l1,v_p, 4));
    freeList(l1);

  l1 = fromArray(v, 9);
  l1 = removeIf(l1, true);
  assert(l1==NULL);
    freeList(l1);

  l1 = fromArray(p, 8);
  l1 = removeIf(l1, esPar);
  assert(l1==NULL);
    freeList(l1);

  l1 = fromArray(p, 8);
  l1 = removeIf(l1, esImpar);
  assert(checkElems(l1, p, 8));
    freeList(l1);
  
  l1 = removeIf(NULL, esImpar);
  assert(l1==NULL);
    freeList(l1);

  printf ("OK!\n");
  return 0;
}


// AMBAS SOLUCIONES ESTAN BIEN!!!!!!!!!!!!!!!!!!!!!!!


// Estoy suponiendo que no esta ordenada la lista porque en ese caso
// tendria que pedir una funcion de orden ya que en principio no sabemos
// si los elementos son numeros
TList removeIf(TList list, int (*criteria)(int)) {
    if (list == NULL)
        return list;
    if (criteria(list->elem)) {
        TList aux = list;
        list = removeIf(list->tail, criteria);
        free(aux);
    } else {
        list->tail = removeIf(list->tail, criteria);
    }
    return list;
}

/* TList removeIf (TList list, int (*criteria)(int)) { */
/*     if (list == NULL) return NULL; */
/*     if (criteria(list->elem)) { */
/*         TList aux = list; */
/*         list = list->tail; */
/*         free(aux); */
/*         list = removeIf(list, criteria); */
/*     } else { */
/*         list->tail = removeIf(list->tail, criteria); */
/*     } */
/*     return list; */
/* } */


