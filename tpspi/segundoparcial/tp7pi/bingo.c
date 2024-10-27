#include <stdlib.h>
#include <getnum.h>
#include <rand.h>

#define FILS 3
#define COLS 5
#define JUGADORES 2
#define BALLS 90
#define TOOK 1

typedef  int TipoLinea[5];

typedef  TipoLinea  TipoCarton [3];

int take_ball(char taken[BALLS]) {
    int take;
    do {
        take = randInt(1, BALLS);
    } while(taken[take] == 0);
    taken[take] = TOOK;
    return take;
}

// Este item me fuerza a que cada vez que extraiga una bolita, voy a tener que recorrer toda la matriz
/* imprimirá paso a paso la bolilla extraída y los números faltantes (que aún no salieron)de cada cartón */
// Si gano el jugador[i], retorna su subindice
int play(int n_players, TipoCarton board[n_players]) {
    char taken[BALLS] = {0};
}

/* Las bolillas están representadas por los números del 1 al 90 y cada jugador tiene un cartón con 15 números distintos. */
/* Los cartones son generados por el programa en forma aleatoria */
int ** board_mkr() {
    int ** board = malloc(FILS * sizeof(*board));
    for(int i = 0; i < FILS; ++i) {
        board[i] = malloc(COLS * sizeof(int));
        for(int j = 0; j < COLS; ++j) {
            board[i][j] = randInt(1, BALLS - 1);
        }
    }
    return board;
}

int main(void){
    int n_players;
    do {
        n_players = getint("How many players are you?");
    } while(n_players <= 0);

    TipoCarton players;
    for(int i = 0; i < n_players; ++i) {
    }
}

