#ifndef LIST_H
#define LIST_H

#include "Patient.h"

typedef struct ListNode {
    PatientPtr patient;
    struct ListNode *next;
} ListNode;

typedef ListNode* ListNodePtr;

typedef struct List {
    int len;
    ListNodePtr head;
} List;

typedef List* ListPtr;

ListPtr List_Init();

void List_Close(ListPtr l);

int List_InsertSorted(ListPtr list, const PatientPtr patient);

#endif