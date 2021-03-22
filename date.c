#include <stdio.h>
#include <time.h>

#include "date.h"

int date_compare(Date* d1, Date* d2) { //returns -1 if d1<d2, 1 if d1>d2, 0 otherwise

    if (d1->year < d2->year) {
        return -1;
    } else if (d1->year > d2->year) {
        return 1;
    } else {
        if (d1->month < d2->month) {
            return -1;
        } else if (d1->month > d2->month) {
            return 1;
        } else {
            if (d1->day < d2->day) {
                return -1;
            } else if (d1->day > d2->day) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

void get_current_date_time() {

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("now: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}