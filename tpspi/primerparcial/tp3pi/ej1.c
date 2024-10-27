#include <stdio.h>

int main(){
    printf("Introduzca un caracter: ");
    int c = getchar();
    
    if(c >= 'a' && c <= 'z')
        printf("Es una letra minuscula");
    else if(c >= 'A' && c <= 'Z')
        printf("Es una letra mayuscula");
    else
        printf("No es una letra");
    reutrn 0;
}
