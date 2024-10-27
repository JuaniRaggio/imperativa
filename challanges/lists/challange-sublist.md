---
id: challange-sublist
aliases:
  - challange-sublist
tags:
  - clang
  - structs
  - linkedlists
  - lists
  - pi
  - imperativa
  - heap
---
## Contents
---
Escribir una funcion recursiva llamada sublist() que reciba una lista y dos valores
enteros indicando el inicio y el fin de la sublista a devolver (comenzando desde 0).
La funcion debe devolver una nueva lista con los elementos de la sublista.

Si el inicio es mayor al fin, la funcion debe devolver NULL.
Si el fin es mayor a la longitud de la lista, la funcion debe devolver hasta el ultimo elemento.

Usar la siguiente definicion de lista:
```c
typedef​ struct node * TList;

typedef​ struct node {
  int elem;
  struct node * tail;
} TNode;

```

Ejemplos:
Partiendo de una lista 5 -> 4 -> 3 -> 2 -> 1 -> NULL

- Input: start = 1, end = 3
  Output: 4 -> 3 -> 2 -> NULL

- Input: start = 0, end = 0
  Output: 5 -> NULL

- Input: start = 0, end = 10
  Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL

- Input: start = 10, end = 0
  Output: NULL

- Input: start = 7, end = 11
  Output: NULL
  
- Input: start = -2, end = -4
  Output: NULL

- Input: start = -1, end = 2
  Output: NULL

