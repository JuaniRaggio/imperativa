---
tags:
  - clang
  - imperativa
  - pi
---
Hacer la función "incrementoFCMinMax" que recibe un arreglo con **ángulos** 
y un arreglo con las **distancias** que se pueden recorrer en cada  
dirección.  
La función deberá ==determinar el ángulo== correspondiente a la ==mínima== y   a la ==máxima distancia== que puede recorrer y ==obtener los incrementos en==   **Fila y en Columna** para esos ángulos, para retornar dichos incrementos  
al programa que invoque la función. Tener en cuenta que los  
incrementos son:  
Angulo 0 45 90 135 180 225 270 315  
En Fila 0 -1 -1 -1 0 1 1 1  
En Col 1 1 0 -1 -1 -1 0 1  
Ejemplo: Si recibe  
Ángulos[] = {45,90,135,225,180,0} y  
Distancias[] = {12, 1,4,20,7,9}  
La máxima distancia la puede obtener en ángulo 225 y la mínima en ángulo 90,  
por lo que lo que debe retornar es:  
fMin = -1 y cMin = 0  
fMax = 1 y cMax = -1
**Si lo que me pasan no tiene sentido, es decir no puedo desreferenciar o me pasan un vector vacio, no deberia modificar nada**

[[incremento.c]]

```C
#define LETRAS ('Z'-'A'+1)
 
void copiaCeros(char apariciones[], char * out){
  int j = 0;
  for(int i = 0; i < LETRAS; ++i){
    if(apariciones[i] == 0){
      out[j++] = i + 'A';
    }
  }
  out[j] = '\0';
}
 
void complemento(char * in, char * out){
  /* 
  ** Por el ejemplo entiendo que out tiene al menos 27 lugares
  ** para las 26 letras del alfabeto ingles y el cero final
  */﻿﻿
  char apariciones[LETRAS] = {0};
  for(int i = 0; in[i] != '\0'; ++i){
    if(isalpha(in[i]))
      ++apariciones[toupper(in[i]) - 'A'];
  }
  // Si apariciones[i] == 0 quiere decir que la letra que corresponde a
  // ese subindice no estaba asique la deberia copiar en out
  copiaCeros(apariciones, out);
}﻿
```



