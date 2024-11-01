#include <stdlib.h>
#include "bibleADT.h"

#define BOOKS_IN_BIBLE 76
#define BLOCK 50

struct book {
    char ** verses;
    size_t space;
};

typedef struct book tBook;

struct bibleCDT {
    tBook books[BOOKS_IN_BIBLE];
};

bibleADT newBible() {
    return calloc(1, sizeof(struct book));
}

// En estas funciones que tenemos que hacer muchas operaciones sobre un campo especifico del ADT
// es conveniente hacer al principio un puntero a ese que queremos usar, en este caso a un book
// y accedemos directo a los campos del book
// Porque sino te pasa lo que me paso a mi jajaja
int addVerse(bibleADT bible, size_t bookNbr, size_t verseNbr, const char * verse) {
    struct book * aux = &bible->books[bookNbr - 1];
    if (bible->books[bookNbr - 1].space == 0) bible->books[bookNbr - 1].verses = NULL;
    if (bible->books[bookNbr - 1].verses[verseNbr - 1] != NULL) return 0;
    if (bible->books[bookNbr - 1].space < verseNbr) {
        bible->books[bookNbr - 1].verses = 
            realloc(bible->books[bookNbr - 1].verses, sizeof(bible->books[bookNbr - 1].verses) * (verseNbr - 1));
        while (bible->books[bookNbr - 1].space < verseNbr) {
            bible->books[bookNbr - 1].verses[bible->books[bookNbr - 1].space++] = NULL;
        }
    }
    int i = 0;
    while (verse[i] != '\0') {
        if (i % BLOCK == 0) {
            bible->books[bookNbr - 1].verses[verseNbr - 1] 
                = realloc(bible->books[bookNbr - 1].verses[verseNbr - 1], sizeof(bible->books[bookNbr - 1].verses[verseNbr - 1]) * (i + BLOCK));
        }
        bible->books[bookNbr - 1].verses[verseNbr - 1][i] = verse[i];
        ++i;
    }
    bible->books[bookNbr - 1].verses[verseNbr - 1] 
        = realloc(bible->books[bookNbr - 1].verses[verseNbr - 1], sizeof(bible->books[bookNbr - 1].verses[verseNbr - 1]) * i);
    return 1;
}

char * getVerse(bibleADT bible, size_t bookNbr, size_t verseNbr) {
    char * retVerse = NULL;
}

void freeBible(bibleADT bible) {
    for (int i = 0; i < BOOKS_IN_BIBLE; ++i) {
        for (int j = 0; j < bible->books[i].space; ++j) {
            free(bible->books[i].verses[j]);
        }
    }
    free(bible);
}

