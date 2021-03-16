#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

Hashtable* hash_create(int HASHNODES) {
    int i;
    Hashtable* ht = malloc(sizeof (Hashtable));
    ht->hash_nodes = HASHNODES;

    ht->nodes = (HashtableNode**) malloc(HASHNODES * sizeof (HashtableNode*)); //create hashtable for diseases
    for (i = 0; i < HASHNODES; i++) {
        ht->nodes[i] = NULL;
    }

    return ht;
}

void hash_destroy(Hashtable* ht) {
    int i;

    for (i = 0; i < ht->hash_nodes; i++) {
        HashtableNode* temp = ht->nodes[i];

        while (temp != NULL) {
            ht->nodes[i] = temp->next;

            bloom_destroy(temp->bloom);
            free(temp->virusName);
            free(temp);
            
            temp = ht->nodes[i];
        }
    }

    free(ht->nodes);
    free(ht);
}

int hash_function(unsigned char *str, int buckets) {

    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % buckets;
}

HashtableNode* hash_search(Hashtable* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableNode* temp = ht->nodes[pos];

    while (temp != NULL) {
        if (!strcmp(temp->virusName, virusName))
            return temp;

        temp = temp->next;
    }
    return temp;
}

HashtableNode* hash_insert(Hashtable* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableNode* new;
    HashtableNode* temp = ht->nodes[pos];

    new = (HashtableNode*) malloc(sizeof (HashtableNode));

    new->virusName = (char*) malloc(strlen(virusName) + 1);
    strcpy(new->virusName, virusName);
    new->next = ht->nodes[pos];
    ht->nodes[pos] = new;

    return new;
}

void hash_delete(Hashtable* ht, char* virusName) {

    int pos = hash_function((unsigned char*) virusName, ht->hash_nodes);

    HashtableNode* temp = ht->nodes[pos], *temp2;
    int first = 1; // flag to check if we are in first node

    while (temp != NULL) {
        if (!strcmp(temp->virusName, virusName)) {
            if (first)
                ht->nodes[pos] = temp->next;
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