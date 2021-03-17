#ifndef RECORD_H
#define RECORD_H

#include "Date.h"

typedef struct Record {
    char* citizenID;
    char* firstName;
    char* lastName;
    char* country;
    int age;
    char* virusName;
    Date* dateVaccinated;

} Record;

#endif /* RECORD_H */

