// Esta macro recibe un tipo de dato como primer paramentro
// Ej: tenemos una 
// struct persona {
// ...
// };
// Lo que recibe offsetof como primer parametro es struct persona
// No recibe una variable de ejemplo, recibe literalmente "struct persona"
#define offsetof(dataStructure, field) (unsigned long)(&(((dataStructure *)NULL)->field))

#include <assert.h>
#include <stdio.h>

typedef struct {
    int v1;
    char v2;
    char v3;
    double d1;
    char arr1[5];
} prueba;

int main(void){
    assert(offsetof(prueba, v1) == 0);
    assert(offsetof(prueba, v2) == 4);
    assert(offsetof(prueba, v3) == 5);
    assert(offsetof(prueba, d1) == 8);
    assert(offsetof(prueba, arr1[0]) == 16);
    printf("OK!\n");
    return 0;
}

