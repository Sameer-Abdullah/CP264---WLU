/**
 * -------------------------------------
 * @project a9
 * @file main.c
 * @author Sameer Abdullah
 * @version 2025-03-20
 * -------------------------------------
 */

#include <stdio.h>
#include "heap.h"

int main() {
	HEAP *heap = new_heap(10);  // create a heap with capacity 10

	HEAPDATA items[] = { { 5, 100 }, { 3, 200 }, { 8, 300 }, { 1, 400 }, { 6,
			500 } };

	for (int i = 0; i < 5; i++) {
		heap_insert(heap, items[i]);
		printf("Inserted: key=%d, value=%d\n", items[i].key, items[i].value);
	}

	HEAPDATA min = heap_find_min(heap);
	printf("\nMin element: key=%d, value=%d\n", min.key, min.value);

	int index = heap_search_value(heap, 300);
	if (index != -1)
		printf("Value 300 found at index %d with key %d\n", index,
				heap->hda[index].key);
	else
		printf("Value 300 not found\n");

	HEAPDATA extracted = heap_extract_min(heap);
	printf("\nExtracted Min: key=%d, value=%d\n", extracted.key,
			extracted.value);

	printf("\nHeap after extracting min:\n");
	for (int i = 0; i < heap->size; i++) {
		printf("Index %d: key=%d, value=%d\n", i, heap->hda[i].key,
				heap->hda[i].value);
	}

	heap_clean(&heap);
	return 0;
}
