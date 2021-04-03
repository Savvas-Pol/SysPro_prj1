#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include <stdbool.h>

#include "record.h"
#include "citizen.h"

FILE* read_arguments(int argc, char** argv, int* bloomSize);
void fill_record(char* line, Record* temp);
bool find_conflict(Record record, Citizen* citizen);
void free_record(Record* temp);

#endif