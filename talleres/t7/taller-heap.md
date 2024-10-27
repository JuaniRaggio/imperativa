---
id: taller-heap
aliases:
  - taller-heap
tags:
  - clang
  - heap
  - pi
  - imperativa
---
#### 26-09-2024
---
1. Completar para que los tres codigos sean iguales
```c
int * arr;
int i;
arr = malloc(TAM*sizeof(int));
for(i = 0; i < TAM; ++i)
	arr[i] = 0;
mostrarArreglo(arr, TAM);
free(arr);

arr = NULL;
arr = realloc(arr, TAM * sizeof(*arr));
for(int i = 0; i < TAM; ++i)
	arr[i++] = 0;

arr = calloc(TAM, sizeof(*arr));
```

2. Hacer una función que lea números enteros de entrada estándar (los lee con getint) y los guarde en un arreglo. El arreglo debe crecer a medida que se necesita. La carga en el arreglo finaliza cuando un valor se repite por primera vez.
```c
#define BLOCK 5
#define FIRSTBK 10
#define BYTE 8

char check_prev(int * arr, int to_add) {
    // Necesito hacer una mascara de MAX_INT - MIN_INT + 1 bits
    // como puedo calcular cuantos bytes necesito?
    unsigned char views[(MAX_INT - MIN_INT + 1) / BYTE + 1] = {0};
    if((views[to_add/BYTE] & (0x01 > to_add % BYTE)) == 0){
        views[to_add/BYTE] = views[to_add/BYTE] | (0x01 > to_add % BYTE);
        return 1;
    }
    return 0;
}

char add_int(int * arr, int to_add, int * dim) {
    if(check_prev(arr, to_add)){
        arr[*dim] = to_add;
        return 1;
    }
    return 0;
}

int * cargarNumeros(int * dim) {
    char keepitup = 0;
    int * arr = malloc(sizeof(*arr) * FIRSTBK);
    int aux;
    for(*dim = 0; keepitup; ++*dim) {
        if(*dim % BLOCK == 0){
            arr = realloc(arr, sizeof(*arr) * (*dim + BLOCK));
        }
        aux = getint("");
        keepitup = add_int(arr, aux, dim);
    }
    arr = realloc(arr, sizeof(*arr) * *dim);
    return arr;
}

int main(void) { 
    int dim;
    int *arr;
    arr = cargarNumeros(&dim);
    for (int i = 0; i < dim; i++)
        printf("%d ", arr[i]);
    free(arr);
    return 0; 
}
```
3. *El supervector:*
Implementar un programa que lea de la entrada estándar hasta EOF y genere el supervector que *todo lo puede guardar*. Luego imprimir el contenido del vector en salida estándar.
```c
#define BLOCK 5
#define INITBLOCK 15

int * super_mkr(int * dim){
    int * super = malloc(BLOCK * sizeof(int));
    *dim = 0;
    // Recordemos que * tiene mayor presedencia que el + asique se hace primero la desreferencia y despues el post-incremento
    while((super[*dim++] = getchar()) != EOF){
        if(*dim % BLOCK == 0){
            super = realloc(super, (*dim + BLOCK) * sizeof(*super));
        }
    }
}

void show_vec(int * vec, int dim){
    for(int i = 0; i < dim; ++i){
        printf("%c", vec[i]);
    }
}

int main(){
    int dim = 0, * super_vector = super_mkr(&dim);
    show_vec(super_vector, dim);
}
```

> [!NOTE] Doubts
> - Si hago arr = realloc(arr, ...), sin haber inicializado previamente arr -> Estamos jugando con la suerte pues no sabemos a donde va a estar apuntando arr por lo que tenemos que por lo menos inicializar arr en NULL
> - En el ejercicio 2 -> No es tan eficiente hacer una mascara de la cantidad de bits
## References
---
- [[Taller 7 2024-2 sin respuestas.pptx.pdf|Presentacion taller]]
---

