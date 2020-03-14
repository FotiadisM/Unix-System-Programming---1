#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

#include "AVL.h"
#include "Patient.h"

typedef struct HashEntry {
    char *key;
    AVLTreePtr tree;
    struct HashEntry *next;
} HashEntry;

typedef HashEntry* HashEntryPtr;

typedef struct HashNode {
    HashEntryPtr entry;
    struct HashNode *next;
} HashNode;

typedef HashNode* HashNodePtr;

typedef struct HashTable {
    int size;
    int elements;
    size_t bucketSize;
    HashNodePtr table;
} HashTable;

typedef HashTable* HashTablePtr;

unsigned long hash(const char *str);

HashEntryPtr HashEntry_Init(const char* str);

HashTablePtr HashTable_Init(const int size, const size_t bucketSize);

void HashTable_Close(HashTablePtr ht);

void HashNode_Close(HashNodePtr node);

AVLTreePtr HashTable_LocateKey(HashNodePtr ht, const char *key);

AVLTreePtr HashNode_Insert(HashNodePtr node, const char *key, const int entriesPerBucket);

int HashTable_Insert(HashTablePtr ht, const char* key, const PatientPtr patient);

#endif