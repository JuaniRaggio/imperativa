/* Escribir una función recursiva productoEsc que reciba tres parámetros de entrada representando dos vectores de números reales de igual tamaño */
/* y su dimensión. La función debe regresar en su nombre el producto escalar de los vectores recibidos. */
#include <stdio.h>
#include <assert.h>

#define EPS 0.0001

double productoEsc(double v1[], double v2[], int dim);

int main(void) {

  double v1[] = {0.0, 1.0, 2.2, 3.5, 4.5};

  double v2[] = {0.0, -1.0, 5.0, -3.0, 3.0};
  
  double res[] = {0, -1.0, 10.0, -0.5, 13.0};

  assert(productoEsc(v1, v2, 0)==0.0);
  
  for(int i=0; i<5; i++){
        printf("%g ", productoEsc(v1, v2, i + 1));
     assert(productoEsc(v1, v2, i+1) - res[i] < EPS);
    }
  

  printf ("OK!\n");
  return 0;
}

double productoEsc(double v1[], double v2[], int dim){
    if (dim == 0)
        return 0;
    return (v1[0] * v2[0]) + productoEsc(v1 + 1, v2 + 1, dim - 1);
}

