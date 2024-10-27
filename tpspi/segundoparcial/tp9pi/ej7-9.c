#include <stdio.h>
#include <assert.h>

int busquedaBinaria(int v[], int dim, int nro);

int main(void) {

  int v[] = {-10, -5, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45};

  assert(busquedaBinaria(v, 0, -10)==0);
  assert(busquedaBinaria(v, 1, -10)==1);
  assert(busquedaBinaria(v, 2, -10)==1);
  assert(busquedaBinaria(v, 2, -5)==1);
  assert(busquedaBinaria(v, 2, 0)==0);

  assert(busquedaBinaria(v+1, 2, -10)==0);
  assert(busquedaBinaria(v+1, 2, -5)==1);
  assert(busquedaBinaria(v+1, 2, 0)==1);
  
  for(int i=0; i < 12; i++)
    assert(busquedaBinaria(v, 12, v[i])==1);
    
  for(int i=0; i < 11; i++)
    assert(busquedaBinaria(v, 11, v[i])==1);


  printf ("OK!\n");
  return 0;
}

int busquedaBinaria(int v[], int dim, int nro) {
    if (dim == 0)
        return 0;
    return v[dim/2] == nro || (v[dim/2] < nro ? busquedaBinaria(v + dim/2 + 1, dim - dim/2 - 1, nro):busquedaBinaria(v, dim/2, nro));
}

