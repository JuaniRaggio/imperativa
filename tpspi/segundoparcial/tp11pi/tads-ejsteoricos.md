---
id: tads-ejsteoricos
tags:
  - clang
  - imperativa
  - ADT
  - structs
  - pi
aliases:
  - tads-ejsteoricos
---
#### Ejercicio 9
---
1. Si bien definir la estructura en el archivo fuente .c oculta la implementación del TAD, igualmente el usuario (si conoce cómo es realmente la estructura) puede modificar los datos de la misma desde el front-end. Explicar cómo.
*Si cramos una estructura en el front-end que sea igual a la que creamos en el TAD y luego casteamos el puntero para que "simule" ser un puntero a la estructura que creamos, al tener el mismo tamaño en cuanto a bytes y los mismos campos, los calculos internos para acceder a los campos van a ser los mismos por lo que vamos a poder acceder a esos bytes. Entonces vamos a asignarle un new casteado a nuestra estructura y va a ser lo mismo*

2. Explicar cómo puede hacer el desarrollador de un TAD para evitar que el usuario pueda modificar la estructura. Debe ser un método 100% efectivo. Pista: la función new… no debe retornar un puntero.
*Que la funcion retorne void, manejando una estructura interna que solo existe en nuestro archivo.*

## Doubts
---
- Si se usa el *metodo 100% efectivo*, solo se podria manejar un solo TAD a la vez no?
