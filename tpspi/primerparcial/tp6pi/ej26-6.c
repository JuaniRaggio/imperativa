#include <stdio.h>
#include <assert.h>
#include <string.h>

void insertaDesde(char * s1, const char * s2, char c);

int main(void) {
    char str1[60] = "manuel";
    char str2[] = "javi";
    insertaDesde(str1, str2,'n');
    assert(strcmp(str1,"majavi")==0);

    char str3[20];
    strcpy(str3, "manuel");
    insertaDesde(str3, "javi" ,'l');
    assert(strcmp(str3,"manuejavi")==0); // muestra manuejavi

    char str4[60];
    strcpy(str4, "lalala");
    insertaDesde(str4, "javi",'j');
    assert(strcmp("lalala",str4)==0);

    insertaDesde(str4, "javier ibaniez de toledo",'l');
    assert(strcmp("javier ibaniez de toledo",str4)==0);

    strcpy(str4,"12345");
    insertaDesde(str4, "6789abcdefgh",'5');
    assert(strcmp("12346789abcdefgh",str4)==0);

    /* insertaDesde("Pensando en ti", "El dumen es un bobo", '3'); */

    insertaDesde("Jorge el que te coje", str4, 'j');

    puts("OK!");
    return 0;
}

#define TOPE 100

void catFrom(char * s1, int from, const char * s2){
    int j = 0;
    while(s2[j] != '\0' && j < TOPE){
        s1[from++] = s2[j++];
    }
    s1[from] = '\0';
}

void insertaDesde(char * s1, const char * s2, char c) {
    // Esta funcion es peligrosa ya que nada me asegura que me pasen un string null terminated
    int i, found = 0;
    for (i = 0; s1[i] != '\0' /*&& i < TOPE*/; ++i)
    {
        if(s1[i] == c) {
            catFrom(s1, i, s2);
            break;
        }
    }
}

