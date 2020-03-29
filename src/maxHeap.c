#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Queue.h"
#include "../include/maxHeap.h"

maxHeapNodePtr maxHeapNode_Init(const char* str, int count)
{
    maxHeapNodePtr node = NULL;

    if ((node = malloc(sizeof(maxHeapNode))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    if ((node->key = malloc(strlen(str) + 1)) == NULL) {
        perror("malloc failed");
        free(node);
        return NULL;
    }

    strcpy(node->key, str);
    node->count = count;
    node->left = node->right = NULL;

    return node;
}

maxHeapPtr maxHeap_Init()
{
    maxHeapPtr heap = NULL;

    if ((heap = malloc(sizeof(maxHeap))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    heap->len = 0;
    heap->root = NULL;

    return heap;
}

void maxHeap_Close(maxHeapPtr heap)
{
    maxHeapNode_Close(heap->root);

    free(heap);
}

void maxHeapNode_Close(maxHeapNodePtr node)
{
    if (node == NULL) {
        return;
    }

    maxHeapNode_Close(node->left);
    maxHeapNode_Close(node->right);

    free(node->key);
    free(node);
}

int CBTInsert(maxHeapPtr heap, maxHeapNodePtr newNode)
{
    QueuePtr queue = NULL;
    maxHeapNodePtr node = heap->root;

    if ((queue = Queue_Init()) == NULL) {
        return -1;
    }

    if (node == NULL) {
        heap->root = newNode;
        Queue_Close(queue);
        return 0;
    }

    while (node->left != NULL && node->right != NULL)
    {
        Queue_Insert(queue, node->left);
        Queue_Insert(queue, node->right);
        node = Queue_Pop(queue);
    }

    if (node->left == NULL) {
        node->left = newNode;
    }
    else if (node->right == NULL) {
        node->right = newNode;
    }

    Queue_Close(queue);

    return 0;
}

int maxHeap_Insert(maxHeapPtr heap, const char* key, const int count)
{
    maxHeapNodePtr newNode = NULL;

    if ((newNode = maxHeapNode_Init(key, count)) == NULL) {
        return -1;
    }

    if (CBTInsert(heap, newNode) == -1) {
        return -1;
    }

    return 0;
}