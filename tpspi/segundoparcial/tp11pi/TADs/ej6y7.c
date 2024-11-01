#include <stdlib.h>
#include <utillist.h>

int elemAtIdx(TList list, int idx) {
    TList aux = list;
    while (idx > 0 && aux != NULL) {
        aux = aux->tail;
        --idx;
    }
    if (aux == NULL)
        exit(1);
    return aux->elem;
}

void map(TList list, int (*modifier)(int)) {
    if (list == NULL)
        return;
    list->elem = modifier(list->elem);
    map(list->tail, modifier);
}

