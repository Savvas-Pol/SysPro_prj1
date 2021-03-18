#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "citizen.h"
#include "date.h"

typedef struct SL_Node {

    int level;
    // Citizen* id;
    // Date* date;
    
    struct SL_Node **next;

} SL_Node;


typedef struct SkipList {
    
    struct SL_Node * head;
    int maxLevel;

} SkipList;

SkipList* skiplist_init(int maxLevel);
void skiplist_destroy();

SL_Node* skiplist_search();
void skiplist_insert();

#endif /* SKIPLIST_H */

