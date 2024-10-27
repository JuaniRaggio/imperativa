#include <stdio.h>
#include <assert.h>

#define ALTO 6
#define ANCHO 5

void suavizar(unsigned char imagen[ALTO][ANCHO], unsigned int w);

int equals(unsigned int cols, unsigned char m1[][cols], unsigned char m2[][cols], unsigned int rows) {
  for (int i=0; i < rows; i++) {
     for(int j=0; j < cols; j++) {
         if ( m1[i][j] != m2[i][j]) {
            return 0;
         } else {
                printf("El [%d][%d] esta ok\n", i, j);
            }
     }
  }
  return 1;  
}

int main(void) {
  unsigned char bmp[ALTO][ANCHO] =    {
      {10,10,20,23,24},
      {10,12,18,25,23},
      {12,14,18,26,22},
      {12,14,19,20,22},
      {13,16,19,20,22},
      {14,14,19,21,23}};
 
  
  suavizar(bmp, 3);
  unsigned char suave[ALTO][ANCHO] =    {
      {10,13,18,22,23},
      {11,13,18,22,23},
      {12,14,18,21,23},
      {13,15,18,20,22},
      {13,15,18,20,21},
      {14,15,18,20,21}};

  assert(equals(ANCHO, bmp, suave, ALTO));

  // Ahora una con w=5
  unsigned char suave5[ALTO][ANCHO] =    {
	{14,16,17,19,20},
	{14,16,17,18,20},
	{14,16,17,18,20},
	{15,16,17,18,20},
	{15,16,17,18,20},
	{15,16,17,18,19}};

   suavizar(bmp, 5);
   assert(equals(ANCHO, bmp, suave5, ALTO));

  puts("OK!");
  return 0;
}
/* Ejercicio 15 ***(resuelto en video) */

/* Una imagen bmp se almacena en un archivo como una matriz de píxeles. */

/* Si la imagen es de escala de grises, cada píxel ocupa un solo byte. Así, si la imagen tiene 20x30 píxeles, ocupa 600 bytes 
 * donde un byte con el valor 0x00 corresponde al negro y un byte con el valor 0xFF corresponde al blanco. 
 * Cualquier valor entre 0x00 y 0xFF será una tonalidad de gris. 
 */

/*
 * Realizar una función suavizar que, dada una imagen, la suavice aplicando un filtro de media de valor W, con W impar. 
 * Esto significa que cada píxel (i, j) de la nueva imagen se obtiene a partir de la media aritmética de los píxeles que se 
 * encuentran en la imagen original de la submatriz de tamaño WxW centrada en (i,j).
 */

/*
 * La función suavizar recibe como únicos parámetros la matriz y W. Si W es menor que 3 o no es impar,
 * la función no altera la imagen.  
 */

/* El ancho y alto de la imagen son las constantes simbólicas ANCHO y ALTO respectivamente. */

#define MAX(a, b) ((a) > (b) ? (a):(b))
#define MIN(a, b) ((a) < (b) ? (a):(b))

unsigned char average_submatrix(const unsigned char image[ALTO][ANCHO], int i, int j, int subdim){
    // avg lo hacemos unsigned int porque es posible que se exceda del max unsigned char
    subdim = subdim/2;
    int avg = 0, px = 0;
    for(int x = MAX(0, i - subdim); x <= MIN(ALTO - 1, i + subdim); ++x) {
        for(int y = MAX(0, j - subdim); y <= MIN(ANCHO - 1, j + subdim); ++y){
            avg += image[x][y];
            ++px;
        }
    }
    return avg/px;
}

void pastetrix(unsigned char source[ALTO][ANCHO], unsigned char target[ALTO][ANCHO]){
    for(int i = 0; i < ALTO; ++i){
        for(int j = 0; j < ANCHO; ++j){
            target[i][j] = source[i][j];
        }
    }
}

void suavizar(unsigned char imagen[ALTO][ANCHO], unsigned int w) {
    if (w % 2 == 0 || w < 3 || ANCHO <= 0 || ALTO <= 0)
        return;
    // Hacemos una copia para que los cambios no afecten al promedio de los pixels "vecinos"
    unsigned char copy[ALTO][ANCHO];
    for (int i = 0; i < ALTO; ++i){
        for (int j = 0; j < ANCHO; ++j){
            copy[i][j] = average_submatrix(imagen, i, j, w);
        }
    }
    pastetrix(copy, imagen);
}

// EL PROBLEMA CON LA SIG SOL ES QUE NO SE HACE LA COPIA DE LA IMAGEN Y AL MODIFICAR LA IMAGEN DIRECTO, ADULTERA LOS PROMEDIOS
//
/* #define MAX(a, b) ((a) > (b) ? (a):(b)) */
/* #define MIN(a, b) ((a) < (b) ? (a):(b)) */
/*  */
/* static int filter(unsigned char img[ALTO][ANCHO], unsigned int w, int i, int j){ */
/*     const int iLimit = MIN(i + (int)w/2 + 1, ALTO); */
/*     const int jLimit = MIN(j + (int)w/2 + 1, ANCHO); */
/*     const int newi = MAX(i - (int)w/2, 0), newj = MAX(j - (int)w/2, 0); */
/*     int average = 0, divider = 0; */
/*     for(i = newi; i < iLimit; ++i){ */
/*         for(j = newj; j < jLimit; ++j){ */
/*             average += img[i][j]; */
/*             ++divider; */
/*         } */
/*     } */
/*     average /= (divider != 0 ? divider:1); */
/*     return average; */
/* } */
/*  */
/* void suavizar(unsigned char imagen[ALTO][ANCHO], unsigned int w){ */
/*     if(w < 3 || w % 2 == 0) */
/*         return; */
/*     for(int i = 0; i < ALTO; ++i){ */
/*         for(int j = 0; j < ANCHO; ++j){ */
/*             imagen[i][j] = filter(imagen, w, i, j); */
/*         } */
/*     } */
/* } */
/*  */
