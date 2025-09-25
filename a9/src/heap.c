/**
 * -------------------------------------
 * @project a9
 * @file heap.c
 * @author Sameer Abdullah
 * @version 2025-03-20
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
	int r = 0;
	if (a < b)
		r = -1;
	else if (a > b)
		r = 1;
	return r;
}

HEAP* new_heap(int capacity) {
	HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
	if (hp == NULL)
		return NULL;
	hp->hda = (HEAPDATA*) malloc(sizeof(HEAPDATA) * capacity);
	if (hp->hda == NULL) {
		free(hp);
		return NULL;
	};
	hp->capacity = capacity;
	hp->size = 0;
	return hp;
}

int heapify_up(HEAPDATA *hda, int index) {
	int parent = (index - 1) / 2;
	while (index > 0 && cmp(hda[index].key, hda[parent].key) < 0) {
		HEAPDATA temp = hda[index];
		hda[index] = hda[parent];
		hda[parent] = temp;
		index = parent;
		parent = (index - 1) / 2;
	}
	return index;
}

int heapify_down(HEAPDATA *hda, int n, int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int smallest = index;

	if (left < n && cmp(hda[left].key, hda[smallest].key) < 0)
		smallest = left;
	if (right < n && cmp(hda[right].key, hda[smallest].key) < 0)
		smallest = right;

	if (smallest != index) {
		HEAPDATA temp = hda[index];
		hda[index] = hda[smallest];
		hda[smallest] = temp;
		return heapify_down(hda, n, smallest);
	}
	return index;
}

void heap_insert(HEAP *heap, HEAPDATA new_node) {
	if (heap->size >= heap->capacity) {
		int new_capacity = heap->capacity * 2;
		HEAPDATA *new_hda = realloc(heap->hda, sizeof(HEAPDATA) * new_capacity);
		if (new_hda == NULL)
			return;
		heap->hda = new_hda;
		heap->capacity = new_capacity;
	}

	heap->hda[heap->size] = new_node;
	heapify_up(heap->hda, heap->size);
	heap->size++;
}

HEAPDATA heap_find_min(HEAP *heap) {
	if (heap->size > 0)
		return heap->hda[0];
	HEAPDATA dummy = { 0, 0 };
	return dummy;
}

HEAPDATA heap_extract_min(HEAP *heap) {
	HEAPDATA min = { 0, 0 };
	if (heap->size == 0)
		return min;
	min = heap->hda[0];
	heap->size--;
	heap->hda[0] = heap->hda[heap->size];
	heapify_down(heap->hda, heap->size, 0);
	return min;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
	if (index < 0 || index >= heap->size)
		return 0;
	KEYTYPE old_key = heap->hda[index].key;
	heap->hda[index].key = new_key;
	if (new_key < old_key)
		heapify_up(heap->hda, index);
	else
		heapify_down(heap->hda, heap->size, index);
	return 1;
}

int heap_search_value(HEAP *heap, VALUETYPE data) {
	for (int i = 0; i < heap->size; i++) {
		if (heap->hda[i].value == data)
			return i;
	}
	return -1;
}

void heap_sort(HEAPDATA *arr, int n) {
	HEAP *heap = new_heap(n);
	for (int i = 0; i < n; i++) {
		heap_insert(heap, arr[i]);
	}
	for (int i = 0; i < n; i++) {
		arr[i] = heap_extract_min(heap);
	}
	heap_clean(&heap);

	for (int i = 0; i < n / 2; i++) {
		HEAPDATA temp = arr[i];
		arr[i] = arr[n - 1 - i];
		arr[n - 1 - i] = temp;
	}
}

void heap_clean(HEAP **heapp) {
	if (heapp) {
		HEAP *heap = *heapp;
		if (heap->capacity > 0) {
			heap->capacity = 0;
			heap->size = 0;
			free(heap->hda);
			free(heap);
		}
		*heapp = NULL;
	}
}
