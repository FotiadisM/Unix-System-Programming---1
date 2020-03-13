#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

#include "./Patient.h"

typedef struct HashEntry {
    PatientPtr *value;
    struct HashEntry *next;
} HashEntry;

typedef HashEntry* HashEntryPtr;

typedef struct HashNode {
    int elements;
    HashEntryPtr entry;
} HashNode;

typedef HashNode* HashNodePtr;

typedef struct HashTable {
    int size;
    int elements;
    size_t bucketSize;
    HashNodePtr table;
} HashTable;

typedef HashTable* HashTablePtr;

HashTablePtr HashTable_Init(const int size, const size_t bucketSize);

void HashTable_Close(HashTablePtr ht);

unsigned long hash(const char *str);

int HashTable_Insert(HashTablePtr ht, const char* key, const PatientPtr patient);

#endif