---
id: tads-ejspracticos
tags:
  - clang
  - imperativa
  - ADT
  - structs
  - strings
  - pi
  - recursividad
  - matrices
  - heap
  - linkedlists
  - lists
aliases:
  - tads-ejspracticos
  - guia-tads
---
> [!NOTE] Aclaracion
> Este es un archivo en el que anoto los razonamientos previos para plantear las structs de los TADs y/o las funciones. Pero *mas que nada como plantear las estructuras de datos para la eficiencia*

# bagADT
---
- [[bagADT-draft|bagADT borrador]]
- [[bagADT.h]]
- [[bagADT.c]]

El siguiente es un TAD de “bag”. Un bag o bolsa es un conjunto de elementos sin orden pero donde cada elemento puede aparecer más de una vez.

```c
typedef struct bagCDT * bagADT;

typedef ... elemType;    // Tipo de elemento a insertar

/**
** Retorna 0 si los elementos son iguales
*/
static int compare (elemType e1, elemType e2) {
}

/* Retorna un nuevo bag de elementos genéricos. Al inicio está vacío */
bagADT newBag();

/* Inserta un elemento. Retorna cuántas veces está
** elem en el conjunto luego de haberlo insertado (p.e. si es la 
** primera inserción retorna 1).
*/
unsigned int add(bagADT bag, elemType elem);

/* Retorna cuántas veces aparece el elemento en el bag */
unsigned int count(const bagADT bag, elemType elem);

/* Retorna la cantidad de elementos distintos que hay en el bag */
unsigned int size(const bagADT bag);

/* Remueve una aparición de un elemento. Retorna cuántas veces está
** elem en el conjunto luego de haberlo borrado 
*/

unsigned int delete(bagADT bag, elemType elem);

/* Retorna el elemento que aparece más veces. Si hay más de uno
** con esa condición, retorna cualquiera de los dos.
** Precondición: el bag no debe estar vacío. En caso de estar vacío
** aborta la ejecución
*/

elemType mostPopular(bagADT bag);
```

- Si quiere poder recorrer los elementos, pero de forma de obtener únicamente los que tienen menos de N repeticiones, ¿cuál de las siguientes opciones le parece más adecuada agregar en el .h?

1. Opción 1: una función que reciba N y retorne un vector con todos los elementos, con un parámetro de salida indicando la dimensión.
```c
elemType * filterN(bagADT bag, unsigned int n, unsigned int * dim );
```

> [!NOTE] Porque *la opcion 1*
> Tiene sentido devolver una copia de los elementos ya que le da la libertad al usuario de hacer lo que necesite con esos elementos, recorrerlos las veces que sea necesario y no podria modificar los datos reales ya que serian copias
> Ademas no estamos entregando informacion de mas, es exactamente lo que el usuario quiere
  
2. Opción 2: agregar una función "Preparar elementos" que reciba el N, luego un iterador para recorrer (toBegin, hasNext, next)
```c
// Esta función se encarga de ordenar internamente y dejar<br><br>// listos para recorrer los elementos que tienen menos de n<br><br>// repeticiones.<br><br>
void filterN(bagADT bag, unsigned int n);
void toBeginN(bagADT bag);
int hasNextN(const bagADT bag);
elemType nextN(bagADT bag);
```

> [!NOTE] Porque *NO la opcion 2*
> No tiene sentido hacer esto porque nuestra implementacion guarda los elementos ordenados de menor a mayor, por lo que ordenarlos en terminos de cantidad de apariciones no tendria sentido para las demas funciones

3. Opción 3: una función toBegin que reciba N y prepare los elementos, luego el usuario debe invocar a  hasNext y next
```c
void toBeginN(bagADT bag, unsigned int n);
int hasNextN(const bagADT bag);
elemType nextN(bagADT bag);
```

> [!NOTE] Podria ser la 3
> Esta forma no estaria tan mal pero necesitariamos un vector auxiliar en el que guardariamos todos los elementos con N apariciones y despues de esto *volver a recorrer el vector* uno por uno, ya que no los tenemos ordenados por cantidad de apariciones.
> **Entonces esta forma no seria eficiente**

4. Opción 4: una función que retorne un vector con todos los elementos, indicando para cada uno la cantidad de veces que aparece. El que invoca a la función podrá ordenarlos, descartar lo que aparezcan menos o más veces de las deseadas. De esta forma podrá hacer todos los filtros que desee
```c
struct elemCount * elems(const bagADT bag);

struct elemCount {
   elemType elem;
   size_t count;
};
```

> [!NOTE] Porque *NO la opcion 4*
> No tiene sentido retornar TODOS los elementos si solo queres los de N apariciones

# socialADT
---
Se desea almacenar nombres de personas, y para cada persona los nombres de sus "allegados".

Se asegura para todos los nombres (de las personas y sus allegados) que se cumple:

1. se enviarán en minúsculas (no es necesario validarlo)
2. estarán compuestos por valores ASCII menores a 128 (US-ASCII)
3. no serán extensos (a lo sumo 20 cacharacteres)

El objetivo es poder mantener la base actualizada de personas y sus allegados, para lo cual se definió el siguiente contrato para manejarlo con un TAD.

Tener en cuenta que al almacenar nombres se almacena una COPIA de los mismos (ver ejemplos de uso antes de comenzar a programar el TAD)

```c
typedef struct socialCDT * socialADT;

/* Crea un nuevo TAD vacío */
socialADT newSocial();

/* Libera todos los recursos reservados por el TAD */
void freeSocial(socialADT soc);

/* Almacena una nueva persona. Si la persona existe, no hace nada
** Guarda una copia del nombre, no simplemente el puntero */
void addPerson(socialADT soc, const char * name);

/* Si existe una persona con ese nombre, agrega la nueva relación
** Si la persona no existe, no hace nada
** Si related ya estaba relacionado, lo agrega repetido
** Almacena una copia de related, no simplemente el puntero
*/
void addRelated(socialADT soc, const char * name, const char * related);

/* Retorna una copia de los nombres relacionados con una persona
** en orden alfabético.
** Para marcar el final, después del último nombre se coloca NULL
** Si la persona no existe, retorna un vector que sólo tiene a NULL como
** elemento
*/
char ** related(const socialADT soc, const char * person);

/* Retorna una copia de los nombres de las personas en orden alfabético.
** Para marcar el final, después del último nombre se coloca NULL
** Si no hay personas, retorna un vector que sólo tiene a NULL como
** elemento
*/
char ** persons(const socialADT soc);
```

> [!NOTE] Nombres => *a lo sumo 20 caracteres*
> Esto nos indica que podemos guardar los nombres en vectores de 21 caracteres (+1 por el '\0') y no necesitamos alocar memoria en el heap. *Por lo menos para los nombres*


> [!NOTE] Lista ordenada
> Notemos tanto como para addPerson y addRelated nos conviene tener los nombres ordenados alfabeticamente asi nos damos cuenta mas rapido si tenemos que agregar o no a la persona, *ojo que* **addRelated** *agrega aunque esten repetidos*. Igualmente, para **related** vamos a tener que retornar los nombres de los relacionados en orden alfabetico asique tambien nos conviene para esa funcion agregarlos ordenados, idem para **persons**.


> [!NOTE] Para no hacer reallocs en el vector de retorno
> Tenemos que guardarnos la longitud de la lista para que cuando nos pidan un vector con los allegados de x persona o cuando nos pidan un vector con las personas, con un malloc ya nos alcanza y no tenemos que agrandar el vector por bloques


> [!NOTE] En caso de querer guardar grandes cantidades de nombres y allegados => para mejorar la eficiencia
> Cada lista de allegados y personas, va a ser parte de un vector que su indice indica la palabra con la que empiezan los nombres


```c
#define MAX_NAME_LEN 20
#define AZ ('z' - 'a')

struct related {
	char name[MAX_NAME_LEN];
	struct related * next;
};

typedef struct related * relatedList;

struct people {
	char name[MAX_NAME_LEN];
	relatedList related;
	size_t relatedLen;
	struct people * next;
};

typedef struct people * peopleList;

struct socialCDT {
	peopleList localPeople;
	size_t listLen;
};
```

# rankingADT
---
Se desea implementar una colección que permita guardar elementos genéricos sin repeticiones. La colección se llamará *rankingADT*, ya que tiene la particularidad que tiene que servir para acceder fácilmente a los elementos que están al tope del ranking. Los elementos van "escalando posiciones" en el ranking a medida que son consultados.
Si la colección tiene N elementos, se dice que el que está en el tope del ranking está en el puesto 1. El que está último en el ranking está en el puesto N del ranking.
**Implementar el .c completo**

*.h*
```c
typedef const char * elemType;   // cambiar al tipo deseado

typedef struct rankingCDT * rankingADT;

typedef int (*compare)(elemType source, elemType target);

/* Crea un nuevo ranking. Recibe un vector con elementos, donde el primer
** elemento (elems[0]) está al tope del ranking (puesto 1), elems[1] en el 
** puesto 2, etc. Si dim es cero significa que no hay elementos iniciales
*/
rankingADT newRanking(elemType elems[], size_t dim, compare cmp);

/* Agrega un elemento en la posición más baja del ranking, si no estaba.
** Si el elemento estaba, es equivalente a accederlo, por lo que sube un 
** puesto en el ranking
*/
void addRanking(rankingADT ranking, elemType elem);

/* La cantidad de elementos en el ranking */
size_t size(const rankingADT ranking);

/* Si n es una posición válida del ranking, guarda en elem el elemento que está 
** en el puesto n y retorna 1.
** Si no hay elemento en la posición n, retorna cero y no modifica *elem
** Este acceso también hace que el elemento suba un puesto en el ranking
*/
int getByRanking(rankingADT ranking, size_t n, elemType * elem);

/* top: entrada/salida
** Recibe cuántos elementos al tope del ranking se desean 
** Almacena cuántos pudo guardar (ver ejemplos)
** Si el ranking está vacío *top queda en cero y retorna NULL
*/
elemType * getTopRanking(const rankingADT ranking, size_t * top);

/* 1 si el elemento consultado está en el ranking, cero si no 
** Este acceso también hace que el elemento suba un puesto en el ranking
*/
int contains(rankingADT ranking, elemType elem);

/* Baja una posición en el ranking para el elemento que está en la posición n */
void downByRanking(rankingADT ranking, size_t n);

void freeRanking(rankingADT r);

/* Retorna la posición en el ranking (1 es el tope) o 0 si no está en el ranking */
int position(const rankingADT r, elemType elem);
```


> [!NOTE] IMPORTANTE!!
> Esta implementacion es muy rebuscada y las funciones se hacen muy complicadas. Puede hacerse para practicar pero Marcelo me dijo que no era necesario hacerlo asi.
> Basta con hacer *un vector* que guarde los elementos del ranking y que los indices indiquen el rank en el que estan. Obiamente *idx = 0 <=> rank = 1*


> [!NOTE] Lista vs Vector
> - Notemos que todas las funciones menos para contains y position, nos conviene un vector ya que  buscamos acceder por indice y si queremos agregar, simplemente necesitamos guardar cual fue la ultima posicion que guardamos y lo guardamos al final. Siendo el elemento en [0] el mas alto, osea el de rank 1.
> - Por otro lado para contains y position, nos conviene tener los elementos guardados en orden ascendente. De esta manera no tenemos que recorrer todo el vector para saber si un elemento esta o no en el ranking.


> [!NOTE] Conclusion
> Primero vamos a querer tener una lista para guardar los elementos de forma ordenada ascendentemente.
> Tambien podemos hacer un vector de punteros a estructura, donde esas estructuras son...


```c
struct elementInfo {
	elemType value;
	size_t rank;
};
```


> [!NOTE] Porque vector de punteros a struct?
> De esta forma, solo tenemos la cantidad de estructuras equivalente a la cantidad de elementos en el ranking y no las tenemos repetidas

# listADT
---
Se desea implementar un TAD para listas de elementos *no repetidos*, que permita recorrerla con dos criterios: *en forma ascendente* o **por el orden de inserción de los elementos.**

```c
#ifndef __tp11_ej14_h_

#define __tp11_ej14_h_

typedef struct listCDT * listADT;
 
typedef int elemType;  	// Tipo de elemento a insertar, por defecto int

 
/* Retorna una lista vacía.
*/
listADT newList(int (*compare) (elemType e1, elemType e2));

/* Agrega un elemento. Si ya estaba no lo agrega */
void add(listADT list, elemType elem);

/* Elimina un elemento. */
void remove(listADT list, elemType elem);

/* Resetea el iterador que recorre la lista en el orden de inserción */
void toBegin(listADT list);

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en el orden de inserción. Sino retorna 0 */
int hasNext(listADT list);

/* Retorna el elemento siguiente del iterador que recorre la lista en el orden de inserción. 
** Si no hay un elemento siguiente o no se invocó a toBegin aborta la ejecución.
*/
elemType next(listADT list);

/* Resetea el iterador que recorre la lista en forma ascendente */
void toBeginAsc(listADT list);

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en forma ascendente. Sino retorna 0 */
int hasNextAsc(listADT list);

/* Retorna el elemento siguiente del iterador que recorre la lista en forma ascendente. 
** Si no hay un elemento siguiente o no se invocó a toBeginAsc aborta la ejecución.
*/
elemType nextAsc(listADT list);

/* Libera la memoria reservada por la lista */
void freeList(listADT list);


#endif
```


> [!NOTE] Lista vs Vector
> Se me habia ocurrido hacer un *vector de punteros a elemType y una lista ordenada ascendentemente*. De esta forma, el vector va a ser recorrido en orden de insercion mientras que si queremos recorrer ascendentemente, recorremos la lista.


> [!NOTE] Pero
> *La funcion remove* nos caga, porque si queremos borrar un elemento del vector y mantener el orden de insercion, tenemos que correr todos los elementos que le siguen al que vamos a borrar y no es eficiente


> [!NOTE] Eso nos lleva a que
> 1. La *lista ordenada* va a estar si o si.
> 2. El vector queda *descartado* por lo que mencionamos anteriormente


> [!NOTE] Conclusion
> 1. Se pueden mantener dos listas, una en orden de insercion y otra en orden ascendente
> 2. Se puede tener una sola lista, la cual tenga *4 punteros a nodo*
> 	1. El nodo al siguiente ascendente
> 	2. El nodo al anterior ascendente
> 	3. El nodo al siguiente insertado
> 	4. El nodo al anterior insertado


> [!NOTE] Aclaracion
> En esta materia no es necesario aprender double-linked lists asique no piden que hagamos la segunda solucion. La implementacion en la vida real seria mejor esa pero no es necesario, se puede hacer a modo de challange

*Estructuras*
```c
struct node {
  elemType value;
  struct node * prevInsert;
  struct node * nextInsert;
  struct node * prevIncreasing;
  struct node * nextIncreasing;
};

typedef struct node * header;

typedef int (*fCompare)(elemType, elemType);

struct listCDT {
  header firstInc; // Es el primero de la lista ascendente
  header firstAdded;
  header lastAdded; // Es el ultimo agregado
  header iteratorAdded;
  header iteratorInc;
  fCompare cmp;
};

```




## Doubts
---
- *rankingADT* => No estoy seguro si la estructura esta bien. Marcelo: "Esta bien para practicar pero es muy rebuscada, no es lo que esperamos"

