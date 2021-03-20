#ifndef LIST_H
#define LIST_H

typedef struct List {
    int num;
    struct List *next;

} List;


List* list_search(List* l, int num);
void list_insert(List** l, int num);
void list_delete(List** l, int num);
void print_list(List* l);



#endif