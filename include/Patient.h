#ifndef PATIENT_H
#define PATIENT_H

#include "./Date.h"

typedef struct Patient {
    char* id;
    char* fName;
    char* lName;
    char* diseaseID;
    char* country;
    DatePtr entryDate;
    DatePtr exitDate;
} Patient;

typedef Patient* PatientPtr;

PatientPtr Patient_Init(char *line);

void Patient_Close(PatientPtr patient);

void Patient_Print(const PatientPtr patient);

#endif