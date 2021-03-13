#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int hash_function(unsigned char *str, int buckets){

    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % buckets;
}

Node* hash_search(Node** ht, int pos, char* virusName){

	Node* temp = ht[pos];

	while(temp != NULL){
		if(!strcmp(temp->virusName, virusName))
			return temp;
		
		temp = temp->next;
	}
	return temp;
}

Node* hash_insert(Node** ht, int pos, char* virusName){

	Node* new;
	Node* temp = ht[pos];

	new = (Node*)malloc(sizeof(Node));

	new->virusName = (char*)malloc(strlen(virusName));
	strcpy(new->virusName, virusName);
	new->next = NULL;

	if(ht[pos] == NULL)
		ht[pos] = new;
	else{
		while(temp != NULL){
			if(temp->next == NULL){
				temp->next = new;
				return new;
			}
			else
				temp = temp->next;
		}
	}

	return new;

}

void hash_delete(Node** ht, int pos, char* virusName){

	Node* temp = ht[pos], *temp2;
	int first = 1;					// flag to check if we are in first node

	while(temp != NULL){
		if(!strcmp(temp->virusName, virusName)){
			if(first)
				ht[pos] = temp->next;
			else
				temp2->next = temp->next;

			free(temp->virusName);
			free(temp);
			return;
		}
		temp2 = temp;
		temp = temp->next;
		first = 0;
	}
}