#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(int argc, char** argv){
	
	/*	---		DECLARATIONS	---	*/

	int i, bloomSize;

	List* l = NULL;

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

	

	
	return 0;
}