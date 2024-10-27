#include <stdio.h>
#include <assert.h>
#include <string.h>
 
 
void eliminaRepetidas(char * str);
 
 
int main() {
    char str1[] = "gooooooooooooooooool     de    Argentinaaaaaaaaaaaaaaaaaaaaaaaaa gol de Messssssssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
    eliminaRepetidas(str1);
    assert(strcmp(str1, "gol de Argentina gol de Mesi") == 0);
    eliminaRepetidas(str1);
    assert(strcmp(str1, "gol de Argentina gol de Mesi") == 0);
 
 
    char str2[] = "aaaaaaaa";
    eliminaRepetidas(str2);
    assert(strcmp(str2, "a") == 0);
 
 
    char str3[] = "abcabcabcabczzzzzza";
    eliminaRepetidas(str3);
    assert(strcmp(str3, "abcabcabcabcza") == 0);
 
 
    eliminaRepetidas(NULL);
 
 
    char str4[] = "a";
    eliminaRepetidas(str4);
    assert(strcmp(str4, "a") == 0);
 
 
    char str5[] = "";
    eliminaRepetidas(str5);
    assert(strcmp(str5, "") == 0);
 
 
    char *str_break = "a"; // por qué no rompe el programa? forzar un error modificando el string
    eliminaRepetidas(str_break);
 
 
    puts("OK");
    return 0;
}

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






