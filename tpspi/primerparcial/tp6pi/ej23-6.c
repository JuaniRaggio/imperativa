#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef unsigned int uInt ;


/* Recibe un string con el formato dd/mm/yyyy y retorna por parámetro el día, mes
** y año de la misma. En caso de que el formato sea inválido
** o la fecha incorrecta, retorna FALSE y no altera los parámetros
*/
int valorFecha( const char * fecha, uInt *dia, uInt *mes, uInt * anio);


int main(void) {
  unsigned int d=100, m=200, a=300;
  int res;
  res = valorFecha("", &d, &m, &a);
  assert(res==0);
  assert(d==100);
  assert(m==200);
  assert(a==300);

  res = valorFecha("29/02/1999", &d, &m, &a);
  assert(res==0);
  assert(d==100);
  assert(m==200);
  assert(a==300);

  res = valorFecha("30/14/2020", &d, &m, &a);
  assert(res==0);
  assert(d==100);
  assert(m==200);
  assert(a==300);

  res = valorFecha("12/12/", &d, &m, &a);
  assert(res==0);
  assert(d==100);
  assert(m==200);
  assert(a==300);

  res = valorFecha("1/1/2000", &d, &m, &a);
  assert(res==0);
  assert(d==100);
  assert(m==200);
  assert(a==300);

  res = valorFecha("12/01/2000", &d, &m, &a);
  assert(res==1);
  assert(d==12);
  assert(m==1);
  assert(a==2000);

  res = valorFecha("29/02/1900", &d, &m, &a);
  assert(res==0);
  assert(d==12);
  assert(m==1);
  assert(a==2000);

  res = valorFecha("29/02/2000", &d, &m, &a);
  assert(res==1);
  assert(d==29);
  assert(m==2);
  assert(a==2000);

  puts("OK");
  return 0;
}

#define ESBISIESTO(a) ((a) % 4 == 0 && (a) % 400 == 0)
#define MINDIA 1
#define MINMES 1
#define MAXMES 12
#define MINANIO 1000
#define MAXANIO 9999

int testMY(int x, int max, int min) {
    return (x <= max && x >= min);
}

int valorFecha( const char * fecha, uInt *dia, uInt *mes, uInt * anio){
    
    typedef enum meses { FEBB = 0, ENE, FEB, MAR, ABR, MAY, JUN, JUL, AGO, SEP, OCT, NOV, DIC } m;
    uInt diasM[] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Use el 0 para los dias del febrero bisiesto 

    if(fecha[2] != '/' || fecha[5] != '/' )
        return 0;

    int auxMes = atoi(fecha + 3);
    int auxAnio = atoi(fecha + 6);
    if (!testMY(auxMes, MAXMES, MINMES)  || !testMY(auxAnio, MAXANIO, MINANIO)) {
        return 0;
    } 

    int maxDia = (auxMes == FEB && ESBISIESTO(auxAnio) ? diasM[FEBB]:diasM[auxMes]), auxDia = atoi(fecha);
    if (!testMY(auxDia, maxDia, MINDIA)) {
        return 0;
    }

    *dia = auxDia;
    *mes = auxMes;
    *anio = auxAnio;
    return 1;
} 



