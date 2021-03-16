#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list.h"
#include "BF.h"

typedef struct HashtableNode {
    char* virusName;
    BF* bloom;
    List* vaccinated_persons;
    List* not_vaccinated_persons;
    struct HashtableNode* next; //pointer to next bucket node
} HashtableNode;

typedef struct Hashtable {
    HashtableNode** nodes;
    int hash_nodes;
} Hashtable;

int hash_function(unsigned char *str, int buckets);

Hashtable* hash_create(int HASHNODES);
void hash_destroy(Hashtable* ht);

HashtableNode* hash_search(Hashtable* ht, char* virusName);
HashtableNode* hash_insert(Hashtable* ht, char* virusName);
void hash_delete(Hashtable* ht, char* virusName);




#endif