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

bibleADT newBible(void) {
    return calloc(1, sizeof(struct bibleCDT));
}

// En estas funciones que tenemos que hacer muchas operaciones sobre un campo especifico del ADT
// es conveniente hacer al principio un puntero a ese que queremos usar, en este caso a un book
// y accedemos directo a los campos del book
// Porque sino queda poco legible
int addVerse(bibleADT bible, size_t bookNbr, size_t verseNbr, const char * verse) {
    tBook * bookToModify = &bible->books[bookNbr - 1];
    if (bookToModify->space < verseNbr) {
        bookToModify->verses = realloc(bookToModify->verses, sizeof(bookToModify->verses) * verseNbr);
        while (bookToModify->space < verseNbr) {
            bookToModify->verses[bookToModify->space++] = NULL;
        }
    } else if (bookToModify->verses[verseNbr - 1] != NULL) {
        return 0;
    }
    size_t i = 0;
    while (verse[i] != '\0') {
        if (i % BLOCK == 0) {
            bookToModify->verses[verseNbr - 1] = realloc(bookToModify->verses[verseNbr - 1], i + BLOCK);
        }
        bookToModify->verses[verseNbr - 1][i] = verse[i];
        i++;
    }
    bookToModify->verses[verseNbr - 1][i++] = '\0';
    bookToModify->verses[verseNbr - 1] = realloc(bookToModify->verses[verseNbr - 1], i);
    return 1;
}

char * verseCopy(char * verse) {
    char * copy = NULL;
    int i;
    for (i = 0; verse[i] != '\0'; ++i) {
        if (i % BLOCK == 0) {
            copy = realloc(copy, sizeof(*copy) * (i + BLOCK));
        }
        copy[i] = verse[i];
    }
    copy[i++] = '\0';
    copy = realloc(copy, sizeof(*copy) * i);
    return copy;
}

char * getVerse(bibleADT bible, size_t bookNbr, size_t verseNbr) {
    if (bible->books[bookNbr - 1].verses == NULL || bible->books[bookNbr - 1].verses[verseNbr - 1] == NULL) {
        return NULL;
    }
    return verseCopy(bible->books[bookNbr - 1].verses[verseNbr - 1]);
}

void freeBible(bibleADT bible) {
    for (int i = 0; i < BOOKS_IN_BIBLE; ++i) {
        for (int j = 0; j < bible->books[i].space; ++j) {
            free(bible->books[i].verses[j]);
        }
        free(bible->books[i].verses);
    }
    free(bible);
}

