
/* Hacer una función que reciba dos parámetros de entrada representando arreglos de números enteros positivos, ordenados en forma
 * ascendente 
 * y sin elementos repetidos. El último elemento de cada arreglo es -1. La función debe devolver en un tercer parámetro de salida 
 * un arreglo
 * ordenado con la unión de los dos primeros, también terminado en -1. */
/* 	Ejemplo: Dados v1 y v2 arreglos de enteros, se espera que la unión sea: */

#define FIN -1

void copyfrom(const int arr[], int from, int rta[]){
    do{
        rta[]
    }while(arr[i++] != fin);
}

void unirArreglos ( const int ar1[], const int ar2[], int resultado[]){
    int i = 0, j = 0, w = 0;
    for(; ar1[i] != FIN && ar2[j] != FIN;){
        if(ar1[i] < ar2[j]){
            resultado[w++] = ar1[i++];
        } else if(ar1[i] > ar2[j]){
            resultado[w++] = ar2[j++];
        } else {
            resultado[w++] = ar2[j++];
            i++;
        }
    }
    ar1[i] == FIN ? copyfrom(ar2, j, w, resultado):copyfrom(ar1, i, w, resultado);
    resultado[w] = '\0';
}

