/*
Dado un vector de N elementos enteros positivos, implementar la funcion
int_hash_table() que devuelva un puntero de punteros a enteros, donde la
cantidad de punteros es M, y cada posicion (es decir cada uno de los M punteros)
tiene una cantidad indicada en otro puntero recibido por parametro (contiene basura)
llamado quantities, entonces la cantidad de elementos del puntero i se indica en
quantities[i].
Cada elemento del vector recibido se asignara al puntero correspondiente de acuerdo
a una funcion provista llamada hash() que recibe un entero y la cantidad de punteros M,
y devuelve un entero positivo menor a M. En caso que no haya ningun elemento para un
puntero, se asignara NULL.
La funcion hash() se encuentra ya implementada, es provista y NO debe modificarse.
Prototipo:
unsigned int** int_hash_table(unsigned int* vector, unsigned int N, unsigned int* quantities, unsigned int M) {
Consideraciones:
- No guardar mas bytes de los necesarios, en caso de necesitarlo.
- Modularizar lo mas posible (ej. la funcion int_hash_table() debe tener una logica
  muy simple, delegando en otras funciones la resolucion de problemas ajenos a su
  responsabilidad).
- Liberar toda la memoria dinamica que se solicite, en caso de necesitarla.
- No utilizar ciclos anidados.
Ejemplos:
- Input: vector = {1, 2, 3}, N = 3, quantities = {?, ?, ?}, M = 2
- Output: { {2}, {1, 3} } porque 1 % 2 = 1, 2 % 2 = 0, 3 % 2 = 1
          quantities = {1, 2}
- Input: vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, N = 10, quantities = {?, ?, ?}, M = 3
- Output: { {3, 6, 9}, {1, 4, 7, 10}, {2, 5, 8} } porque 1 % 3 = 1, 2 % 3 = 2, 3 % 3 = 0, 4 % 3 = 1, ...
          quantities = {3, 4, 3}
- Input: vector = {1, 1, 1, 6, 6, 4, 0}, N = 7, quantities = {?, ?, ?, ?, ?}, M = 5
- Output: { {0}, {1, 1, 1, 6, 6}, {NULL}, {NULL}, {4} } porque 1 % 5 = 1, 6 % 5 = 1, 4 % 5 = 4, 0 % 5 = 0
          quantities = {1, 5, 0, 0, 1}
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static unsigned int hash(unsigned int value, unsigned int M);
unsigned int** int_hash_table(unsigned int* vector, unsigned int N, unsigned int* quantities, unsigned int M);

int main() {
    unsigned int vector[] = {1, 1, 1, 6, 6, 4, 0};
    unsigned int quantities[7];
    unsigned int N = 7;
    unsigned int M = 5;

    unsigned int** hash_table = int_hash_table(vector, N, quantities, M);

    unsigned int expected_quantities[] = {1, 5, 0, 0, 1};
    unsigned int r1[] = {0};
    unsigned int r2[] = {1, 1, 1, 6, 6};
    unsigned int r5[] = {4};
    unsigned int * expected_map[] = {
        r1,
        r2,
        NULL,
        NULL,
        r5
    };

    for (int i = 0 ; i < M; i++) {
        assert(quantities[i] == expected_quantities[i]);
        for (int j = 0; j < expected_quantities[i]; j++) {
            assert(hash_table[i][j] == expected_map[i][j]);
        }
        if(quantities[i] == 0) {
            assert(hash_table[i] == expected_map[i]);
        }
    }

    // ESTE PROGRAMA TIENE LEAKS DE MEMORIA,
    // los pueden ver utilizando la flag -fsanitize=address
    // resuelvanlos :D
    puts("OK!");
    return 0;
}

/*
funcion hash() que recibe un entero y la cantidad de punteros M,
y devuelve un entero positivo menor a M
*/

#define BLOCK 5

static unsigned int hash(unsigned int value, unsigned int M) {
    return value % M;
}


unsigned int** int_hash_table(unsigned int* vector, unsigned int N, unsigned int* quantities, unsigned int M) {
    unsigned int **table = malloc(sizeof(*table) * M);
    for(int i = 0; i < M; ++i) {
        table[i] = NULL;
        quantities[i] = 0;
        // quantities va a ser un vector de dimensiones que me indica cuanto tengo guardado en cada table[i]
    }

    unsigned int r_pos;
    for(int i = 0; i < N; ++i) {
        r_pos = hash(vector[i], M);
        if(quantities[r_pos] % BLOCK == 0) {
            table[r_pos] = realloc(table[r_pos], sizeof(**table) * (quantities[r_pos] + BLOCK));
        }
        table[r_pos][quantities[r_pos]++] = vector[i];
    }
    // A cada elemento del vector, le va a assignar una posicion en table, mediante la funcion hash()

    for(int i = 0; i < M; ++i) {
        if(quantities[i] % BLOCK != 0)
            table[i] = realloc(table[i], sizeof(**table) * quantities[r_pos]);
        // Realloc a la posicion final ya que me piden no dejar bytes de mas
        // El if esta para no hacer tantos llamados al sistema en caso de que no sea necesario
    }
    return table;
}

