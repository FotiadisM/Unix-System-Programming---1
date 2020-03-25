#ifndef LIST_H
#define LIST_H

#include "Patient.h"

#define F_PATIENT 1
#define DF_PATIENT 0

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

void List_Close(ListPtr l, int bool);

int List_Insert(ListPtr list, const PatientPtr patient);

ListNodePtr List_InsertSorted(ListPtr list, const PatientPtr patient);

void List_Print(ListPtr list);

#endif