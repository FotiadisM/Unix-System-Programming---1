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