#ifndef LIST_H
#define LIST_H

typedef struct Citizen{
	
	char* citizenID;
	char* firstName;
	char* lastName;
	char* country;
	int age;
	char* virusName;
	char* dateVaccinated;
}Citizen;

typedef struct List{
	
	int num;
	struct List *next;

}List;


List* list_search(List* l, int num);
void list_insert(List* l, int num);
void list_delete(List* l, int num);
void print_list(List* l);



#endif