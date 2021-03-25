#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int hash_function(unsigned char *str, int buckets) {

    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % buckets;
}

HashtableVirus* hash_virus_create(int hashNodes) {

    int i;
    
    HashtableVirus* ht = malloc(sizeof (HashtableVirus));
    ht->hash_nodes = hashNodes;

    ht->nodes = (HashtableVirusNode**) malloc(hashNodes * sizeof (HashtableVirusNode*)); //create hashtable for diseases
    for (i = 0; i < hashNodes; i++) {
        ht->nodes[i] = NULL;
    }

    return ht;
}

void hash_virus_destroy(HashtableVirus* ht) {

    int i;

    for (i = 0; i < ht->hash_nodes; i++) {
        HashtableVirusNode* temp = ht->nodes[i];

        while (temp != NULL) {
            ht->nodes[i] = temp->next;

            bloom_destroy(temp->bloom);
            skiplist_destroy(temp->vaccinated_persons);
            skiplist_destroy(temp->not_vaccinated_persons);
            
            free(temp->virusName);
            free(temp);
            
            temp = ht->nodes[i];
        }
    }

    free(ht->nodes);
    free(ht);
}

HashtableVirusNode* hash_virus_search(HashtableVirus* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableVirusNode* temp = ht->nodes[pos];

    while (temp != NULL) {
        if (!strcmp(temp->virusName, virusName))
            return temp;

        temp = temp->next;
    }
    return temp;
}

HashtableVirusNode* hash_virus_insert(HashtableVirus* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableVirusNode* new;

    new = (HashtableVirusNode*) malloc(sizeof (HashtableVirusNode));

    new->virusName = (char*) malloc(strlen(virusName) + 1);
    strcpy(new->virusName, virusName);
    new->next = ht->nodes[pos];
    ht->nodes[pos] = new;

    return new;
}

void hash_virus_delete(HashtableVirus* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableVirusNode* temp = ht->nodes[pos], *temp2;
    int first = 1; // flag to check if we are in first node

    while (temp != NULL) {
        if (!strcmp(temp->virusName, virusName)) {
            if (first)
                ht->nodes[pos] = temp->next;
            else
                temp2->next = temp->next;

            free(temp->virusName);
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
        first = 0;
    }
}

HashtableCitizen* hash_citizen_create(int hashNodes) {

    int i;
    
    HashtableCitizen* ht = malloc(sizeof (HashtableCitizen));
    ht->hash_nodes = hashNodes;

    ht->nodes = (HashtableCitizenNode**) malloc(hashNodes * sizeof (HashtableCitizenNode*)); //create hashtable for citizens
    for (i = 0; i < hashNodes; i++) {
        ht->nodes[i] = NULL;
    }

    return ht;
}

void hash_citizen_destroy(HashtableCitizen* ht) {

    int i;

    for (i = 0; i < ht->hash_nodes; i++) {
        HashtableCitizenNode* temp = ht->nodes[i];

        while (temp != NULL) {
            ht->nodes[i] = temp->next;

            citizen_destroy(temp->citizen);
            free(temp);
            
            temp = ht->nodes[i];
        }
    }

    free(ht->nodes);
    free(ht);
}

HashtableCitizenNode* hash_citizen_search(HashtableCitizen* ht, char* citizenID) {

    int pos = hash_function((unsigned char*) citizenID, ht->hash_nodes);

    HashtableCitizenNode* temp = ht->nodes[pos];

    while (temp != NULL) {
        if (!(strcmp(temp->citizen->citizenID, citizenID)) ) {
            return temp;
        }

        temp = temp->next;
    }
    return temp;
}

HashtableCitizenNode* hash_citizen_search_for_all_fields(HashtableCitizen* ht, Citizen *citizen) {
    int pos = hash_function((unsigned char*) citizen->citizenID, ht->hash_nodes);

    HashtableCitizenNode* temp = ht->nodes[pos];

    while (temp != NULL) {
        if (!(strcmp(temp->citizen->citizenID, citizen->citizenID)) &&
                !(strcmp(temp->citizen->firstName, citizen->firstName)) &&
                !(strcmp(temp->citizen->lastName, citizen->lastName)) &&
                !(strcmp(temp->citizen->country, citizen->country)) &&
                (temp->citizen->age == citizen->age)) {
            return temp;
        }

        temp = temp->next;
    }
    return temp;
}

HashtableCitizenNode* hash_citizen_insert(HashtableCitizen* ht, Citizen *citizen) {

    int pos = hash_function((unsigned char*) citizen->citizenID, ht->hash_nodes);

    HashtableCitizenNode* new;

    new = (HashtableCitizenNode*) malloc(sizeof (HashtableCitizenNode));

    new->citizen = citizen;
    
    new->next = ht->nodes[pos];
    ht->nodes[pos] = new;

    return new;
}

void hash_citizen_delete(HashtableCitizen* ht, char* citizenID) {

    int pos = hash_function((unsigned char*) citizenID, ht->hash_nodes);

    HashtableCitizenNode* temp = ht->nodes[pos], *temp2;
    int first = 1; // flag to check if we are in first node

    while (temp != NULL) {
        if (!(strcmp(temp->citizen->citizenID, citizenID))) {
            if (first)
                ht->nodes[pos] = temp->next;
            else
                temp2->next = temp->next;

            free(temp->citizen);
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
        first = 0;
    }
}

HashtableCountry* hash_country_create(int hashNodes) {

    int i;
    
    HashtableCountry* ht = malloc(sizeof (HashtableCountry));
    ht->hash_nodes = hashNodes;

    ht->nodes = (HashtableCountryNode**) malloc(hashNodes * sizeof (HashtableCountryNode*)); //create hashtable for countries
    for (i = 0; i < hashNodes; i++) {
        ht->nodes[i] = NULL;
    }

    return ht;
}

void hash_country_destroy(HashtableCountry* ht) {

    int i;

    for (i = 0; i < ht->hash_nodes; i++) {
        HashtableCountryNode* temp = ht->nodes[i];

        while (temp != NULL) {
            ht->nodes[i] = temp->next;

            free(temp->countryName);
            free(temp);
            
            temp = ht->nodes[i];
        }
    }

    free(ht->nodes);
    free(ht);
}

HashtableCountryNode* hash_country_search(HashtableCountry* ht, char* countryName) {

    int pos = hash_function((unsigned char*) countryName, ht->hash_nodes);

    HashtableCountryNode* temp = ht->nodes[pos];

    while (temp != NULL) {
        if (!strcmp(temp->countryName, countryName))
            return temp;

        temp = temp->next;
    }
    return temp;
}

HashtableCountryNode* hash_country_insert(HashtableCountry* ht, char* countryName) {

    int pos = hash_function((unsigned char*) countryName, ht->hash_nodes);

    HashtableCountryNode* new;

    new = (HashtableCountryNode*) malloc(sizeof (HashtableCountryNode));

    new->countryName = (char*) malloc(strlen(countryName) + 1);
    strcpy(new->countryName, countryName);
    new->population = 1;
    new->next = ht->nodes[pos];
    ht->nodes[pos] = new;

    return new;
}

void hash_country_delete(HashtableCountry* ht, char* countryName) {

    int pos = hash_function((unsigned char*) countryName, ht->hash_nodes);

    HashtableCountryNode* temp = ht->nodes[pos], *temp2;
    int first = 1; // flag to check if we are in first node

    while (temp != NULL) {
        if (!strcmp(temp->countryName, countryName)) {
            if (first)
                ht->nodes[pos] = temp->next;
            else
                temp2->next = temp->next;

            free(temp->countryName);
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
        first = 0;
    }
}