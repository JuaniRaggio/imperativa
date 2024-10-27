#include <stdbool.h>
#define ASC 1
#define DSC -1
#define NONE 0

int filaAsc(unsigned int dim, int fila[]) {
    int ascendencia = NONE;
    for(int i = 1; i < dim; ++i) {
        if (fila[i - 1] < fila[i] && ascendencia != DSC) {
            ascendencia = ASC;
        } else if (fila[i - 1] > fila[i] && ascendencia != ASC) {
            ascendencia = DSC;
        } else if (fila[i - 1] != fila[i]) {
            return NONE;
        }
    }
    return ascendencia;
}

int algunaAsc(unsigned int dim, int m[][dim]) {
    bool found = false;
    for(int i = 0; i < dim && !found; ++dim) {
        found = filaAsc(dim, m[i]) == true;
    }
    return found;
}

int todasAsc(unsigned int dim, int m[][dim]) {
    bool found = true;
    for(int i = 0; i < dim && found; ++i){
        found = filaAsc(dim, m[i]);
    }
    return found;
}

int eliminaRep(int v[], unsigned int dim) {
    int i = 0, j = 1, lv = !v[i];
    while(j < dim){
        if(v[i] == lv){
            ++j;
        } else {
            v[i++] = v[j];
            lv = v[j++];
        }
    }
    return i;
}


