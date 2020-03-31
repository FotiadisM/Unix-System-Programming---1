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

maxHeapNodePtr CBTGetLast(maxHeapPtr heap)
{
    QueuePtr queue = NULL;
    maxHeapNodePtr node = NULL, tmp = NULL;

    if ((queue = Queue_Init()) == NULL) {
        return NULL;
    }

    if (Queue_Insert(queue, heap->root) == -1) {
        Queue_Close(queue);
        return NULL;
    }

    while (queue->size != 0)
    {
        node = Queue_Pop(queue);
        if (node->left != NULL) {
            if (Queue_Insert(queue, node->left) == -1) {
                Queue_Close(queue);
                return NULL;
            }
        }
        if (node->right != NULL) {
            if (Queue_Insert(queue, node->right) == -1) {
                Queue_Close(queue);
                return NULL;
            }
        }
    }

    // spaghetti_start
    if (Queue_Insert(queue, heap->root) == -1) {
        Queue_Close(queue);
        return NULL;
    }

    while (queue->size != 0)
    {
        tmp = Queue_Pop(queue);

        if (tmp->left != NULL)
        {
            if (!strcmp(tmp->left->key, node->key)) {
                tmp->left = NULL;
                break;
            }
            if (Queue_Insert(queue, tmp->left) == -1) {
                Queue_Close(queue);
                return NULL;
            }
        }
        if (tmp->right != NULL)
        {
            if (!strcmp(tmp->right->key, node->key)) {
                tmp->right = NULL;
                break;
            }
            if (Queue_Insert(queue, tmp->right) == -1) {
                Queue_Close(queue);
                return NULL;
            }
        }

    }
    // spaghetti_end

    Queue_Close(queue);

    return node;
}

int maxHeapNode_Swap(maxHeapNodePtr node1,maxHeapNodePtr node2)
{
    char *str = node1->key;
    int count = node1->count;

    node1->key = node2->key;
    node2->key = str;

    node1->count = node2->count;
    node2->count = count;

    return 0;
}

void maxHeap_Rebalance(maxHeapNodePtr node)
{
    if (node->left != NULL)
    {
        maxHeap_Rebalance(node->left);
        if (node->left->count > node->count) {
            if (maxHeapNode_Swap(node, node->left) == -1) {
                printf("maxHeap_Rebalance() failed\n");
            }
        }
    }

    if (node->right != NULL)
    {
        maxHeap_Rebalance(node->right);
        if (node->right->count > node->count) {
            if (maxHeapNode_Swap(node, node->right) == -1) {
                printf("maxHeap_Rebalance() failed\n");
            }
        }
    }
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

    maxHeap_Rebalance(heap->root);

    heap->len++;

    return 0;
}

int maxHeapNode_Remove(maxHeapPtr heap)
{
    maxHeapNodePtr node = NULL;

    if ((node = CBTGetLast(heap)) == NULL) {
        printf("CBGGetLast() Error\n");
        return -1;
    }

    maxHeapNode_Swap(heap->root, node);

    printf("%s %d\n", node->key, node->count);
    free(node->key);
    free(node);

    maxHeap_Rebalance(heap->root);

    return 0;
}