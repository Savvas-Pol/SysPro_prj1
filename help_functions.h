#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "record.h"

FILE* read_arguments(int argc, char** argv, int* bloomSize);
void fill_record(char* line, Record* temp);
void free_record(Record* temp);

#endif