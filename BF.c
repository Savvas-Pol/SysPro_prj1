#include <stdio.h>
#include <stdlib.h>

#include "BF.h"


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


void bloom_filter(BF** b, char* id){
	
	int pos;
	
	// pos = bloom_hash1((*b)->size,id);
	// if((*b)->vector[pos] == 0)
	// 	(*b)->vector[pos] = 1;
	
	// pos = bloom_hash2((*b)->size,id);
	// if((*b)->vector[pos] == 0)
	// 	(*b)->vector[pos] = 1;
	
	// pos = bloom_hash3((*b)->size,id);
	// if((*b)->vector[pos] == 0)
	// 	(*b)->vector[pos] = 1;
	
}
