#include <stdlib.h>
#include <string.h>

#include "../include/defines.h"
#include "../include/diseaseMonitor.h"

int DM_Init(const char* fileName, ListPtr list, HashTablePtr h1, HashTablePtr h2)
{
    char *dest = NULL;
    FILE *filePtr = NULL;
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
        if(List_InsertSorted(list, patient) == -1) {
            return -1;
        }
        if(HashTable_Insert(h1, patient->diseaseID, patient) == -1) {
            return -1;
        }
        if(HashTable_Insert(h2, patient->country, patient) == -1) {
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
    globalDiseaseStats(h1, NULL, NULL);
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

void globalDiseaseStats(HashTablePtr ht, DatePtr d1, DatePtr d2)
{
    HashEntryPtr entryPtr = NULL;
    HashNodePtr nodePtr = NULL;

    for(int i=0; i < ht->size; i++) {
        nodePtr = &(ht->table[i]);
        while(nodePtr != NULL) {
            entryPtr = nodePtr->entry;
            while(entryPtr != NULL) {
                printf("disease: %s, patients: %d\n", entryPtr->key, entryPtr->tree->elements);
                entryPtr = entryPtr->next;
            }
            nodePtr = nodePtr->next;
        }
    }
}