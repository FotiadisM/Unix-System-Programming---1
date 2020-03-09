#include <stdlib.h>
#include <string.h>

#include "../include/HashTable.h"
#include "../include/diseaseMonitor.h"

int DM_Init(const char* fileName, const int diseaseHTEntries, const int countryHTEntries, const size_t bucketSize)
{
    HashTablePtr ht = NULL;
    HashTable_Init(ht, diseaseHTEntries);

    return 1;
}