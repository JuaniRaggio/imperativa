#include <stdlib.h>
#include <stdio.h>

typedef struct node * TList;

typedef struct node {
    int elem;
    struct node * tail;
} TNode;

TList eliminaRec(TList lista) {
    if (lista == NULL || lista->tail == NULL) return lista;
    if (lista->elem >= lista->tail->elem) {
        TList toFree = lista->tail;
        lista->tail = lista->tail->tail;
        free(toFree);
        lista = eliminaRec(lista);
        return lista;
    }
    lista->tail = eliminaRec(lista->tail);
    return lista;
}

// Función auxiliar para imprimir la lista
void printList(TList list) {
    while (list != NULL) {
        printf("%d ", list->elem);
        list = list->tail;
    }
    printf("\n");
}

// Función auxiliar para crear un nodo de la lista
TList createNode(int elem, TList tail) {
    TList newNode = malloc(sizeof(TNode));
    if (newNode == NULL) {
        perror("Error al crear nodo");
        exit(1);
    }
    newNode->elem = elem;
    newNode->tail = tail;
    return newNode;
}

// Función auxiliar para liberar la memoria de la lista
void freeListPrime(TList list) {
    TList temp;
    while (list != NULL) {
        temp = list;
        list = list->tail;
        free(temp);
    }
}

// Función de prueba
void testPurgeAscendingOrder(void) {
    // Test case 1: Lista en orden ascendente, no debería cambiar
    TList list1 = createNode(1, createNode(3, createNode(4, createNode(5, createNode(8, createNode(10, NULL))))));
    printf("Test case 1 - Lista original: ");
    printList(list1);
    list1 = eliminaRec(list1);
    printf("Test case 1 - Lista después de purgar: ");
    printList(list1);
    freeListPrime(list1);

    // Test case 2: Lista con elementos fuera de orden
    TList list2 = createNode(1, createNode(1, createNode(3, createNode(2, createNode(4, createNode(5, createNode(8, createNode(10, createNode(1, NULL)))))))));
    printf("\nTest case 2 - Lista original: ");
    printList(list2);
    list2 = eliminaRec(list2);
    printf("Test case 2 - Lista después de purgar: ");
    printList(list2);
    freeListPrime(list2);

    // Test case 3: Lista con un solo elemento mayor al resto
    TList list3 = createNode(12, createNode(1, createNode(3, createNode(4, createNode(5, createNode(8, createNode(10, NULL)))))));
    printf("\nTest case 3 - Lista original: ");
    printList(list3);
    list3 = eliminaRec(list3);
    printf("Test case 3 - Lista después de purgar: ");
    printList(list3);
    freeListPrime(list3);
}

int main(void) {
    testPurgeAscendingOrder();
    return 0;
}
