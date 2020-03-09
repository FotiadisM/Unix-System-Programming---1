#include "../include/diseaseMonitor.h"

int DM_Init(const char* fileName, const int* diseaseHTEntries, const int* countryHTEntries, const size_t* bucketSize)
{
    printf("%s, %d, %d, %zu\n", fileName, *diseaseHTEntries, *countryHTEntries, *bucketSize);

    return 0;
}