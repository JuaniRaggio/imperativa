---
tags:
  - clang
  - pi
---
## Strings - Ejercicio
Escribir la función *eliminaRepetidas*, que *recibe un string* y que, por cada
secuencia de caracteres repetidos, **deja uno solo**.

● Ejemplos:
Recibe “gooooooooooooooooool de Argentinaaaaaaaaaaaaaaaaaaaaaaaaa gol de
Messssssssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii” -> “gol de Argentina gol de Mesi”
Recibe “la llama que llama” -> “la lama que lama”
Recibe “aaaaaaa aaaa” -> “a a”
● ¿Qué ocurre si se invoca …?
● char nom[] = “messsssiiii”;
● char \*otro = “messsssiiii”;
● eliminaRepetidas(nom); mesi
● eliminaRepetidas(otro); mesi

1. ==Pensar en si vamos a copiar la primer aparicion o la ultima==

> [!Decido copiar la primer aparicion]
> 
> + Me tengo que guardar la ultima letra copiada para saber si lo que estoy recorriendo lo tengo que seguir copiando o no

> [!En caso de elegir copiar la ultima aparicion]
> 	+ Tengo que estar preguntando siempre si el siguiente es igual o no, si no lo es, copio, si lo es, sigo recorriendo sin hacer nada. Tambien es una buena opcion

2. Luego esto se hace exactamente igual que el [[eliminaCeros.c]]

 [[elimina_reps.c]]
 
```C
 void eliminaRepetidas(char * str){
    if(str == NULL)
        return;
    char last = !str[0];
    int j = 0;
    for(int i = 0; str[i] != '\0'; ++i) {
        if(last != str[i])
            str[j++] = str[i];
        last = str[i];
    }
    str[j] = '\0';
}

```


