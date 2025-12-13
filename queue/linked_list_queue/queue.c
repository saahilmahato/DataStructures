#include <stdlib.h>

#include "queue.h"

Queue *createQueue(void) {
    Queue *q = malloc(sizeof(*q));
    if (!q)
        return NULL;

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}

bool enqueue(Queue *q, const int value) {
    if (!q)
        return false;

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->size++;

    return true;
}

bool dequeue(Queue *q, int *out_value) {
    if (!q || !q->front)
        return false;

    if (out_value)
        *out_value = q->front->data;

    ListNode *toDelete = q->front;
    q->front = toDelete->next;
    free(toDelete);

    if (!q->front)
        q->rear = NULL;

    q->size--;

    return true;
}

bool front(const Queue *q, int *out_value) {
    if (!q || !q->front)
        return false;

    if (out_value)
        *out_value = q->front->data;

    return true;
}

bool isEmpty(const Queue *q) { return !q || q->size == 0; }

size_t size(const Queue *q) { return q ? q->size : 0; }

void destroy(Queue **q) {
    if (q && *q) {
        while ((*q)->front) {
            ListNode *toDelete = (*q)->front;
            (*q)->front = (*q)->front->next;
            free(toDelete);
        }

        free(*q);
        *q = NULL;
    }
}
