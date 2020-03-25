#include <stdlib.h>
#include <string.h>

#include "../include/fnclib.h"
#include "../include/defines.h"
#include "../include/diseaseMonitor.h"

int DM_Init(const char* fileName, ListPtr list, HashTablePtr h1, HashTablePtr h2)
{
    char *dest = NULL;
    FILE *filePtr = NULL;
    ListNodePtr node = NULL;
    PatientPtr patient = NULL;

    if((dest = malloc(strlen(FILE_LOCATION) + strlen(fileName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(dest, FILE_LOCATION);
    strcat(dest, fileName);

    if((filePtr = fopen(dest, "r")) == NULL) {
        perror(dest);
        free(dest);
        return -1;
    }

    while((patient = DM_GetPatient(filePtr)) != NULL)
    {
        Patient_Print(patient);

        if((node = List_InsertSorted(list, patient)) == NULL) {
            return -1;
        }

        if(HashTable_Insert(h1, patient->diseaseID, node) == -1) {
            return -1;
        }

        if(HashTable_Insert(h2, patient->country, node) == -1) {
            return -1;
        }
    }
    printf("\n");

    free(dest);
    fclose(filePtr);

    return 0;
}

int DM_Run(char* line, ListPtr list, HashTablePtr h1, HashTablePtr h2)
{
    char s1[11], s2[11];
    DatePtr d1, d2;

    strcpy(s1, "0-0-995");
    strcpy(s2, "0-0-3000");

    d1 = Date_Init(s1);
    d2 = Date_Init(s2);

    // strcpy(s1, "00-00-2005");
    // strcpy(s2, "00-00-3000");

    globalDiseaseStats(h1, d1, d2);
    globalDiseaseStats(h1, NULL, NULL);
    diseaseFrequency(h1, "COVID-2019", NULL, d1, d2);
    // numCurrentPatients(h1, NULL);
    // insertPatientRecord(list, h1, h2, "1234", "blah", "blah", "COVID-2019", "Greece", s1, NULL);
    // numCurrentPatients(h1, NULL);
    // printf("---------\n");
    // recordPatientExit(list, "1234", s2);
    // printf("---------\n");
    // numCurrentPatients(h1, NULL);

    free(d1);
    free(d2);

    return 0;
}

PatientPtr DM_GetPatient(FILE *filePtr)
{
    char *line = NULL;
    size_t len = 0;
    PatientPtr patient = NULL;

    if(getline(&line, &len, filePtr) == -1) {
        free(line);
        return NULL;
    }

    if((patient = Patient_Init(line)) == NULL) {
        free(line);
        return NULL;
    }

    free(line);

    return patient;
}