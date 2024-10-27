---
id: myList
aliases:
  - myList
tags:
  - lists
  - linkedlists
  - structs
  - imperativa
  - pi
  - recursividad
  - heap
  - clang
---
## Files
---


## Contents
---
##### Primer implementacion de list
```c
int isEmpty(const list l) {
	return l == NULL;
}

unsigned int size(const list l) {
	if (l == NULL)
		return 0;
	return 1 + size(l->next);
}

int belongs(const list l, int elem) {
	if (l == NULL || elem < l->elem)
		return 0;
	else if (l->elem == elem)
		return 1;
	else
		return belongs(l->next, elem);
}

void liberenAWilly(list l) {
	if (l == NULL) {
		return;
	} else {
		liberenAWilly(l->next);
		free(l);
	}
}

list addElem(list l, int elem) {
	if (l == NULL || l->elem > elem) {
		list new = malloc(sizeof(*new));
		new->elem = elem;
		new->next = l;
		return l;
	} else if (l->elem < elem) {
		l->next = addElem(l->next, elem);
		return l;
	}
	return l;
}

```

- Implementar una funcion *get(list, idx)* que me devuelve el *elemento* en el indice *idx*
```c
typedef int elemType;

elemType get(TList myList, elemType idx) {
	assert(myList != NULL && idx > 0);
	if (idx == 0) {
		return myList->elem;
	} else if (idx > 0) {
		return get(myList->tail, idx - 1);
	}
}

```
En realidad si la funcion retorna elemType, tendria que recibir un puntero a funcion

- Implementar una funcion **int * toArray(const List l, int * dim)** que pase una lista a un arreglo y lo retorne
```c
#define BLOCK 10

int * toArray(const List l, int * dim) {
	List aux = l;
	int * receiver = NULL, i;
	for (i = 0; aux != NULL; ++i) {
		if (i % BLOCK == 0) {
			receiver = realloc(receiver, sizeof(*receiver) * i);
		}
		receiver[i] = aux->elem;
		aux = aux->tail;
	}
	receiver = realloc(reciever, sizeof(*receiver) * i);
	*dim = i;
	return receiver;
}
```

> [!NOTE] Puntero auxiliar
> No es necesario crear el puntero auxiliar porque l es una copia de la direccion de memoria de la lista, por lo que si modifico eso, no va a cambiar

- Implementar una funcion **head(list)** que me devuelve la head de esa lista y **tail(list)** que me devuelve la tail de list
```c
int head(const List l) {
	assert(l != NULL);
	return l->elem;
}

List tail(List l) {
	assert(l != NULL && l->tail != NULL);
	return l->tail;
}

// Otra forma
int head(const List l) {
	if (l == NULL)
		fprinf("Error al invocar head, el parametro es NULL");
	return l->elem;
}

List tail(List l) {
	if (l == NULL) {
		fprintf("Error al invocar tail, el parametro es NULL");
	}
	return l->tail;
}
```

- Implementar una funcion **int belnogsIter(const List l, int elem)**
```c
int belongsIter(const List l, int elem) {
	List iterador = l;
	while(iterador != NULL) {
		if (iterador->elem == elem)
			return true;
		else if (iterador->elem < elem)
			iterador = iterador->tail;
		else
			return false;
	}
	return false;
}

```

- Implementar una funcion **int indexOf(const List l, int elem)**
```c
int indexOf(const List l, int elem) {
	if (l == NULL || l->elem > elem)
	   return -1;
	if (l->elem == elem)
		return 0;
	int idx = indexOf(l->tail, elem);
	return idx != -1 ? 1 + idx:-1;
}
```

- Implementar una funcion **int * arrayTo(const List l, int * dim)**
```c
int * arrayTo(const List l, int * dim) {

}
```

## Doubts
---
- #### Que es mas eficiente, recorrer dos veces y hacer un solo malloc, es decir, size y malloc(size) o hacer un solo recorrido pero muchos mallocs
Ambas tienen ventajas y desventajas, pero la diferencia no es mucha asique podemos hacer la implementacion que nos parezca mas comoda

