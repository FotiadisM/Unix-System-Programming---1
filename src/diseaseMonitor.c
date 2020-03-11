#include <stdlib.h>
#include <string.h>

#include "../include/HashTable.h"
#include "../include/diseaseMonitor.h"

int DM_Init(const char* fileName, HashTablePtr h1, HashTablePtr h2)
{
    char *dest = NULL;
    FILE *filePtr = NULL;
    PatientPtr patient = NULL;

    if((dest = malloc(strlen("./Assets/") + strlen(fileName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(dest, "./Assets/");
    strcat(dest, fileName);

    if((filePtr = fopen(dest, "r")) == NULL) {
        perror(fileName);
        return -1;
    }

    while((patient = DM_GetPatient(filePtr)) != NULL)
    {
        printf("id: %s, name: %s %s, disease: %s, country: %s\n", patient->id, patient->fName, patient->lName, patient->diseaseID, patient->country);

        free(patient);
    }

    free(dest);
    fclose(filePtr);

    return 1;
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