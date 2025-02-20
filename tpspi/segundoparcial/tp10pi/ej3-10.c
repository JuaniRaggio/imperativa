#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utillist.h"

// TambiÃ©n podria ser de tipo TList
void order (TList list);

int main(void) {

  int v[] = {1,1,2,1,0,-1,3,3,3,3,3,10,9,100,100,998};
  int dimV = sizeof(v)/sizeof(v[0]);
  TList list = fromArray(v, dimV);
  
  order(list);
  int o[] = {1,2,3,10,100,998};
  assert(checkElems(list, o, sizeof(o)/sizeof(o[0]))==1);

  order(list);
  assert(checkElems(list, o, sizeof(o)/sizeof(o[0]))==1);
  freeList(list);
 
  TList empty = NULL;
  order(empty);
  assert(empty ==NULL);

  list = fromArray(v,1);
  order(list);
  assert(list->elem ==1 && list->tail == NULL);
  freeList(list);

  int w[] = {1,1,1,1,1,1,1,1,1,1};
  list = fromArray(w, sizeof(w)/sizeof(w[0]));
  order(list);
  assert(list->elem ==1 && list->tail == NULL);
  freeList(list);

  printf ("OK!\n");
  return 0;
}

void order (TList list) {
    if (list == NULL || list->tail == NULL) {
        return;
    } else if (list->elem < list->tail->elem) {
        order(list->tail);
    } else if (list->elem >= list->tail->elem) {
        TList aux = list->tail;
        list->tail = list->tail->tail;
        free(aux);
        order(list);
    }
}

