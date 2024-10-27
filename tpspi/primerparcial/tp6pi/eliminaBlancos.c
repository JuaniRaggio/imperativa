#include <stdio.h>
#include <assert.h>
#include <string.h>

void
eliminaBlancos (char cadena[]);

int main(void) {
  char s[60] = "   "; // cant impar de blancos
  eliminaBlancos(s);
  assert(strcmp(s, " ")==0);

  eliminaBlancos(s);
  assert(strcmp(s, " ")==0);

  strcpy(s,"  ");
  eliminaBlancos(s);
  assert(strcmp(s, " ")==0);
  
  strcpy(s," . . .  ");
  eliminaBlancos(s);
  assert(strcmp(s, " . . . ")==0);

  strcpy(s,"");
  eliminaBlancos(s);
  assert(strcmp(s, "")==0);

  strcpy(s,"sinblancos");
  eliminaBlancos(s);
  assert(strcmp(s, "sinblancos")==0);



  printf("OK!\n");
  return 0;
}

#include <stdbool.h>
#define MAX 100

void eliminaBlancos (char cadena[]) {
    bool blanco = false;
    int j = 0;
    for(int i = 0; cadena[i] != '\0' && i < MAX; ++i) {
        if (!blanco || cadena[i] != ' ') {
            cadena[j++] = cadena[i];
        }
        blanco = cadena[i] == ' ';
    }
    cadena[j] = '\0';
}

