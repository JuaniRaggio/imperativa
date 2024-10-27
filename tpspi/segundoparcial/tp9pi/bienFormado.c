#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int bienformado(char * s);

int main(void) {
 char * zero[]={"abcd4a10bb2", "", "0000", "a1", "abc3", "0a1"};

  char * not_zero[] ={ "a", "1", "a2", "abc2", "abc4", "abc33", "0123", "2aa", "$1", "@@2", "abcd22", "@@"};

  for(int i=0; i < sizeof(zero)/sizeof(zero[0]);i++) {
    printf("%s\n", zero[i]);
    assert(bienformado(zero[i])==0);
  }    

  for(int i=0; i < sizeof(not_zero)/sizeof(not_zero[0]);i++) {
    printf("%s\n", not_zero[i]);
    assert(bienformado(not_zero[i]) !=0);
 }

  puts("OK!");
  return 0;
}

int bienformado(char * s) {
    if (*s == '\0')
        return 0;
    if (isdigit(*s)) {
        if (*(s + 1) == '\0') {
            return -(*s - '0');
        } else {
            return bienformado(s + 1) == 0;
        }
    } else if (isalpha(*s)) {
        return 1 + bienformado(s + 1) == 0;
    }
    return 0;
}

