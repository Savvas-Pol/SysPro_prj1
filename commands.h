#ifndef COMMANDS_H
#define COMMANDS_H

#include "record.h"
#include "hashtable.h"


void insert_citizen_record(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, Record record);

void vaccine_status_bloom(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName);

void vaccine_status_id_virus(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName);

void vaccine_status_id(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID);

void population_status(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName, char* date1, char* date2);

void population_status_country(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* country, char* virusName, char* date1, char* date2);

void pop_status_by_age(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName, char* date1, char* date2);

void pop_status_by_age_country(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* country, char* virusName, char* date1, char* date2);

void vaccinate_now(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * firstName, char * lastName, char * country, char * age, char * virusName);

void list_nonVaccinated_Persons(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName);

#endif /* COMMANDS_H */

