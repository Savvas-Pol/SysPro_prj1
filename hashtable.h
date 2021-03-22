#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "skiplist.h"
#include "BF.h"

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
    char* citizenID;
    char* firstName;
    char* lastName;
    struct HashtableCitizenNode* next; //pointer to next bucket node
} HashtableCitizenNode;

typedef struct HashtableCitizen {
    HashtableCitizenNode** nodes;
    int hash_nodes;
} HashtableCitizen;

typedef struct HashtableCountryNode {
    char* countryName;
    int population;
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
HashtableVirusNode* hash__virus_insert(HashtableVirus* ht, char* virusName);
void hash_virus_delete(HashtableVirus* ht, char* virusName);

HashtableCitizen* hash_citizen_create(int hashNodes);
void hash_citizen_destroy(HashtableCitizen* ht);
HashtableCitizenNode* hash_citizen_search(HashtableCitizen* ht, char* citizenID, char* firstName, char* lastName);
HashtableCitizenNode* hash__citizen_insert(HashtableCitizen* ht, char* citizenID, char* firstName, char* lastName);
void hash_citizen_delete(HashtableCitizen* ht, char* citizenID, char* firstName, char* lastName);

HashtableCountry* hash_country_create(int hashNodes);
void hash_country_destroy(HashtableCountry* ht);
HashtableCountryNode* hash_country_search(HashtableCountry* ht, char* countryName);
HashtableCountryNode* hash_country_insert(HashtableCountry* ht, char* countryName);
void hash_country_delete(HashtableCountry* ht, char* countryName);


#endif