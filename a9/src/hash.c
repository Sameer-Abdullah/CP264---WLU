/**
 * -------------------------------------
 * @project a9
 * @file hash.c
 * @author Sameer Abdullah
 * @version 2025-03-20
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HNODE* hashtable_search(HASHTABLE *ht, char *name) {
	int index = hash(name, ht->size);
	HNODE *current = ht->hna[index];
	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

int hashtable_insert(HASHTABLE *ht, DATA data) {
	HNODE *existing = hashtable_search(ht, data.name);
	if (existing != NULL) {
		existing->data.value = data.value;
		return 1;
	}

	int index = hash(data.name, ht->size);
	HNODE *new_node = (HNODE*) malloc(sizeof(HNODE));
	if (new_node == NULL)
		return 0;

	new_node->data = data;
	new_node->next = NULL;

	if (ht->hna[index] == NULL) {
		ht->hna[index] = new_node;
	} else {
		HNODE *current = ht->hna[index];
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
	}

	ht->count++;
	return 1;
}

int hashtable_delete(HASHTABLE *ht, char *name) {
	int index = hash(name, ht->size);
	HNODE *current = ht->hna[index];
	HNODE *prev = NULL;

	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) {
			if (prev == NULL) {
				ht->hna[index] = current->next;
			} else {
				prev->next = current->next;
			}
			free(current);
			ht->count--;
			return 1;
		}
		prev = current;
		current = current->next;
	}
	return 0;
}

int hash(char *key, int size) {
	unsigned int hash = 0;
	while (*key) {
		hash += *key++;
	}
	return hash % size;
}

HASHTABLE* new_hashtable(int size) {
	HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
	ht->hna = (HNODE**) malloc(sizeof(HNODE**) * size);
	int i;
	for (i = 0; i < size; i++)
		*(ht->hna + i) = NULL;

	ht->size = size;
	ht->count = 0;
	return ht;
}

void hashtable_clean(HASHTABLE **htp) {
	if (*htp == NULL)
		return;
	HASHTABLE *ht = *htp;
	HNODE *p, *temp;
	int i;
	for (i = 0; i < ht->size; i++) {
		p = ht->hna[i];
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		ht->hna[i] = NULL;
	}
	free(ht->hna);
	ht->hna = NULL;
	*htp = NULL;
}
