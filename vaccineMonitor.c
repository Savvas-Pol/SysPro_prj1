#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hashtable.h"
#include "BF.h"

#define K 16			// K for Hash Functions
#define MAXLEVEL 4		// Skip List Level
#define HASHNODES 20	// HashTable for Diseases

int main(int argc, char** argv){
	
	/*	---		DECLARATIONS	---	*/

	int i, j, bloomSize, pos;
	char* token, *token2;

	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	Record temp;
	Node* node;

	List* l = NULL;
	BF* bloom;

	FILE* citizenRecordsFile;

	/*		---------------		*/

	if(argc < 5){							//	read arguments from command line
		printf("Wrong arguments!!!\n");
		return -1;
	}
	else{
		for(i = 0; i < 4; i++){	
			if(!strcmp(argv[i], "-c")){
				if(!(citizenRecordsFile = fopen(argv[i+1], "r"))){
					printf("Error in opening %s\n", argv[i+1]);
					return -1;
				}
			}
			else if(!strcmp(argv[i], "-b")){
				bloomSize = atoi(argv[i+1]);
			}
		}
	}

	Node** ht = (Node**)malloc(HASHNODES*sizeof(Node*));		//create hashtable for diseases
	for(i = 0; i < HASHNODES; i++){
		ht[i] = NULL;
	}

	while((read = getline(&line, &len, citizenRecordsFile)) != -1){					//line by line
		token = strtok(line, " \n");												//word by word
		i = 0;
		while(token != NULL){
			if(i == 0){
				temp.citizenID = malloc(sizeof(strlen(token)));
				strcpy(temp.citizenID, token);
			}
			else if(i == 1){
				temp.firstName = malloc(sizeof(strlen(token)));
				strcpy(temp.firstName, token);
			}
			else if(i == 2){
				temp.lastName = malloc(sizeof(strlen(token)));
				strcpy(temp.lastName, token);
			}
			else if(i == 3){
				temp.country = malloc(sizeof(strlen(token)));
				strcpy(temp.country, token);
			}
			else if(i == 4){
				temp.age = atoi(token);
			}
			else if(i == 5){
				temp.virusName = malloc(sizeof(strlen(token)));
				strcpy(temp.virusName, token);
			}
			else if(i == 6){
				if(!strcmp(token, "YES")){
					j = 0;
					token = strtok(NULL, " \n");
					token = strtok(token, "-\n");
					temp.dateVaccinated = malloc(sizeof(Date));
					while(token != NULL){
						if(j == 0)
							temp.dateVaccinated->day = atoi(token);
						else if(j == 1)
							temp.dateVaccinated->month = atoi(token);
						else if(j == 2)
							temp.dateVaccinated->year = atoi(token);
						token = strtok(NULL, "-\n");
						j++;
					}
				}
				else{
					temp.dateVaccinated = NULL;
				}
			}
			token = strtok(NULL, " \n");
			i++;
		}
		// printf("%s %s %s %s %d %s ",temp.citizenID, temp.firstName, temp.lastName, temp.country, temp.age, temp.virusName);
		// if(temp.dateVaccinated != NULL)
		// 	printf("%d-%d-%d\n", temp.dateVaccinated->day, temp.dateVaccinated->month, temp.dateVaccinated->year);
		// else
		// 	printf("\n");
		pos = hash_function(temp.virusName, HASHNODES);
		if(hash_search(ht, pos, temp.virusName) == NULL){
			node = hash_insert(ht, pos, temp.virusName);
			node->bloom = bloom_init(bloomSize);
		}
	}
	
	return 0;
}