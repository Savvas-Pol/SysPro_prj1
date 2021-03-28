#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "skiplist.h"
#include "constants.h"

bool find_conflict(Record record, Citizen* citizen) {
    if (strcmp(record.citizenID, citizen->citizenID) != 0) {
        return true;
    }
    if (strcmp(record.firstName, citizen->firstName) != 0) {
        return true;
    }
    if (strcmp(record.lastName, citizen->lastName) != 0) {
        return true;
    }
    if (strcmp(record.country, citizen->country) != 0) {
        return true;
    }
    if (record.age != citizen->age) {
        return true;
    }

    return false;
}

void insert_citizen_record(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, Record record) {

    HashtableVirusNode * virusNode = hash_virus_search(ht_viruses, record.virusName);

    bool vaccinating = record.dateVaccinated != NULL;

    if (virusNode != NULL) {
        SkipListNode* sn1 = skiplist_search(virusNode->vaccinated_persons, record.citizenID);
        SkipListNode* sn2 = skiplist_search(virusNode->not_vaccinated_persons, record.citizenID);

        bool vaccinated = sn1 != NULL;
        bool not_vaccinated = sn2 != NULL;

        if (vaccinated || not_vaccinated) {
            if (vaccinating && vaccinated) {
                printf("Error: Already vaccinated \n");
                return;
            }

            if (vaccinating && !vaccinated) {
                if (!find_conflict(record, sn2->citizen)) {
                    Citizen * c = sn2->citizen;

                    skiplist_delete(virusNode->not_vaccinated_persons, c->citizenID);
                    skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
                    bloom_filter_insert(virusNode->bloom, c->citizenID, bloomSize);
                    printf("Vaccinating: %s %s %s \n", c->citizenID, c->firstName, c->lastName );
                } else {
                    printf("Conflict on: %s %s %s \n", record.citizenID, record.firstName, record.lastName );
                }
                return;
            }

            if (!vaccinating && vaccinated) {
                printf("Error: Already vaccinated \n");
                return;
            }

            if (!vaccinating && !vaccinated) {
                printf("Error: Already registered as not vaccinated \n");
                return;
            }
            printf("oops \n");
            exit(1);
        } else {
            HashtableCitizenNode* cn = hash_citizen_search(ht_citizens, record.citizenID);

            if (cn != NULL) {
                if (vaccinating) {
                    skiplist_insert(virusNode->vaccinated_persons, cn->citizen, record.dateVaccinated, cn->citizen->citizenID);
                    bloom_filter_insert(virusNode->bloom, cn->citizen->citizenID, bloomSize);
                } else {
                    skiplist_insert(virusNode->not_vaccinated_persons, cn->citizen, record.dateVaccinated, cn->citizen->citizenID);
                }
                printf("insert successful on existing citizen: %s %s %s %s \n", cn->citizen->citizenID, cn->citizen->firstName, cn->citizen->lastName, record.virusName);
                return;
            } else {
                Citizen * c = citizen_create(record.citizenID, record.firstName, record.lastName, record.country, record.age);

                hash_citizen_insert(ht_citizens, c);

                HashtableCountryNode * cc = hash_country_search(ht_countries, c->country);
                if (cc == NULL) {
                    hash_country_insert(ht_countries, c->country);
                }

                if (vaccinating) {
                    skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
                    bloom_filter_insert(virusNode->bloom, c->citizenID, bloomSize);
                } else {
                    skiplist_insert(virusNode->not_vaccinated_persons, c, record.dateVaccinated, c->citizenID);
                }
                
                printf("insert successful on new citizen: %s %s %s %s \n", c->citizenID, c->firstName, c->lastName, record.virusName);
                return;
            }
        }
    } else {
        printf("new virus created: %s \n", record.virusName);
        
        virusNode = hash_virus_insert(ht_viruses, record.virusName);
        virusNode->bloom = bloom_init(bloomSize);
        virusNode->vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
        virusNode->not_vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
    }


    Citizen * c = citizen_create(record.citizenID, record.firstName, record.lastName, record.country, record.age);

    hash_citizen_insert(ht_citizens, c);

    HashtableCountryNode * cc = hash_country_search(ht_countries, c->country);
    if (cc == NULL) {
        hash_country_insert(ht_countries, c->country);
    }

    if (vaccinating) {
        skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
        bloom_filter_insert(virusNode->bloom, c->citizenID, bloomSize);
    } else {
        skiplist_insert(virusNode->not_vaccinated_persons, c, record.dateVaccinated, c->citizenID);
    }
    
    printf("insert successful on new citizen: %s %s %s %s \n", c->citizenID, c->firstName, c->lastName, record.virusName);
    
    return;
}

void vaccine_status_bloom(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status_bloom: %s , %s \n", citizenID, virusName);
    
    HashtableVirusNode * virusNode = hash_virus_search(ht_viruses, virusName);

    if (virusNode != NULL) {
        int q = bloom_filter_check(virusNode->bloom, citizenID, HASH_FUNCTIONS_K);
        
        if (q == 0) {
            printf("NOT VACCINATED \n");
        } else {
            printf("MAYBE \n");
        }
    } else {
        printf("virus missing: %s \n", virusName);
    }
}

void vaccine_status_id_virus(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status: %s , %s \n", citizenID, virusName);
    
    HashtableVirusNode * virusNode = hash_virus_search(ht_viruses, virusName);

    if (virusNode != NULL) {
        SkipListNode* sn1 = skiplist_search(virusNode->vaccinated_persons, citizenID);
        
        bool vaccinated = sn1 != NULL;
        
        if (vaccinated) {
            printf("VACCINATED ON %d-%d-%d \n", sn1->date->day, sn1->date->month, sn1->date->year);
        } else {
            printf("NOT VACCINATED \n");
        }
        
    } else {
        printf("virus missing: %s \n", virusName);
    }
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

    HashtableVirusNode * virusNode = hash_virus_search(ht_viruses, virusName);

    if (virusNode != NULL) {
    	SkipListNode* temp = virusNode->not_vaccinated_persons->head->next[0];

    	while(temp != NULL) {
    		if(strcmp(temp->citizen->citizenID, "ZZZZZ") != 0)		//don't print skip list tail node
    			printf("%s %s %s %s %d\n", temp->citizen->citizenID, temp->citizen->firstName, temp->citizen->lastName, temp->citizen->country, temp->citizen->age);
    		temp = temp->next[0];
    	}
    } else {
        printf("virus missing: %s \n", virusName);
    }
}