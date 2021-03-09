#include <stdio.h>
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

void list_insert(List** l, int num){

	List* new;
	List* temp = *l;
	List* temp2 = NULL;
	int first = 1, flag = 0;
	
	new = (List*)malloc(sizeof(List));
	new->num = num;

	while((temp != NULL) && !flag){
		if(num < temp->num){			//adding in the middle of the list
			new->next = temp;
			if(first)
				*l = new;
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
			*l = new;				//adding to the beginning of the list
		else
			temp2->next = new;		//adding to the end of the list
		new->next = NULL;
	}
}

void list_delete(List** l, int num){
	
	List* temp = *l;
	List* temp2 = NULL;
	int first = 1;

	while(temp != NULL){
		if(num == temp->num){
			if(first)
				*l = temp->next;
			else
				temp2->next = temp->next;
			
			free(temp);
			break;
		}
		first = 0;
		temp2 = temp;
		temp = temp->next;
	}
}

void print_list(List* l){

	List* temp = l;

	if(temp == NULL)
		printf("Empty List\n");
	else{
		printf("List contains : ");
		while(temp != NULL){
			printf("%d\t", temp->num);
			temp = temp->next;
		}
		printf("\n");
	}
}