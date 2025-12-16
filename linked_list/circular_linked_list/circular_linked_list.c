#include <stdlib.h>

#include "circular_linked_list.h"

size_t get_length(const ListNode *head) {
    size_t length = 0;

    if (!head)
        return length;

    const ListNode *current = head;
    do {
        length++;
        current = current->next;
    } while (current != head);

    return length;
}

bool insert_first(ListNode **head, const int data) {
    ListNode *new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return false;

    new_node->data = data;

    if (!*head) {
        *head = new_node;
        new_node->next = new_node;
        return true;
    }

    ListNode *current = *head;
    while (current->next != *head)
        current = current->next;

    new_node->next = *head;
    current->next = new_node;
    *head = new_node;

    return true;
}

bool insert_last(ListNode **head, const int data) {
    ListNode *new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return false;

    new_node->data = data;

    if (!*head) {
        *head = new_node;
        new_node->next = new_node;
        return true;
    }

    ListNode *current = *head;
    while (current->next != *head)
        current = current->next;

    new_node->next = *head;
    current->next = new_node;

    return true;
}

bool insert_at_position(ListNode **head, const int data, const size_t position) {
    if (position == 0)
        return insert_first(head, data);

    if (!*head)
        return false;

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        current = current->next;
        if (current == *head)
            return false;
    }

    ListNode *new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return false;

    new_node->data = data;
    new_node->next = current->next;
    current->next = new_node;

    return true;
}

bool delete_first(ListNode **head) {
    if (!*head)
        return false;

    ListNode *to_delete = *head;

    if (to_delete->next == *head) {
        free(to_delete);
        *head = NULL;
        return true;
    }

    ListNode *current = *head;

    while (current->next != *head)
        current = current->next;

    *head = (*head)->next;
    current->next = *head;

    free(to_delete);

    return true;
}

bool delete_last(ListNode **head) {
    if (!*head)
        return false;

    ListNode *current = *head;

    if (current->next == *head) {
        free(current);
        *head = NULL;
        return true;
    }

    while (current->next->next != *head)
        current = current->next;

    free(current->next);
    current->next = *head;

    return true;
}

bool delete_from_position(ListNode **head, const size_t position) {
    if (!*head)
        return false;

    if (position == 0)
        return delete_first(head);

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        current = current->next;
        if (current == *head)
            return false;
    }

    ListNode *to_delete = current->next;
    current->next = to_delete->next;

    free(to_delete);

    return true;
}

void delete_list(ListNode **head) {
    if (!*head)
        return;

    ListNode *current = *head;
    do {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    } while (current != *head);

    *head = NULL;
}
