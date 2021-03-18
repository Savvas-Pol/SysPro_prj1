#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "record.h"

FILE* read_arguments(int argc, char** argv, int* bloomSize);
void create_temp_node(char* line, char* token, Record* temp);
void free_temp_node(Record* temp);

#endif