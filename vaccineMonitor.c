#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_functions.h"
#include "list.h"
#include "hashtable.h"
#include "BF.h"
#include "record.h"

#define K 16   // K for Hash Functions
#define MAXLEVEL 4  // Skip List Level
#define HASHTABLE_NODES 100

int main(int argc, char** argv) {

    /*	---		DECLARATIONS	---	*/

    int i, j, bloomSize, pos;
    char* token, *token2;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    Record temp;
    HashtableNode* hashNode;

    List* l = NULL;
    BF* bloom;

    FILE* citizenRecordsFile;

    /*		---------------		*/

    if((citizenRecordsFile = read_arguments(argc, argv, &bloomSize)) == NULL){
        return -1;
    }

    Hashtable* ht_viruses = hash_create(HASHTABLE_NODES);
    Hashtable* ht_citizens = hash_create(HASHTABLE_NODES);
    Hashtable* ht_countries = hash_create(HASHTABLE_NODES);

    while ((read = getline(&line, &len, citizenRecordsFile)) != -1) { //line by line
        
        create_temp_node(line, token, &temp);

        if (hash_search(ht_viruses, temp.virusName) == NULL) {
            hashNode = hash_insert(ht_viruses, temp.virusName);
            hashNode->bloom = bloom_init(bloomSize);
            hashNode->vaccinated_persons = skiplist_init(MAXLEVEL);
            //skiplist_insert();
            hashNode->not_vaccinated_persons = skiplist_init(MAXLEVEL);
            //skiplist_insert();
        }
        bloom_filter(hashNode->bloom, temp.virusName, K);

        free_temp_node(&temp);

    }

    //waiting input from user

    if (line != NULL) {
        free(line);
    }

    fclose(citizenRecordsFile);

    // for(i = 0; i < HASHTABLE_NODES; i++){

    // }
    hash_destroy(ht_viruses);
    hash_destroy(ht_citizens);
    hash_destroy(ht_countries);

    return 0;
}