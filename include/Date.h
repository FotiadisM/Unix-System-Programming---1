#ifndef DATE_H
#define DATE_H

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef Date* DatePtr;

DatePtr Date_Init(DatePtr date, const char* info);

#endif