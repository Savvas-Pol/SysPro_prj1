#include <stdlib.h>

#include "list.h"

List* list_search(List* l, int num){
	
	List* temp = l;

	while(temp != NULL){
		if(temp->num == num)
			return temp;
		else
			temp = temp->next;
	}
	return temp;
}

void list_insert(List* l, int num){

	List* new;
	List* temp = l;
	List* temp2 = NULL;
	int first = 1, flag = 0;
	
	new = (List*)malloc(sizeof(List));
	new->num = num;

	while((temp != NULL) && !flag){
		if(num < temp->num){			//adding in the middle of the list
			new->next = temp;
			if(first)
				temp = new;
			else
				temp2->next = new;
			flag = 1;
		}
		first = 0;
		temp2 = temp;
		temp = temp->next;
	}
	if(!flag){
		if(first)
			temp = new;				//adding to the beginning of the list
		else
			temp2->next = new;		//adding to the end of the list
		new->next = NULL;
	}
}

void list_delete(List* l, int num){
	
	// List* temp = l;
	// List* temp2 = NULL;
	// int flag = 0;

	// while((temp != NULL) && !flag){
	// 	if(num == temp->num){
	// 		flag = 1;
	// 	}
	// }
}