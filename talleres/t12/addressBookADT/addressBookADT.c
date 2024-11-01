#include "addressBookADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contactList {
    tContact contact;
    struct contactList * next;
};

typedef struct contactList * contactsHeader;

struct groupList {
    char * groupName;
    contactsHeader people;
    struct groupList * next;
};

typedef struct groupList * groupsHeader;

struct addressBookCDT {
    groupsHeader groups;
    struct groupList * iteratorForGroups;
    struct contactList * iteratorForContacts;
};

addressBookADT newAddressBook(void){
    return calloc(1, sizeof(struct addressBookCDT));
}

groupsHeader addGroupRec(groupsHeader group, const char * toAdd, int * added) {
    int cmp;
    if (group == NULL || (cmp = strcasecmp(group->groupName, toAdd)) > 0) {
        groupsHeader new = malloc(sizeof(*new));
        new->people = NULL;
        new->groupName = malloc(strlen(toAdd) + 1);
        strcpy(new->groupName, toAdd);
        new->next = group;
        *added = 1;
        return new;
    } else if (cmp < 0) {
        group->next = addGroupRec(group->next, toAdd, added);
        return group;
    }
    *added = 0;
    return group;
}

int addGroup(addressBookADT book, const char * groupName) {
    int added = 0;
    book->groups = addGroupRec(book->groups, groupName, &added);
    return added;
}

contactsHeader addContactRec(contactsHeader person, tContact toAdd, int * added) {
    int cmp;
    if (person == NULL || (cmp = strcasecmp(person->contact.name, toAdd.name)) > 0) {
        contactsHeader new = malloc(sizeof(*new));
        new->next = person;
        new->contact = toAdd;
        *added = 1;
        return new;
    } else if (cmp < 0) {
        person->next = addContactRec(person->next, toAdd, added);
        return person;
    }
    *added = 0;
    return person;
}

int addContact(addressBookADT book, const char * groupName, tContact contact) {
    int added = 0, cmp;
    for (groupsHeader aux = book->groups; aux != NULL; aux = aux->next) {
       if ((cmp = strcasecmp(aux->groupName, groupName)) == 0) {
            aux->people = addContactRec(aux->people, contact, &added);
            return added;
       } else if (cmp > 0) {
           return 0;
       }
    }
    return 0;
}


void toBeginForGroup(addressBookADT book, const char * groupName) {
    int cmp;
    for (groupsHeader aux = book->groups; aux != NULL; aux = aux->next) {
        cmp = strcasecmp(aux->groupName, groupName);
        if (cmp == 0) {
            book->iteratorForContacts = aux->people;
            return;
        } else if (cmp > 0) {
            book->iteratorForContacts = NULL;
            return;
        }
    }
    // No existe el grupo en el que se quiere iterar
    printf("No existe el grupo %s, en el que se desea iterar\n", groupName);
    /* book->iteratorForContacts = NULL; */
    return;
}


int hasNextForGroup(addressBookADT book) {
    return book->iteratorForContacts != NULL;
}

/* Retorna un contacto, aborta si no hay siguiente */
tContact nextForGroup(addressBookADT book) {
    if (!hasNextForGroup(book)) {
        printf("Error en la linea %d en el archivo %s, se llama a la funcion %s"
                " sin llamar previamente a hasNextForGroup()", __LINE__, __FILE__, __func__);
        exit(1);
    }
    tContact retValue;
    memcpy(&retValue, &book->iteratorForContacts->contact, sizeof(tContact));
    book->iteratorForContacts = book->iteratorForContacts->next;
    return retValue;
}

/*
** Permite iterar por todos los grupos de la agenda
** El orden es alfabÃ©tico por nombre del grupo.
*/
void toBegin(addressBookADT book) {
    book->iteratorForGroups = book->groups;
}

int hasNext(addressBookADT book) {
    return book->iteratorForGroups != NULL;
}

/* Retorna una copia del grupo, aborta si no hay siguiente */
char * next(addressBookADT book) {
    if (!hasNext(book)) {
        printf("Error en la linea %d en el archivo %s, se llama a la funcion %s"
                " sin llamar previamente a hasNext()", __LINE__, __FILE__, __func__);
        exit(1);
    }
    char * retValue = malloc(strlen(book->iteratorForGroups->groupName) + 1);
    strcpy(retValue, book->iteratorForGroups->groupName);
    book->iteratorForGroups = book->iteratorForGroups->next;
    return retValue;
}

