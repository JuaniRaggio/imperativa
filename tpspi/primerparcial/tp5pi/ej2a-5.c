#include <stdio.h>
#include <ctype.h>

int main(){
for ( int i = 46; i <= 'H'; i++)
{
      printf("%d %c %c\t", i, i, tolower(i));
      printf("%s ", isalnum(i)? "si" : "no");
      printf("%s ", isalpha(i)? "si" : "no");
      printf("%s ", isdigit(i)? "si" : "no");
      printf("%s ", islower(i)? "si" : "no");
      printf("%s ", isupper(i)? "si" : "no");
      printf("%s ", isxdigit(i)? "si" : "no");
      printf("%s ", iscntrl(i)? "si" : "no");
      printf("%s \n", ispunct(i)? "si" : "no");
}
}
