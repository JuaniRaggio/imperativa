#include <stdio.h>
#include <assert.h>

#define DIM 9

int sudokuSolver(char m[][DIM]);

int main(void) {
  // Una matriz vacía no es solución
  char sudoku[DIM][DIM] = {{0}};

  assert(sudokuSolver(sudoku)==0);

  char sudoku2[DIM][DIM] = {
        {3,8,1,9,7,6,5,4,2}, 
        {2,4,7,5,3,8,1,9,6},
        {5,6,9,2,1,4,8,7,3},
        {6,7,4,8,5,2,3,1,9},
        {1,3,5,7,4,9,6,2,8},
        {9,2,8,1,6,3,7,5,4},
        {4,1,2,6,8,5,9,3,7},
        {7,9,6,3,2,1,4,8,5},
        {8,5,3,4,9,7,2,6,1}
  };

    sudokuSolver(sudoku2);

  assert(sudokuSolver(sudoku2)==1);
  
  char sudoku3[DIM][DIM] = {
        {2,8,1,9,7,6,5,4,2}, 
        {3,4,7,5,3,8,1,9,6},
        {5,6,9,2,1,4,8,7,3},
        {6,7,4,8,5,2,3,1,9},
        {1,3,5,7,4,9,6,2,8},
        {9,2,8,1,6,3,7,5,4},
        {4,1,2,6,8,5,9,3,7},
        {7,9,6,3,2,1,4,8,5},
        {8,5,3,4,9,7,2,6,1}
  };

  assert(sudokuSolver(sudoku3)==0);
  
  // Cuando se tomó este ejercicio en un parcial, en una de las respuestas
  // sólo chequeaban que la suma de cada fila, columna y cuadrado fuera 45
  char sudoku4[DIM][DIM] = {
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}, 
        {5,5,5,5,5,5,5,5,5}
  };

  assert(sudokuSolver(sudoku4)==0);

  char sudoku5[DIM][DIM] = {
        {3,8,1,9,7,6,5,4,12}, 
        {2,4,7,5,3,8,1,9,6},
        {5,6,9,2,1,4,8,7,3},
        {6,7,4,8,5,2,3,1,9},
        {1,3,5,7,4,9,6,2,8},
        {9,2,8,1,6,3,7,5,4},
        {4,1,2,6,8,5,9,3,7},
        {7,9,6,3,2,1,4,8,5},
        {8,5,3,4,9,7,2,6,1}
  };

  assert(sudokuSolver(sudoku5)==0);

    puts("ok!");

  return 0;
}

/* Ejercicio 20 ***   */
/* Escribir una función que compruebe si una solución dada a un Sudoku es correcta sabiendo que: */

/* Un tablero sudoku se compone de una matriz de 9 filas por 9 columnas. A su vez el tablero se subdivide en 9 subcuadrados de 
 * 9 casillas cada uno (3x3) NO SUPERPUESTOS (un número en una posición NO puede pertenecer a dos subcuadrados).  */

/* Se debe verificar que todas las casillas contienen un número comprendido entre el 1 y el 9. 
 * Si alguna casilla contiene un número menor a 1 o mayor a 9, es incorrecta la matriz. */

/* Por fila, no hay valores repetidos */
/* Por columna, no hay valores repetidos */
/* Por subcuadrado, no hay valores repetidos */

#include <stdbool.h>
#define ONE 0x01
#define VALIDVALUES 9
#define SQUARE 3

bool reportRepetitions(char m[][DIM], int i) {
    bool exit = false;
    unsigned xyviews = 0, lastxy = 0;
    for(int j = 0; j < DIM && !exit; ++j) {
        // Tenemos que recorrer toda la fila i + toda la columna i
        /* m[i][j]: */
        xyviews = (xyviews | (1 << (m[i][j] - ONE)));
        /* m[j][i]; */
        xyviews = (xyviews | (1 << (m[j][j] + VALIDVALUES - ONE)));
        if(m[i][j] <= 0 || m[i][j] > VALIDVALUES || m[j][i] <= 0 || m[j][i] > VALIDVALUES || xyviews == lastxy) {
            exit = true;
        } else {
            lastxy = xyviews;
        }
    }
    return exit;
}

bool subSquare(char m[][DIM], int i, int j) {
    bool exit = false;
    short unsigned views = 0, lastview = 0;
    for(int x = i - SQUARE + 1; x <= i; ++x) {
        for(int y = j - SQUARE + 1; y <= j; ++y) {
            views = (views | (ONE << (m[x][y] - ONE)));
            if(views == lastview) {
                exit = true;
                break;
            } else {
                lastview = views;
            }
        }
    }
    return exit;
}

bool reportRepetitions2(char m[][DIM], int i){
    bool rep = false;
    char xa[VALIDVALUES] = {false}, ya[VALIDVALUES] = {false};
    for(int j = 0; j < DIM && !rep; ++j) {
        if (m[i][j] > VALIDVALUES || m[i][j] <= 0 || m[j][i] > VALIDVALUES || m[j][i] <= 0|| xa[m[i][j] - 1] == true || ya[m[j][i] - 1] == true)
        {
            rep = true;
        } else {
            xa[m[i][j] - 1] = true;
            ya[m[j][i] - 1] = true;
        }
    }
    return rep;
}

int sudokuSolver(char m[][DIM]){
    bool rep = false;
    for(int i = 0; i < DIM && !rep; ++i) {
        rep = reportRepetitions(m, i);
        if(i % 3 == 2) {
            // Llegamos hasta la ultima fila del subcuadrado para no tener que volver a validar los datos
            rep = subSquare(m, i, i) || subSquare(m, i, (i + SQUARE) % 9) || subSquare(m, i, (i + 2*SQUARE) % 9);
        }
    }
    return !rep;
}
