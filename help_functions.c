#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_functions.h"


FILE* read_arguments(int argc, char** argv, int* bloomSize) {
	int i;

	FILE* citizenRecordsFile;

	if (argc < 5) {
		printf("Wrong arguments!!!\n");
		return NULL;
	} else {
		for (i = 0; i < 4; i++) {
			if (!strcmp(argv[i], "-c")) {
				if (!(citizenRecordsFile = fopen(argv[i + 1], "r"))) {
					printf("Error in opening %s\n", argv[i + 1]);
					return NULL;
				}
			} else if (!strcmp(argv[i], "-b")) {
				*bloomSize = atoi(argv[i + 1]);
			}
		}
	}
	return citizenRecordsFile;
}

void fill_record(char* line, Record* temp) {
	int i = 0, j;

	char* token;
	token = strtok(line, " \n"); //word by word

	while (token != NULL) {
		if (i == 0) {
			temp->citizenID = malloc((strlen(token)) + 1);
			strcpy(temp->citizenID, token);
		} else if (i == 1) {
			temp->firstName = malloc((strlen(token)) + 1);
			strcpy(temp->firstName, token);
		} else if (i == 2) {
			temp->lastName = malloc((strlen(token)) + 1);
			strcpy(temp->lastName, token);
		} else if (i == 3) {
			temp->country = malloc((strlen(token)) + 1);
			strcpy(temp->country, token);
		} else if (i == 4) {
			temp->age = atoi(token);
		} else if (i == 5) {
			temp->virusName = malloc((strlen(token)) + 1);
			strcpy(temp->virusName, token);
		} else if (i == 6) {
			if (!strcmp(token, "YES")) {
				j = 0;
				token = strtok(NULL, " \n");
				token = strtok(token, "-\n");

				temp->dateVaccinated = malloc(sizeof (Date));

				while (token != NULL) {
					if (j == 0)
						temp->dateVaccinated->day = atoi(token);
					else if (j == 1)
						temp->dateVaccinated->month = atoi(token);
					else if (j == 2)
						temp->dateVaccinated->year = atoi(token);
					token = strtok(NULL, "-\n");
					j++;
				}

			} else {
				temp->dateVaccinated = NULL;
			}
		}

		token = strtok(NULL, " \n");
		i++;
	}
}

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

void free_record(Record* temp) {
	free(temp->citizenID);
	free(temp->country);
	free(temp->firstName);
	free(temp->lastName);
	free(temp->virusName);

	if (temp->dateVaccinated != NULL) {
		free(temp->dateVaccinated);
	}
}