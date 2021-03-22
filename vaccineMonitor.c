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

    HashtableVirus* ht_viruses = hash_virus_create(HASHTABLE_NODES);
    HashtableCitizen* ht_citizens = hash_citizen_create(HASHTABLE_NODES);
    HashtableCountry* ht_countries = hash_country_create(HASHTABLE_NODES);

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

            if (!strcmp(token, "/populationStatus") || !strcmp(token, "populationStatus")) {
                char * tokens[5];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");
                tokens[2] = strtok(NULL, " \n");
                tokens[3] = strtok(NULL, " \n");
                tokens[4] = strtok(NULL, " \n");
                
                if (tokens[0] == NULL) {
                    printf("syntax error\n");
                } else if(tokens[0] != NULL && tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL) {
                    population_status(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2]);
                } else if(tokens[0] != NULL && tokens[1] != NULL && tokens[2] != NULL && tokens[3] != NULL && tokens[4] == NULL) {
                    population_status_country(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2], tokens[3]);
                } else { // more than 2
                    printf("syntax error\n");
                }
            }

            if (!strcmp(token, "/popStatusByAge") || !strcmp(token, "popStatusByAge")) {
                char * tokens[5];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");
                tokens[2] = strtok(NULL, " \n");
                tokens[3] = strtok(NULL, " \n");
                tokens[4] = strtok(NULL, " \n");
                
                if (tokens[0] == NULL) {
                    printf("syntax error\n");
                } else if(tokens[0] != NULL && tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL) {
                    pop_status_by_age(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2]);
                } else if(tokens[0] != NULL && tokens[1] != NULL && tokens[2] != NULL && tokens[3] != NULL && tokens[4] == NULL) {
                    pop_status_by_age_country(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2], tokens[3]);
                } else { // more than 2
                    printf("syntax error\n");
                }
            }

            if (!strcmp(token, "/insertCitizenRecord") || !strcmp(token, "insertCitizenRecord")) {
                // char * tokens[9];
                // Record record;
                
                // tokens[0] = strtok(NULL, " \n");
                // tokens[1] = strtok(NULL, " \n");
                // tokens[2] = strtok(NULL, " \n");
                // tokens[3] = strtok(NULL, " \n");
                // tokens[4] = strtok(NULL, " \n");
                // tokens[5] = strtok(NULL, " \n");
                // tokens[6] = strtok(NULL, " \n");
                // tokens[7] = strtok(NULL, " \n");
                // tokens[8] = strtok(NULL, " \n");

                // if (tokens[0] == NULL) {
                //     printf("syntax error\n");
                // } else if (tokens[0] != NULL && tokens[1] != NULL && tokens[2] != NULL && tokens[3] != NULL && tokens[4] != NULL && tokens[5] != NULL && tokens[6] != NULL && tokens[7] == NULL) {
                //     insert_citizen_record(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
                // } else {
                //     vaccinate_now(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
                // }
            }

            if (!strcmp(token, "/vaccinateNow") || !strcmp(token, "vaccinateNow")) {
                char * tokens[7];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");
                tokens[2] = strtok(NULL, " \n");
                tokens[3] = strtok(NULL, " \n");
                tokens[4] = strtok(NULL, " \n");
                tokens[5] = strtok(NULL, " \n");
                tokens[6] = strtok(NULL, " \n");

                if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL || tokens[4] == NULL || tokens[5] == NULL || tokens[6] != NULL) {
                    printf("syntax error\n");
                } else {
                    vaccinate_now(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
                }
            }

            if (!strcmp(token, "/list-nonVaccinated-Persons") || !strcmp(token, "list-nonVaccinated-Persons")) {
                char * tokens[2];
                
                tokens[0] = strtok(NULL, " \n");
                tokens[1] = strtok(NULL, " \n");

                if (tokens[0] == NULL || tokens[1] != NULL) {
                    printf("syntax error\n");
                } else {
                    list_nonVaccinated_Persons(ht_viruses, ht_citizens, ht_countries, bloomSize, tokens[0]);
                }
            }

            if (!strcmp(token, "/exit") || !strcmp(token, "exit")) {
                break;
            }
        }
    }
    
    
    // frees

    if (line != NULL) {
        free(line);
    }

    fclose(citizenRecordsFile);

    hash_virus_destroy(ht_viruses);
    hash_citizen_destroy(ht_citizens);
    hash_country_destroy(ht_countries);

    return 0;
}