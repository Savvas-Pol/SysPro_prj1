#include <stdlib.h>

#include "skiplist.h"

SkipList* skiplist_init(int maxLevel){

	int i;
    
    SkipList* sl = malloc(sizeof (SkipList));
    sl->maxLevel = maxLevel;

    sl->head = NULL;

    return sl;
}
