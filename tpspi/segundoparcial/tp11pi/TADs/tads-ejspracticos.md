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

> [!NOTE] IMPORTANTISIMO PARA LOS TADS JODIDOS
> Para las funciones que tenemos tads muy complejos, es muy recomendable hacer un puntero a lo que queremos modificar y acceder desde ahi, sino las funciones se nos hacen un choclo
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

# addressBookADT
---
Se desea mantener una lista de contactos, (addressBook)
Por cada contacto se guarda únicamente su nombre y número de teléfono.
Cada contacto estará dentro de un grupo, y cada grupo se identifica únicamente por su nombre.
No puede haber dos grupos con el mismo nombre, sin diferenciar entre mayúsculas y minúsculas (el grupo "personal" es el mismo que "Personal",
"PERSONAL", etc.)
Dentro de un grupo no puede haber dos contactos con el mismo nombre (tampoco diferencia entre mayúsculas y minúsculas), pero sí puede repetirse entre distintos grupos, por ejemplo tanto el grupo "PERSONAL" como "INDESEABLES" puede tener a "James" como contacto.

```c
typedef struct tContact {
    char * name;
    char * phoneNumber;
} tContact;

typedef struct addressBookCDT * addressBookADT;

/* Crea un nuevo TAD vacÃ­o */
addressBookADT newAddressBook(void);

/* Almacena un nuevo grupo de contactos. Si el grupo existe, no hace nada.
** No diferencia entre minÃºsculas y mayÃºsculas, el grupo "abc" es el mismo que "ABC",
** "Abc", etc. pero distinto que " abc" o "abc "
** Almacena una copia del nombre, que no tiene un lÃ­mite para su longitud
*/
int addGroup(addressBookADT, const char * groupName);

/* Si existe un grupo de nombre groupName, agrega el contacto contact a la agenda
** Si el grupo no existe, no hace nada
** Si el contact ya estaba relacionado al grupo (habÃ­a uno con el mismo nombre),
** no lo agrega
*/
int addContact(addressBookADT, const char * groupName, tContact contact);

/*
** Permite iterar por todos los contactos de la agenda
** QUE PERTENEZCAN AL GRUPO INDICADO por parÃ¡metro en toBegin
** El orden es alfabÃ©tico por nombre del contacto.
*/
void toBeginForGroup(addressBookADT, const char * groupName);

int hasNextForGroup(addressBookADT);

/* Retorna un contacto, aborta si no hay siguiente */
tContact nextForGroup(addressBookADT);

/*
** Permite iterar por todos los grupos de la agenda
** El orden es alfabÃ©tico por nombre del grupo.
*/
void toBegin(addressBookADT);

int hasNext(addressBookADT);

/* Retorna una copia del grupo, aborta si no hay siguiente */
char * next(addressBookADT);
```


> [!NOTE] Notemos que
> Tanto los *grupos* como los *contactos* no pueden estar repetidos, por lo que vamos a querer tenerlos ordenados a ambos. Entonces si o si los grupos van a ser una lista y cada grupo va a tener su lista de contactos.
> Entonces vamos a hacer una lista de listas.

```c
struct contactList {
    tContact contact;
    struct contactList * next;
};

typedef struct contactList * contactsHeader;

struct groupList {
    char * groupName;
    contactsHeader people;
    struct groupList * next;
};

typedef struct groupList * groupsHeader;

struct addressBookCDT {
    groupsHeader groups;
    struct groupList * iteratorForGroups;
    struct contactList * iteratorForContacts;
};
```


> [!NOTE] Ademas
> Necesitamos los iteradores.
> 1. *iteratorForGroups* es para las funciones que quieren recorrer los nombres de los grupos
> 2. *iteratorForContacts* es para las funciones que quieren recorrer los contactos dentro de un grupo en especial


# moveToFrontADT
---
Se desea guardar una colección de elementos *no repetidos*, en la cual los elementos más "populares" (los que más se consultan) estén al principio de la colección. De esta forma, será más rápido acceder a los elementos que más veces se consulten. Para ello se definió que el conjunto de datos opere de la siguiente forma:
- Cuando se inserta un elemento (no repetido) se lo inserta al final
- Cuando se consulta un elemento (con la función get) el mismo es enviado al principio de la colección 
El contrato con el TAD es el siguiente:

```c
typedef struct moveToFrontCDT * moveToFrontADT;

typedef ... elemType;  // Tipo de elemento a insertar

/* Retorna un nuevo conjunto de elementos genéricos. Al inicio está vacío 
** La función compare retorna 0 si los elementos son iguales, negativo si e1 es 
** "menor" que e2 y positivo si e1 es "mayor" que e2
*/

moveToFrontADT newMoveToFront(int (*compare) (elemType e1, elemType e2));

  

/* Libera todos los recursos del TAD */
void freeMoveToFront(moveToFrontADT m);

/* Inserta un elemento si no está. Lo inserta al final.
** Retorna 1 si lo agregó, 0 si no.
*/
unsigned int add(moveToFrontADT moveToFront, elemType elem);

/* Retorna la cantidad de elementos que hay en la colección */
unsigned int size(moveToFrontADT moveToFront);

/* Se ubica al principio del conjunto, para poder iterar sobre el mismo */
void toBegin(moveToFrontADT moveToFront);

  

/* Retorna 1 si hay un elemento siguiente en el iterador, 0 si no */
int hasNext(moveToFrontADT moveToFront);

  

/* Retorna el siguiente elemento. Si no hay siguiente elemento, aborta */
elemType next(moveToFrontADT moveToFront);

/* Retorna una copia del elemento. Si no existe retorna NULL.
** Para saber si el elemento está, usa la función compare. 
** Si el elemento estaba lo ubica al principio.
*/
elemType * get(moveToFrontADT moveToFront, elemType elem);
```


> [!NOTE] Hay dos opciones
> 1. Hacer dos listas.
> 	1. Manteniendo el orden ascendente para ver cuando agregamos elementos
> 	2. Manteniendo el orden de consulta. Si consultan un elemento, pasa a ser el primero de esta lista pero no cambia el orden de la primer lista
> 2. Hacer una lista. Dentro de la misma vamos a tener un puntero al siguiente ascendente y un puntero al siguiente en popularidad. El CDT va a tener un puntero al primero en orden ascendente y un puntero al primero de popularidad. Si hubiese una funcion delete, necesitariamos tener un puntero al anterior en orden asc y un puntero al anterior en popularidad.


# phrasesADT
---
Se desea crear un TAD que dé soporte para almacenar y recuperar frases, donde cada frase tiene asociada una clave numérica (un valor entero positivo). Las claves son únicas (no puede haber dos frases con la misma clave, aunque sí podría pasar que dos claves tengan la misma frase).

Para ello se crea el siguiente contrato, y se cuenta además con un programa de prueba (leer completamente ambos antes de implementar el TAD).

No hay un límite previsto para la longitud de cada frase, pueden ser unos pocos o miles de caracteres.

> [!NOTE] Como lo encaramos?
> *Se espera que casi todas las claves estén usadas.* => Podemos crear un vector de una. Desde keyFrom siendo el indice 0 y keyTo el ultimo indice valido => Nos vamos a tener que guardar estos keyFrom y keyTo para poder determinar si el key que nos pasa el usuario es valido


```c
#ifndef __phrasesADT__
#define __phrasesADT__

#include <stdio.h>

typedef struct phrasesCDT * phrasesADT;

// Necesitamos tener dentro de nuestra estructura, el intervalo de claves valido
/*
* Recibe cuál será el rango de claves válidas a utilizar, por ejemplo si
* keyFrom=1001, keyTo=1500 habrá un máximo de 500 frases a almacenar
* keyFrom=1001, keyTo=3500 habrá un máximo de 2500 frases a almacenar
* Si los parámetros son inválidos retorna NULL
*/
phrasesADT newPhrasesADT(size_t keyFrom, size_t keyTo);

/* Libera toda la memoria reservada por el TAD */
void freePhrases(phrasesADT ph);

// Para la funcion put notemos que necesitamos guardar cuanto espacio se guardo para la frase
/*
* Agrega una frase. Si la clave key es inválida retorna 0, sinó retorna 1 (uno)
* Si ya hay una frase asociada a la clave, actualiza la frase almacenada,
* reemplazándola por el parámetro phrase.
* Se almacena una copia de la frase.
*/
int put(phrasesADT ph, size_t key, const char * phrase);

/*
* Retorna una copia de la frase asociada a la clave key. Si no hay frase asociada
* a la clave key retorna NULL, lo mismo si la clave es inválida.
*/
char * get(const phrasesADT ph, size_t key);

/*
* Cantidad de frases almacenadas
*/
size_t size(const phrasesADT ph);

/*
* Retorna un string con todas las frases concatenadas 
* Si no hay frases retorna un string vacío
*/
char * concatAll(const phrasesADT ph);

/*
* Retorna un string con todas las frases concatenadas cuyas claves estén entre
* from y to inclusive. Si from o to son inválidas (están fuera del rango)
* retorna NULL
* Si no hay frases en ese rango, retorna un string vacío
*/
char * concat(const phrasesADT ph, size_t from, size_t to);

#endif

```

```c
struct phrase {
    // Si no esta ocupada la phrase, text == NULL
    char * text;
    size_t textLen;
};

struct phrasesCDT {
    size_t keyFrom;
    size_t keyTo;
    size_t ocupied;
    struct phrase * phrasesCollection;
};
```

# polyADT
---
El enunciado nos dice practicamente como es la estructura. Que sea sin header quiere decir que el polyCDT va a ser un nodo y que dentro de el vamos a tener un next.

> [!NOTE] Importante a tener en cuenta. Me equivoque en esto
> Si tenemos una lista sin header es exactamente igual que la lista con header solo que el CDT en si va a ser el primer nodo. *Por lo que si queremos crear un polyCDT vacio, con devolver NULL ya estaria.*
> Yo lo que habia hecho era crear un campo "isEmpty" dentro del CDT pero no tiene sentido porque tendriamos un isEmpty para todos los nodos y no es lo que queremos
> Entonces para saber si una lista sin header esta vacia, basta preguntar si el primer nodo es NULL, *listeralmente igual que en las listas con header*

```c
#ifndef PI_POLYADT_H
#define PI_POLYADT_H

/*
 * Se cuenta con un TAD polinomio el cual implementa cada polinomio como una lista simplemente
 * encadenada sin header ordenada en forma descendente por el grado de la variable. El contrato para el TAD
 * poliniomio es el siguiente:
 *
 *   polinomio: (10, 5) -> (3, 6) -> (0, 1)
 *   polinomio: sum(a_i * x^i)_0^i
 *
 * Se pide:
 *  1) Definir struct polyCDT
 *  2) Implementar la funcion addPolynomial
 * */

typedef struct polyCDT * polyADT;

/*
 *  Retorna un polinomio vacio ( NULL )
 * */
polyADT newPolynomial(void);


/*
 *  Retorna 1 si el polinomio esta vacio
 *          0 en caso contrario
 * */
int isEmpty(polyADT poly);

/*
 *  Agrega un término al polinomio con el coeficiente y grado.
 *  Se inserta ordenado por grado, en forma decreciente.
 *  Si ya existe un termino con ese grado o no se pudo agregar retorna cero.
 *  Si no existia y se pudo agregar, retorna uno.
 * */
int addTerm(polyADT *poly, float coef, int degree);

/*
 * Suma los polinomios enviados como parametro y obtiene un nuevo polinomio.
 * En caso de error retorna NULL
 * */
polyADT addPolynomial(polyADT p, polyADT q);

#endif //PI_POLYADT_H

```

# skipListADT
---
Una Skip-list es una lista donde cada nodo, en vez de tener una referencia al nodo siguiente, tiene un vector de referencias, donde el elemento 0 contiene una referencia al siguiente nodo, pero los elementos siguientes tienen referencias a nodos que están más "lejanos". Para determinar el tamaño de ese vector de referencias se basa en la probabilidad. El resultado es una lista que empíricamente tiene un orden logarítmico para todas las funciones.

La altura de una skip-list está dada por la mayor dimensión del vector de referencias.

Crear un TAD que -dada una altura máxima- implemente una skip-list que permita mantener elementos ordenados, aceptando repetidos, y que también permita saber si un elemento está o no en la lista, y recorrerla con un iterador.

- [[skiplists.pdf|Presentacion de como funcionan las skipLists]]

## Doubts
---
- *rankingADT* => No estoy seguro si la estructura esta bien. Marcelo: "Esta bien para practicar pero es muy rebuscada, no es lo que esperamos"
- Si quiero *swapear elementos en una lista*, me conviene swapear los elementos y no los punteros
