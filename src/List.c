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

void List_Close(ListPtr list, int bool)
{
    ListNodePtr ptr = NULL;

    while(list->head != NULL) {
        ptr = list->head;
        list->head = list->head->next;
        if(bool) {
            Patient_Close(ptr->patient);
        }
        free(ptr);
    }

    free(list);
}

int List_Insert(ListPtr list, const PatientPtr patient)
{
    ListNodePtr newNode = NULL;

    if((newNode = malloc(sizeof(ListNode))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    newNode->patient = patient;
    newNode->next = list->head;
    list->head = newNode;

    list->len++;

    return 0;
}

ListNodePtr List_InsertSorted(ListPtr list, const PatientPtr patient)
{
    ListNodePtr newNode = NULL;

    if((newNode = malloc(sizeof(ListNode))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    newNode->patient = patient;

    if(list->head == NULL || Date_Compare(patient->entryDate, list->head->patient->entryDate) == -1) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        ListNodePtr ptr = list->head;

        while(ptr->next != NULL) {
            if (Date_Compare(ptr->next->patient->entryDate, patient->entryDate) == -1) {
                break;
            }
            ptr = ptr->next;
        }

        newNode->next = ptr->next;
        ptr->next = newNode;
    }
    list->len++;

    return newNode;
}

void List_Print(ListPtr list)
{
    ListNodePtr ptr = list->head;

    while(ptr != NULL){
        Patient_Print(ptr->patient);
        ptr = ptr->next;
    }

}