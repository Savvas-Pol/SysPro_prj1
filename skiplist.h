#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "citizen.h"
#include "date.h"

#define SKIP_LIST_MAX_LEVEL 23

typedef struct SkipListNode {
    Citizen* citizen;
    Date* date;

    struct SkipListNode **next;
} SkipListNode;

typedef struct SkipList {
    struct SkipListNode * head;
    struct SkipListNode * tail;
    int maxLevel;
} SkipList;

SkipList* skiplist_init(int maxLevel);
void skiplist_destroy(SkipList* sl);

SkipListNode* skiplist_search(SkipList* sl, char * id);
void skiplist_insert(SkipList* sl, Citizen * citizen, Date * date);
void skiplist_delete(SkipList* sl, char * id);

#endif /* SKIPLIST_H */
