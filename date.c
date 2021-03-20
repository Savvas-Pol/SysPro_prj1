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