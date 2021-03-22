#ifndef DATE_H
#define DATE_H

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

int date_compare(Date* d1, Date* d2);

void get_current_date_time();

#endif /* DATE_H */

