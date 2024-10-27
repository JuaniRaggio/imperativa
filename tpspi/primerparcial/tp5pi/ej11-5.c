#include <ctype.h>
#include <stdio.h>

int main() {
  int a, b, c;
  a = getchar();
  b = getchar();
  c = getchar();

  if (isupper(a) && a != 'A' && a != 'E' && a != 'I' && a != 'O' && a != 'U')
    printf("El caracter %c es una consonante mayúscula \n", a);
  else if(islower(a) && a != 'a' && a != 'e' && a != 'i' && a != 'o' && a != 'u') 
    printf("El caracter %c es una consonante minúscula \n", a);
  else if((isalpha(a)) && (tolower(a) == 'a' || tolower(a) == 'o' || tolower(a) == 'e' || tolower(a) == 'i' || tolower(a) == 'u')) 
    printf("El caracter %c es una vocal \n", a);
  else
    printf("El caracter %c no es una letra \n", a);

  if(b%2) 
    printf("El valor ASCII de %c es par \n", b);

  if(isdigit(b)) 
    printf("El caracter %c representa un dígito par \n", b);

  if(isupper(c) || c == 'a'||c == 'e'||c == 'i'||c == 'o'|| c == 'u') 
    printf("El caracter %c es una vocal o es mayúscula \n", c);

  if(isalpha(c) && (c = tolower(c)) != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') 
    printf("El caracter %c no es una vocal pero es letra \n", c);
}
