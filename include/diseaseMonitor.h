#ifndef DISEASEMONITOR_H
#define DISEASEMONITOR_H

#include <stdio.h>

#include "HashTable.h"
#include "Patient.h"

int DM_Init(const char* fileName, ListPtr list, HashTablePtr h1, HashTablePtr h2);

int DM_Run(char* line, ListPtr list, HashTablePtr h1, HashTablePtr h2);

PatientPtr DM_GetPatient(FILE *filePtr);

void globalDiseaseStats(HashTablePtr ht, DatePtr d1, DatePtr d2);

#endif