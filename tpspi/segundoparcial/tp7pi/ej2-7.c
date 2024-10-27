#include <getnum.h>
#include <stdio.h>
#include <stdlib.h>

char base_reciever(int * to_recieve, int * to_transform){
    int ok = 0;
    char * ltgt = malloc(2);
    ok = scanf("%[<]%d%[>]%d", ltgt, to_recieve, ltgt + 1, to_transform);
    if(ok != 4 || ltgt[0] != '<' || ltgt[1] != '>'){
        // This function automatically cleans the buffer
        while(getchar() != '\n');
        return 0;
    }
    free(ltgt);
    return 1;
}

int main(){
    int to_recieve, to_transform, numbers;
    do{
        printf("Ingrese la base y el numero que desea transformar en el siguiente formato:\n"
               "<\"base a recibir\">\"base a la cual desee los numeros\"");
    } while(base_reciever(&to_recieve, &to_transform) == 0);
}

// Faltaria hacer la funcion que pasa de entero en base x a entero en base y

