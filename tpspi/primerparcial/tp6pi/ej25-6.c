#include <stdio.h>
#include <assert.h>
#include <string.h>

unsigned int copiaSubVector(const char * arregloIn, char * arregloOut, unsigned int desde, unsigned int hasta, unsigned int dimMax);

int main(void) {
  char s[100];
  assert(copiaSubVector("un texto", s,0,0,1)==0);
  assert(strcmp(s, "")==0);
  assert(copiaSubVector("un texto", s,0,0,10)==1);
  assert(strcmp(s, "u")==0);
  assert(copiaSubVector("un texto", s,0,10,1)==0);
  assert(strcmp(s, "")==0);

  assert(copiaSubVector("un texto", s,45,130,1)==0);


  assert(copiaSubVector("un texto", s,0,130,2)==1);
  assert(strcmp(s, "u")==0);

  assert(copiaSubVector("un texto", s,0,130,202)==8);
  assert(strcmp(s, "un texto")==0);

  assert(copiaSubVector("un texto", s,0,7,202)==8);
  assert(strcmp(s, "un texto")==0);

  assert(copiaSubVector("un texto", s,0,7,9)==8);
  assert(strcmp(s, "un texto")==0);

  assert(copiaSubVector("un texto", s,2,5,8)==4);
  assert(strcmp(s, " tex")==0);
  
  assert(copiaSubVector("un texto", s,45000,130000,10)==0);

  printf("OK!\n");
  return 0;
}

#define MAX 50

unsigned int copiaSubVector(const char * arregloIn, char * arregloOut, unsigned int desde, unsigned int hasta, unsigned int dimMax){
    unsigned int len;

    // Recordemos que si me pasan un string, si puedo ver la longitud desde la funcion y de hecho es importante verlo ya que me puede generar
    // un segmentation fault o pueden forzarme a trabajar en una zona de memoria que no queremos afectar

    if (desde < 0 || hasta < 0 || desde > hasta || (len = strlen(arregloIn)) < desde)
        return 0;
    unsigned int copiados = 0;
    while(arregloIn[desde] != '\0' && copiados < dimMax - 1 && desde <= hasta && copiados < MAX) {
        arregloOut[copiados++] = arregloIn[desde++];
    }
    arregloOut[copiados] = '\0';
    return copiados;
}



