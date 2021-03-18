#ifndef SKIPLIST_H
#define SKIPLIST_H


typedef struct SL_Node {

    int level;
    // date, citizen id
    
    struct SL_Node **next;

} SL_Node;


typedef struct SkipList {
    
    struct SL_Node * head;
    int maxLevel;

} SkipList;


#endif /* SKIPLIST_H */

