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

int List_InsertSorted(ListPtr list, const PatientPtr patient)
{
    ListNodePtr newNode = NULL;

    if((newNode = malloc(sizeof(ListNode))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    newNode->patient = patient;
    newNode->next = list->head;

    if(list->head == NULL || Date_Compare(patient->entryDate, list->head->patient->entryDate) == -1) {
        list->head = newNode;
    }
    else {
        ListNodePtr ptr = list->head;

        while(ptr->next != NULL && Date_Compare(ptr->next->patient->entryDate, patient->entryDate) == -1) {
            ptr = ptr->next;
        }

        newNode->next = ptr->next;
        ptr->next = newNode;
    }

    return 0;
}