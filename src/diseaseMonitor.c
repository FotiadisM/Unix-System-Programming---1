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
    char s1[11], s2[11];
    DatePtr d1, d2;

    strcpy(s1, "00-00-2005");
    strcpy(s2, "00-00-3000");

    d1 = Date_Init(s1);
    d2 = Date_Init(s2);

    globalDiseaseStats(h1, d1, d2);
    diseaseFrequency(h1, "COVID-2019", NULL, d1, d2);
    numCurrentPatients(h1, NULL);

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

void globalDiseaseStats(const HashTablePtr ht, const DatePtr d1, const DatePtr d2)
{
    HashNodePtr nodePtr = NULL;

    for (int i=0; i < ht->size; i++) {
        nodePtr = &(ht->table[i]);
        while (nodePtr != NULL) {
            for (int j=0; j < ht->bucketSize; j++) {
                if (nodePtr->entries[j] != NULL) {
                    if (d2 == NULL) {
                        printf("disease: %s, patients: %d\n", nodePtr->entries[j]->key, nodePtr->entries[j]->tree->elements);
                    }
                    else {
                        printf("disease: %s, patients: %d\n", nodePtr->entries[j]->key, AVLNode_countPatients(nodePtr->entries[j]->tree->root, NULL, d1, d2));
                    }

                }
            }
            nodePtr = nodePtr->next;
        }
    }
    printf("\n");
}

void diseaseFrequency(const HashTablePtr ht, const char* disease, const char* country, const DatePtr d1, const DatePtr d2)
{
    HashNodePtr nodePtr = &(ht->table[hash(disease) % ht->size]);

    while(nodePtr != NULL) {
        for (int j=0; j < ht->bucketSize; j++) {
            if (nodePtr->entries[j] != NULL) {
                if (!strcmp(nodePtr->entries[j]->key, disease)) {
                    printf("patients: %d\n", AVLNode_countPatients(nodePtr->entries[j]->tree->root, country, d1, d2));
                    break;
                }
            }
        }
        nodePtr = nodePtr->next;
    }
    printf("\n");

}

int recordPatientExit(ListPtr list, char* id, char* d2)
{
    ListNodePtr ptr = list->head;

    while(ptr != NULL) {
        if (!strcmp(ptr->patient->id, id)) {
            if((ptr->patient->exitDate = Date_Init(d2)) == NULL) {
                perror("malloc failed");
                return -1;
            }
            break;
        }
    }

    return 0;
}

void numCurrentPatients(HashTablePtr ht, char* disease)
{
    HashNodePtr nodePtr = NULL;

    if (disease == NULL) {
        for (int i=0; i < ht->size; i++) {
            nodePtr = &(ht->table[i]);
            while (nodePtr != NULL) {
                for (int j=0; j < ht->bucketSize; j++) {
                    if (nodePtr->entries[j] != NULL) {
                        printf("Disease: %s, patients: %d\n", nodePtr->entries[j]->key, AVLNode_countNullPatients(nodePtr->entries[j]->tree->root));
                    }
                }
                nodePtr = nodePtr->next;
            }
        }
    }
    else {
        nodePtr = &(ht->table[hash(disease) % ht->size]);
        while (nodePtr != NULL) {
            for (int j=0; j < ht->bucketSize; j++) {
                if (nodePtr->entries[j] != NULL) {
                    if (!strcmp(nodePtr->entries[j]->key, disease)) {
                        printf("Disease: %s, patients: %d\n", disease, AVLNode_countNullPatients(nodePtr->entries[j]->tree->root));
                        break;
                    }
                }
            }
            nodePtr = nodePtr->next;
        }
    }
    printf("\n");
}

int insertPatientRecord(ListPtr list, HashTablePtr h1, HashTablePtr h2, char* reccordID, char* fName, char* lName, char* disease, char* country, char* d1, char* d2)
{
    PatientPtr patient = NULL;

    if((patient = malloc(sizeof(Patient))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if((patient->id = malloc(strlen(reccordID) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->id, reccordID);

    if((patient->fName = malloc(strlen(fName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->fName, fName);

    if((patient->lName = malloc(strlen(lName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->lName, lName);

    if((patient->diseaseID = malloc(strlen(disease) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->diseaseID, disease);

    if((patient->country = malloc(strlen(country) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->country, country);

    if((patient->entryDate = Date_Init(d1)) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if(d2 == NULL) {
        patient->exitDate = NULL;
    }
    else {
        if((patient->exitDate = Date_Init(d2)) == NULL) {
            perror("malloc failed");
            return -1;
        }
    }

    if(List_InsertSorted(list, patient) == -1) {
        return -1;
    }
    if(HashTable_Insert(h1, patient->diseaseID, patient) == -1) {
        return -1;
    }
    if(HashTable_Insert(h2, patient->country, patient) == -1) {
        return -1;
    }

    return 0;
}