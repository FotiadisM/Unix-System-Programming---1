#ifndef FNCLIB_H
#define FNCLIB_H

#include "maxHeap.h"
#include "HashTable.h"

#define _Disease 1
#define t_Countries 2

void globalDiseaseStats(const HashTablePtr ht, const DatePtr d1, const DatePtr d2);

void diseaseFrequency(const HashTablePtr ht, const char* disease, const char* country, const DatePtr d1, const DatePtr d2);

void topk_Diseases(const HashTablePtr h1, const HashTablePtr h2, const char* country, const int k, const DatePtr d1, const DatePtr d2);

void topk_Countries(const HashTablePtr h1, const HashTablePtr h2, const char *disease, const int k, const DatePtr d1, const DatePtr d2);

maxHeapPtr topk_InitHeap(const HashTablePtr h1, const HashTablePtr h2, const char* key, DatePtr d1, DatePtr d2, const int flag);

int insertPatientRecord(ListPtr list, HashTablePtr h1, HashTablePtr h2, char* reccordID, char* dName, char* lName, char* disease, char* country, char* d1, char* d2);

int recordPatientExit(ListPtr list, char* id, char* d2);

void numCurrentPatients(HashTablePtr h1, char* disease);

#endif