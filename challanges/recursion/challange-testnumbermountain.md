---
id: challange-testnumbermountain
aliases:
  - challange-testnumbermountain
tags:
  - pi
  - clang
  - recursividad
  - imperativa
---
#### 14-10-2024
---
#################################################
    NIVEL DE DIFICULTAD: 5/10 - Podria ser un ejercicio de parcial [VERIFICADO]
#################################################

Una montaña de numeros consiste en dado un numero n, imprimir todos los numeros de manera escalonada
ascendente hasta n y luego descendente hasta 1. Por ejemplo, si n = 5, la montaña de numeros es:
1 2 3 4 5 4 3 2 1

Se pide implementar la funcion number_mountain() que reciba un numero entero n y guarde
la montaña de numeros en un puntero. Ademas, se debe imprimir por pantalla la montaña de numeros
a medida que se va armando.

La montaña no puede estar formada por mas de 100 numeros y debe contener todos numeros positivos
(el 0 no cuenta).

En caso que no se pueda armar la montaña de numeros, la funcion debe devolver NULL y no imprimir nada.

Consideraciones:
- Liberar toda la memoria reservada (en caso de ser necesario).
- No utilizar variables globales.
- Se pueden usar funciones auxiliares.
- La funcion recursiva no debe ocupar mas de 6 lineas.

Tips:
- Combinar recursion de tipo stack (FILO - ida) con recursion de tipo cola (FIFO - vuelta).
- Pensar como la funcion recursiva sabe el numero a guardar en la montaña y como frenar la recursion (caso base).
- Pensar si se puede saber de antemano el tamaño de la montaña.

Ejemplos:
- Input: n = 5
  Output: mountain = [1, 2, 3, 4, 5, 4, 3, 2, 1]
          terminal = 1 2 3 4 5 4 3 2 1

- Input: n = 1
  Output: mountain = [1]
          terminal = 1

- Input: n = 0
  Output: mountain = NULL -> no se puede armar la montaña de numeros porque no tiene numeros
          terminal =

- Input: n = 100
  Output: mountain = NULL -> no se puede armar la montaña de numeros porque supera el limite de 100 numeros
          terminal =

- Input: n = 63
  Output: mountain = NULL -> no se puede armar la montaña de numeros porque supera el limite de 100 numeros
          terminal =

- Input: n = -5
  Output: mountain = NULL -> no se puede armar la montaña de numeros porque tendria numeros negativos
          terminal =

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned int *number_mountain(int n);

int main()
{
    int n = 5;
    unsigned int *mountain = number_mountain(n);
    assert(mountain != NULL);
    unsigned int expected_5[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    unsigned int *expected_ptr = expected_5;
    for (int i = 0; i < (2 * n - 1); i++)
    {
        assert(expected_ptr[i] == mountain[i]);
    }

    n = 1;
    mountain = number_mountain(n);
    assert(mountain != NULL);
    unsigned int expected_1[] = {1};
    expected_ptr = expected_1;
    for (int i = 0; i < (2 * n - 1); i++)
    {
        assert(expected_ptr[i] == mountain[i]);
    }

    n = 0;
    mountain = number_mountain(n);
    assert(mountain == NULL);

    n = 100;
    mountain = number_mountain(n);
    assert(mountain == NULL);

    n = 63;
    mountain = number_mountain(n);
    assert(mountain == NULL);

    n = -5;
    mountain = number_mountain(n);
    assert(mountain == NULL);

    // EL PROGRAMA NO DEBE TENER LEAKS DE MEMORIA
    printf("OK!");
    return 0;
}
```


## Doubts
---

## References
---


