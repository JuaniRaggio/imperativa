/* Una Skip-list es una lista donde cada nodo, en vez de tener una referencia al nodo siguiente, tiene un vector de referencias, donde el elemento 0  */
/* contiene una referencia al siguiente nodo, pero los elementos siguientes tienen referencias a nodos que están más "lejanos".  */
/* Para determinar el tamaño de ese vector de referencias se basa en la probabilidad. El resultado es una lista que empíricamente tiene un orden  */
/* logarítmico para todas las funciones. */
/* La altura de una skip-list está dada por la mayor dimensión del vector de referencias. */
/* Crear un TAD que -dada una altura máxima- implemente una skip-list que permita mantener elementos ordenados, aceptando repetidos,  */
/* y que también permita saber si un elemento está o no en la lista, y recorrerla con un iterador. */

