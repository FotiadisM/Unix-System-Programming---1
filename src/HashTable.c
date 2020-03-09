#include <stdio.h>
#include <stdlib.h>

#include "../include/HashTable.h"

int HashTable_Init(HashTablePtr ht, const int size)
{
    if((ht = malloc(sizeof(HashTable))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    ht->size = size;
    ht->elements = 0;

    if((ht->table = malloc(size*sizeof(HashEntryPtr))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    for(int i=0; i < size; i++) {
        ht->table[i] = NULL;
    }

    return 0;
}

void HashTable_Close(HashTablePtr ht)
{
    HashEntryPtr ptr = NULL;

    for(int i=0; i < ht->size; i++) {
        if(ht->table[i] != NULL) {
            // ptr = ht->table[i];
            // ht->table[i] = ptr->next;
            // if(ptr->value != NULL) {
            //     Patient_Close(ptr->value);
            //     free(ptr->value);
            // }
            // free(ptr);
        }
    }
}