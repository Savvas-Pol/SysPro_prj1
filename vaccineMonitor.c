#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_functions.h"
#include "list.h"
#include "hashtable.h"
#include "BF.h"
#include "Record.h"

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
    HashtableNode* node;

    List* l = NULL;
    BF* bloom;

    FILE* citizenRecordsFile;

    /*		---------------		*/

    if((citizenRecordsFile = read_arguments(argc, argv, &bloomSize)) == NULL){
        return -1;
    }

    Hashtable* ht = hash_create(HASHTABLE_NODES);

    while ((read = getline(&line, &len, citizenRecordsFile)) != -1) { //line by line
        
        create_temp_node(line, token, &temp);

        if (hash_search(ht, temp.virusName) == NULL) {
            node = hash_insert(ht, temp.virusName);
            node->bloom = bloom_init(bloomSize);
            // node->skiplist_1 = skiplist_init(maxLevel);
            // node->skiplist_2 = skiplist_init(maxLevel);
        }

        free_temp_node(&temp);

    }

    if (line != NULL) {
        free(line);
    }

    fclose(citizenRecordsFile);

    hash_destroy(ht);

    return 0;
}