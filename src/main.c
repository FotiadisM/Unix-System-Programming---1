#include <stdlib.h>
#include <string.h>

#include "../include/HashTable.h"
#include "../include/diseaseMonitor.h"

int main(int argc, char *argv[])
{
    char* fileName = NULL;
    size_t bucketSize = 0;
    int diseaseHTEntries = 0, countryHTEntries = 0;
    HashTablePtr diseaseHT = NULL, countryHT = NULL;

    if(argc < 9) {
        printf("Wrong Usage");
        return -1;
    }

    for(int i=1; i < argc; i++) {
        if(!strcmp(argv[i], "-p")) {
            i++;    // malloc(sizeof(argv[++i])) doesn't seem to work
            if((fileName = malloc(strlen(argv[i]) + 1)) == NULL) {
                perror("malloc failed");
                return -1;
            }
            strcpy(fileName, argv[i]);
        }
        else if(!strcmp(argv[i], "-h1")) {
            if((diseaseHTEntries = atoi(argv[++i])) == 0) {
                printf("Wrong Input: \"-h1 %s\"\n", argv[i]);
                return -1;
            }

        }
        else if(!strcmp(argv[i], "-h2")) {
            if((countryHTEntries = atoi(argv[++i])) == 0) {
                printf("Wrong Input \"-h2 %s\"\n", argv[i]);
                return -1;
            }
        }
        else if(!strcmp(argv[i], "-b")) {
            if(sscanf(argv[++i], "%zu", &bucketSize) == EOF) {
                perror("sscanf failed");
                return -1;
            }
        }
        else {
            printf("Unknown command \"%s\"\n", argv[i]);
            return -1;
        }
    }

    if((diseaseHT = HashTable_Init(diseaseHT, diseaseHTEntries, bucketSize)) == NULL) {
        return -1;
    }
    if((countryHT = HashTable_Init(countryHT, countryHTEntries, bucketSize)) == NULL) {
        return -1;
    }

    if(DM_Init(fileName, diseaseHT, countryHT) == -1) {
        printf("DM_Init failed\n");
        return -1;
    }

    HashTable_Close(diseaseHT);
    HashTable_Close(countryHT);


    free(fileName);

    return 0;
}