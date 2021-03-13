#include <stdio.h>
#include <stdlib.h>

#include "BF.h"

unsigned long djb2(unsigned char *str){
	int c;
	unsigned long hash = 5381;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c

	return hash;
}

unsigned long sdbm(unsigned char *str){
	int c;
	unsigned long hash = 0;

	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

unsigned long hash_i(unsigned char *str, unsigned int i){
	return djb2(str) + i * sdbm(str) + i * i;
}


BF* bloom_init(int bloomSize){
	
	BF* bloom;
	
	if((bloom = malloc(sizeof(BF))) == NULL){
		printf(" Error in allocation of Bloom Filter...\n");
		return NULL;
	}
	
	bloom->size = bloomSize;
	
	if((bloom->vector = calloc(bloom->size,sizeof(bool))) == NULL){
		printf(" Error in allocation of vector...\n");
		return NULL;
	}
	
	return bloom;
	
}


void bloom_filter(BF** b, char* str, int K){
	
	int pos;
	
	for(i = 0; i < K; i++){
		pos = hash_i(str, i);
		// b[pos]
	}
	
}
