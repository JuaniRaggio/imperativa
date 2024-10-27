#include <stdio.h>
#include <assert.h>

#define COLS 4

int sonAmigas(const int (m1[])[COLS], unsigned int fils1,const int (m2[])[COLS], unsigned int fils2);

int 
main(void)
{
  int m1[][COLS] = {{0,1,2,3}, {4,4,5,6}, {7,8,8,9}};
  int m2[][COLS] = {{0,1,2,3}, {-3,7,8,9}, {-1,3,4,7}, {4,5,6,8}};
  int m3[][COLS] = {{2,3,3,7}};
  assert(sonAmigas(m1,3,m2,4)==1);
  assert(sonAmigas(m1,1,m2,4)==1);
  assert(sonAmigas(m1,2,m2,4)==1);
  assert(sonAmigas(m1,2,m2,2)==0);
  assert(sonAmigas(m2,4,m1,3)==2);
  assert(sonAmigas(m1,3,m3,1)==0);
  assert(sonAmigas(m3,1,m1,3)==0);
  int res = sonAmigas(m1,3,m1,3);
  assert(res==1 || res==2);
  
  printf("OK !\n");

  return 0;
}

/* Una fila es amiga de otra si todos los elementos de una fila están incluidos en otra. */
/* Una matriz es amiga de otra si todas las filas de la primera matriz son amigas de alguna fila de la segunda matriz. */

/* m1: la primera matriz de enteros  */
/* fils1: la cantidad de filas de la primera matriz de enteros */
/* m2: la segunda matriz de enteros */
/* fils2: la cantidad de filas de la segunda matriz de enteros */

/* Nota 1: Se cuenta con la constante simbólica COLS que indica la cantidad de columnas de la primera y segunda matriz de 
 * enteros. */

/* Nota 2: Todas las filas tienen sus elementos ordenados de manera no descendente (cada elemento es menor o igual al
 * siguiente) */

#include <stdbool.h>
#define ONEOFTWO 1
#define TWOOFONE 2
#define NONE 0

bool testNOFriendship(const int r1[COLS], const int r2[COLS]){
    bool found = true;
    for(int i = 0; i < COLS && found; ++i){
        found = false;
        for(int j = 0; j < COLS; ++j){
            if (r1[i] == r2[j]){
                found = true;
                break;
            }
        }
    }
    return found;
}

bool testFriendship(const int r1[COLS], const int r2[COLS]){
    bool found = false, keepGoing = true;
    for(int i = 0, j = 0; i < COLS && j < COLS && keepGoing;){
        if (r1[i] < r2[j]) {
            keepGoing = false;
        } else if (r1[i] > r2[j]) {
            found = false;
            ++j;
        } else {
            found = true;
            ++i;
        }
    }
    return found;
}

bool rowFriendship(const int row[COLS], const int m2[][COLS], unsigned int fils2){
    bool foundFriend = false;
    for(int i = 0; i < fils2 && !foundFriend; ++i){
        foundFriend = testFriendship(row, m2[i]);
    }
    return foundFriend;
}

bool friendof(const int (m1[])[COLS], unsigned int fils1, const int (m2[])[COLS], unsigned int fils2){
    bool friendship = true;
    for(int i = 0; i < fils1 && friendship; ++i){
        friendship = rowFriendship(m1[i], m2, fils2);
    }
    return friendship;
}

int sonAmigas(const int (m1[])[COLS], unsigned int fils1,const int (m2[])[COLS], unsigned int fils2){
/* La función debe retornar: */
/* 1: si la primera matriz es amiga de la segunda */
/* 2: si la segunda matriz es amiga de la primera */
/* 0: en cualquier otro caso */
    return (friendof(m1, fils1, m2, fils2) == true ? ONEOFTWO:(friendof(m2, fils2, m1, fils1) == true ? TWOOFONE:NONE));
}

