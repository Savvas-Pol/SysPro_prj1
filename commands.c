#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "skiplist.h"
#include "constants.h"
#include "date.h"
#include "hashtable_citizen.h"
#include "hashtable_virus.h"
#include "hashtable_country.h"
#include "help_functions.h"

void insert_citizen_record(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, Record record, int flag) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, record.virusName);		//search if virus exists

	bool vaccinating = record.dateVaccinated != NULL;	//if date is not NULL we have YES

	if (virusNode != NULL) {
		SkipListNode* sn1 = skiplist_search(virusNode->vaccinated_persons, record.citizenID);			//search citizen in vaccinated_persons skiplist
		SkipListNode* sn2 = skiplist_search(virusNode->not_vaccinated_persons, record.citizenID);		//search citizen in not_vaccinated_persons skiplist

		bool vaccinated = sn1 != NULL;
		bool not_vaccinated = sn2 != NULL;

		if (vaccinated || not_vaccinated) { 		//if already in a skiplist
			if (vaccinating && vaccinated) {	//YES and already vaccinated
				printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %d-%d-%d\n", sn1->citizen->citizenID, sn1->date->day, sn1->date->month, sn1->date->year);
				return;
			}

			if (vaccinating && !vaccinated) {		//YES and not vaccinated
				if (flag == 0) {		//command from keyboard
					if (!find_conflict(record, sn2->citizen)) { 		//check if given record is correct
						Citizen* c = sn2->citizen;

						skiplist_delete(virusNode->not_vaccinated_persons, c->citizenID);
						skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
						bloom_filter_insert(virusNode->bloom, c->citizenID, HASH_FUNCTIONS_K);
						// printf("Vaccinating: %s %s %s \n", c->citizenID, c->firstName, c->lastName);
					} else {
						printf("Conflict on: %s %s %s\n", record.citizenID, record.firstName, record.lastName);
					}
				} else {		//while reading file
					printf("Conflict on: %s %s %s\n", record.citizenID, record.firstName, record.lastName);
				}
				return;
			}

			if (!vaccinating && vaccinated) {	//NO and already vaccinated
				printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %d-%d-%d\n", sn1->citizen->citizenID, sn1->date->day, sn1->date->month, sn1->date->year);
				return;
			}

			if (!vaccinating && !vaccinated) {		//NO and not vaccinated
				printf("Error: Already registered as not vaccinated\n");
				return;
			}
			exit(1);
		} else {		//if not in any skiplist
			HashtableCitizenNode* cn = hash_citizen_search(ht_citizens, record.citizenID);

			if (cn != NULL) {
				if (vaccinating) {
					skiplist_insert(virusNode->vaccinated_persons, cn->citizen, record.dateVaccinated, cn->citizen->citizenID);
					bloom_filter_insert(virusNode->bloom, cn->citizen->citizenID, HASH_FUNCTIONS_K);
				} else {
					skiplist_insert(virusNode->not_vaccinated_persons, cn->citizen, record.dateVaccinated, cn->citizen->citizenID);
				}
				//printf("insert successful on existing citizen: %s %s %s %s\n", cn->citizen->citizenID, cn->citizen->firstName, cn->citizen->lastName, record.virusName);
				return;
			} else {
				Citizen* c = citizen_create(record.citizenID, record.firstName, record.lastName, record.country, record.age);

				hash_citizen_insert(ht_citizens, c);

				HashtableCountryNode* cc = hash_country_search(ht_countries, c->country);
				if (cc == NULL) {
					hash_country_insert(ht_countries, c->country);
				}

				if (vaccinating) {
					skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
					bloom_filter_insert(virusNode->bloom, c->citizenID, HASH_FUNCTIONS_K);
				} else {
					skiplist_insert(virusNode->not_vaccinated_persons, c, record.dateVaccinated, c->citizenID);
				}

				//printf("insert successful on new citizen: %s %s %s %s \n", c->citizenID, c->firstName, c->lastName, record.virusName);
				return;
			}
		}
	} else {		//if virus does not exist
		//printf("new virus created: %s \n", record.virusName);

		virusNode = hash_virus_insert(ht_viruses, record.virusName);
		virusNode->bloom = bloom_init(bloomSize);
		virusNode->vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
		virusNode->not_vaccinated_persons = skiplist_init(SKIP_LIST_MAX_LEVEL);
	}


	Citizen* c = citizen_create(record.citizenID, record.firstName, record.lastName, record.country, record.age);

	hash_citizen_insert(ht_citizens, c);

	HashtableCountryNode* cc = hash_country_search(ht_countries, c->country);
	if (cc == NULL) {
		hash_country_insert(ht_countries, c->country);
	}

	if (vaccinating) {
		skiplist_insert(virusNode->vaccinated_persons, c, record.dateVaccinated, c->citizenID);
		bloom_filter_insert(virusNode->bloom, c->citizenID, HASH_FUNCTIONS_K);
	} else {
		skiplist_insert(virusNode->not_vaccinated_persons, c, record.dateVaccinated, c->citizenID);
	}

	//printf("insert successful on new citizen: %s %s %s %s \n", c->citizenID, c->firstName, c->lastName, record.virusName);

	return;
}

void vaccine_status_bloom(HashtableVirus* ht_viruses, char * citizenID, char * virusName) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		int q = bloom_filter_check(virusNode->bloom, citizenID, HASH_FUNCTIONS_K);

		if (q == 0) {
			printf("NOT VACCINATED \n");
		} else {
			printf("MAYBE \n");
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}

void vaccine_status_id_virus(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, char * citizenID, char * virusName) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);
	HashtableCitizenNode* citizenNode = hash_citizen_search(ht_citizens, citizenID);

	if (citizenNode != NULL) {
		if (virusNode != NULL) {
			SkipListNode* sn1 = skiplist_search(virusNode->vaccinated_persons, citizenID);

			bool vaccinated = sn1 != NULL;

			if (vaccinated) {
				printf("VACCINATED ON %d-%d-%d \n", sn1->date->day, sn1->date->month, sn1->date->year);
			} else {
				printf("NOT VACCINATED \n");
			}

		} else {
			printf("Virus: %s missing\n", virusName);
		}
	} else {
		printf("Citizen: %s missing\n", citizenID);
	}
}

void vaccine_status_id(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, char * citizenID) {

	int i;
	HashtableVirusNode* temp;
	SkipListNode* citizen;
	HashtableCitizenNode* citizenNode = hash_citizen_search(ht_citizens, citizenID);

	if (citizenNode != NULL) {
		for (i = 0; i < HASHTABLE_NODES; i++) {
			temp = ht_viruses->nodes[i];
			while (temp != NULL) {
				citizen = skiplist_search(temp->vaccinated_persons, citizenID);
				if (citizen != NULL) {
					printf("%s YES %d-%d-%d \n", temp->virusName, citizen->date->day, citizen->date->month, citizen->date->year);
				}

				citizen = skiplist_search(temp->not_vaccinated_persons, citizenID);
				if (citizen != NULL) {
					printf("%s NO \n", temp->virusName);
				}
				temp = temp->next;
			}
		}
	} else {
		printf("Citizen: %s missing\n", citizenID);
	}
}

void population_status_virus(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, char* virusName) {

	int i;
	HashtableCountryNode* temp;
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		for (i = 0; i < HASHTABLE_NODES; i++) {
			temp = ht_countries->nodes[i];
			while (temp != NULL) {
				population_status_country(ht_viruses, ht_countries, temp->countryName, virusName);
				temp = temp->next;
			}
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}

void population_status_country(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* country, char* virusName) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);
	HashtableCountryNode* countryNode = hash_country_search(ht_countries, country);
	int vaccinated_people = 0, total = 0;
	double percentage;

	if (countryNode != NULL) {
		if (virusNode != NULL) {
			SkipListNode* temp = virusNode->vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check vaccinated_persons skiplist for vaccinated people
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						vaccinated_people++;
						total++;
					}
				}
				temp = temp->next[0];
			}

			temp = virusNode->not_vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check not_vaccinated_persons skiplist to find total people for percentage
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						total++;
					}
				}
				temp = temp->next[0];
			}
			percentage = (double)vaccinated_people / total * 100;
			if (total != 0)
				printf("%s %d %.2f%%\n", country, vaccinated_people, percentage);
			else
				printf("%s %d 0.00%%\n", country, vaccinated_people);
		} else {
			printf("Virus: %s missing\n", virusName);
		}
	} else {
		printf("Country: %s missing\n", country);
	}
}

void population_status_virus_dates(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* virusName, char* date1, char* date2) {
	
	int i;
	HashtableCountryNode* temp;
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		for (i = 0; i < HASHTABLE_NODES; i++) {
			temp = ht_countries->nodes[i];
			while (temp != NULL) {
				population_status_country_dates(ht_viruses, ht_countries, temp->countryName, virusName, date1, date2);
				temp = temp->next;
			}
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}

void population_status_country_dates(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* country, char* virusName, char* date1, char* date2) {
	
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);
	HashtableCountryNode* countryNode = hash_country_search(ht_countries, country);
	int vaccinated_people = 0, total = 0, j;
	double percentage;
	Date* date_from = calloc(1, sizeof (Date));
	Date* date_to = calloc(1, sizeof (Date));

	char tempdate1[11];		//max possible digits of a date
	char tempdate2[11];
	
	strcpy(tempdate1, date1);
	char* token = strtok(tempdate1, "-");
	j = 0;
	while (token != NULL) {
		if (j == 0)
			date_from->day = atoi(token);
		else if (j == 1)
			date_from->month = atoi(token);
		else if (j == 2)
			date_from->year = atoi(token);
		token = strtok(NULL, "-\n");
		j++;
	}
	
	strcpy(tempdate2, date2);
	token = strtok(tempdate2, "-");
	j = 0;
	while (token != NULL) {
		if (j == 0)
			date_to->day = atoi(token);
		else if (j == 1)
			date_to->month = atoi(token);
		else if (j == 2)
			date_to->year = atoi(token);
		token = strtok(NULL, "-\n");
		j++;
	}

	if (countryNode != NULL) {
		if (virusNode != NULL) {
			SkipListNode* temp = virusNode->vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check vaccinated_persons skiplist for vaccinated people
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						if((date_compare(temp->date, date_from)) == 1 && (date_compare(temp->date, date_to)) == -1) {
							vaccinated_people++;                        
						}
						total++;
					}
				}
				temp = temp->next[0];
			}

			temp = virusNode->not_vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check not_vaccinated_persons skiplist to find total people for percentage
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						total++;
					}
				}
				temp = temp->next[0];
			}
			percentage = (double)vaccinated_people / total * 100;
			if (total != 0)
				printf("%s %d %.2f%%\n", country, vaccinated_people, percentage);
			else
				printf("%s %d 0.00%%\n", country, vaccinated_people);
		} else {
			printf("Virus: %s missing\n", virusName);
		}
	} else {
		printf("Country: %s missing\n", country);
	}
	
	free(date_from);
	free(date_to);
}

void pop_status_by_age_virus(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* virusName) {

	int i;
	HashtableCountryNode* temp;
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		for (i = 0; i < HASHTABLE_NODES; i++) {
			temp = ht_countries->nodes[i];
			while (temp != NULL) {
				pop_status_by_age_country(ht_viruses, ht_countries, temp->countryName, virusName);
				temp = temp->next;
			}
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}

void pop_status_by_age_country(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* country, char* virusName) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);
	HashtableCountryNode* countryNode = hash_country_search(ht_countries, country);
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, total1 = 0, total2 = 0, total3 = 0, total4 = 0;
	double percentage1, percentage2, percentage3, percentage4;

	if (countryNode != NULL) {
		if (virusNode != NULL) {
			SkipListNode* temp = virusNode->vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check vaccinated_persons skiplist for vaccinated people
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						if (temp->citizen->age > 0 && temp->citizen->age <= 20) {
							sum1++;
							total1++;
						}
						else if (temp->citizen->age > 20 && temp->citizen->age <= 40) {
							sum2++;
							total2++;
						}
						else if (temp->citizen->age > 40 && temp->citizen->age <= 60) {
							sum3++;
							total3++;
						}
						else {
							sum4++;
							total4++;
						}
					}
				}
				temp = temp->next[0];
			}

			temp = virusNode->not_vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check not_vaccinated_persons skiplist to find total people for percentage
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						if (temp->citizen->age > 0 && temp->citizen->age <= 20) {
							total1++;
						}
						else if (temp->citizen->age > 20 && temp->citizen->age <= 40) {
							total2++;
						}
						else if (temp->citizen->age > 40 && temp->citizen->age <= 60) {
							total3++;
						}
						else {
							total4++;
						}
					}
				}
				temp = temp->next[0];
			}
			percentage1 = (double)sum1 / total1 * 100;
			percentage2 = (double)sum2 / total2 * 100;
			percentage3 = (double)sum3 / total3 * 100;
			percentage4 = (double)sum4 / total4 * 100;
			printf("%s\n", country);
			if (total1 != 0)
				printf("0-20 %d %.2f%%\n", sum1, percentage1);
			else
				printf("0-20 %d 0.00%%\n", sum1);
			if (total2 != 0)
				printf("20-40 %d %.2f%%\n", sum2, percentage2);
			else
				printf("20-40 %d 0.00%%\n", sum2);
			if (total3 != 0)
				printf("40-60 %d %.2f%%\n", sum3, percentage3);
			else
				printf("40-60 %d 0.00%%\n", sum3);
			if (total4 != 0)
				printf("60+ %d %.2f%%\n", sum4, percentage4);
			else
				printf("60+ %d 0.00%%\n", sum4);
		} else {
			printf("Virus: %s missing\n", virusName);
		}
	} else {
		printf("Country: %s missing\n", country);
	}

}

void pop_status_by_age_virus_dates(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* virusName, char* date1, char* date2) {
	
	int i;
	HashtableCountryNode* temp;
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		for (i = 0; i < HASHTABLE_NODES; i++) {
			temp = ht_countries->nodes[i];
			while (temp != NULL) {
				pop_status_by_age_country_dates(ht_viruses, ht_countries, temp->countryName, virusName, date1, date2);
				temp = temp->next;
			}
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}

void pop_status_by_age_country_dates(HashtableVirus* ht_viruses, HashtableCountry* ht_countries, char* country, char* virusName, char* date1, char* date2) {
	
	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);
	HashtableCountryNode* countryNode = hash_country_search(ht_countries, country);
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, total1 = 0, total2 = 0, total3 = 0, total4 = 0, j;
	double percentage1, percentage2, percentage3, percentage4;

	Date* date_from = calloc(1, sizeof (Date));
	Date* date_to = calloc(1, sizeof (Date));

	char tempdate1[11];
	char tempdate2[11];
	
	strcpy(tempdate1, date1);
	char* token = strtok(tempdate1, "-");
	j = 0;
	while (token != NULL) {
		if (j == 0)
			date_from->day = atoi(token);
		else if (j == 1)
			date_from->month = atoi(token);
		else if (j == 2)
			date_from->year = atoi(token);
		token = strtok(NULL, "-\n");
		j++;
	}

	strcpy(tempdate2, date2);

	token = strtok(tempdate2, "-");
	j = 0;
	while (token != NULL) {
		if (j == 0)
			date_to->day = atoi(token);
		else if (j == 1)
			date_to->month = atoi(token);
		else if (j == 2)
			date_to->year = atoi(token);
		token = strtok(NULL, "-\n");
		j++;
	}

	if (countryNode != NULL) {
		if (virusNode != NULL) {
			SkipListNode* temp = virusNode->vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check vaccinated_persons skiplist for vaccinated people
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						if ((date_compare(temp->date, date_from)) == 1 && (date_compare(temp->date, date_to)) == -1) {
							if (temp->citizen->age > 0 && temp->citizen->age <= 20) {
								sum1++;
								total1++;
							}
							else if (temp->citizen->age > 20 && temp->citizen->age <= 40) {
								sum2++;
								total2++;
							}
							else if (temp->citizen->age > 40 && temp->citizen->age <= 60) {
								sum3++;
								total3++;
							}
							else {
								sum4++;
								total4++;
							}
						}
					}
				}
				temp = temp->next[0];
			}

			temp = virusNode->not_vaccinated_persons->head->next[0];
			while (temp != NULL) {  //check not_vaccinated_persons skiplist to find total people for percentage
				if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) {
					if (!strcmp(temp->citizen->country, country)) {
						if (temp->citizen->age > 0 && temp->citizen->age <= 20) {
							total1++;
						}
						else if (temp->citizen->age > 20 && temp->citizen->age <= 40) {
							total2++;
						}
						else if (temp->citizen->age > 40 && temp->citizen->age <= 60) {
							total3++;
						}
						else {
							total4++;
						}
					}
				}
				temp = temp->next[0];
			}
			percentage1 = (double)sum1 / total1 * 100;
			percentage2 = (double)sum2 / total2 * 100;
			percentage3 = (double)sum3 / total3 * 100;
			percentage4 = (double)sum4 / total4 * 100;
			printf("%s\n", country);
			if (total1 != 0)
				printf("0-20 %d %.2f%%\n", sum1, percentage1);
			else
				printf("0-20 %d 0.00%%\n", sum1);
			if (total2 != 0)
				printf("20-40 %d %.2f%%\n", sum2, percentage2);
			else
				printf("20-40 %d 0.00%%\n", sum2);
			if (total3 != 0)
				printf("40-60 %d %.2f%%\n", sum3, percentage3);
			else
				printf("40-60 %d 0.00%%\n", sum3);
			if (total4 != 0)
				printf("60+ %d %.2f%%\n", sum4, percentage4);
			else
				printf("60+ %d 0.00%%\n", sum4);
		} else {
			printf("Virus: %s missing\n", virusName);
		}
	} else {
		printf("Country: %s missing\n", country);
	}
	free(date_from);
	free(date_to);
}

void vaccinate_now(HashtableVirus* ht_viruses, HashtableCitizen* ht_citizens, HashtableCountry* ht_countries, int bloomSize, char * citizenID, char * firstName, char * lastName, char * country, char * age, char * virusName) {

	Date* d = get_current_date();

	Record record = { 0 };
	
	record.citizenID = malloc((strlen(citizenID)) + 1);
	record.firstName = malloc((strlen(firstName)) + 1);
	record.lastName = malloc((strlen(lastName)) + 1);
	record.country = malloc((strlen(country)) + 1);
	record.virusName = malloc((strlen(virusName)) + 1);

	strcpy(record.citizenID, citizenID);
	strcpy(record.firstName, firstName);
	strcpy(record.lastName, lastName);
	strcpy(record.country, country);
	record.age = atoi(age);
	strcpy(record.virusName, virusName);

	record.dateVaccinated = d;

	insert_citizen_record(ht_viruses, ht_citizens, ht_countries, bloomSize, record, 0);

	// free(d);
	
	free_record(&record);
}

void list_nonVaccinated_Persons(HashtableVirus* ht_viruses, char* virusName) {

	HashtableVirusNode* virusNode = hash_virus_search(ht_viruses, virusName);

	if (virusNode != NULL) {
		SkipListNode* temp = virusNode->not_vaccinated_persons->head->next[0]; //first node after head

		while (temp != NULL) {
			if (strcmp(temp->citizen->citizenID, "ZZZZZ") != 0) //don't print skip list tail node
				printf("%s %s %s %s %d\n", temp->citizen->citizenID, temp->citizen->firstName, temp->citizen->lastName, temp->citizen->country, temp->citizen->age);
			temp = temp->next[0];
		}
	} else {
		printf("Virus: %s missing\n", virusName);
	}
}