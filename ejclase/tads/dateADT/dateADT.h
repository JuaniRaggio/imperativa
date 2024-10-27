#ifndef __DATEADT__H__
#define __DATEADT__H__

typedef struct dateCDT * dateADT;

dateADT newDate(unsigned char day, unsigned char month, unsigned int year);

void freeDate(dateADT date);

int setDat(dateADT date, int day);

void dateToString(const dateADT date, char s[]);

#endif

