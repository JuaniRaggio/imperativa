/* Sean Nombre y Curso dos arreglos que contienen el nombre y el curso( ‘G’ o ‘H’) de cada uno de los alumnos de una materia.  */
/* Escribir una función que reciba dichos arreglos como parámetros de entrada y retorne en parámetros de salida otros dos arreglos CursoG y */
/* CursoH con el nombre de los alumnos separados por curso. El string vacío en el nombre indica fin del arreglo. */
#include <ctype.h>
#include <string.h>

// Estoy suponiendo que los arreglos tienen el espacio necesario
void curse_organizer(const char **student, const char *course, char **courseG, char **courseH) {
    for(int i = 0; *student[i] != '\0'; ++i) {
        if (toupper(course[i]) == 'G') {
            strcpy(courseG[i], student[i]);
        } else if (toupper(course[i]) == 'H') {
            strcpy(courseH[i], student[i]);
        }
    }
}

