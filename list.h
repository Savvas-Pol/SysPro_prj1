#ifndef LIST_H
#define LIST_H

typedef struct List{
	
	int num;
	struct List *next;

}List;

List* list_search();
void list_insert();
void list_delete();



#endif