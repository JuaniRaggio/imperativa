#include <getnum.h>
#include <rand.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 5
#define BLOCK 4
#define LETRAS ('z' - 'a')

int read_assign(char adivinadas[], int * ok, const char * palabra);
void game_over(const char * word, char * guessed);
void show_vec(char vec[]);
int fill_vecs(char vec[], char c, const char * arr, int *restantes);
char ** add_word(char *** old_dic, int * dim, int * cant);
char ** dic_mkr(int palabras);
void jugar(char ** dic, int dim);

int main(void){
    // Si creo un vector static en el main, se me vuelve a crear cada vez que ejecuto el programa?
    // Entiendo que si lo hago en una funcion, se crearia solo la primera vez que llame a la funcion
    // pero necesito que el vector diccionario se cree una sola vez por si quiero agregar palabras
    int cant = DEFAULT, space = DEFAULT;
    char ** dic = dic_mkr(cant);
    int opcion;
    do {
        randomize();
        opcion = getint("Introduzca:\n\t1 - Si desea jugar\n\t2 - Si desea agregar una palabra al diccionario"
                        "\n\t3 - Si desea cerrar el programa\n");
        switch(opcion) {
            case 1:
                jugar(dic, cant);
                break;
            case 2:
                dic = add_word(&dic, &cant, &space);
                break;
        }
    } while(opcion != 3);
    free(dic);
    return 0;
}

char ** dic_mkr(int palabras) {
    char ** new_dic = malloc(palabras * sizeof(*new_dic));
    new_dic[0] = "hola";
    new_dic[1] = "pelele";
    new_dic[2] = "aurora";
    new_dic[3] = "league of legends";
    new_dic[4] = "eclesiastico";
    return new_dic;
}

char ** add_word(char *** old_dic, int * dim, int * space) {
    if(*dim % *space) {
        *space += BLOCK;
        *old_dic = realloc(*old_dic, sizeof(**old_dic) * *space);
    }
    // Hay alguna forma de recibir un str de entrada standard y apuntar a una zona de memoria con ese str, es decir hacerlo cte
    // o puedo hacer que las palabras que agregue sean vectores dinamicos
    return *old_dic;
}

void show_vec(char vec[]) {
    for(int i = 0; vec[i] != '\0'; ++i)
        printf("%c", vec[i]);
    printf("\n");
    return;
}

int fill_vecs(char vec[], char c, const char * arr, int *restantes){
    int i, a_adivinar = 0;
    for(i = 0; arr[i] != '\0'; ++i) {
        if(arr[i] == ' '){
            vec[i] =  ' ';
        }else { 
            vec[i] = '-';
            ++a_adivinar;
        }
    }
    vec[i] = '\0';
    *restantes = a_adivinar;
    return i;
}

void game_over(const char * word, char * guessed) {
    printf("%s la palabra a adivinar era: %s\n", strcmp(word, guessed) == 0 ? "Felicitaciones":"Lo siento :%(", word);
    return;
}

int read_assign(char adivinadas[], int * ok, const char palabra[]) {
    int guessed_one = 0;
    char letra = getchar();
    letra = tolower(letra);
    for(int i = 0; palabra[i] != '\0'; ++i) {
        if(palabra[i] == letra && adivinadas[i] != letra) {
            adivinadas[i] = letra;
            ++*ok;
            guessed_one = 1;
        }
    }
    while(getchar() != '\n');
    return guessed_one == 0 ? 1:0;
}

void jugar(char ** dic, int dim) {
    int p_idx = randInt(0, dim - 1), 
    vidas = getint("Ingrese la cantidad de vidas que desea tener: "),
    restantes = strlen(dic[p_idx]), win = 0;
    char adivinadas[restantes + 1];
    fill_vecs(adivinadas, '-', dic[p_idx], &restantes);
    printf("Adivine la palabra...");
    while(vidas > 0 && restantes != win) {
        show_vec(adivinadas);
        vidas -= read_assign(adivinadas, &win, dic[p_idx]);
    }
    // Podria hacer una hashtable que haria que el accesso a las letras sea mas rapido
    game_over(dic[p_idx], adivinadas);
    return;
}

