#include <stdbool.h>
#include <string.h>
#include <rand.h>
#include <stdlib.h>
#include <stdio.h>
#include "hangmanADT.h"

#define BLOCK 15

struct level {
    char ** words;
    size_t savedSpace;
    size_t wordsDim;
};

typedef struct level * levels;

struct hangmanCDT {
    levels words;
    // dim va a ser maxLevel pero cuando accedamos
    // va a ser con maxLevel - 1
    size_t dim;
};

hangmanADT newHangman(unsigned int maxLevel) {
    hangmanADT new = malloc(sizeof(struct hangmanCDT));
    new->dim = maxLevel;
    new->words = calloc(new->dim, sizeof(struct level));
    // Lo hago con calloc para que al inicio sean NULL
    return new;
}

bool add(levels level, char * toAdd) {
    int cmp;
    for (int i = 0; i < level->wordsDim; ++i) {
        cmp = strcasecmp(level->words[i],toAdd);
        if (cmp > 0) {
            return false;
        } else if (cmp == 0) {
            if (level->savedSpace == level->wordsDim) {
                level->savedSpace += BLOCK;
                level->words = realloc(level->words, sizeof(char *) * level->savedSpace);
            }
            level->words[level->wordsDim] = malloc(strlen(toAdd) + 1);
            strcpy(level->words[level->wordsDim++], toAdd);
            return true;
        }
    }
    return false;
}

void mycpy(levels level, char * words[]) {
    int i, j;
    for (i = 0; words[i] != NULL; ++i) {
        /* for (j = 0; j < level->wordsDim; ++j) { */
        /*     if (strcasecmp(level->words[j], words[i]) == 0) */
        /* } */
        add(level, words[i]);
    }
}

int addWords(hangmanADT h, char * words[], unsigned int level) {
    level--;
    if (h->dim <= level) return -1;
    int oldDim = h->words[level].wordsDim;
    mycpy(&h->words[level], words);
    return h->words[level].wordsDim - oldDim;
}

int size(const hangmanADT h, unsigned int level) {
    level--;
    if (h->dim < level) return -1;
    return h->words[level].wordsDim;
}

char * word(const hangmanADT h, unsigned int level) {
    return h->words[level].words[randInt(0, h->words[level].wordsDim - 1)];
}

char ** words(const hangmanADT h, unsigned int level) {
    level--;
    if (h->dim < level) return NULL;
    char ** retVector = malloc(sizeof(char *) * h->words[level].wordsDim);
    for (int i = 0; i < h->words[level].wordsDim; ++i) {
        retVector[i] = malloc(strlen(h->words[level].words[i]) + 1);
        strcpy(retVector[i], h->words[level].words[i]);
    }
    return retVector;
}

