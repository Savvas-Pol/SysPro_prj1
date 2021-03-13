#ifndef HASHTABLE_H__
#define	HASHTABLE_H__

#include "list.h"
#include "BF.h"

typedef struct Node{

	char* virusName;
	BF* bloom;
	List* vaccinated_persons;
	List* not_vaccinated_persons;
	struct Node* next;	//pointer to next bucket node

}Node;

int hash_function(unsigned char *str, int buckets);

Node* hash_search(Node** ht, int pos, char* virusName);
void hash_insert(Node** ht, int pos, char* virusName);
void hash_delete(Node** ht, int pos, char* virusName);

#endif