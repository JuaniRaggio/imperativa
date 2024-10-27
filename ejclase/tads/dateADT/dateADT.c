#include <stdlib.h>
#include <stdbool.h>
#include "dateADT.h"

struct dateCDT {
    unsigned char day, month;
    unsigned int year;
};

static bool isValidDate(unsigned char day, unsigned char month, unsigned int year) {}

dateADT newDate(unsigned char day, unsigned char month, unsigned int year) {
    if (!isValidDate(day, month, year))
        return NULL;
    dateADT new = malloc(sizeof(*new));
    new->day = day;
    new->month = month;
    new->year = year;
    return new;
}

