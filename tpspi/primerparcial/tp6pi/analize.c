#include <stdio.h>
#include <assert.h>
#include <string.h>

#define CHARS_DIM 256

void analize(const char * text, char * chars);

int main(void) {
  char chars[CHARS_DIM];
  char chars2[CHARS_DIM];
  analize("El zorro mete la cola, pero no la pata!", chars);
  assert(strcmp(" !,Eacelmnoprtz", chars)==0);
  analize("ababababab", chars2);
  assert(strcmp("ab", chars2)==0);
  
  analize("", chars);
  assert(strcmp("", chars)==0);
  analize(".............................", chars);
  assert(strcmp(".", chars)==0);
  
  puts("OK");
  return 0;
}
void turnOff(char * vec, int dim){
    for (int i = 0; i < dim; ++i)
        vec[i] = 0;
}

void delZeros(char * v, int dim){
    int j = 0;
    for(int i = 0; i < dim; ++i){
        if(v[i])
        {
            v[j++] = i;
        }
    }
    v[j] = '\0';
}

void analize(const char * text, char * chars){
    turnOff(chars, CHARS_DIM);
    for (int i = 0; text[i] != '\0'; ++i)
    {
        chars[text[i]] = 1;
    }
    delZeros(chars, CHARS_DIM);
}

