#include <stdio.h>
#include <assert.h>

/* Calcula la desviacion estandar */
double desv(const unsigned char vector[], int dim );


int main(void) {
  double d;
  unsigned char arreglo2[] = { 0x33, 0x33, 0x33, 0x33, 0x33 };
  for(int i=0; i <= 10; i++)
    assert(desv(arreglo2, i)==0);
  

  unsigned char arreglo[] = { 0x37, 0xF2, 0x03, 0x4A, 0xFF };
  assert(desv(arreglo, 1)==0);
  assert(desv(arreglo, 2)==2.0);

  assert(desv(arreglo, 3) > 4.98 && desv(arreglo, 3) < 4.99);

  assert(desv(arreglo, 10) > 5.6071 && desv(arreglo, 3) < 5.6072);

  puts("OK!");
}

#include <math.h>
/*  */
/* static double sumVec(const unsigned char vector[], int dim){ */
/*     double ans = 0; */
/*     do{ */
/*         ans += vector[--dim]; */
/*     }while(dim > 0); */
/*     return ans; */
/* } */
/*  */
/* double desv(const unsigned char vector[], int dim) { */
/*     double prom = sumVec(vector, dim)/dim, ans = 0; */
/*     do{ */
/*         ans += pow(vector[--dim] - prom, 2); */
/*     }while(dim > 0); */
/*     return sqrt(ans); */
/* } */
#define LOW 0x0F
#define HIGH 0xF0

int sumVec(const unsigned char vector[], int dim){
    char w;
    int ans = 0;
    for(double i = 0; i < dim/2.0; i += .5){
        if(i == floor(i)){
            ans += ((vector[(int)i] & HIGH) >> 4);
        } else {
            ans += vector[(int)i] & LOW;
        }
    }
    return ans;
}

double desv(const unsigned char vector[], int dim){
    if(dim == 0)
        return 0;
    double prom = (double)sumVec(vector, dim)/dim;
    double ans = 0;
    printf("El prom es: %g\n", prom);
    for(double i = 0; i < dim/2.0; i += .5){
        if(i == floor(i)){
            ans += pow(((vector[(int)i] & HIGH) >> 4) - prom, 2);
        } else {
            ans += pow((vector[(int)i] & LOW) - prom, 2);
        }
    }
    ans = sqrt(ans/dim);
    printf("El desv es: %g\n", ans);
    return ans;
}



