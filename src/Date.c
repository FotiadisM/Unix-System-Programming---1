#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Date.h"

DatePtr Date_Init(char* info)
{
    DatePtr date = NULL;

    if((date = malloc(sizeof(Date))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    date->day = atoi(strtok(info, "-"));
    date->month = atoi(strtok(NULL, "-"));
    date->year = atoi(strtok(NULL, " "));

    return date;
}

int Date_Compare(const DatePtr d1, const DatePtr d2)
{
    if(d1->year < d2->year) {
        return -1;
    }
    else if(d1->year > d2->year) {
        return 1;
    }
    else {
        if(d1->month < d2->month) {
            return -1;
        }
        else if(d1->month > d2->month) {
            return 1;
        }
        else {
            if(d1->day < d2->day) {
                return -1;
            }
            else if(d1->day > d2->day) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}

void Date_Print(const DatePtr date)
{
    printf("%2d-%2d-%4d ", date->day, date->month, date->year);
}