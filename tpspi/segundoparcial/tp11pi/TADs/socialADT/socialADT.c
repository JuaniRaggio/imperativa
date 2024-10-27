#include "socialADT.h"

struct socialCDT {
};

socialADT newSocial();

void freeSocial(socialADT soc);

void addPerson(socialADT soc, const char * name);

void addRelated(socialADT soc, const char * name, const char * related);

char ** related(const socialADT soc, const char * person);

char ** persons(const socialADT soc);

