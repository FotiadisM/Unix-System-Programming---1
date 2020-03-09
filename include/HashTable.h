#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "./Patient.h"

typedef struct HashEntry {
    PatientPtr value;
    struct HashEntry *next;
} HashEntry;

typedef HashEntry* HashEntryPtr;

typedef struct HashNode {
    HashEntryPtr *entry;
} HashNode;

typedef HashNode* HashNodePtr;

typedef struct HashTable {
    int size;
    int elements;
    HashEntryPtr *table;
} HashTable;

typedef HashTable* HashTablePtr;

int HashTable_Init(HashTablePtr ht, const int size);

void HashTable_Close(HashTablePtr ht);

#endif