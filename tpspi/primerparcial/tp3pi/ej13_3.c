#include "../fcatedra/getnum.h"
#include <stdio.h>

int main(){
    int lado;
    do{
        lado = getint("Ingrese el largo del lado del cuadrado: ");
    }while(lado < 0);

    for(int i = 0; i < lado; ++i){
        for(int j = 0; j < lado; ++j)
            printf("*");
        printf("\n");
    }
    
    /* Con un solo for: */
    for(int i = 0; i < lado * lado; ++i){
        if(i%lado == 0)
            printf("\n");
        printf("*");
    }
}

