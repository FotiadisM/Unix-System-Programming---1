#ifndef FNCLIB_H
#define FNCLIB_H

#include "HashTable.h"

void globalDiseaseStats(const HashTablePtr ht, const DatePtr d1, const DatePtr d2);

void diseaseFrequency(const HashTablePtr ht, const char* disease, const char* country, const DatePtr d1, const DatePtr d2);

int insertPatientRecord(ListPtr list, HashTablePtr h1, HashTablePtr h2, char* reccordID, char* dName, char* lName, char* disease, char* country, char* d1, char* d2);

int recordPatientExit(ListPtr list, char* id, char* d2);

void numCurrentPatients(HashTablePtr h1, char* disease);

#endif