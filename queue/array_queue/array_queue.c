#include <stdint.h>
#include <stdlib.h>

#include "array_queue.h"

Queue *create_queue(void) {
    Queue *q = malloc(sizeof(*q));
    if (!q)
        return nullptr;

    q->array = malloc(INITIAL_CAPACITY * sizeof(int));
    if (!q->array) {
        free(q);
        return nullptr;
    }

    q->capacity = INITIAL_CAPACITY;
    q->front = q->rear = q->size = 0;

    return q;
}

bool resize_queue(Queue *q) {
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

void delete_queue(Queue **q) {
    if (q && *q) {
        free((*q)->array);
        free(*q);
        *q = nullptr;
    }
}

bool enqueue(Queue *q, const int value) {
    if (!q)
        return false;

    if (is_full(q) && !resize_queue(q))
        return false;

    q->array[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;

    return true;
}

bool dequeue(Queue *q, int *out_value) {
    if (!q || is_empty(q))
        return false;

    if (out_value)
        *out_value = q->array[q->front];

    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return true;
}

bool front(const Queue *q, int *out_value) {
    if (!q || is_empty(q))
        return false;

    if (out_value)
        *out_value = q->array[q->front];

    return true;
}

bool is_empty(const Queue *q) { return !q || q->size == 0; }

bool is_full(const Queue *q) { return q && q->size == q->capacity; }

size_t size(const Queue *q) { return q ? q->size : 0; }
