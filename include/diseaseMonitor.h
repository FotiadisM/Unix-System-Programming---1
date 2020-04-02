#ifndef DISEASEMONITOR_H
#define DISEASEMONITOR_H

#include <stdio.h>

#include "HashTable.h"

int DM_Init(const char* fileName, ListPtr list, HashTablePtr h1, HashTablePtr h2);

int DM_Run(char* line, ListPtr list, HashTablePtr h1, HashTablePtr h2);

PatientPtr DM_GetPatient(FILE *filePtr);

int DM_PatientExist(const ListPtr list, const PatientPtr patient);

int DM_ValidatePatient(const ListPtr list, const PatientPtr patient);

#endif