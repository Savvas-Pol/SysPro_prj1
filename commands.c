    
#include <stddef.h>
#include <stdio.h>

#include "commands.h"
#include "skiplist.h"
#include "constants.h"



void insert_citizen_record(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, Record record) {
//    HashtableNode * hashNode;
//    
//    if (hash_search(ht_viruses, record.virusName) == NULL) {
//        hashNode = hash_insert(ht_viruses, record.virusName);
//        hashNode->bloom = bloom_init(bloomSize);
//        hashNode->vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
//        hashNode->not_vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
//    }
//    
//    bloom_filter_insert(hashNode->bloom, record.virusName, HASH_FUNCTIONS_K);
//    
    
}

void vaccine_status_bloom(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status_bloom: %s , %s \n", citizenID, virusName);
}

void vaccine_status_id_virus(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status: %s , %s \n", citizenID, virusName);
}

void vaccine_status_id(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID) {
    printf("CALLED vaccine_status: %s\n", citizenID);
}

void population_status(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName, char* date1, char* date2) {
	printf("CALLED population_status: %s %s %s\n", virusName, date1, date2);
}

void population_status_country(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* country, char* virusName, char* date1, char* date2) {
	printf("CALLED population_status: %s %s %s %s\n", country, virusName, date1, date2);
}

void pop_status_by_age(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName, char* date1, char* date2) {
	printf("CALLED pop_status_by_age: %s %s %s\n", virusName, date1, date2);
}

void pop_status_by_age_country(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* country, char* virusName, char* date1, char* date2) {
	printf("CALLED pop_status_by_age_country: %s %s %s %s\n", country, virusName, date1, date2);
}

void vaccinate_now(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * firstName, char * lastName, char * country, char * age, char * virusName) {
	printf("CALLED vaccinate_now: %s %s %s %s %s %s\n", citizenID, firstName, lastName, country, age, virusName);
}

void list_nonVaccinated_Persons(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char* virusName) {
	printf("CALLED list_nonVaccinated_Persons: %s\n", virusName);
}