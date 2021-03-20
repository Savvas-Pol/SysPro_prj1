
#ifndef COMMANDS_H
#define COMMANDS_H

#include "record.h"
#include "hashtable.h"


void insert_citizen_record(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, Record record);

void vaccine_status_bloom(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID, char * virusName);

void vaccine_status_id_virus(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID, char * virusName);

void vaccine_status_id(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID);

#endif /* ΨΟΜΜΑΝΔΣ_H */

