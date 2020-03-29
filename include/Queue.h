#ifndef QUEUE_H
#define QUEUE_H

typedef struct maxHeapNode maxHeapNode;
typedef maxHeapNode* maxHeapNodePtr;

typedef struct QueueNode
{
    maxHeapNodePtr item;
    struct QueueNode *next;
} QueueNode;

typedef QueueNode* QueueNodePtr;

typedef struct Queue
{
    int size;
    QueueNodePtr head;
    QueueNodePtr tail;
} Queue;

typedef Queue* QueuePtr;

QueuePtr Queue_Init();

void Queue_Close(QueuePtr q);

int Queue_Insert(QueuePtr q, maxHeapNodePtr item);

maxHeapNodePtr Queue_Pop(QueuePtr q);

maxHeapNodePtr Queue_getFront(QueuePtr q);

#endif