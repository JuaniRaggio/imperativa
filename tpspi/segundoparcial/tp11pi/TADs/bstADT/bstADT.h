#ifndef __bstADT_h_
#define __bstADT_h_

/* Un árbol binario de búsqueda (BST por sus siglas en inglés) es un árbol binario en donde para cada nodo se cumple que todos los nodos de su subárbol 
 * izquierdo son menores que él, y todos los nodos de su subárbol derecho son mayores que él. No hay elementos repetidos. */
/* Implementar el ADT para BST, que se encuentra definido en forma parcial (faltan algunas funcionalidades) en el archivo bstADT.h */

typedef int elemType;

typedef int (*cmp)(elemType, elemType);

typedef struct bstCDT * bstADT;

// Crea un arbol binario de busqueda
bstADT newBst(cmp);

// Libera toda la memoria reservada por el TAD
void freeBst(bstADT bst);

// Cantidad de nodos en el arbol
unsigned int size(const bstADT bst);

// Devuelve la altura del arbol (la longitud de la rama mas larga)
// Un arbol vacio tiene altura 0
unsigned int height(const bstADT bst);

// Retorna 1 si el elemento estaก en el arbol, cero si no esta
int belongs(const bstADT bst, elemType elem);

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int insert(bstADT bst, elemType elem);

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
elemType * inorder(const bstADT bst);

// TODO: borrar un elemento, recorrido preorder, postorder
// Mas avanzado aun: verificar si es balanceado por altura o no, crear iteradores inorder, preorder, postorder


#endif
