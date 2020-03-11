#include <stdlib.h>

#include "../include/HashTable.h"

HashTablePtr HashTable_Init(HashTablePtr ht, const int size, const int bucketSize)
{
    if((ht = malloc(sizeof(HashTable))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    ht->size = size;
    ht->elements = 0;
    ht->bucketSize = bucketSize;

    if((ht->table = malloc(size*sizeof(HashNode))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    for(int i=0; i < size; i++) {
        ht->table[i].elements = 0;
        ht->table[i].entry = NULL;
    }

    return ht;
}

void HashTable_Close(HashTablePtr ht)
{
    HashEntryPtr tmpHashEntry = NULL;

    for(int i=0; i < ht->size; i++) {
        while(ht->table[i].entry != NULL) {
            tmpHashEntry = ht->table[i].entry;
            ht->table[i].entry = tmpHashEntry->next;
            free(tmpHashEntry->value);
            free(tmpHashEntry);
        }
    }

    free(ht->table);
    free(ht);
}