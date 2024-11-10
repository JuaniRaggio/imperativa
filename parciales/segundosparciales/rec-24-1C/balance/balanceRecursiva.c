#include <stdlib.h>
#include <stdio.h>

typedef struct docNode {
    int id;
    double amount;
    struct docNode * tail;
} docNode;

typedef docNode * docList;

typedef struct balanceNode {
    int id;
    double balance;
    struct balanceNode * tail;
} balanceNode;

typedef balanceNode * balanceList;


balanceList balance(docList list) {
    if (list == NULL) return NULL;
    balanceList aux = balance(list->tail);
    if (aux == NULL || list->id != aux->id) {
        balanceList new = malloc(sizeof(*new));
        new->id = list->id;
        new->balance = list->amount;
        new->tail = aux;
        return new;
    }
    aux->balance += list->amount;
    return aux;
}

// Función para crear un nodo de docList
docList createDocNode(int id, double amount, docList tail) {
    docList newNode = (docList)malloc(sizeof(docNode));
    newNode->id = id;
    newNode->amount = amount;
    newNode->tail = tail;
    return newNode;
}

// Función para crear un nodo de balanceList
balanceList createBalanceNode(int id, double balance, balanceList tail) {
    balanceList newNode = (balanceList)malloc(sizeof(balanceNode));
    newNode->id = id;
    newNode->balance = balance;
    newNode->tail = tail;
    return newNode;
}

// Función para imprimir una balanceList (para verificar el resultado)
void printBalanceList(balanceList list) {
    while (list != NULL) {
        printf("{%d, %.1f} -> ", list->id, list->balance);
        list = list->tail;
    }
    printf("NULL\n");
}

// Función de prueba
void testBalance() {
    // Crear la lista de documentos según el ejemplo
    docList docs = createDocNode(1, 100.0, 
                  createDocNode(1, -90.0, 
                  createDocNode(1, -10.0, 
                  createDocNode(3, 95.0, 
                  createDocNode(3, -10.0, 
                  createDocNode(5, -10.0, NULL))))));

    // Llamar a la función balance
    balanceList result = balance(docs);

    // Crear la lista esperada
    balanceList expected = createBalanceNode(1, 0.0,
                          createBalanceNode(3, 85.0,
                          createBalanceNode(5, -10.0, NULL)));

    // Imprimir el resultado y el esperado para compararlos
    printf("Resultado de balance: ");
    printBalanceList(result);
    printf("Esperado: ");
    printBalanceList(expected);

    // Liberar memoria (opcional, pero recomendado)
    // Aquí deberías implementar la liberación de memoria para ambas listas.
}

int main() {
    testBalance();
    return 0;
}

