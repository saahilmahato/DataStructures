#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

Queue *createQueue(void) {
    Queue *q = malloc(sizeof(*q));
    if (!q)
        return NULL;

    q->array = malloc(INITIAL_CAPACITY * sizeof(int));
    if (!q->array) {
        free(q);
        return NULL;
    }

    q->capacity = INITIAL_CAPACITY;
    q->front = q->rear = q->size = 0;

    return q;
}

bool resize(Queue *q) {
    if (!q || q->capacity > SIZE_MAX / GROWTH_FACTOR) {
        return false;
    }

    const size_t newCapacity = q->capacity * GROWTH_FACTOR;
    int *newArray = malloc(newCapacity * sizeof(int));
    if (!newArray)
        return false;

    for (int i = 0; i < q->size; ++i)
        newArray[i] = q->array[(q->front + i) % q->capacity];

    free(q->array);
    q->array = newArray;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = q->size;

    return true;
}

bool enqueue(Queue *q, const int value) {
    if (!q)
        return false;

    if (isFull(q) && !resize(q))
        return false;

    q->array[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;

    return true;
}

bool dequeue(Queue *q, int *out_value) {
    if (!q || isEmpty(q))
        return false;

    if (out_value)
        *out_value = q->array[q->front];

    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return true;
}

bool front(const Queue *q, int *out_value) {
    if (!q || isEmpty(q))
        return false;

    if (out_value)
        *out_value = q->array[q->front];

    return true;
}

bool isEmpty(const Queue *q) { return !q || q->size == 0; }

bool isFull(const Queue *q) { return q && q->size == q->capacity; }

size_t size(const Queue *q) { return q ? q->size : 0; }

void destroy(Queue **q) {
    if (q && *q) {
        free((*q)->array);
        free(*q);
        *q = NULL;
    }
}
