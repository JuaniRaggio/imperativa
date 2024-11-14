#include <stdlib.h>
#include <stdio.h>

typedef struct node * TList;

typedef struct node {
    int elem;
    struct node * tail;
} TNode;

TList deleteAll(TList l1, TList l2) {
    if (l1 == NULL || l2 == NULL) return l1;
    if (l1->elem == l2->elem) {
        TList aux = l1;
        l1 = deleteAll(l1->tail, l2->tail);
        free(aux);
        return l1;
    } else if (l1->elem < l2->elem) {
        l1->tail = deleteAll(l1->tail, l2);
        return l1;
    }
    l1 = deleteAll(l1, l2->tail);
    return l1;
}

TList createList(const int arr[], size_t size) {
    if (size == 0) return NULL;
    TList head = malloc(sizeof(TNode));
    head->elem = arr[0];
    head->tail = createList(arr + 1, size - 1);
    return head;
}

// Función auxiliar para imprimir una lista
void printList(TList l) {
    while (l != NULL) {
        printf("%d ", l->elem);
        l = l->tail;
    }
    printf("\n");
}

// Función auxiliar para liberar la memoria de una lista
void freeListPrime(TList l) {
    if (l != NULL) {
        freeListPrime(l->tail);
        free(l);
    }
}

// Función principal para probar deleteAll
int main(void) {
    // Crear lista l: {1, 2, 3, 4, 5, 6, 7}
    int arrL[] = {1, 2, 3, 4, 5, 6, 7};
    TList l = createList(arrL, sizeof(arrL) / sizeof(arrL[0]));

    // Crear lista m: {0, 1, 3, 5, 10, 11, 14}
    int arrM[] = {0, 1, 3, 5, 10, 11, 14};
    TList m = createList(arrM, sizeof(arrM) / sizeof(arrM[0]));

    // Imprimir listas originales
    printf("Lista l original: ");
    printList(l);
    printf("Lista m: ");
    printList(m);

    // Ejecutar deleteAll
    l = deleteAll(l, m);

    // Imprimir lista l después de eliminar los elementos de m
    printf("Lista l después de deleteAll: ");
    printList(l);

    // Liberar memoria
    freeListPrime(l);
    freeListPrime(m);

    return 0;
}

