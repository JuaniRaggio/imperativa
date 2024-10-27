#include <stdio.h>
#define MIN 60
// This macro has to return the amount of minutes that passed from h1:m1 to h2:m2
#define ELAPSED(h1, m1, h2, m2) ((h1)*MIN+(m1))>((h2)*MIN+(m2)) ? ((h1)*MIN+(m1))-((h2)*MIN+(m2)):((h2)*MIN+(m2))-((h1)*MIN+(m1))

int main(){
    int minutos, h1, h2, m1, m2;
    h1 = 2; m1 = 10; h2 = 3; m2 = 15;
    minutos = ELAPSED(h1, m1, h2, m2);/* minutos = 65 */
    printf("Esto deberia ser 65 y es: %d\n", minutos);
    minutos = ELAPSED(3, 15, 2, 10);		/* minutos = 65 */
    printf("Esto deberia ser 65 y es: %d\n");
    minutos = ELAPSED(h1, m1, h1 + 1, m1);	/* minutos = 60 */
    printf("Esto deberia ser 60 y es: %d\n", minutos);
}

