#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#define ALLOWED 1
#define NOTAWL 0
#define OK 1

int test_changes(int letras, char ladder[][letras], int current_word, int * last_change){
    // Para nuestra implementacion no es necesario porque inicializamos i en 1
    if(current_word == 0) {
        return OK;
    } 
    int local_change = -1;
    for(int i = 0, current_changes = 0; i < letras; ++i) {
        if(tolower(ladder[current_word - 1][i]) != tolower(ladder[current_word][i])) {
            local_change = i;
            ++current_changes;
        }
        if(*last_change == local_change || current_changes > ALLOWED) {
            return NOTAWL;
        }
    }
    *last_change = local_change;
    return OK;
}

int isWordLadder(int palabras, int letras, char ladder[][letras]){
    int last_change = -1; // Inicializamos en -1 pues no nos interviene con el primer cambio
    for(int i = 1; i < palabras; ++i) {
        if(test_changes(letras, ladder, i, &last_change) == NOTAWL) {
            return NOTAWL;
        }
    }
    return OK;
}

#define COLS 4

int
main(void) {
    char wordMatrix[][COLS] = {
            {'T', 'e', 'S', 't'},
            {'b', 'e', 'S', 'T'},
            {'B', 'E', 's', 'o'},
            {'B', 'E', 'S', 'A'}};
    // Considerando todas las filas no es escalera
    // pues los últimos dos cambios son en la última letra
    assert(!isWordLadder(4, 4, wordMatrix));
    // Considerando una sola fila es escalera
    assert(isWordLadder(1, 4, wordMatrix) == 1);
    // Considerando las tres primeras filas es escalera
    assert(isWordLadder(3, 4, wordMatrix) == 1);

    char wordMatrix2[][3] = {
            {'T', 'e', 'S'},
            {'t', 'b', 'e'},
            {'S', 'b', 'E'},
            {'B', 'b', 'e'}};
    // TeS -> Tbe cambian dos letras
    assert(!isWordLadder(4, 3, wordMatrix2));

    char wordMatrix3[][3] = {
            {'a', 'm', 'o'},
            {'a', 'r', 'o'},
            {'o', 's', 'a'}};
    // aro -> osa cambian tres letras
    assert(!isWordLadder(3, 3, wordMatrix3));
    puts("OK!");
    return 0;
}
