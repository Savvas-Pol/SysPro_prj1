    
#include <stddef.h>
#include <stdio.h>

#include "commands.h"
#include "skiplist.h"
#include "constants.h"



void insert_citizen_record(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, Record record) {
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

void vaccine_status_bloom(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status_bloom: %s , %s \n", citizenID, virusName);
}

void vaccine_status_id_virus(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID, char * virusName) {
    printf("CALLED vaccine_status: %s , %s \n", citizenID, virusName);
}

void vaccine_status_id(Hashtable* ht_viruses, Hashtable* ht_citizens, Hashtable* ht_countries, int bloomSize, char * citizenID) {
    printf("CALLED vaccine_status: %s\n", citizenID);
}