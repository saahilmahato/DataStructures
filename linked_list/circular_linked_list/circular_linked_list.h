#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdbool.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

size_t get_length(const ListNode *head);

bool insert_first(ListNode **head, int data);

bool insert_last(ListNode **head, int data);

bool insert_at_position(ListNode **head, int data, size_t position);

bool delete_first(ListNode **head);

bool delete_last(ListNode **head);

bool delete_from_position(ListNode **head, size_t position);

void delete_list(ListNode **head);

#endif
