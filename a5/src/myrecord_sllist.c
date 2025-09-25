/**
 * -------------------------------------
 * @project a5
 * @file myrecord_sllist.c
 * @author Sameer Abdullah
 * @version 2025-02-14
 * -------------------------------------
 */

#include <stdio.h>  // For printf
#include <stdlib.h> // For malloc, free
#include <string.h> // For strcmp, strcpy
#include "myrecord_sllist.h"


/**
 * Search singly linked list by name key.
 */
NODE *sll_search(SLL *sllp, char *name) {
    NODE *current = sllp->start;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            return current; // Found
        }
        current = current->next;
    }
    return NULL; // Not found
}

/**
 * Insert a new record into the linked list sorted by name.
 */
void sll_insert(SLL *sllp, char *name, float score) {
    // Create new node
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(new_node->data.name, name);
    new_node->data.score = score;
    new_node->next = NULL;

    // Insert in sorted order
    if (sllp->start == NULL || strcmp(name, sllp->start->data.name) < 0) {
        new_node->next = sllp->start;
        sllp->start = new_node;
    } else {
        NODE *current = sllp->start;
        while (current->next != NULL && strcmp(current->next->data.name, name) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    sllp->length++;
}

/**
 * Delete a record by name from the linked list.
 */
int sll_delete(SLL *sllp, char *name) {
    NODE *current = sllp->start, *prev = NULL;

    while (current != NULL && strcmp(current->data.name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return 0; // Name not found
    }

    if (prev == NULL) {
        // Removing the first node
        sllp->start = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    sllp->length--;
    return 1;
}

/**
 * Clean the entire singly linked list.
 */
void sll_clean(SLL *sllp) {
    NODE *current = sllp->start;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    sllp->start = NULL;
    sllp->length = 0;
}
