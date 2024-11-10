#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "museumTicketADT.h"

#define DAYS 366

// Se desea administrar los tickets para un año
// Cantidad de tickets vendidos en un año
// Tenemos un vector para los dias del año y la cantidad de tickets vendidos en
// ese año
// Cada elemento va a ser una estructura que va a necesitar tener la cantidad
// de tickets que se vendieron ese dia
// Cada elemento va a ser una lista para guardar los nombres pues yearTickets
// nos pide buscar por nombre de visitante
// Iteradores para recorrer a las personas de un dia

struct visitor {
    char * name;
    // opcional, una persona puede comprar mas de un ticket
    size_t tickets;
    struct visitor * next;
};

typedef struct visitor * tVisitor;

struct day {
    tVisitor visitorsList;
    tVisitor iterator;
    size_t soldTickets;
};

typedef struct day tDay;

struct museumTicketCDT {
    tDay dayInfo[DAYS];
    size_t soldTickets; 
};

museumTicketADT newMuseumTicket(void) {
    return calloc(1, sizeof(struct museumTicketCDT));
}

size_t isValidDay(size_t day) { return (day >= DAYS || day == 0) ? DAYS + 1:day - 1; }

tVisitor addTicketRec(tVisitor list, char * visitor, size_t * sold) {
    int cmp;
    if (list == NULL || (cmp = strcasecmp(list->name, visitor)) > 0) {
        tVisitor newTicket = malloc(sizeof(struct visitor));
        newTicket->name = malloc(strlen(visitor) + 1);
        strcpy(newTicket->name, visitor);
        newTicket->tickets = 1;
        *sold = 1;
        newTicket->next = list;
        return newTicket;
    } else if (cmp == 0) {
        *sold = 1;
        list->tickets++;
        return list;
    }
    list->next = addTicketRec(list->next, visitor, sold);
    return list;
}

int addTicket(museumTicketADT museum, size_t dayOfYear,  char * visitor) {
    if ((dayOfYear = isValidDay(dayOfYear)) == DAYS + 1) return 0;
    size_t sold;
    museum->dayInfo[dayOfYear].visitorsList = addTicketRec(museum->dayInfo[dayOfYear].visitorsList, visitor, &sold);
    if (!sold) return 0;
    museum->soldTickets++;
    return ++museum->dayInfo[dayOfYear].soldTickets;
}

int dayTickets(const museumTicketADT museum, size_t dayOfYear){
    if ((dayOfYear = isValidDay(dayOfYear)) == DAYS + 1) return -1;
    return museum->dayInfo[dayOfYear].soldTickets;
}

int yearTickets(const museumTicketADT museumTicketADT) { return museumTicketADT->soldTickets; }

void toBeginByDay(museumTicketADT museum, size_t dayOfYear) {
    if ((dayOfYear = isValidDay(dayOfYear)) == DAYS + 1) {
        printf("Valor invalido de dayOfYear en la linea %d en el archivo %s", __LINE__, __FILE__);
        exit(1);
    }
    museum->dayInfo[dayOfYear].iterator = museum->dayInfo[dayOfYear].visitorsList;
}

size_t hasNextByDay(museumTicketADT museum, size_t dayOfYear) {
    if ((dayOfYear = isValidDay(dayOfYear)) == DAYS + 1) {
        printf("Valor invalido de dayOfYear en la linea %d en el archivo %s", __LINE__, __FILE__);
        exit(1);
    }
    return museum->dayInfo[dayOfYear].iterator != NULL;
}

char * nextByDay(museumTicketADT museum, size_t dayOfYear) {
    if ((dayOfYear = isValidDay(dayOfYear)) == DAYS + 1) { //|| !hasNextByDay(museum, dayOfYear + 1)) {
        printf("Error al llamar a la funcion %s en la linea %d", __func__, __LINE__);
        exit(1);
    }
    tVisitor aux = museum->dayInfo[dayOfYear].iterator;
    return strcpy(malloc(strlen(aux->name) + 1), aux->name);
}

void freeListRec(tVisitor list) {
    if (list == NULL) return;
    freeListRec(list->next);
    free(list->name);
    free(list);
}

void freeMuseumTicket(museumTicketADT museumTicketADT) {
    for (int i = 0; i < DAYS; ++i) {
        freeListRec(museumTicketADT->dayInfo[i].visitorsList);
    }
    free(museumTicketADT);
}

