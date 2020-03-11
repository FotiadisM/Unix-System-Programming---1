#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Patient.h"

PatientPtr Patient_Init(char *line)
{
    char *s = NULL;
    PatientPtr patient = NULL;

    if((patient = malloc(sizeof(Patient))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    s = strtok(line, " ");
    if((patient->id = malloc(strlen(s) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(patient->id, s);

    s = strtok(NULL, " ");
    if((patient->fName = malloc(strlen(s) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(patient->fName, s);

    s = strtok(NULL, " ");
    if((patient->lName = malloc(strlen(s) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(patient->lName, s);

    s = strtok(NULL, " ");
    if((patient->diseaseID = malloc(strlen(s) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(patient->diseaseID, s);

    s = strtok(NULL, " ");
    if((patient->country = malloc(strlen(s) + 1)) == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(patient->country, s);

    s = strtok(NULL, "\n");
    patient->entryDate = Date_Init(s);

    s = strtok(NULL, "\n");
    if(!strcmp(s, "-")) {
        patient->exitDate = NULL;
    }
    else {
        patient->exitDate = Date_Init(s);
    }

    return patient;
}

void Patient_Close(PatientPtr patient)
{
    free(patient->id);
    free(patient->fName);
    free(patient->lName);
    free(patient->diseaseID);
    free(patient->country);

    free(patient->entryDate);
    if(patient->exitDate != NULL) {
        free(patient->exitDate);
    }

    free(patient);
}

void Patient_Print(PatientPtr patient)
{
    printf("%s %s %s %s %s %d-%d-%d ", patient->id, patient->fName, patient->lName, patient->diseaseID, patient->country, patient->entryDate->day, patient->entryDate->month, patient->entryDate->year);
    if(patient->exitDate != NULL) {
        printf("exit: %d-%d-%d\n", patient->exitDate->day, patient->exitDate->month, patient->exitDate->year);
    }
    else {
        printf("-\n");
    }
}