#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include "socialADT.h"

#define MAX_NAME_LEN 21

struct related {
    char name[MAX_NAME_LEN];
    struct related * next;
};

typedef struct related * relatedList;

struct people {
    char name[MAX_NAME_LEN];
    relatedList related;
    size_t relatedLen;
    struct people * next;
};

typedef struct people * peopleList;

struct socialCDT {
    peopleList localList;
    size_t peopleLen;
};

socialADT newSocial() {
    return calloc(1, sizeof(struct socialCDT));
}

static void freeRelated(relatedList related) {
    if (related == NULL)
        return;
    freeRelated(related->next);
    free(related);
}

static void freePeople(peopleList people) {
    if (people == NULL)
        return;
    freePeople(people->next);
    freeRelated(people->related);
    free(people);
}

void freeSocial(socialADT soc) {
    freePeople(soc->localList);
    free(soc);
}

peopleList addPersonRec(peopleList people, const char * name, int * added) {
    int cmp;
    if (people == NULL || (cmp = strcasecmp(people->name, name)) > 0 ) {
        peopleList newPerson = malloc(sizeof(*newPerson));
        newPerson->next = people;
        strcpy(newPerson->name, name);
        newPerson->related = NULL;
        newPerson->relatedLen = 0;
        *added = 1;
        return newPerson;
    } else if (cmp == 0) {
        *added = 0;
        return people;
    }
    people->next = addPersonRec(people->next, name, added);
    return people;
}

void addPerson(socialADT soc, const char * name) {
    int added = 0;
    soc->localList = addPersonRec(soc->localList, name, &added);
    soc->peopleLen += added;
}

static relatedList addRelatedRec(relatedList related, const char * name) {
    int cmp;
    if (related == NULL || (cmp = strcasecmp(related->name, name)) == 0 || cmp > 0) {
        relatedList newRelated = malloc(sizeof(struct related));
        strcpy(newRelated->name, name);
        newRelated->next = related;
        return newRelated;
    }
    related->next = addRelatedRec(related->next, name);
    return related;
}

void addRelated(socialADT soc, const char * name, const char * related) {
    peopleList iterator = soc->localList;
    int cmp;
    while (iterator != NULL) {
        if ((cmp = strcasecmp(iterator->name, name)) == 0) {
            iterator->related = addRelatedRec(iterator->related, related);
            ++iterator->relatedLen;
            return;
        } else if (cmp > 0) {
            break;
        }
        iterator = iterator->next;
    }
}

char ** makeRelatedVector(const peopleList person) {
    int i = 0;
    char ** vector = malloc(sizeof(char *) * (person->relatedLen + 1));
    for (relatedList iterator = person->related; iterator != NULL; iterator = iterator->next, ++i) {
        vector[i] = malloc(strlen(iterator->name) + 1);
        strcpy(vector[i], iterator->name);
    }
    vector[i] = NULL;
    return vector;
}

char ** related(const socialADT soc, const char * person) {
    peopleList iterator = soc->localList;
    int cmp;
    while (iterator != NULL) {
        if ((cmp = strcasecmp(iterator->name, person)) == 0) {
            return makeRelatedVector(iterator);
        } else if (cmp > 0) {
            break;
        }
        iterator = iterator->next;
    }
    char ** vector = malloc(sizeof(char *));
    vector[0] = NULL;
    return vector;
}

char ** persons(const socialADT soc) {
    char ** peopleVector = malloc(sizeof(char *) * (soc->peopleLen + 1));
    int i = 0;
    for (peopleList iterator = soc->localList; iterator != NULL; iterator = iterator->next, ++i) {
        peopleVector[i] = malloc(strlen(iterator->name) + 1);
        strcpy(peopleVector[i], iterator->name);
    }
    peopleVector[i] = NULL;
    return peopleVector;
}

