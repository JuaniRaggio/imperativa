#include <assert.h>
#include <stdio.h>

#define QUEEN 1
#define THREADS 0
#define OK 1

void init(int dim, char arr[dim]){
    for(int i = 0; i < dim; ++i){
        arr[i] = 0;
    }
}

int check_threads(int dim, char tab[][dim], int i, int j, char f[dim], char c[dim], char di[2*dim-1], char id[2*dim-1],
                int nQueens) {
    if(nQueens > dim || f[i] == QUEEN || c[j] == QUEEN || di[j + dim - i] == QUEEN || id[i + j] == QUEEN)
        return THREADS;
    f[i] = QUEEN;
    c[j] = QUEEN;
    di[j + dim - i] = QUEEN;
    id[i + j] = QUEEN;
    return OK;
    // Si algo falla, retornamos THREAD, sino OK
}

int nQueens(int dim, char tab[][dim]) {
    int n = 0, cleanQueen = OK;
	char fil[dim], col[dim], di[2 * dim - 1], id[2 * dim - 1];
	init(dim, fil); init(dim, col); init(dim, di); init(dim, id);
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim; ++j){
            if(tab[i][j] == '1'){
                ++n;
                cleanQueen = check_threads(dim, tab, i, j, fil, col, di, id, n);
            }
            if(!cleanQueen)
                return THREADS;
        }
    }
    return n == dim;
}

int
main(void) {
    char board[][8] = {
            {'0', '0', '0', '0', '1', '0', '0', '0'},
            {'0', '1', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '0', '0', '0', '0', '0'},
            {'1', '0', '0', '0', '1', '1', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0'},
    };
    // Hay dos reinas en la columna 4, y dos en la fila 5
    assert(nQueens(8, board) == 0);

    char board2[][6] = {
            {'0', '0', '0', '1', '0', '0'},
            {'1', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '1', '0'},
            {'0', '1', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '1'},
            {'0', '0', '1', '0', '0', '0'}
    };
    // Hay 6 reinas y no se atacan, retorna true
    assert(nQueens(6, board2));
    
    char board3[][6] = {
            {'0', '0', '1', '0', '0', '0'},
            {'1', '0', '0', '0', '0', '0'},
            {'0', '1', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '1', '0'},
            {'0', '0', '0', '1', '0', '0'},
            {'0', '0', '0', '0', '0', '1'}
    };
    // Las reinas en 1,0 y 2,1 se amenazan en forma diagonal
    assert(nQueens(6, board3)==0);
    
	char board4[][6] = {
            {'0', '0', '0', '1', '0', '0'},
            {'0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '1', '0'},
            {'0', '1', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '1'},
            {'0', '0', '1', '0', '0', '0'}
    };
	// No se amenanzan pero hay menos de 6 reinas
    assert(nQueens(6, board3)==0);
	
    // No hay solución para tableros de dimension 2 o 3
    assert(nQueens(3, board2)==0);
    assert(nQueens(2, board2)==0);

    char board1[][1] = {{'1'}};
    assert(nQueens(1, board1));

    printf("OK!\n");
    return 0;
}
