#include <stdio.h>
#include <stdlib.h>

#include "../include/Queue.h"

QueuePtr Queue_Init()
{
    QueuePtr q = NULL;

    if ((q = malloc(sizeof(Queue))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    q->size = 0;
    q->head = q->tail = NULL;

    return q;
}

void Queue_Close(QueuePtr q)
{
    QueueNodePtr node = NULL;

    while (q->head != NULL)
    {
        node = q->head->next;
        free(q->head);
        q->head = node;
    }

    free(q);
}

int Queue_Insert(QueuePtr q, struct maxHeapNode *item)
{
    QueueNodePtr node = NULL;

    if ((node = malloc(sizeof(QueueNode))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    node->item = item;
    node->next = NULL;

    if (q->size) {
        q->tail->next = node;
        q->tail = node;
    }
    else {
        q->head = q->tail = node;
    }

    q->size++;

    return 0;
}
struct maxHeapNode *Queue_Pop(QueuePtr q)
{
    struct maxHeapNode *item;
    QueueNodePtr node = q->head;

    q->head = node->next;

    item = node->item;
    q->size--;

    free(node);

    return item;
}