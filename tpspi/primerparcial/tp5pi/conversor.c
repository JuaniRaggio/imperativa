#include <ctype.h>
#define DELTA ('a' - 'A')
#include <stdio.h>

int mayMin(int c);
int minMay(int c);
int sigCar(int c);
int circ(int c);
void menu(void);

int main() {
  menu();
  return 0;
}

void menu() {
  printf("Introduzca : \n1 - Si desea convertir su caracter de minuscula a "
         "mayuscula\n"
         "2 - Si desea convertir su caracter de mayuscula a minuscula\n"
         "3 - Si desea imprimir el caracter siguiente\n"
         "4 - Si desea imprimir la letra en forma circular\n");
  int opcion, c;
  while ((opcion = getchar() - '0') < 1 && opcion > 4) {
    printf("La opcion no existe\n");
  }
  printf("Introduzca el caracter que desea modificar: ");
  while (!isalpha(c = getchar())) {
    printf("El caracter es invalido\n");
  }
  switch (opcion) {
  case 1:
    c = minMay(c);
    break;
  case 2:
    c = mayMin(c);
    break;
  case 3:
    c = sigCar(c);
    break;
  case 4:
    c = circ(c);
    break;
  }
  printf("%c", c);
}

int minMay(int c) {
  if (c <='z' && c >= 'a')
    c = c - DELTA;
  return c;
}

int mayMin(int c) {
  if (c <= 'Z' && c >= 'A')
    c = c + DELTA;
  return c;
}

int circ(int c) {
  if (c == 'z')
    c = 'a';
  else if (c == 'Z')
    c = 'A';
  else
    c = c + 1;
  return c;
}

int sigCar(int c) { return c + 1; }
