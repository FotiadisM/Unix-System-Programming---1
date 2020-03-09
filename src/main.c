#include <stdlib.h>
#include <string.h>

#include "../include/diseaseMonitor.h"

int main(int argc, char *argv[])
{
    size_t bucketSize = 0;
    int diseaseHTEntries = 0, countryHTEntries = 0;
    char* fileName = NULL;

    if(argc < 9) {
        printf("Wrong Usage");
        return -1;
    }

    for(int i=1; i < argc; i++) {
        if(!strcmp(argv[i], "-p")) {
            i++;    // malloc(sizeof(argv[++i])) doesn't seem to work
            if((fileName = malloc(sizeof(argv[i]))) == NULL) {
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

    if(DM_Init(fileName, diseaseHTEntries, countryHTEntries, bucketSize) == -1) {
        printf("DM_Init failed\n");
        return -1;
    }

    free(fileName);

    return 0;
}