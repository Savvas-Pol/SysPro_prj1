#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "BF.h"

int main(int argc, char** argv){
	
	/*	---		DECLARATIONS	---	*/

	int i, bloomSize;
	char* token;

	char* line = NULL;
	size_t len = 0;
	ssize_t read;

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

	// bloom = bloom_init(bloomSize);

	while((read = getline(&line, &len, citizenRecordsFile)) != -1){					//line by line
		token = strtok(line, " \n");												//word by word
		i = 0;
		while(token != NULL){
			
			// if(i == 0){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 1){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 2){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 3){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 4){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 5){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 6){
			// 	printf("%d : %s\n", i, token);
			// }
			// else if(i == 7){
			// 	printf("%d : %s\n", i, token);
			// }
			
			token = strtok(NULL, " \n");
			i++;
		}
	}
	
	return 0;
}