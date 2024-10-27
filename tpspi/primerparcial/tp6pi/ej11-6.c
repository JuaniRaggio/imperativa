#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXCOL 10

/* Ordena por el método de burbujeo */
void ordenaMatriz (int matriz[][MAXCOL], int fil, int col, int colOrd);

int checkVector(const int v1[], const int v2[], int dim) {
  for(int i=0; i < dim; i++)
    if ( v1[i] != v2[i])
      return 0;
  return 1;
}

int main(void) {
  int m[][MAXCOL] = { {1, 2, 3, 4, 5},
            {6, 2, 8, 9, 10},
            {3, 5, 8, 2, 1},
            {8, 7, 3, 6, 7}};

  int m2[][MAXCOL] = { {1, 2, 3, 4, 5},
            {6, 2, 8, 9, 10},
            {3, 5, 8, 2, 1},
            {8, 7, 3, 6, 7}};
  
  // La matriz no cambia 
  ordenaMatriz(m, 4, 5, 2);

  for(int i=0; i < 4; i++)
    assert(checkVector(m[i], m2[i], 5));

  ordenaMatriz(m, 4, 5, 1);
  assert(checkVector(m[0], m2[0], 5));
  assert(checkVector(m[1], m2[2], 5));
  assert(checkVector(m[2], m2[1], 5));
  assert(checkVector(m[3], m2[3], 5));
  
  ordenaMatriz(m, 4, 5, 3);
  assert(checkVector(m[0], m2[0], 5) || checkVector(m[0], m2[3], 5));
  assert(checkVector(m[1], m2[0], 5) || checkVector(m[1], m2[3], 5));
  assert(checkVector(m[2], m2[1], 5) || checkVector(m[2], m2[2], 5));
  assert(checkVector(m[3], m2[1], 5) || checkVector(m[3], m2[2], 5));

  printf("OK!\n");
  return 0;
}

static void swapVec(int v1[], int v2[], int dim){
    int aux;
    for(int i = 0; i < dim; ++i){
        aux = v1[i];
        v1[i] = v2[i];
        v2[i] = aux;
    }
}

void ordenaMatriz (int matriz[][MAXCOL], int fil, int col, int colOrd){
    colOrd = colOrd - 1;
    bool swapped;
    for(int i = fil - 1; i > 0; --i){ // We don't include the 0 cause it will be in its correct place for the time we get there
        swapped = false;
        for(int j = 1; j <= i; ++j){
            if(matriz[j - 1][colOrd] > matriz[j][colOrd]){
                swapVec(matriz[j - 1], matriz[j], col);
                swapped = true;
            }
        }
        if(swapped == false)
            return;
    }
}


