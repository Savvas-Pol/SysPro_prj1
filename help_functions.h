#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include <stdbool.h>

#include "record.h"
#include "citizen.h"

FILE* read_arguments(int argc, char** argv, int* bloomSize);		//reads arguments from command line
void fill_record(char* line, Record* temp);		//breaks line into tokens and creates a new record
bool find_conflict(Record record, Citizen* citizen);			//finds if any value is different from that of the citizen
void free_record(Record* temp);		//free

#endif
