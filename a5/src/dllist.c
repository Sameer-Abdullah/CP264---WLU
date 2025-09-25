/**
 * -------------------------------------
 * @project a5
 * @file dllist.c
 * @author Sameer Abdullah
 * @version 2025-02-14
 * -------------------------------------
 */

#include "dllist.h"
#include <stdio.h>   // For printf
#include <stdlib.h>  // For malloc, free


/*
 * Create and return a new node using malloc() with passed data value.
 */
NODE *dll_node(char value) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

/*
 * Insert a given node at the beginning of a doubly linked list.
 */
void dll_insert_start(DLL *dllp, NODE *np) {
    if (dllp->start == NULL) {
        dllp->start = np;
        dllp->end = np;
    } else {
        np->next = dllp->start;
        dllp->start->prev = np;
        dllp->start = np;
    }
    dllp->length++;
}

/*
 * Insert a given node at the end of a doubly linked list.
 */
void dll_insert_end(DLL *dllp, NODE *np) {
    if (dllp->end == NULL) {
        dllp->start = np;
        dllp->end = np;
    } else {
        np->prev = dllp->end;
        dllp->end->next = np;
        dllp->end = np;
    }
    dllp->length++;
}

/*
 * Delete the first node of a doubly linked list.
 */
void dll_delete_start(DLL *dllp) {
    if (dllp->start == NULL) {
        return; // List is empty
    }

    NODE *temp = dllp->start;
    dllp->start = dllp->start->next;

    if (dllp->start != NULL) {
        dllp->start->prev = NULL;
    } else {
        dllp->end = NULL;
    }

    free(temp);
    dllp->length--;
}

/*
 * Delete the last node of a doubly linked list.
 */
void dll_delete_end(DLL *dllp) {
    if (dllp->end == NULL) {
        return; // List is empty
    }

    NODE *temp = dllp->end;
    dllp->end = dllp->end->prev;

    if (dllp->end != NULL) {
        dllp->end->next = NULL;
    } else {
        dllp->start = NULL;
    }

    free(temp);
    dllp->length--;
}

/*
 * Clean and free the nodes of a doubly linked list and reset start and length.
 */
void dll_clean(DLL *dllp) {
    NODE *current = dllp->start;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
}
