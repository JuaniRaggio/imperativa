#include <stdio.h>
#include <assert.h>

unsigned int ackermann(unsigned int m, unsigned int n);

int main(void) {

  for(int i=0; i < 100; i++)
     assert(ackermann(0, i)==i+1);

  assert(ackermann(3,0)==5);
  assert(ackermann(3,2)==29);

  puts("Wait for it...");

  assert(ackermann(4,1)==65533);

  puts("Legendary!");
  return 0;
}

unsigned int ackermann(unsigned int m, unsigned int n) {
    if(m == 0)
        return n + 1;
    else if(n == 0)
        return ackermann(m - 1, 1);
    else
        return ackermann(m - 1, ackermann(m, n - 1));
}

