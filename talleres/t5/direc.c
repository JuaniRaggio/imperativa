#include <stdio.h>
#include <assert.h>
 
#define FILAS 7
#define COLS 6
 
#define ERROR (-1)
 
int calculaDireccion(char mat[][COLS], int alto, int ancho, int x, int y);
 
int
main(void) {
    char tablero[][COLS] = {
            {'0', '0', '0', '0', '1', '0'},
            {'X', 'X', '0', '0', '0', '0'},
            {'0', '0', '0', '0', 'X', 'X'},
            {'0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', 'X', '0', '0'},
            {'1', '0', '0', 'X', 'X', 'X'}
    };
    int res = calculaDireccion(tablero, FILAS, COLS, 4, 1);
    assert(res == 0 || res == 45);
 
    assert(calculaDireccion(tablero, FILAS, COLS, 0, 0) == 0);
    assert(calculaDireccion(tablero, FILAS, COLS, 6, 2) == 90);
    assert(calculaDireccion(tablero, FILAS, COLS, 5, 4) == 135);
    assert(calculaDireccion(tablero, FILAS, COLS, 3, 5) == 180);
    assert(calculaDireccion(tablero, FILAS, COLS, 0, 5) == 225);
 
    res = calculaDireccion(tablero, FILAS, COLS, 3, 2);
    assert(res == 0 || res == 45 || res == 90 || res == 270);
 
    // Jugador fuera del tablero
    assert(calculaDireccion(tablero, FILAS, COLS, FILAS, COLS) == ERROR);
 
    printf("OK!\n");

    return 0;
}

#define MAX(a, b) ((a) >= (b) ? (a):(b))

unsigned int calcVersor(char mat[][COLS], int alto, int ancho, int x, int y, int i, int j){
    unsigned int dist = 0;
    for(;x >= 0 && x < alto && y >= 0 && y < ancho; x += i, y += j) {
        if(mat[x][y] == 'X' || mat[x][y] != 1)
            break;
        ++dist;
    }
    return dist;
}

int calculaDireccion(char mat[][COLS], int alto, int ancho, int x, int y){
    unsigned int maxdir = 0, dirs;
    int retValue = 0;
    for(int i = -1; i < 1; ++i) {
        for(int j = -1; j < 1; ++j) {
            if(i != 0 || j != 0){
                dirs = calcVersor(mat, alto, ancho, x, y, i, j);
            }
            if(dirs > maxdir) {
                maxdir = dirs;
                retValue += 45;
            }
        }
    }
    return retValue;
}

