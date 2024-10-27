---
id: guia8-teoricos
aliases:
  - guia8-teoricos
  - structs-guia
tags:
  - clang
  - structs
  - pi
  - imperativa
  - lists
  - strings
  - matrices
  - heap
---
#### 06-10-2024
---
#### Ejercicio 1
---
Corregir los siguientes fragmentos de codigo
```c
char c = 'a';

char *p = malloc(sizeof(char));

// No tiene sentido hacer esto, estas perdiendo la direccion de memoria 
// de la memoria allocada
p = &c;

// En cambio hacer esto
*p = c;

// o no allocar p y asignarle &c
```

```c
struct art {

    int code;

   double price;

};

  

struct art * newArt(int code, double price) {
// No tiene sentido hacer calloc pues me inicializa la struct toda en 0
// si despues voy a pisar esos valores
	struct art * p = calloc(1, sizeof(struct art));
	
// Mejor hacer:
	struct art * p = malloc(sizeof(struct art));
	
	p->code = code;
	
	p->price = price;
	
	return p;

}
```

```c
int * p = malloc(n * sizeof(int));

   int * q = p;

   /* llenamos y usamos el vector */

   //   ...

   //   ...

   // Ya no los necesitamos, podemos liberar ambos vectores

// p y q apuntan al mismo lugar, hacer free(p) es lo mismo que free(q)
// Entonces estas liberando dos veces lo mismo, basta con hacerlo una vez
   free(p);  

   free(q);
```

```c
// Fragmento de codigo para buscar las secuencias repetidas de un vector
for (int i=0; i<dim ; i++){
      if(vec[i] == vec[i+1]) {
// Esta mal el limite del for ya que i + 1 va a exceder dim y vas a leer
// una zona que no queres leer
// Entonces hacer:
for(int i = 0; i + 1 < dim; ++i){
	if(vec[i] == vec[i + 1]){
	...
	}
}

```

```c
struct art {

    int code;

   double price;

};

  

struct art * newArt(int code, double price) {

    struct art p;

    p.code = code;

    p.price = price;
    // La zona del stack de esta funcion no tiene nada que ver con el de
    // las funciones que vayan a estar fuera de este scope, por lo que
    // &p va a ser una zona de memoria que podria ser pisada por otra 
    // funcion o incluso por el main
    // Por lo que hay que crear el struct en el heap para que no pueda
    // ser pisado por otra funcion
    return &p;
}
```

```c
int * p;

p = realloc(p, cant * sizeof(int));
// p puede no inicializarse en null por lo que apunta a cualquier lado,
// por lo que realloc va a dar un error de ejecucion
```

#### Ejercicio 2
---
Indique si cada uno de los siguientes enunciados es verdadero o falso. Si es falso, 

explicar por qué:

1. Las estructuras pueden contener únicamente un tipo de datos.
==Falso== => Justamente lo que nos permite una struct a diferencia de un vector es agrupar *datos homogeneos*

3. Dos uniones pueden ser comparadas entre sí para determinar si son iguales
==Falso== => Dependiendo si con exactamente del mismo tipo o no. Independientemente de si los tipos de datos dentro de dos structs distintas son los mismos y estan en el mismo orden, si o si tienen que ser el mismo tipo. Ademas de esto si dentro de la struct hay vectores de dimension constante, puede pasar que el relleno sea distinto y nos de que dos structs son distintas mientras que lo que nosotros podemos leer vamos a definirlas como iguales. Conclusion, si bien se puede comparar, no es seguro que vaya a darte un resultado coherente con lo que uno esperaria que de

4. La palabra reservada typedef se utiliza para definir nuevos tipos de datos.
==Falso== => typedef se utiliza para renombrar tipos de datos existentes o combinaciones de tipos de datos existentes

1. Las estructuras no pueden ser comparadas.
==Falso== => Como mencionamos en el item 3, si pueden ser comparadas pero no significa que el resultado de la comparacion me de un resultado coherente con lo que espero

6. Una estructura de n elementos siempre ocupa más memoria que n variables del mismo tipo que los campos de la estructura.
==Falso== => Depende de que tipo de datos sean y depende si la cantidad de datos que se usan es multiplo de 4

7. Con  *typedef int Matriz\[5\]\[10\]*  se reservan  50 * sizeof(int) bytes de memoria.
==Verdadero==

#### Ejercicio 3
---
Encontrar el error en cada uno de los siguientes puntos:

1. Suponer que struct carta se ha definido conteniendo dos apuntadores al tipo char: figura y palo. También, la variable c ha sido declarada del tipo struct carta y la variable cPtr ha sido declarada como puntero a struct carta. La variable cPtr ha sido asignada a la dirección de c. Se imprime  printf("%s\n", * cPtr->figura);
Deberia ser => ` printf("%s\n", cPtr->figura`

2. Suponer que el arreglo corazones\[13\] ha sido declarado del tipo struct carta.  
Se intenta imprimir el miembro figura del elemento 10 del arreglo con  printf("%s\n", corazones.figura);
Deberia ser =>  ``` printf("%s\n", corazones[10].figura```

3. Se declara la estructura persona:
```c
struct persona  {
	char apellido[15];
	char nombre[15];
	int edad;
};

// Ahi se creo la estructura: struct persona
// Para crear la estructura persona:
typedef struct {
	char apellido[15];
	char nombre[15];
	int edad;
} persona;

```

4. Suponiendo que struct persona ha sido definida como en la parte (c), pero con la corrección apropiada, se declara la variable m a través de:  persona m;
Si se usa el typedef como lo anote yo, es correcto declarar una variable m a traves de: persona m;
Si no se desea usar typedef, deberia ser: struct persona m;


5. Indicar cuál de los siguientes fragmentos de código es correcto para recorrer un vector de estructuras definidas según el punto c

| **Esta es incorrecta** ya que v es una constante y se la esta intentando modificar                                                                                            | *Esta es correcta*                                                                                                                                                                                           |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| struct persona v[DIM];<br><br>// se llena el vector<br><br>...<br><br>  <br><br>for (int i=0; i<DIM; i++) {<br><br>   printf("%s\n", (\*v).apellido);<br><br>   v++;<br><br>} | struct persona v[DIM];<br><br>struct persona \*p = v;<br><br>// se llena el vector<br><br>...<br><br>  <br><br>for (int i=0; i<DIM; i++) {<br><br>   printf("%s\n", (\*p).apellido);<br><br>   p++;<br><br>} |

#### Ejercicio 4
---
1. Simular un juego de naipes de 52 cartas, en el cual se mezcle el mazo y se tomen las 5 primeras cartas, indicando si se obtuvo alguna de las siguientes configuraciones:    

- PAR:  hay sólo dos de las cinco cartas con igual valor
- PIERNA:  hay sólo tres de las cinco cartas de igual valor
- POKER: hay cuatro cartas con igual valor

2. Extender el punto anterior de modo tal que jueguen la computadora contra el usuario hasta que se acabe el mazo o el usuario decida no seguir jugando. Acumular los puntajes obtenidos por ambos jugadores considerando que el ganador de cada mano obtiene 1 punto y solo se considera empate (un punto para cada uno) una mano donde ambos jugadores tienen la misma configuración y con la misma figura (de coincidir sólo en configuración, gana aquella de figura mayor).

> [!NOTE] Source code...
> [[naipes.c|Ejercicio 4 - Juego de naipes]]

#### Ejercicio 7
---

> [!NOTE] Para este ejercicio es util tener en cuenta
> [[Direcciones e incrementos...]]

Se desea escribir una función para resolver una sopa de letras. Una sopa de letras se representa como una matriz de char de FILS filas y COLS columnas, donde FILS y COLS son constantes previamente definidas.

Se cuenta además con un vector ordenado que contiene las palabras a buscar, donde cada elemento es un string constante, y como marca de final contiene el string vacío.

Se cuenta además con las siguientes declaraciones de tipos

```c
typedef enum {DER=0, IZQ, ABA, ARR, I_AR, I_AB, D_AR, D_AB } Tdireccion;

struct posicion {
	char * palabra;
	size_t fila;
	size_t columna;
	Tdireccion direccion;
};

```

Se pide escribir la función resolverSopa que reciba:
- una matriz de char de FILS x COLS que representa la sopa de letras
- un diccionario ordenado alfabéticamente (vector de strings constantes donde el último elemento es un string vacío)

y retorne un vector de tipo struct posicion que contenga las palabras del diccionario que se encontraron en la sopa de letras, considerando que las palabras pueden estar en forma horizontal (hacia la izquierda o la derecha), vertical (hacia abajo o hacia arriba) o diagonal; y donde el último elemento del vector está representado por el valor NULL en el campo palabra.

El vector de respuesta debe ocupar la menor cantidad de memoria posible.

Si la palabra aparece más de una vez en la sopa, la respuesta debe contener todas las apariciones. 

En caso de error la función debe liberar la memoria reservada y retornar NULL.

#### Ejercicio 8
---
Se desea implementar una estructura para guardar palabras, donde se sabe que cada palabra ocupa a lo sumo 20 caracteres. Indique para cada una de las opciones propuestas si sirve o no, y en caso de no servir cuál es el error cometido

1. 
```c
struct dictionary {
	char * words[21];   // vector dinámico de strings de hasta 20 chars
	size_t dim; // cantidad de palabras
};
```
 No esta bien pues es un vector de punteros a char, pero el vector es estatico por lo que solo vas a poder tener 21 punteros a char.
 
2. 
```c
struct dictionary {
    char * words[];   // vector dinámico de strings 
    size_t dim; // cantidad de palabras
};
```
No va a compilar pues le falta la cantidad de caracteres que almacena el vector words

3. 
```c
struct dictionary {
    char ** words;   // vector dinámico de strings 
    size_t dim; // cantidad de palabras
};```
Puede funcionar pero habria que hacer un malloc para la cantidad de palabras y para la longitud de cada palabra asique va a ser ineficiente, si las palabras se van a querer modificar y/o agrandar en un futuro, es una buena opcion pero no tiene mucho sentido eso

4. ```
```c
struct dictionary {
    char ** words;   // vector dinámico de strings
    // el último elemento es NULL
};
```
No funciona pues no se sabe cuantas palabras tenes, si queres agregar una palabra vas a tener que recorrer todo el vector y no tiene sentido tener que hacer eso cada vez que quieras agregar una palabra al diccionario. Como en el caso anterior, al menos deberias guardarte la cantidad de palabras dentro de la estructura

5. 
```c
struct dictionary {
    char ** words;   // vector dinámico de strings 
// el último elemento es ""
};
```
Idem anterior

6. 
```c
struct dictionary {
    char * words;   	// vector dinámico de strings 
    size_t dim;		// cantidad de palabras
};
```
char * words; no es un vector dinamico de strings, es un vector de caracteres o un puntero a char

7. 
```c
typedef char Tword[21];
struct dictionary {
    Tword * word;   	// vector dinámico de strings de hasta 20 chars
    size_t dim;		// cantidad de palabras
};
```
Este a diferencia del primero si funciona porque es un puntero a vectores de 21 caracteres, ese puntero puede ser apuntado al heap y crear una zona de memoria continua con los vectores

8. 
```c
typedef char Tword[21];
struct dictionary {
    Tword ** word;   	// vector dinámico de strings de hasta 20 chars
    size_t dim;		// cantidad de palabras
};
```
En realidad funciona pero es como una matriz de vectores de 21 caracteres, entonces dim no deberia ser la cantidad de palabras pues no sabes si es la cantidad de "columnas" o de "filas", si bien no son filas y columnas, se podria pensar asi

## Doubts
---
##### No estoy seguro de si este punto se lee asi o si se puede leer como dice el comentario 
```c
struct dictionary {
	char * words[21];   // vector dinámico de strings de hasta 20 chars
	size_t dim; // cantidad de palabras
};
```
	 No esta bien pues es un vector de punteros a char, pero el vector es estatico por lo que solo vas a poder tener 21 punteros a char.
##### No estoy seguro si este punto esta bien pensado
```c
typedef char Tword[21];
struct dictionary {
    Tword ** word;   	// vector dinámico de strings de hasta 20 chars
    size_t dim;		// cantidad de palabras
};
```
En realidad funciona pero es como una matriz de vectores de 21 caracteres, entonces dim no deberia ser la cantidad de palabras pues no sabes si es la cantidad de "columnas" o de "filas", si bien no son filas y columnas, se podria pensar asi

 
## References
---
- [Guia PDF](https://drive.google.com/drive/folders/1pkYURTKs3os16e4T2UIsxej-g3U8G9C7)
