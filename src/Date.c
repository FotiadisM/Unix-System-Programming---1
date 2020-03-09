#include <stdlib.h>
#include <string.h>

#include "../include/Date.h"

void Date_Init(DatePtr date, const char* info)
{
    char* s = malloc(sizeof(info));

    strcpy(s, info);

    date->day = atoi(strtok(s, "-"));
    date->month = atoi(strtok(NULL, "-"));
    date->year = atoi(strtok(NULL, "-"));

    free(s);
}