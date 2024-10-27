#include <stdio.h>
#include <assert.h>
#include <string.h>

#define ERROR 0
#define EXITO 1
#define CANT_VOCAL 5

int elimVocales(char * s, int m[][CANT_VOCAL], unsigned int n);

int main(void) {
  int m[6][CANT_VOCAL];
  char s[] = "las buenas ideas escasean, si";

  assert(elimVocales(s, m, 6)==EXITO);
  assert(strcmp(s, "ls bns ds scsn, s")==0);
  assert(m[0][0] == 1);
  assert(m[1][0] == 8);
  assert(m[2][0] == 14);
  assert(m[3][0] == 20);
  assert(m[4][0] == 23);
  assert(m[5][0] == -1);
  
  assert(m[0][1] == 6);
  assert(m[1][1] == 13);
  assert(m[2][1] == 17);
  assert(m[3][1] == 22);
  assert(m[4][1] == -1);

  assert(m[0][2] == 11);
  assert(m[1][2] == 28);
  assert(m[2][2] == -1);

  assert(m[0][3] == -1);

  assert(m[0][4] == 5);
  assert(m[1][4] == -1);

  strcpy(s, "las buenas ideas escasean, si");
  assert(elimVocales(s, m, 1)==ERROR);
  assert(strcmp(s, "las buenas ideas escasean, si")==0);
  assert(m[0][0]==-1);
  assert(m[0][1]==-1);
  assert(m[0][2]==-1);
  assert(m[0][3]==-1);
  assert(m[0][4]==-1);

  assert(elimVocales(s, m, 5)==ERROR);
  assert(strcmp(s, "ls bns ds scsan, s")==0);
  assert(m[0][0] == 1);
  assert(m[1][0] == 8);
  assert(m[2][0] == 14);
  assert(m[3][0] == 20);
  assert(m[4][0] == -1);
  
  assert(m[0][1] == 6);
  assert(m[1][1] == 13);
  assert(m[2][1] == 17);
  assert(m[3][1] == 22);
  assert(m[4][1] == -1);

  assert(m[0][2] == 11);
  assert(m[1][2] == 28);
  assert(m[2][2] == -1);

  assert(m[0][3] == -1);

  assert(m[0][4] == 5);
  assert(m[1][4] == -1);

  printf("OK!\n");
  return 0;
}

#include <ctype.h>

#define ISVOWEL(a) (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
#define END -1

int look_up(char c, const char vowels[]){
    // Looks for c in vowels, returns c's index
    for(int i = 0; i < CANT_VOCAL; ++i){
        if(c == vowels[i])
            return i;
    }
    return END;
}

int incInc(int m[][CANT_VOCAL], unsigned int n, int i, int to_inc, unsigned int ap[CANT_VOCAL]) {
    // Increase views vector
    // assigns to m, its corresponding value if there is space left
    if(ap[to_inc] >= n - 1){
        return ERROR;
    }

    m[ap[to_inc]++][to_inc] = i;
    m[ap[to_inc]][to_inc] = END;

    return EXITO;
    // return 1 si todo ok, 0 si no lo pudo agragar
}

int elimVocales(char * s, int m[][CANT_VOCAL], unsigned int n) {
    // Fill first row w/end mark
    for(int i = 0; i < CANT_VOCAL; ++i)
        m[0][i] = END;

    if(n <= 1)
        return ERROR;

    // Views vector
    unsigned int ap[CANT_VOCAL] = {0};

    // vowels vector
    static const char vow[] = {'a', 'e', 'i', 'o', 'u'};
    int j = 0, to_inc, ret = EXITO;
    char aux;

    for(int i = 0; s[i] != '\0'; ++i) {
        aux = tolower(s[i]);
        if(ISVOWEL(aux)) {
            to_inc = look_up(aux, vow);
            if(!incInc(m, n, i, to_inc, ap)){
                ret = ERROR;
                s[j++] = s[i];
            }
        } else {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
    return ret;
}


