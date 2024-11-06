#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictADT.h"

#define LETTERS ('z'-'a'+1)
#define IDX(letter) (tolower(letter) - 'a')

struct word {
    char * word;
    char * definition;
    size_t wordLen;
    size_t defLen;
    struct word * next;
};

typedef struct word * wordList;

struct wordDict {
    wordList firstWord;
    size_t wordsWithLetter;
};

struct dictCDT {
    struct wordDict dict[LETTERS];
    size_t wordsInDict;
};

dictADT newDict(void) {
    return calloc(1, sizeof(struct dictCDT));
}

#define BLOCK 50

static void myCpy(char ** t, const char * source, size_t * from) {
    int i;
    for (i = 0; source[i] != '\0'; ++i) {
        if (*from % BLOCK == 0) {
            *t = realloc(*t, *from + BLOCK + 1);
        }
        (*t)[*from++] = source[i];
    }
    (*t)[*from] = '\0';
}

wordList addDefRec(wordList list, const char * word, const char * definition, int * added) {
    int cmp;
    if (list == NULL || (cmp = strcasecmp(list->word, word)) > 0) {
        wordList new = malloc(sizeof(*new));
        new->wordLen = strlen(word);
        new->word = malloc(new->wordLen + 1);
        new->defLen = 0;
        strcpy(new->word, word);
        myCpy(&new->definition, definition, &new->defLen);
        new->next = list;
        return new;
    } else if (cmp == 0) {
        myCpy(&list->definition, definition, &list->defLen);
        *added = 0;
        return list;
    }
    list->next = addDefRec(list->next, word, definition, added);
    return list;
}

/* Recibe una palabra y una definición. Si la palabra existe, agrega la nueva
   definición a la  ya existente.
   Si la palabra no existe en el diccionario, la agrega junto con su definición
*/
void addDefinition(dictADT dict, const char * word, const char * deff) {
    // Me aseguran que las palabras son minusculas y validas
    int added = 0, idx = IDX(word[0]);
    dict->dict[idx].firstWord = addDefRec(dict->dict[idx].firstWord, word, deff, &added);
    dict->dict[idx].wordsWithLetter += added;
    dict->wordsInDict += added;
}

char * getDeffRec(const wordList list, const char * word) {
    int cmp;
    if (list == NULL || (cmp = strcasecmp(list->word, word)) > 0) return NULL;
    if (cmp == 0) {
        char * def = malloc(list->wordLen);
        int i = 0;
        while (word[i] != '\0') {
            def[i] = word[i];
            ++i;
        }
        return def;
    }
    return getDeffRec(list->next, word);
}

char * getDeff(const dictADT dict, const char * word) {
    return getDeffRec(dict->dict[IDX(word[0])].firstWord, word);
}

/* Retorna un vector ordenado con la copia de todas las palabras que
   comienzan con una letra.
   Si no hay palabras que empiecen con la letra retorna NULL y *dim en cero
*/
char ** wordsBeginWith(const dictADT dict, char letter, size_t * dim) {
    struct wordDict * aux = &dict->dict[IDX(letter)];
    char ** wordsWith = malloc(sizeof(*wordsWith) * aux->wordsWithLetter);
    for (int i = 0; i < dict->dict[IDX(letter)].wordsWithLetter; ++i) {
    }
}

/* Retorna un vector ordenado con la copia de todas las palabras del diccionario
   Si no hay palabras retorna NULL y *dim en cero
*/
char ** words(const dictADT dict, size_t * dim);

/* Remueve la palabra del diccionario. Si no existe no hace nada */
void removeWord(dictADT dict, const char * word);
// TAREA

void freeDictRec(wordList list) {
    if (list == NULL) return;
    freeDictRec(list->next);
    free(list->word);
    free(list->definition);
    free(list);
}

/* Libera todos los recursos utilizados por el TAD */
void freeDict(dictADT dict) {
    for (int i = 0; i < dict->wordsInDict; ++i)
        freeDictRec(dict->dict[i].firstWord);
    free(dict);
}

