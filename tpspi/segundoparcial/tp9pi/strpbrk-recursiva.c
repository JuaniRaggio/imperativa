#include <stdio.h>
#include <assert.h>
#include <string.h>

// La primera aparicion de alguno de los caracteres de la cadena chars
char * strpbrkRec(const char * target, const char * chars);

int main(void) {
  char * s = "abcde";
  char * t = "abcdeab";

  assert( strpbrk(s, "") == strpbrkRec(s, ""));
  assert( strpbrk(s, "a") == strpbrkRec(s, "a"));
  assert( strpbrk(s, "xa") == strpbrkRec(s, "xa"));
  assert( strpbrk(s, "xye") == strpbrkRec(s, "xye"));
  assert( strpbrk(s, "r") == strpbrkRec(s, "r"));
  assert( strpbrk(t, "ba") == t);
  assert( strpbrkRec(t, "ba") == strpbrk(t, "ba"));
    printf("OK!");
  return 0;
}

char * strpbrkRec(const char * target, const char * chars) {
    if (*target == '\0' || *chars == '\0') 
        return NULL;
    else if (*target == *chars)
        return target;
    char * caracter = strpbrkRec(target, chars + 1);
    if (caracter != NULL)
        return caracter;
    return strpbrkRec(target + 1, chars);
}

