/* La computadora construye un conjunto aleatorio de X dígitos distintos (para X usar una constante simbólica). Sólo se usan los dígitos del 1 al 9 */

/* Se le  pide ingresar al usuario el nivel en que quiere jugar.
 * Según esto se trabajará con una tolerancia de hasta N pasos, dentro de los cuales si no logra ganar el juego se termina automáticamente.  */

/* El jugador entra un conjunto de X dígitos distintos por teclado.  */

/* Si el número propuesto por el jugador coincide con el que generó la máquina o la cantidad de chances excedió el número tope N , el juego finaliza */
/* sino el programa debe informarle cuántos dígitos están BIEN (son correctos y están en su lugar) y cuántos son REGULARES */
/* (son correctos pero están fuera de lugar) y se vuelve a ejecutar el paso anterior. Así se va guiando al jugador hasta que adivine el número. */

#include <stdio.h>
#include <getnum.h>
#include <rand.h>

#define LOW 1
#define HIGH 9
#define X 5

void rand_maker(char digits[X], unsigned char * views_digit);
int choose_lvl(void); // Le solicita al usuario que ingrese que nivel quiere jugar y lo retorna en su nombre
unsigned char recieves_digits(char recieved[X]); // Reads and appends digits in the recieved vector
int compares(char digits[X], unsigned char views_digit, char recieved[X], unsigned char views_recieved);

int main(void){
    unsigned char r_views = 0, d_views = 0;
    char digits[X], recieved[X];
    randomize();
    rand_maker(digits, &d_views);
    for(int lvl = choose_lvl(); lvl > 0; --lvl){
        r_views = recieves_digits(recieved);
        if(compares(digits, d_views, recieved, r_views)){
            printf("You won, congrats!");
            return 0;
        }
    }
    printf("Game over!\n");
    return 0;
}

static int rm(unsigned char * views_digit){
    int r;
    unsigned char last_views;
    do {
        last_views = *views_digit;
        r = randInt(LOW, HIGH);
        *views_digit = *views_digit | (0x01 << (r - 1));
    } while(last_views == *views_digit);
    return r;
}

void rand_maker(char digits[X], unsigned char * views_digit) {
    *views_digit = 0;
    for(int i = 0; i < X; ++i) {
        digits[i] = rm(views_digit);
    }
}

int choose_lvl(void) {
    return getint("Introduce level: ");
}

unsigned char recieves_digits(char recieved[X]) {
    printf("Guess the number: ");
    int i = 0;
    unsigned char views = 0;
    do{
        recieved[i] = getchar() - '0';
        views = views | (0x01 << (recieved[i] - 1));
    } while(i < X && recieved[i++] != '\n');
    return views;
}

int compares(char digits[X], unsigned char views_digit, char recieved[X], unsigned char views_recieved) {
    unsigned char regular = 0, good = 0;
    for(int i = 0; i < X; ++i) {
        if(digits[i] == recieved[i])
            ++good;
        else if(((views_digit >> (digits[i] - 1)) | 0x01) && ((views_recieved >> (recieved[i] - 1)) | 0x01))
            ++regular;
    }
    printf("%d are regular, %d are good\n", regular, good);
    return good == X;
}

