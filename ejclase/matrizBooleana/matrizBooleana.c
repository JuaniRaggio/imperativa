#include <stdbool.h>
#include "matrizBooleana.h"

struct col {
    size_t col;
    struct col * siguiente;
};

struct fila {
    size_t fila;
    struct col * primera;
    struct fila * siguiente;
};

struct boolMatCDT {
    bool defaultValue;
    struct fila * primera;
};

void setDefaultValue(boolMatADT mat, bool value) { mat->defaultValue = value; }

struct fila * deleteRowRec(struct fila * primera, size_t row, size_t col);

struct col * addColRec(struct col * primera, size_t col) {
    if (primera == NULL || primera->col > col) {
        struct col * nueva = malloc(sizeof(struct col));
        nueva->col = col;
        nueva->siguiente = primera;
        return nueva;
    } else if (primera->col < col) {
        primera->siguiente = addColRec(primera->siguiente, col);
        return primera;
    }
    return primera;
}

struct fila * addRowRec(struct fila * primera, size_t row, size_t col) {
    if (primera == NULL || primera->fila > row) {
        struct fila * nueva = malloc(sizeof(struct fila));
        nueva->fila = row;
        nueva->primera = NULL;
        nueva->primera = addColRec(nueva->primera, col);
        return nueva;
    } else if (primera->fila == row) {
        primera->primera = addColRec(primera->primera, col);
        return primera;
    }
    primera->siguiente = addRowRec(primera->siguiente, row, col);
    return primera;
}

void setFalse(boolMatADT m, size_t row, size_t col) {
    if (m->defaultValue == false) m->primera = addRowRec(m->primera, row, col);
    else m->primera = deleteRowRec(m->primera, row, col);
}

void setTrue(boolMatADT m, size_t row, size_t col) {
    if (m->defaultValue == true) m->primera = addRowRec(m->primera, row, col);
    else m->primera = deleteRowRec(m->primera, row, col);
}

