#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#define INITIAL_CAPACITY 8
#define GROWTH_FACTOR 2

typedef struct Queue {
    int *array;
    size_t capacity;
    size_t front;
    size_t rear;
    size_t size;
} Queue;

Queue *create_queue(void);

bool resize_queue(Queue *q);

void delete_queue(Queue **q);

bool enqueue(Queue *q, int value);

bool dequeue(Queue *q, int *out_value);

bool front(const Queue *q, int *out_value);

bool is_empty(const Queue *q);

bool is_full(const Queue *q);

size_t size(const Queue *q);

#endif
