#include <stdlib.h>
#include <string.h>

#include "../include/defines.h"
#include "../include/HashTable.h"

unsigned long hash(const char *str)
{
    int c;
    unsigned long hash = HASH_SEED;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

HashEntryPtr HashEntry_Init(const char* key)
{
    HashEntryPtr entry = NULL;

    if((entry = malloc(sizeof(HashEntry))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    if((entry->key = malloc(strlen(key) + 1)) == NULL) {
        perror("malloc failed");
        free(entry);
        return NULL;
    }
    strcpy(entry->key, key);
    // entry->key = key;

    if((entry->tree = AVLTree_Init(entry->tree)) == NULL) {
        free(entry->key);
        free(entry);
        return NULL;
    }

    entry->next = NULL;

    return entry;
}

HashTablePtr HashTable_Init(const int size, const size_t bucketSize)
{
    HashTablePtr ht = NULL;

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
        ht->table[i].entry = NULL;
        ht->table[i].next = NULL;
    }

    return ht;
}

void HashTable_Close(HashTablePtr ht)
{
    HashNodePtr tmpHashNode = NULL;

    for(int i=0; i < ht->size; i++) {
        while(ht->table[i].next != NULL) {
            tmpHashNode = ht->table[i].next;
            ht->table[i].next = tmpHashNode->next;
            HashNode_Close(tmpHashNode);
            free(tmpHashNode);
        }
        HashNode_Close(&(ht->table[i]));
    }

    free(ht->table);
    free(ht);
}

void HashNode_Close(HashNodePtr node)
{
    HashEntryPtr tmpHashEntry = NULL;

    while(node->entry != NULL) {
        tmpHashEntry = node->entry;
        node->entry = node->entry->next;
        free(tmpHashEntry->key);
        AVLTree_Close(tmpHashEntry->tree);
        free(tmpHashEntry);
    }
}

AVLTreePtr HashTable_LocateKey(HashNodePtr node, const char *key)
{
    HashNodePtr tmpHashNode = node;
    HashEntryPtr tmpHashEntry = NULL;

    while (tmpHashNode != NULL)
    {
        tmpHashEntry = tmpHashNode->entry;
        while (tmpHashEntry != NULL)
        {
            if (!strcmp(tmpHashEntry->key, key)) {
                return tmpHashEntry->tree;
            }
            tmpHashEntry = tmpHashEntry->next;
        }
        tmpHashNode = tmpHashNode->next;
    }

    return NULL;
}

AVLTreePtr HashNode_Insert(HashNodePtr node, const char *key, const int entriesPerBucket)
{
    int count = 0;
    HashNodePtr tmpHashNode = node;
    HashEntryPtr tmpHashEntry = NULL;

    while (tmpHashNode->next != NULL) {
        tmpHashNode = tmpHashNode->next;
    }

    tmpHashEntry = tmpHashNode->entry;
    while (tmpHashEntry != NULL) {
        if (++count == entriesPerBucket) {
            break;
        }
        tmpHashEntry = tmpHashEntry->next;
    }

    if (count == entriesPerBucket) {
        if ((tmpHashNode->next = malloc(sizeof(HashNode))) == NULL) {
            return NULL;
        }
        tmpHashNode = tmpHashNode->next;
        tmpHashNode->next = NULL;
        tmpHashNode->entry = NULL;
    }

    tmpHashEntry = tmpHashNode->entry;
    if ((tmpHashNode->entry = HashEntry_Init(key)) == NULL) {
        return NULL;
    }

    tmpHashNode->entry->next = tmpHashEntry;

    return tmpHashNode->entry->tree;
}

int HashTable_Insert(HashTablePtr ht, const char* key, const PatientPtr patient)
{
    int index = hash(key) % ht->size;
    AVLTreePtr tree = NULL;

    if ((tree = HashTable_LocateKey(&(ht->table[index]), key)) == NULL)
    {
        if ((tree = HashNode_Insert(&(ht->table[index]), key, ht->bucketSize / (sizeof(HashEntryPtr) + sizeof(HashNodePtr)))) == NULL)
        {
            return -1;
        }
        ht->elements++;
    }

    return AVLTree_Insert(tree, patient->entryDate, patient);
}