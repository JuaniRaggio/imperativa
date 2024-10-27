#include <string.h>
// Se necesita uns wrapper ya que strlen solo me va a servir para el caso inicial
// porque para el segundo caso si hago strlen, no voy a tener un cero atras de la letra que voy a querer
// leer

int palindromoRec(const char * s, int longitud) {
    if (longitud <= 1)
        return 1;
    return s[0] == s[longitud - 1] && palindromoRec(s + 1, longitud - 2);
}

int palindromo(const char * s) {
    int len = strlen(s);
    return palindromoRec(s, len);
}

