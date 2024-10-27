#include <assert.h>
#include <stdio.h>


void unirArreglos ( const int ar1[], const int ar2[], int resultado[]);


void check(const int v1[], const int v2[]) {
  int i;
  for(i=0; v1[i] != -1; i++)
     assert(v1[i]==v2[i]);
  assert(v1[i]==-1);
  assert(v2[i]==-1);
}

int main(void) {
  int v1[] = { 1, 5, 15, 30, 35, 45, 55, -1};
  int v2[] = {-1};
  int v3[] = { 1, -1};
  int v4[] = { 2, 3, 15, 16, 33, 35, 45, 65, -1};
  int dimRes;
  int res[30];

  unirArreglos(v1, v2, res);
  check(v1, res);

  unirArreglos(v2, v2, res);
  check(v2, res);

  unirArreglos(v1, v1, res);
  check(v1, res);

  unirArreglos(v1, v3, res);
  check(v1, res);

  int expected[] = {1, 2, 3, 5, 15, 16, 30, 33, 35, 45, 55, 65, -1};
  unirArreglos(v1, v4, res);
  check(expected, res);

  printf("OK!\n");
  return 0;
}

#define FIN -1

static void pegaArreglo(const int a[], int desdea, int rta[], int desder){
    do{
        rta[desder++] = a[desdea++];
    } while(a[desdea] != FIN);
    rta[desder] = FIN;
}

void unirArreglos (const int ar1[], const int ar2[], int resultado[]){
    int i = 0, j = i, w = i;
    while(ar1[i] != FIN && ar2[j] != FIN){
        if(ar1[i] < ar2[j]){
            resultado[w++] = ar1[i++];
        } else if (ar1[i] > ar2[j]){
            resultado[w++] = ar2[j++];
        } else {
            resultado[w++] = ar1[i++];
            j++;
        }
    }
    ar1[i] == FIN ? pegaArreglo(ar2, j, resultado, w):pegaArreglo(ar1, i, resultado, w);
}

