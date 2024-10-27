#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define FILS 6
#define COLS 7
#define BLOQUE 10
#define DIRECCIONES 8
#define EJES 2
#define EJEX 0
#define EJEY 1

typedef enum {DER=0, IZQ, ABA, ARR, I_AR, I_AB, D_AR, D_AB } Tdireccion;

typedef struct {
	char * palabra;
	size_t fila;
	size_t columna;
	Tdireccion direccion;
} posicion;

typedef struct {
    posicion * encontradas;
    size_t longitud;
} acumulador;


int movimiento(const int direccion[EJES], char * palabra, char sopa[FILS][COLS], int i, int j,
                int * fin) {
    *fin = 0;
    int x, y, z, coincidencias = 0;
    for (y = i, x = j, z = 0; y < FILS && y >= 0 && x < COLS && x >= 0 && palabra[z] != '\0';
    ++z, y += direccion[EJEY], x += direccion[EJEX]) {
        coincidencias += (palabra[z] == sopa[y][x]);
    }
    if (palabra[z] == '\0')
        *fin = 1;
    return coincidencias == z;
}

void agregaPalabra(char * palabra, acumulador * vistas, Tdireccion iterador, int fila, int columna) {
    posicion * aModificar = &(vistas->encontradas[vistas->longitud]);
    if (vistas->longitud % BLOQUE == 0) {
        vistas->encontradas = realloc(vistas->encontradas, sizeof(posicion) * (vistas->longitud + BLOQUE));
    }
    aModificar->direccion = iterador;
    aModificar->fila = fila;
    aModificar->columna = columna;
    aModificar->palabra = malloc(strlen(palabra) + 1);
    strcpy(aModificar->palabra, palabra);
}

Tdireccion maxDireccion(int perpendiculares[DIRECCIONES/2]) {
    int max = 0;
    for(int i = 0; i < DIRECCIONES/2; ++i) {
        perpendiculares[i] = abs(perpendiculares[i]);
        if (perpendiculares[i] > perpendiculares[max]) {
            max = i;
        }
    }
    Tdireccion dir;
    switch (max) {
        case 0:
            dir = ABA;
        break;
        case 1:
            dir = IZQ;
        break;
        case 2:
            dir = ARR;
        break;
        case 3:
            dir = DER;
        break;
    }
    return dir;
}

void agregaCoincidentes(char * palabra, char sopa[FILS][COLS], int i, int j, acumulador * vistas) {
    static int direcciones[DIRECCIONES][EJES] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    int perpendiculares[DIRECCIONES/2] = {j - COLS, i - FILS, FILS - i, COLS - j};
    Tdireccion primeraDireccion = maxDireccion(perpendiculares), iteradorDirecciones = primeraDireccion + 1;
    int marcaFin = 0;
    if (movimiento(direcciones[primeraDireccion], palabra, sopa, i, j, &marcaFin)){
        // Si no llega al final con la mayor longitud, que no pruebe con las otras direcciones
        if(marcaFin == 0)
            return;
        else 
            agregaPalabra(palabra, vistas, primeraDireccion, i, j);
    }
    while(iteradorDirecciones % DIRECCIONES != primeraDireccion) {
        if (movimiento(direcciones[iteradorDirecciones], palabra, sopa, i, j, &marcaFin) && marcaFin == 1) {
            agregaPalabra(palabra, vistas, iteradorDirecciones++, i, j);
        }
    }
}

void buscaCoincidencias(char sopa[FILS][COLS], int i, int j, char ** diccionario, acumulador * vistas) {
    int w = 0;
    while (diccionario[w][0] != '\0' && diccionario[w][0] <= sopa[i][j]) {
        agregaCoincidentes(diccionario[w], sopa, i, j, vistas);
        ++w;
    }
}

posicion * resolverSopa(char ** diccionario, char sopa[FILS][COLS]) {
    acumulador vistas;
    vistas.longitud = 0;
    vistas.encontradas = NULL;
    for(int i = 0; i < FILS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            buscaCoincidencias(sopa, i, j, diccionario, &vistas);
        }
    }
    vistas.encontradas = realloc(vistas.encontradas, sizeof(posicion) * vistas.longitud);
    return vistas.encontradas;
}

int main(void) {
  char * diccionario[] = {"ARRE", "CANCION", "CAPA", "ERROR", "ORCO", "PERRO", "PERTINAZ", "REA", "RIO", ""};
   
  char sopa[FILS][COLS] =
     {{'X','X','X','O','X','X','X'},
      {'A','P','A','C','Y','Y','O'},
      {'Z','E','Z','R','Z','C','X'},
      {'E','R','R','O','R','X','X'},
      {'X','R','I','O','I','E','X'},
      {'X','O','X','X','O','X','X'}};
  
  posicion * res = resolverSopa(diccionario, sopa);
  // La cantidad de palabras encontradas debe ser 9
  int expected = 9;
  int count = 0;
  while ( res[count].palabra != NULL)
     printf("%s\n", res[count++].palabra);
  assert(count == expected);

  assert(strcmp(res[0].palabra,"ARRE")==0);
  assert(res[0].fila==1);
  assert(res[0].columna==2);
  assert(res[0].direccion==D_AB);

  assert(strcmp(res[3].palabra,"ORCO")==0);
  assert(res[3].fila==3);
  assert(res[3].columna==3);
  printf("%d\n", res[3].direccion);
  assert(res[3].direccion==ARR);
  
  assert(strcmp(res[4].palabra,"ORCO")==0);
  assert(res[4].fila==4);
  assert(res[4].columna==3);
  assert(res[4].direccion==D_AR);

  assert(strcmp(res[6].palabra,"REA")==0);
  assert(res[6].fila==3);
  assert(res[6].columna==2);
  assert(res[6].direccion==I_AR);
  free(res);
  puts("OK primera parte");
  
  char * diccionario2[] = {""};
  res = resolverSopa(diccionario2, sopa);
  // La cantidad de palabras encontradas debe ser 0
  expected = 0;
  count = 0;
  while ( res[count].palabra != NULL)
     printf("%s\n", res[count++].palabra);
  assert(count == expected);
  free(res); 
  puts("OK sin palabras encontradas");
  return 0;
}

