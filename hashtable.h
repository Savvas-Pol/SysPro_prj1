#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "skiplist.h"
#include "BF.h"
#include "citizen.h"

typedef struct HashtableVirusNode {
    char* virusName;
    BF* bloom;
    SkipList* vaccinated_persons;
    SkipList* not_vaccinated_persons;
    struct HashtableVirusNode* next; //pointer to next bucket node
} HashtableVirusNode;

typedef struct HashtableVirus {
    HashtableVirusNode** nodes;
    int hash_nodes;
} HashtableVirus;

typedef struct HashtableCitizenNode {
    Citizen * citizen;
    struct HashtableCitizenNode* next; //pointer to next bucket node
} HashtableCitizenNode;

typedef struct HashtableCitizen {
    HashtableCitizenNode** nodes;
    int hash_nodes;
} HashtableCitizen;

typedef struct HashtableCountryNode {
    char* countryName;
    int population;
    // int population_0_20;
    // int population_20_40;
    // int population_40_60;
    // int population_60plus;
    struct HashtableCountryNode* next; //pointer to next bucket node
} HashtableCountryNode;

typedef struct HashtableCountry {
    HashtableCountryNode** nodes;
    int hash_nodes;
} HashtableCountry;

int hash_function(unsigned char *str, int buckets);

HashtableVirus* hash_virus_create(int hashNodes);
void hash_virus_destroy(HashtableVirus* ht);
HashtableVirusNode* hash_virus_search(HashtableVirus* ht, char* virusName);
HashtableVirusNode* hash_virus_insert(HashtableVirus* ht, char* virusName);
void hash_virus_delete(HashtableVirus* ht, char* virusName);

HashtableCitizen* hash_citizen_create(int hashNodes);
void hash_citizen_destroy(HashtableCitizen* ht);
HashtableCitizenNode* hash_citizen_search(HashtableCitizen* ht, char* citizenID);
HashtableCitizenNode* hash_citizen_search_for_all_fields(HashtableCitizen* ht, Citizen *citizen);
HashtableCitizenNode* hash_citizen_insert(HashtableCitizen* ht, Citizen *citizen);
void hash_citizen_delete(HashtableCitizen* ht, char* citizenID);

HashtableCountry* hash_country_create(int hashNodes);
void hash_country_destroy(HashtableCountry* ht);
HashtableCountryNode* hash_country_search(HashtableCountry* ht, char* countryName);
HashtableCountryNode* hash_country_insert(HashtableCountry* ht, char* countryName);
void hash_country_delete(HashtableCountry* ht, char* countryName);


#endif