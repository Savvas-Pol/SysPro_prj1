#ifndef _BF_H_
#define _BF_H_

#include <stdbool.h>


typedef struct BF{
	
	bool* vector;
	int size;
	
}BF;

unsigned long djb2(unsigned char *str);
unsigned long sdbm(unsigned char *str);
unsigned long hash_i(unsigned char *str, unsigned int i);

BF* bloom_init(int n);

void bloom_filter(BF** b, char* str, int K);



#endif
