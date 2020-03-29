#ifndef MAXHEAP_H
#define MAXHEAP_H

struct maxHeapNode {
    char* key;
    int count;
    struct maxHeapNode *left;
    struct maxHeapNode *right;
};

typedef struct maxHeap {
    int len;
    maxHeapNodePtr root;
} maxHeap;

typedef maxHeap* maxHeapPtr;

maxHeapNodePtr maxHeapNode_Init(const char* str, int count);

maxHeapPtr maxHeap_Init();

void maxHeap_Close();

void maxHeapNode_Close();

int CBTInsert(maxHeapPtr heap, maxHeapNodePtr newNode);

int maxHeap_Insert(maxHeapPtr heap, const char* key, const int count);

#endif