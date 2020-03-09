#ifndef DISEASEMONITOR_H
#define DISEASEMONITOR_H

#include <stdio.h>

int DM_Init(const char* fileName, const int* diseaseHTEntries, const int* countryHTEntries, const size_t* bucketSize);

#endif