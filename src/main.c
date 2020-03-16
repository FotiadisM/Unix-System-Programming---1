#include <stdlib.h>
#include <string.h>

#include "../include/AVL.h"
#include "../include/List.h"
#include "../include/HashTable.h"
#include "../include/diseaseMonitor.h"

int main(int argc, char *argv[])
{
    char* fileName = NULL, *line = NULL;
    size_t bucketSize = 0, len = 0;
    int diseaseHTEntries = 0, countryHTEntries = 0;
    ListPtr list = NULL;
    HashTablePtr diseaseHT = NULL, countryHT = NULL;

    if(argc < 9) {
        printf("Wrong Usage");
        return -1;
    }

    for(int i=1; i < argc; i++) {
        if(!strcmp(argv[i], "-p")) {
            i++;    // malloc(sizeof(argv[++i])) doesn't seem to work
            if ((fileName = malloc(strlen(argv[i]) + 1)) == NULL) {
                perror("malloc failed");
                return -1;
            }
            strcpy(fileName, argv[i]);
        }
        else if (!strcmp(argv[i], "-h1")) {
            if ((diseaseHTEntries = atoi(argv[++i])) == 0) {
                printf("Wrong Input: \"-h1 %s\"\n", argv[i]);
                return -1;
            }

        }
        else if (!strcmp(argv[i], "-h2")) {
            if ((countryHTEntries = atoi(argv[++i])) == 0) {
                printf("Wrong Input \"-h2 %s\"\n", argv[i]);
                return -1;
            }
        }
        else if (!strcmp(argv[i], "-b")) {
            if (sscanf(argv[++i], "%zu", &bucketSize) == EOF) {
                perror("sscanf failed");
                return -1;
            }
            if(bucketSize < 16) {
                printf("BucketSize: %zu is too small. Minimum 16 bytes\n", bucketSize);
                if(fileName != NULL) free(fileName);
                return -1;
            }
        }
        else {
            printf("Unknown command \"%s\"\n", argv[i]);
            return -1;
        }
    }

    if ((list = List_Init()) == NULL) {
        return -1;
    }

    if ((diseaseHT = HashTable_Init(diseaseHTEntries, bucketSize)) == NULL) {
        return -1;
    }
    if ((countryHT = HashTable_Init(countryHTEntries, bucketSize)) == NULL) {
        return -1;
    }

    if (DM_Init(fileName, list, diseaseHT, countryHT) == -1)
    {
        printf("DM_Init() failed, program will now exit\n");

        free(fileName);
        HashTable_Close(diseaseHT);
        HashTable_Close(countryHT);
        List_Close(list, F_PATIENT);

        return -1;
    }

    while (getline(&line, &len, stdin) != -1)
    {
        if (!strcmp(line, "/exit\n")) {
            break;
        }
        if(DM_Run(line, list, diseaseHT, countryHT) == -1)
        {
            printf("DM_Run() failed, program will now exit\n");

            free(line);
            free(fileName);
            HashTable_Close(diseaseHT);
            HashTable_Close(countryHT);
            List_Close(list, F_PATIENT);

            return -1;
        }
    }

    HashTable_Close(diseaseHT);
    HashTable_Close(countryHT);
    List_Close(list, F_PATIENT);

    free(line);
    free(fileName);

    return 0;
}