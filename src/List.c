#include <stdio.h>
#include <stdlib.h>

#include "../include/List.h"

ListPtr List_Init()
{
    ListPtr list = NULL;

    if((list = malloc(sizeof(List))) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    list->len = 0;
    list->head = NULL;

    return list;
}

void List_Close(ListPtr list)
{
    ListNodePtr ptr = NULL;

    while(list->head != NULL) {
        ptr = list->head;
        list->head = list->head->next;
        Patient_Close(ptr->patient);
        free(ptr);
    }

    free(list);
}

int List_Insert(ListPtr list, PatientPtr patient)
{
    ListNodePtr newNode = NULL;

    if((newNode = malloc(sizeof(ListNode))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    newNode->patient = patient;
    newNode->next = list->head;
    list->head = newNode;

    return 0;
}