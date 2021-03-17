#ifndef BF_H
#define BF_H

#include <stdbool.h>

typedef struct BF {
    char* vector;
    int size;

} BF;

unsigned long djb2(unsigned char *str);
unsigned long sdbm(unsigned char *str);
unsigned long hash_i(unsigned char *str, unsigned int i);

BF* bloom_init(int n);

void bloom_destroy(BF* b);

void bloom_filter(BF* b, char* str, int K);



#endif
