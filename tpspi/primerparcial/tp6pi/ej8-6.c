#include <assert.h>
#include <stdint.h>
#include <stdio.h>

void unirArreglos(const int ar1[], const int ar2[], int resultado[]);

void check(const int v1[], const int v2[]) {
  int i;
  for (i = 0; v1[i] != -1; i++)
    assert(v1[i] == v2[i]);
  assert(v1[i] == -1);
  assert(v2[i] == -1);
}

int main(void) {
  int v1[] = {1, 5, 15, 15, 30, 35, 35, 35, 35, 35, 45, 55, -1};
  int v2[] = {-1};
  int v3[] = {1, 1, 1, 1, 1, 1, -1};
  int v4[] = {2, 3, 15, 16, 33, 35, 45, 65, -1};

  int res[30];

  int v1_v2[] = {1, 5, 15, 30, 35, 45, 55, -1};
  unirArreglos(v1, v2, res);
  check(v1_v2, res);

  unirArreglos(v2, v2, res);
  check(v2, res);

  unirArreglos(v1, v1, res);
  check(v1_v2, res);

  unirArreglos(v1, v3, res);
  check(v1_v2, res);

  int expected[] = {1, 2, 3, 5, 15, 16, 30, 33, 35, 45, 55, 65, -1};
  unirArreglos(v1, v4, res);
  check(expected, res);

  puts("OK!");
  return 0;
}

#define FIN -1

// Puedo solucionarme la vida guardando el ultimo elemento que copie en rta y no copiar ese


int avanza_cambio(const int ar1[], int desde){
    int actual = ar1[desde];
    while(ar1[desde] != FIN){
        if(ar1[desde] != actual)
            return desde;
        ++desde;
    }
    return desde;
}

void copy_no_reps(const int arr[], int idx, int rta[], int rta_idx){
    while(arr[idx] != FIN){
        if(arr[idx] != arr[idx + 1])
            rta[rta_idx++] = arr[idx];
        ++idx;
    }
    rta[rta_idx] = FIN;
}

void unirArreglos(const int ar1[], const int ar2[], int resultado[]){
    int last_cp = ar1[0] < ar2[0] ? !ar1[0]:!ar2[0];
    int i = 0, j = 0, w = 0;
    while(ar1[i] != FIN && ar2[j] != FIN){
        if(ar1[i] == last_cp){
            i = avanza_cambio(ar1, i);
        }
        if(ar2[j] == last_cp){
            j = avanza_cambio(ar2, j);
        }
        if(ar2[j] == FIN || ar1[i] == FIN)
            break;
        // ar2 => 1 1 1 1 1 2 3
        // ar1 => 1 1 3 4 5 6 7
        // last_cp == ar2 
        // retorna cuanto le tengo que sumar a i para que cambie de elemento fn(ar2, i) -> recorra hasta cambiar de elemento
        // last_cp == ar1
        if(ar1[i] < ar2[j] && last_cp != ar1[i]){
            last_cp = ar1[i];
            resultado[w++] = ar1[i++];
        } else if (ar1[i] > ar2[j] && last_cp != ar2[j]){
            last_cp = ar2[j];
            resultado[w++] = ar2[j++];
        } else {
            last_cp = ar2[j];
            resultado[w++] = ar2[j++];
            i++;
        }
    }
    ar1[i] == FIN ? copy_no_reps(ar2, j, resultado, w):copy_no_reps(ar1, i, resultado, w);
}




















/* #define FIN -1 */
/*  */
/* void printarr(int a[]){ */
/*     for(int i = 0; a[i] != FIN; ++i){ */
/*         printf("%d ", a[i]); */
/*     } */
/*     putchar('\n'); */
/* } */
/*  */
/* void copyarr(int target[], int ft, const int source[], int fs){ */
/*     int lv = FIN; */
/*     while(source[fs] != FIN){ */
/*         if (source[fs] == lv) { */
/*             ++fs; */
/*         } else { */
/*             target[ft++] = source[fs]; */
/*             lv = source[fs++]; */
/*         } */
/*     } */
/*     target[ft] = FIN; */
/* } */
/*  */
/* int del(const int a[], int toDel, int from){ */
/*     int i = 0; */
/*     while(a[from] == toDel){ */
/*         ++i; */
/*         ++from; */
/*     } */
/*     return i; */
/* } */
/*  */
/* void unirArreglos(const int ar1[], const int ar2[], int resultado[]) { */
/*     int i = 0, j = 0, w = 0; */
/*     while (ar1[i] != -1 && ar2[j] != -1){ */
/*         if (ar1[i] == ar2[j]) { */
/*             resultado[w++] = ar1[i]; */
/*             i += del(ar1, ar1[i], i); */
/*             j += del(ar2, ar2[j], j); */
/*         } else if (ar1[i] < ar2[j]) { */
/*             resultado[w++] = ar1[i++]; */
/*         } else if (ar1[i] > ar2[j]) { */
/*             resultado[w++] = ar2[j++]; */
/*         } */
/*     } */
/*     ar1[i] == FIN ? copyarr(resultado, w, ar2, j):copyarr(resultado, w, ar1, i); */
/*     printarr(resultado); */
/* } */
/*  */
