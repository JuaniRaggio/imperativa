#include <stdio.h>
#include <assert.h>

#define VALORABRE 1
#define VALORCIERRA -1

int balance(const char *texto);

int main(void) {

  assert(balance("")==0);
  assert(balance("((()))")==0);
  assert(balance(")(")==0);
  assert(balance("()()")==0);
  assert(balance(")))(((")==0);
  assert(balance("))) ((( ))( ()() ()()(")==0);
  
  assert(balance(")")!=0);
  assert(balance("(")!=0);
  assert(balance(")()")!=0);
  assert(balance(" ) ")!=0);
  assert(balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))")!=0);
  assert(balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))((((((((((((")!=0);

  printf ("OK!\n");
  return 0;
}

int balance(const char *texto) {
    if (*texto == ')') {
        return VALORCIERRA + balance(texto + 1);
    } else if (*texto == '(') {
        return VALORABRE + balance(texto + 1);
    } else if (*texto != '\0') {
        return balance(texto + 1);
    } else {
        return 0;
    }
}

