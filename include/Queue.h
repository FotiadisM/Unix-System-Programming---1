#ifndef QUEUE_H
#define QUEUE_H

struct maxHeapNode;

typedef struct QueueNode
{
    struct maxHeapNode *item;
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

int Queue_Insert(QueuePtr q, struct maxHeapNode *item);

struct maxHeapNode *Queue_Pop(QueuePtr q);

struct maxHeapNode *Queue_getFront(QueuePtr q);

#endif