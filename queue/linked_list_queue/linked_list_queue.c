#include <stdlib.h>

#include "linked_list_queue.h"

Queue *create_queue(void) {
    Queue *q = malloc(sizeof(*q));
    if (!q)
        return nullptr;

    q->front = nullptr;
    q->rear = nullptr;
    q->size = 0;

    return q;
}

void delete_queue(Queue **q) {
    if (q && *q) {
        while ((*q)->front) {
            ListNode *toDelete = (*q)->front;
            (*q)->front = (*q)->front->next;
            free(toDelete);
        }

        free(*q);
        *q = nullptr;
    }
}

bool enqueue(Queue *q, const int value) {
    if (!q)
        return false;

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = value;
    newNode->next = nullptr;

    if (is_empty(q)) {
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
        q->rear = nullptr;

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

bool is_empty(const Queue *q) { return !q || q->size == 0; }

size_t size(const Queue *q) { return q ? q->size : 0; }
