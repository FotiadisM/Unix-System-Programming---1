#ifndef DISEASEMONITOR_H
#define DISEASEMONITOR_H

#include <stdio.h>

#include "HashTable.h"
#include "Patient.h"

int DM_Init(const char* fileName, ListPtr list, HashTablePtr h1, HashTablePtr h2);

int DM_Run(char* line, ListPtr list, HashTablePtr h1, HashTablePtr h2);

PatientPtr DM_GetPatient(FILE *filePtr);

void globalDiseaseStats(const HashTablePtr ht, const DatePtr d1, const DatePtr d2);

void diseaseFrequency(const HashTablePtr ht, const char* disease, const char* country, const DatePtr d1, const DatePtr d2);

// int insertPatientRecprd(char* reccordID, char* disease, char* country, )

#endif