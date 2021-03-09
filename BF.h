#ifndef _BF_H_
#define _BF_H_

#include <stdbool.h>


typedef struct BF{
	
	bool* vector;
	int size;
	
}BF;


BF* bloom_init(int n);

void bloom_filter(BF** b, char* word);



#endif
