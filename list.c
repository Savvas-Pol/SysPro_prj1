#include <stdlib.h>

#include "list.h"

List* list_search(List* l, int num){
	
	List* temp = l;

	if(temp == NULL)
		return NULL;
	else{
		while(temp != NULL){
			if(temp->num == num)
				return temp;
			else
				temp = temp->next;
		}
	}
	return NULL;
}

void list_insert(List* l){
	
}

void list_delete(List* l){
	
}