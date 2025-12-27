#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>

typedef struct HeapNode {
    int data;
    struct HeapNode *left;
    struct HeapNode *right;
} HeapNode;

bool insert(HeapNode **root, int data);
bool extract_min(HeapNode **root, int *out_value);
bool peek_min(const HeapNode *root, int *out_value);

#endif