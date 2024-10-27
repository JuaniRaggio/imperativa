#include <assert.h>
#include <stdio.h>
#include <string.h>

// Le cambiamos el nombre para que no haya conflictos con la biblioteca estandar
char * strCat ( char *s, const char *t);

int main(void){

    char ga[10]="ga";
    char to[]="to";
    char empty[10]="";

    assert(!strcmp("", strCat(empty, empty)));
    assert(!strcmp("gato", strCat(ga, to)));
    assert(!strcmp("gato", strCat(ga, empty)));
    assert(!strcmp("gatoto", strCat(ga, to)));
    assert(!strcmp("gatoto", strCat(empty, ga)));

    puts("OK!");
    return 0;
}

char * strCat(char * s, const char * t) {
    if(t[0] == '\0')
        return s;

    int i = 0;
    while(s[i] != '\0')
        ++i;
    
    for(int j = 0; t[j] != '\0'; j++)
        s[i++] = t[j];

    s[i] = '\0';

    return s;
}

