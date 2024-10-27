#include <assert.h>
#include <stdio.h>

/* 
** Versión de test para vectores ordenados
** Tener en cuenta que el test evalúa resultado final, no eficiencia
*/

int
delDuplicates( const int a[], int dim, int ans[]);


int main(void) {
  int v[] = { -3, -3, -1, 0, 1, 2, 2, 2, 3, 3, 3};
  int res[20];
  int dimRes;

  dimRes = delDuplicates(v, 0, res);
  assert(dimRes==0);

  dimRes = delDuplicates(v, 1, res);
  assert(dimRes==1);
  assert(res[0]==-3);

  dimRes = delDuplicates(v, 2, res);
  assert(dimRes==1);
  assert(res[0]==-3);

  dimRes = delDuplicates(v, 11, res);
  assert(dimRes==6);
  assert(res[0]==-3);
  assert(res[1]==-1);
  assert(res[2]==0);
  assert(res[3]==1);
  assert(res[4]==2);
  assert(res[5]==3);


  int n=80000;
  int v2[n];
  int res2[n];
  for (int i=0; i < n; i++)
     v2[i] = 100;
  dimRes = delDuplicates(v2, n, res2);
  assert(dimRes==1);
  assert(res2[0]==100);

  for (int i=0; i < n; i++)
     v2[i] =i;
  dimRes = delDuplicates(v2, n, res2);
  assert(dimRes==n);
  for (int i=0; i < n; i++)
    assert(res2[i]==i);

  puts("OK!");
  return 0;
}

int delDuplicates(const int a[], int dim, int ans[]){
    int newDim = 0, last = !a[newDim];
    for(int i = 0; i < dim; ++i){
        if(a[i] != last){
            ans[newDim++] = last = a[i];
        }
    }
    return newDim;
}

