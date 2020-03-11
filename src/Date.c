#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Date.h"

DatePtr Date_Init(DatePtr date, const char* info)
{
    char *s = NULL;

    if((date = malloc(sizeof(Date))) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    if((s = malloc(strlen(info) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    strcpy(s, info);

    date->day = atoi(strtok(s, "-"));
    date->month = atoi(strtok(NULL, "-"));
    date->year = atoi(strtok(NULL, "-"));

    free(s);

    return date;
}