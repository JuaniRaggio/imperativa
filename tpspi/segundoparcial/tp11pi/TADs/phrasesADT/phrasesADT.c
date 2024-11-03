#include <string.h>
#include <stdlib.h>
#include "phrasesADT.h"

#define BLOCK 50

// Estoy suponiendo que se usan la mayoria de las phrases

struct phrase {
    // Si no esta ocupada la phrase, text == NULL
    char * text;
    size_t textLen;
};

struct phrasesCDT {
    size_t keyFrom;
    size_t keyTo;
    size_t ocupied;
    struct phrase * phrasesCollection;
};

phrasesADT newPhrasesADT(size_t keyFrom, size_t keyTo) {
    if (keyFrom > keyTo) return NULL;
    phrasesADT newPhrases = malloc(sizeof(struct phrasesCDT));
    newPhrases->keyFrom = keyFrom;
    newPhrases->keyTo = keyTo;
    newPhrases->ocupied = 0;
    newPhrases->phrasesCollection = calloc(keyTo - keyFrom + 1, sizeof(struct phrase));
    return newPhrases;
}


void freePhrases(phrasesADT ph) {
    size_t totalPhrases = ph->keyTo - ph->keyFrom + 1;
    for (size_t i = 0; i < totalPhrases; ++i) {
        free(ph->phrasesCollection[i].text);
    }
    free(ph->phrasesCollection);
    free(ph);
}

char * mkCpy(char * text, size_t textLen) {
    char * copy = malloc(sizeof(*text) * (textLen + 1));
    strcpy(copy, text);
    return copy;
}

char isValidKey(phrasesADT ph, size_t key) {
    return ph->keyTo >= key && ph->keyFrom <= key;
}

// Tengo que acostumbrarme a crear los punteros al principio para que
// las funciones me queden mas legibles
int put(phrasesADT ph, size_t key, const char * phrase) {
    if (!isValidKey(ph, key))
        return 0;
    key = key - ph->keyFrom;
    int i;
    if (ph->phrasesCollection[key].text == NULL)
        ph->ocupied++;
    for (i = 0; phrase[i] != 0; ++i) {
        if (i >= ph->phrasesCollection[key].textLen) {
            ph->phrasesCollection[key].textLen += BLOCK;
            ph->phrasesCollection[key].text = realloc(ph->phrasesCollection[key].text, ph->phrasesCollection[key].textLen);
        }
        ph->phrasesCollection[key].text[i] = phrase[i];
    }
    // Importante primero reallocar y despues agregar el cero final porque sino puede que escribamos en una zona que no
    // pertenece a la alocada
    ph->phrasesCollection[key].textLen = i;
    ph->phrasesCollection[key].text = realloc(ph->phrasesCollection[key].text, ph->phrasesCollection[key].textLen + 1);
    ph->phrasesCollection[key].text[i] = '\0';
    return 1;
}

char * get(const phrasesADT ph, size_t key) {
    if (!isValidKey(ph, key) || ph->phrasesCollection[key - ph->keyFrom].text == NULL)
        return NULL;
    return mkCpy(ph->phrasesCollection[key - ph->keyFrom].text, ph->phrasesCollection[key - ph->keyFrom].textLen);
}

unsigned long concatAndResize(char ** target, unsigned long from, char * source, size_t len) {
    *target = realloc(*target, sizeof(**target) * (from + len + 1));
    int i;
    for (i = 0; source[i] != 0; ++i) {
        (*target)[from++] = source[i];
    }
    (*target)[from] = '\0';
    return from;
}


size_t size(const phrasesADT ph) {
    return ph->ocupied;
}

char * concat(const phrasesADT ph, size_t from, size_t to) {
    if (!isValidKey(ph, from) || !isValidKey(ph, to))
        return NULL;
    from -= ph->keyFrom;
    to -= ph->keyFrom;
    char * chain = NULL;
    unsigned long idx = 0;
    while (from < to) {
        if (ph->phrasesCollection[from].text != NULL) {
            idx = concatAndResize(&chain, idx, ph->phrasesCollection[from].text, ph->phrasesCollection[from].textLen);
        }
        ++from;
    }
    if (chain == NULL) {
        chain = malloc(sizeof(*chain));
        strcpy(chain, "");
    }
    return chain;
}


char * concatAll(const phrasesADT ph) {
    return concat(ph, ph->keyFrom, ph->keyTo);
}

