#include <stdlib.h>
#include <string.h>

#include "../include/Queue.h"
#include "../include/fnclib.h"

void globalDiseaseStats(const HashTablePtr ht, const DatePtr d1, const DatePtr d2)
{
    HashNodePtr nodePtr = NULL;

    for (int i=0; i < ht->size; i++) {
        nodePtr = &(ht->table[i]);
        while (nodePtr != NULL) {
            for (int j=0; j < ht->bucketSize; j++) {
                if (nodePtr->entries[j] != NULL) {
                    if (d1 == NULL || d2 == NULL) {
                        printf("%s %d\n", nodePtr->entries[j]->key, nodePtr->entries[j]->tree->elements);
                    }
                    else {
                        printf("%s %d\n", nodePtr->entries[j]->key, AVLNode_countPatients(nodePtr->entries[j]->tree->root, nodePtr->entries[j]->key, NULL, d1, d2));
                    }
                }
            }
            nodePtr = nodePtr->next;
        }
    }
}

void diseaseFrequency(const HashTablePtr ht, const char* disease, const char* country, const DatePtr d1, const DatePtr d2)
{
    AVLTreePtr tree = NULL;

    if ((tree = HashTable_LocateKey(&(ht->table[hash(disease) % ht->size]), disease, ht->bucketSize)) == NULL) {
        printf("Disease not found\n");
        return;
    }
    printf("%s %d\n", disease, AVLNode_countPatients(tree->root, disease, country, d1, d2));

}

void topk_Diseases(const HashTablePtr h1, const HashTablePtr h2, const char* country, const int k, DatePtr d1, DatePtr d2)
{
    maxHeapPtr heap = NULL;

    if ((heap = topk_InitHeap(h2, h1, country, d1, d2, _Disease)) == NULL) {
        printf("Error\n");
        return;
    }

    for(int i=0; i < k; i++) {
        if (maxHeapNode_Remove(heap) == -1) {
            maxHeap_Close(heap);
            return;
        }
    }

    maxHeap_Close(heap);
}

void topk_Countries(const HashTablePtr h1, const HashTablePtr h2, const char *disease, const int k, DatePtr d1, DatePtr d2)
{
    maxHeapPtr heap = NULL;

    if ((heap = topk_InitHeap(h1, h2, disease, d1, d2, t_Countries)) == NULL) {
        printf("Error\n");
        return;
    }

    for(int i=0; i < k; i++) {
        if (maxHeapNode_Remove(heap) == -1) {
            maxHeap_Close(heap);
            return;
        }
    }

    maxHeap_Close(heap);
}

int recordPatientExit(ListPtr list, char* id, char* d2)
{
    ListNodePtr ptr = list->head;

    while (ptr != NULL) {
        if (!strcmp(ptr->patient->id, id)) {

            if (ptr->patient->exitDate != NULL) {
                printf("Record already has an exit date\n");
                return -1;
            }

            if ((ptr->patient->exitDate = Date_Init(d2)) == NULL) {
                perror("malloc failed");
                return -1;
            }

            if (Date_Compare(ptr->patient->entryDate, ptr->patient->exitDate) == 1) {
                printf("Invalid exit date\n");
                free(ptr->patient->exitDate);
            }
            break;
        }
        ptr = ptr->next;
    }

    printf("Record updated\n");

    return 0;
}

void numCurrentPatients(HashTablePtr ht, char* disease)
{
    HashNodePtr nodePtr = NULL;

    if (disease == NULL) {
        for (int i=0; i < ht->size; i++) {
            nodePtr = &(ht->table[i]);
            while (nodePtr != NULL) {
                for (int j=0; j < ht->bucketSize; j++) {
                    if (nodePtr->entries[j] != NULL) {
                        printf("%s %d\n", nodePtr->entries[j]->key, AVLNode_countNullPatients(nodePtr->entries[j]->tree->root, nodePtr->entries[j]->key));
                    }
                }
                nodePtr = nodePtr->next;
            }
        }
    }
    else {
        nodePtr = &(ht->table[hash(disease) % ht->size]);
        while (nodePtr != NULL) {
            for (int j=0; j < ht->bucketSize; j++) {
                if (nodePtr->entries[j] != NULL) {
                    if (!strcmp(nodePtr->entries[j]->key, disease)) {
                        printf("%s %d\n", disease, AVLNode_countNullPatients(nodePtr->entries[j]->tree->root, disease));
                        break;
                    }
                }
            }
            nodePtr = nodePtr->next;
        }
    }
}

int insertPatientRecord(ListPtr list, HashTablePtr h1, HashTablePtr h2, char* reccordID, char* fName, char* lName, char* disease, char* country, char* d1, char* d2)
{
    ListNodePtr node = NULL;
    PatientPtr patient = NULL;

    if((patient = malloc(sizeof(Patient))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if((patient->id = malloc(strlen(reccordID) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->id, reccordID);

    if((patient->fName = malloc(strlen(fName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->fName, fName);

    if((patient->lName = malloc(strlen(lName) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->lName, lName);

    if((patient->diseaseID = malloc(strlen(disease) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->diseaseID, disease);

    if((patient->country = malloc(strlen(country) + 1)) == NULL) {
        perror("malloc failed");
        return -1;
    }
    strcpy(patient->country, country);

    if((patient->entryDate = Date_Init(d1)) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if(d2 == NULL) {
        patient->exitDate = NULL;
    }
    else {
        if((patient->exitDate = Date_Init(d2)) == NULL) {
            return -1;
        }
    }

    if (( node = List_InsertSorted(list, patient)) == NULL) {
        return -1;
    }
    if (HashTable_Insert(h1, patient->diseaseID, node) == -1) {
        return -1;
    }
    if (HashTable_Insert(h2, patient->country, node) == -1) {
        return -1;
    }

    printf("Record added\n");

    return 0;
}

maxHeapPtr topk_InitHeap(const HashTablePtr h1, const HashTablePtr h2, const char* key, DatePtr d1, DatePtr d2, const int flag)
{
    char str[11];   // BARIEMAI NA KANW MALLOC
    maxHeapPtr heap = NULL;
    AVLTreePtr tree = NULL;
    HashNodePtr nodePtr = &(h1->table[hash(key) % h1->size]);

    if ((heap = maxHeap_Init()) == NULL) {
        return NULL;
    }

    if (d1 == NULL || d2 == NULL) {
        strcpy(str, "0-0-0");       // NEEDED FOR AVLNode_countPatients()
        if ((d1 = Date_Init(str)) == NULL) {
            free(heap);
            return NULL;
        }
        strcpy(str, "0-0-9999");
        if ((d2 = Date_Init(str)) == NULL) {
            free(heap);
            return NULL;
        }
    }

    if((tree = HashTable_LocateKey(nodePtr, key, h1->bucketSize)) == NULL) {
        printf("Disease not found\n");
        free(d1); free(d2);
        free(heap);
        return NULL;
    }

    for (int i=0; i < h2->size; i++) {
        nodePtr = &(h2->table[i]);
        while (nodePtr != NULL) {
            for (int j=0; j < h2->bucketSize; j++) {
                if (nodePtr->entries[j] != NULL)
                {
                    if (flag == _Disease) {
                        if (maxHeap_Insert(heap, nodePtr->entries[j]->key, AVLNode_countPatients(tree->root, nodePtr->entries[j]->key, key, d1, d2)) == -1) {
                            printf("maxHeap_Insert() failed\n");
                            maxHeap_Close(heap);
                            return NULL;
                        }
                    }
                    else {
                        if (maxHeap_Insert(heap, nodePtr->entries[j]->key, AVLNode_countPatients(tree->root, key, nodePtr->entries[j]->key, d1, d2)) == -1) {
                            printf("maxHeap_Insert() failed\n");
                            maxHeap_Close(heap);
                            return NULL;
                        }
                    }
                }
            }
            nodePtr = nodePtr->next;
        }
    }

    free(d1);
    free(d2);

    return heap;
}