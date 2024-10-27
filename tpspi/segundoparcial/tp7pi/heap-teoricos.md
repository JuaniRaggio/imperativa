---
id: guia7-teoricos
aliases:
  - guia7-teoricos
tags:
  - imperativa
  - clang
  - pi
  - heap
---
#### 30-09-2024
---
## Doubts
---
- En la linea 110 (ej13, ultimo item)... Cuando hacemos realloc de un puntero, en caso de que realloc devuelva null, teniamos que guardar una variable auxiliar para que no haya memory leaks pero si no devuelve null, entiendo que realloc hace un free automatico de lo que teniamos en esa zona -> ==Exactamente, realloc libera lo que "recorta" o lo que deje de usar==
#### Ejercicio 11
---
```c
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void resize(char * p, unsigned int bytes) {
    // El problema con esta funcion es que p es una copia de la variable 
    // que me vayan a pasar
    // => p = ... no va a cambiar a la p que me esten pasando por lo que 
    // no se va a tener acceso a esa direccion
    // desde el programa
    p = realloc(p, bytes);
}

char * aMayusculas(char * s) {
    char * t;
    for(t = s; (*t = toupper(*t)); t++);
    return s;
}

int main(void) {
    int v[] = {1, 2, 3, 0};
    /* printf("%s\n", aMayusculas(v + 1)); */
    /* printf("%s\n", v); */
    /* char * p = "Hola mundo!"; */
    /* printf("%s\n", aMayusculas(p + 1)); */
    /* printf("%s\n", p); */
    char * p = NULL;
    resize(p, 100); 
    strcpy(p, "Hello world");
    aMayusculas(p);
    printf("%s\n", p);
    return 0;
}

```

#### Ejercicio 12
---
char * p\[2\]\[3\] =
{{"abc","defg","hi"},{"jklmn","pqrstuvw","xyz"}};
a) ¿Cuántos bytes de memoria ocupa la declaración?
- Ocupa 8 para el puntero.
- Si le sumamos lo que ocupa cada zona de memoria
  seria: 8 + 4 + 5 + 3 + 6 + 9 + 4

b) Completar el siguiente cuadro:

|                                                                         |                       |       |
| ----------------------------------------------------------------------- | --------------------- | ----- |
| Expresión                                                               | Expresión Equivalente | Valor |
| * * * p                                                                 | p[0][0][0]            | 'a'   |
| * * p\[1\]                                                              | p\[1\]\[0\]\[0\]      | 'j'   |
| * * (p\[1\]+2) -> Aca no hace + 2 \* sizeof(char\*) \* strlen(p\[1\]) ? | p\[1\]\[0\]\[\]       | 'l'   |
| \*(\*(p+1)+1)\[7\]                                                      |                       |       |
| (\*(\*(p+1)+1))\[7\]                                                    |                       |       |
| \*(p\[1\]\[2\]+2)                                                       | p\[1\]\[2\]\[2\]      | 'z'   |

#### Ejercicio 13
---
Encontrar el error en cada uno de los segmentos de programa. De ser posible, explicar cómo corregirlo:
```c
int *numero;
printf ("%d\n", *numero); // Borrar el *


float *realPtr;
long *integerPtr;
integerPtr = realPtr; -> integerPtr = (long *) realPtr;

int *x, y;
x = y; -> x = &y;

char s[] = "esta es una cadena de caracteres";  
for (; *s != '\0'; s++) -> Definir un puntero auxiliar con otro nombre
printf("%c ", *s);

short *numPtr, result, auxiliar=0;
void *genericoPtr;
numPtr = &auxiliar;
genericoPtr = numPtr;
result =  * genericoPtr + 7; -> result = *((short *) genericoPtr) + 7;

// La correccion a esto depende de que es lo que se quiera hacer
char * s;
printf("%s\n", s);

char *s, *aux;
s = malloc(20);
aux = realloc(s, 100);
free(s);
free(aux);
---
if(aux != NULL)
	free(aux);
free(s);
---
```

#### Ejercicio 14
---
Se tiene una función con la siguiente declaración:
static int x\[8\] = { 10, 20, 30, 40, 50, 60, 70, 80 };

¿Qué se referencia con x ?
- Es una constante que hace referencia a la direccion del primer vlaor del vector, es decir a donde este el primer byte de 10
¿Qué se referencia con (x+2)?
- Hace referencia a la direccion del 3er elemento
¿Qué se referencia con \*x ?
- Al valor derecho de la direccion de memoria del primer valor del vector x, es decir, 10
¿Qué se referencia con \*x+2 ?
- Idem anterior pero le sumo 2 al respectivo valor derecho -> 12
¿Qué se referencia con \*(x+2) ?
- Al valor derecho del 3er elemento del vector -> 30
Suponiendo que x\[0\] esté almacenado en la dirección de memoria $10F0, en qué dirección de memoria se encuentra almacenado x\[4\]? -> En la direccion $10F0 + sizeof(x\[0\]) * 4, osea en la $1100

#### Ejercicio 15
---
Se tiene una función con la siguiente declaración:

static float  tabla\[2\]\[3\] = {{1.1, 1.2, 1.3}, {2.1, 2.2, 2.3}};

Graficar el almacenamiento en memoria del arreglo tabla (a partir de la dirección $1000) y decir qué tipo de dato es y qué se referencia con:

Suponiendo que se hacen las lineas aisladas, es decir que la primera no afecta a la segunda, la segunda a la tercera y asi...

tabla -> $1000
tabla+1 -> $1000 + 1 * sizeof(\*tabla) -> $1000 + 3\*8
\*(tabla + 1) -> Idem anterior pero al valor derecho, osea &2.1
\*(tabla + 1) + 1 -> $1000 + 3 \* 8 + 1 \* sizeof(\*\*tabla)
\*tabla + 1 -> $1000 + 1 \* sizeof(\*\*tabla)
\*(\*(tabla + 1) + 1)  -> 
\*(\*tabla + 1) -> 1.2
\*(\*(tabla + 1)) -> 2.1
\*(\*tabla + 1) + 1 -> 1.2 + 1
tabla\[1\] -> Direccionde memoria del elemento \[1\]\[0\] -> &2.1
tabla\[0\] + 1 -> &tabla\[0\]\[1\]
\*(tabla\[1\]) + 1 -> tabla\[1\]\[0\] + 1 == 2.1
\*tabla\[1\] -> 1.1
tabla\[0\]\[1\]  -> 1.2

#### Ejercicio 16
---
Se tiene un programa con la siguiente declaración:

static char  \*color\[6\] = { “rojo”, “verde”, “azul”, “blanco”, “negro”, “amarillo” };

 Graficar el almacenamiento en memoria del arreglo color (a partir de $2004).
	 ![[Guia 7.jpeg]]
 ¿Qué se referencia con color?
	2004
 ¿Qué se referencia con (color+2)?
	200F
 ¿Qué se referencia con \*color?
	2004
 ¿Qué se referencia con \*(color + 2)?
	200F
 ¿En qué se diferencian  color\[5\]   y   \*(color + 5)?
	En nada, solo la notacion
 ¿Qué se referencia con \*\*color?
	Es el primer char del primer vector -> r
 ¿Qué se referencia con \*color\[0\]?
	Idem anterior
 ¿Qué se referencia con \*\*color + 2?
	 Idem anterior pero le suma dos -> La letra que viene 2 posiciones despues de la r en la tabla ascii osea la t

#### Ejercicio 18
---
Indicar y corregir los errores en cada una de las siguientes funciones.
![[Guia 7 1.jpeg]]

#### Ejercicio 19
---
Escribir la función copiaPrefijo que dado un string s y un número entero n retorne en su nombre un nuevo string con los primeros n caracteres del string s. Si la longitud de s es menor a n debe retornar una copia de s. En caso de que no se pueda copiar debe retornar NULL. ¿Qué cuidado debe tener el usuario de esta función?
```c
char * copiaPrefijo(const char * s, unsigned int n) {
    char * copia = NULL;
    int i;
    for (i = 0; i < n && s[i] != '\0'; ++i) {
        if(i % BLOCK == 0)
            copia = realloc(copia, sizeof(*copia) * (i + BLOCK));
        copia[i] = s[i];
    }
    copia = realloc(copia, sizeof(char*) * (i + 1));
    copia[i] = '\0';
    return copia;
}
```

