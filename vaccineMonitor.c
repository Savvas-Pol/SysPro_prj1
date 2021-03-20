#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_functions.h"
#include "list.h"
#include "hashtable.h"
#include "BF.h"
#include "record.h"
#include "commands.h"

#define MAXLEVEL 4  // Skip List Level
#define HASHTABLE_NODES 100

int main(int argc, char** argv) {

    /*  ---     DECLARATIONS    --- */

    int i, j, bloomSize, pos;
    char* token, *token2;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* citizenRecordsFile;

    /*      ---------------     */

    if ((citizenRecordsFile = read_arguments(argc, argv, &bloomSize)) == NULL) {
        return -1;
    }

    Hashtable* ht_viruses = hash_create(HASHTABLE_NODES);
    Hashtable* ht_citizens = hash_create(HASHTABLE_NODES);
    Hashtable* ht_countries = hash_create(HASHTABLE_NODES);

    while ((read = getline(&line, &len, citizenRecordsFile)) != -1) { //line by line
        Record record;

        fill_record(line, &record);
        
        insert_citizen_record(ht_viruses, ht_citizens, ht_countries, bloomSize, record);


        free_record(&record);

    }

    while (1) {
        printf("\nGive command: ");
        
        getline(&line, &len, stdin);

        token = strtok(line, " \n");

        if (token != NULL) {
            if (!strcmp(token, "/exit") || !strcmp(token, "exit")) {
                break;
            }
            
            if (!strcmp(token, "/vaccineStatusBloom") || !strcmp(token, "vaccineStatusBloom")) {
                char * tokens[3];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");
                tokens[2] = strtok(NULL, " \n");
                
                if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] != NULL) {
                    printf("syntax error\n");
                } else {
                    vaccine_status_bloom(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1]);
                }
            }
            
            if (!strcmp(token, "/vaccineStatus") || !strcmp(token, "vaccineStatus")) {
                char * tokens[3];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");
                tokens[2] = strtok(NULL, " \n");
                
                if (tokens[0] == NULL) { // none => error
                    printf("syntax error\n");
                } else if(tokens[0] != NULL && tokens[1] == NULL) { // 1 argument -> id
                    vaccine_status_id(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0]);
                } else if(tokens[0] != NULL && tokens[1] != NULL && tokens[2] == NULL) { // 2 arguments -> id , virusName
                    vaccine_status_id_virus(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1]);
                } else { // more than 2
                    printf("syntax error\n");
                }
            }
        }
    }
    
    
    // frees

    if (line != NULL) {
        free(line);
    }

    fclose(citizenRecordsFile);

    hash_destroy(ht_viruses);
    hash_destroy(ht_citizens);
    hash_destroy(ht_countries);

    return 0;
}