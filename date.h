#ifndef DATE_H
#define DATE_H

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

int date_compare(Date* d1, Date* d2);

Date* get_current_date();

Date * duplicateDate(Date *d);

#endif /* DATE_H */

