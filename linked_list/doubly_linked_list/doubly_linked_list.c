#include <stdlib.h>

#include "doubly_linked_list.h"

size_t get_length(const ListNode *head) {
    size_t length = 0;

    while (head) {
        length++;
        head = head->next;
    }

    return length;
}

bool insert_first(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = *head;
    newNode->prev = nullptr;

    if (*head)
        (*head)->prev = newNode;

    *head = newNode;

    return true;
}

bool insert_last(ListNode **head, const int data) {
    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = nullptr;

    if (!*head) {
        newNode->prev = nullptr;
        *head = newNode;
        return true;
    }

    ListNode *current = *head;
    while (current->next)
        current = current->next;

    current->next = newNode;
    newNode->prev = current;

    return true;
}

bool insert_at_position(ListNode **head, const int data, const size_t position) {
    if (position == 0)
        return insert_first(head, data);

    if (!*head)
        return false;

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        if (!current->next)
            return false;

        current = current->next;
    }

    ListNode *newNode = malloc(sizeof(*newNode));
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->prev = current;
    newNode->next = current->next;
    current->next = newNode;

    if (newNode->next)
        newNode->next->prev = newNode;

    return true;
}

bool delete_first(ListNode **head) {
    if (!*head)
        return false;

    ListNode *toDelete = *head;
    *head = (*head)->next;

    if (*head)
        (*head)->prev = nullptr;

    free(toDelete);

    return true;
}

bool delete_last(ListNode **head) {
    if (!*head)
        return false;

    if (!(*head)->next) {
        free(*head);
        *head = nullptr;
        return true;
    }

    ListNode *current = *head;
    while (current->next->next)
        current = current->next;

    free(current->next);
    current->next = nullptr;

    return true;
}

bool delete_from_position(ListNode **head, const size_t position) {
    if (!*head)
        return false;

    if (position == 0)
        return delete_first(head);

    ListNode *current = *head;
    for (size_t i = 0; i < position - 1; ++i) {
        if (!current->next)
            return false;

        current = current->next;
    }

    if (!current->next)
        return false;

    ListNode *toDelete = current->next;
    current->next = toDelete->next;

    if (toDelete->next)
        toDelete->next->prev = current;

    free(toDelete);

    return true;
}

void delete_list(ListNode **head) {
    while (*head) {
        ListNode *toDelete = *head;
        *head = (*head)->next;
        free(toDelete);
    }

    *head = nullptr;
}
