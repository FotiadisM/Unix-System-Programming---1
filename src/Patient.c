#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Patient.h"

PatientPtr Patient_Init(char *line)
{
    PatientPtr patient = NULL;

    if((patient = malloc(sizeof(Patient))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    // patient->id = strtok(line, " ");
    // patient->fName = strtok(NULL, " ");
    // patient->lName = strtok(NULL, " ");
    // patient->diseaseID = strtok(NULL, " ");
    // patient->country = strtok(NULL, " ");

    return patient;
}